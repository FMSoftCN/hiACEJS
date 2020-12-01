/*
 * Copyright (c) 2020 FMSoft.
 */

#include "hi_ace_js.h"

#include <memory>

#include <common/screen_device_proxy.h>
#include <ability.h>
#include "ability_loader.h"

#include "pthread.h"
#include "sys/prctl.h"
#include "unistd.h"

#include "ability_event_handler.h"
#include "ace_log.h"
#include "graphic_startup.h"
#include "js_ability.h"
#include "task_manager.h"
#include "ui_font_header.h"

constexpr static char FONT_PATH[] = "/storage/data/";
constexpr static int UI_TASK_HANDLER_PERIOD = 10 * 1000; // UI task sleep period is 10ms
constexpr static char UI_TASK_THREAD_NAME[] = "UIJobFunc";
constexpr static char ACE_ABILITY_NAME[] = "AceAbility";

static uint32_t g_fontPsramBaseAddr[OHOS::MIN_FONT_PSRAM_LENGTH / 4];
static OHOS::AbilityEventHandler* g_eventHandler = nullptr;

void* UIJobFunc(void* arg)
{
    prctl(PR_SET_NAME, UI_TASK_THREAD_NAME);

    auto handler = static_cast<OHOS::AbilityEventHandler*>(arg);
    if (handler == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "EventHandler is nullptr, fail to start loop");
        return nullptr;
    }

    int ret = pthread_detach(pthread_self());
    if (ret != 0) {
        HILOG_WARN(HILOG_MODULE_ACE, "UIJobFunc detach failed: %{public}d", ret);
    }

    while (true) {
        handler->PostTask([] {
            OHOS::JobManager::GetInstance()->JobHandler();
        });
        usleep(UI_TASK_HANDLER_PERIOD);
    }
    return nullptr;
}

bool HiAceJsRun(const char* bundle, const char* path, HiAceJs* hi_ace_js_out)
{
    if (hi_ace_js_out == nullptr) {
        return false;
    }

    OHOS::Ability *ability = nullptr;
    OHOS::GraphicStartUp::Init();
    OHOS::GraphicStartUp::InitFontEngine(reinterpret_cast<uintptr_t>(g_fontPsramBaseAddr), OHOS::MIN_FONT_PSRAM_LENGTH,
        const_cast<char *>(FONT_PATH), DEFAULT_VECTOR_FONT_FILENAME);

    auto screenDevice = new OHOS::ScreenDevice();
    OHOS::ScreenDeviceProxy::GetInstance()->SetDevice(screenDevice);
    ability = OHOS::AbilityLoader::GetInstance().GetAbilityByName(ACE_ABILITY_NAME);

    g_eventHandler = new OHOS::AbilityEventHandler();
    pthread_t tid;
    int ret = pthread_create(&tid, nullptr, UIJobFunc, g_eventHandler);
    if (ret != 0) {
        return false;
    }

    ability->Init(0, 0, true);

    auto js_ability = std::make_unique<OHOS::ACELite::JSAbility>();
    js_ability->Launch(const_cast<char*>(path), bundle, 0xff);
    *hi_ace_js_out = reinterpret_cast<HiAceJs>(js_ability.release());
    return true;
}

bool HiAceJsShow(HiAceJs hi_ace_js)
{
    if (hi_ace_js != nullptr) {
        auto js_ability = reinterpret_cast<OHOS::ACELite::JSAbility*>(hi_ace_js);
        js_ability->Show();
        return true;
    }
    return false;
}

bool HiAceJsHide(HiAceJs hi_ace_js)
{
    if (hi_ace_js != nullptr) {
        auto js_ability = reinterpret_cast<OHOS::ACELite::JSAbility*>(hi_ace_js);
        js_ability->Show();
        return true;
    }
    return false;
}

bool HiAceJsShutdown(HiAceJs hi_ace_js)
{
    if (hi_ace_js != nullptr) {
        auto js_ability = reinterpret_cast<OHOS::ACELite::JSAbility*>(hi_ace_js);
        js_ability->TransferToDestroy();
        delete js_ability;
    }
    return false;
}
/*
#include "ability_thread.h"

#include <ability.h>
#include <ability_kit_command.h>
#include <ability_service_interface.h>
#include <ability_state.h>
#include <climits>
#include <cstring>
#ifdef ABILITY_WINDOW_SUPPORT
#include <common/graphic_startup.h>
#include <common/task_manager.h>
#include <common/screen_device_proxy.h>
#include <font/ui_font_header.h>
#include <sys/prctl.h>
#endif
#include <dlfcn.h>
#include <kvstore_env.h>

#include "ability_env.h"
#include "ability_env_impl.h"
#include "ability_info.h"
#include "ability_loader.h"
#include "ability_service_interface.h"
#include "adapter.h"
#include "element_name_utils.h"
#include "liteipc_adapter.h"
#include "log.h"

namespace OHOS {
namespace {
constexpr static char PATH_SEPARATOR[] = "/";
constexpr static char LIB_PREFIX[] = "/lib";
constexpr static char LIB_SUFFIX[] = ".so";
constexpr static char ACE_ABILITY_NAME[] = "AceAbility";
#ifdef ABILITY_WINDOW_SUPPORT
#endif
}
bool AbilityThread::isAppRunning_ = true;
bool AbilityThread::isNativeApp_ = true;
bool AbilityThread::isDisplayInited_ = false;

AbilityThread::~AbilityThread()
{
    AdapterFree(identity_);
    delete abilityScheduler_;
    abilityScheduler_ = nullptr;
    delete eventHandler_;
    eventHandler_ = nullptr;
}

void AbilityThread::ThreadMain(uint64_t token)
{
    HILOG_INFO(HILOG_MODULE_APP, "AbilityThread::ThreadMain enter");

    AbilityThread abilityThread;
    abilityThread.AttachBundle(token);

    HILOG_INFO(HILOG_MODULE_APP, "AbilityThread::ThreadMain start loop");
    abilityThread.Run();
}

#ifdef ABILITY_WINDOW_SUPPORT
#endif

void AbilityThread::StartAbilityCallback(const Want &want)
{
    if ((want.sid == nullptr) || (want.element == nullptr)) {
        return;
    }
    HILOG_INFO(HILOG_MODULE_APP, "start ability callback");
    IpcIo io;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&io, data, IPC_IO_DATA_MAX, 0);
    if (!SerializeElement(&io, want.element)) {
        return;
    }
    IpcIoPushInt32(&io, EC_SUCCESS);
    if (Transact(nullptr, *(want.sid), SCHEDULER_APP_INIT, &io, nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        HILOG_ERROR(HILOG_MODULE_APP, "start ability callback failed, ipc error");
    }
}

void AbilityThread::PerformAppInit(const AppInfo &appInfo)
{
    HILOG_INFO(HILOG_MODULE_APP, "Start app init");
    if ((appInfo.bundleName.empty()) || (appInfo.srcPath.empty())) {
        HILOG_ERROR(HILOG_MODULE_APP, "appInfo is null");
        return;
    }
    if (!appInfo.isNativeApp && (appInfo.moduleNames.size() != 1)) {
        HILOG_ERROR(HILOG_MODULE_APP, "only native app support multi hap");
        return;
    }
    AbilityEnvImpl::GetInstance().SetAppInfo(appInfo);
    AbilityThread::isNativeApp_ = appInfo.isNativeApp;

    for (const auto &module : appInfo.moduleNames) {
        std::string modulePath;
        if (appInfo.isNativeApp) {
            modulePath = appInfo.srcPath + PATH_SEPARATOR + module + LIB_PREFIX + module + LIB_SUFFIX;
            if (modulePath.size() > PATH_MAX) {
                continue;
            }
            char realPath[PATH_MAX + 1] = { 0 };
            if (realpath(modulePath.c_str(), realPath) == nullptr) {
                continue;
            }
            void *handle = dlopen(static_cast<char *>(realPath), RTLD_NOW | RTLD_GLOBAL);
            if (handle == nullptr) {
                HILOG_ERROR(HILOG_MODULE_APP, "Fail to dlopen %{public}s, [%{public}s]", modulePath.c_str(), dlerror());
                exit(-1);
            }
            handle_.emplace_front(handle);
        }
    }

    int ret = UtilsSetEnv(GetDataPath());
    HILOG_INFO(HILOG_MODULE_APP, "Set env ret: %{public}d, App init end", ret);
}

void AbilityThread::PerformAppExit()
{
    HILOG_INFO(HILOG_MODULE_APP, "perform app exit");
    eventHandler_->PostTask([] {
        AbilityThread::isAppRunning_ = false;
    });
    for (auto handle : handle_) {
        dlclose(handle);
    }
    eventHandler_->PostQuit();
    handle_.clear();
}

void AbilityThread::PerformTransactAbilityState(const Want &want, int state, uint64_t token, int abilityType)
{
    HILOG_INFO(HILOG_MODULE_APP, "perform transact ability state to [%{public}d]", state);
    Ability *ability = nullptr;
    auto iter = abilities_.find(token);
    if ((iter == abilities_.end()) || (iter->second == nullptr)) {
        if (want.element == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "element name is null, fail to load ability");
            AbilityMsClient::GetInstance().SchedulerLifecycleDone(token, STATE_INITIAL);
            return;
        }
        auto abilityName = isNativeApp_ ? want.element->abilityName : ACE_ABILITY_NAME;
        ability = AbilityLoader::GetInstance().GetAbilityByName(abilityName);
        if (ability == nullptr) {
            HILOG_ERROR(HILOG_MODULE_APP, "fail to load ability: %{public}s", abilityName);
            AbilityMsClient::GetInstance().SchedulerLifecycleDone(token, STATE_INITIAL);
            return;
        }
        HILOG_INFO(HILOG_MODULE_APP, "Create ability success [%{public}s]", want.element->abilityName);

        // Only page ability need to init display
#ifdef ABILITY_WINDOW_SUPPORT
        if (abilityType == PAGE) {
            InitUITaskEnv();
        }
#endif
        ability->Init(token, abilityType, AbilityThread::isNativeApp_);
        abilities_[token] = ability;
    } else {
        ability = iter->second;
    }

    if (ability->GetState() != state) {
        HandleLifecycleTransaction(*ability, want, state);
    }

    HILOG_INFO(HILOG_MODULE_APP, "perform transact ability state done [%{public}d]", ability->GetState());
    AbilityMsClient::GetInstance().SchedulerLifecycleDone(token, ability->GetState());
    if (ability->GetState() == STATE_ACTIVE) {
        StartAbilityCallback(want);
    }

    if (ability->GetState() == STATE_INITIAL) {
        abilities_.erase(token);
        delete ability;
    }
}

void AbilityThread::PerformConnectAbility(const Want &want, uint64_t token)
{
    auto iter = abilities_.find(token);
    if (iter == abilities_.end() || iter->second == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "app has been stopped");
        return;
    }
    const SvcIdentity *sid = iter->second->OnConnect(want);
    AbilityMsClient::GetInstance().ScheduleAms(nullptr, token, sid, CONNECT_ABILITY_DONE);
}

void AbilityThread::PerformDisconnectAbility(const Want &want, uint64_t token)
{
    auto iter = abilities_.find(token);
    if (iter == abilities_.end() || iter->second == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "app has been stopped");
        return;
    }
    iter->second->OnDisconnect(want);
    AbilityMsClient::GetInstance().ScheduleAms(nullptr, token, nullptr, DISCONNECT_ABILITY_DONE);
}

void AbilityThread::PerformDumpAbility(const Want &want, uint64_t token)
{
    auto iter = abilities_.find(token);
    if (iter == abilities_.end() || iter->second == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "app has been stopped");
        return;
    }
    if (want.sid == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "SvcIdentity is null, dump failed");
        return;
    }
    std::string extra("");
    if (want.data != nullptr) {
        auto str = static_cast<char *>(want.data);
        if (want.dataLength == strlen(str) + 1) {
            extra = str;
        }
    }
    iter->second->Dump(extra);
    std::string dumpInfo = iter->second->GetDumpInfo();
    IpcIo io;
    char data[IPC_IO_DATA_MAX];
    IpcIoInit(&io, data, IPC_IO_DATA_MAX, 1);
    BuffPtr dataBuff = {
            .buffSz = dumpInfo.length() + 1, // include \0
            .buff = const_cast<char *>(dumpInfo.c_str()),
    };
    IpcIoPushDataBuff(&io, &dataBuff);
    if (Transact(nullptr, *(want.sid), SCHEDULER_DUMP_ABILITY, &io, nullptr, LITEIPC_FLAG_ONEWAY, nullptr) != LITEIPC_OK) {
        HILOG_ERROR(HILOG_MODULE_APP, "dump ability failed, ipc error");
    }
}

void AbilityThread::HandleLifecycleTransaction(Ability &ability, const Want &want, int state)
{
    // Switch INITIAL state to INACTIVE state
    if (ability.GetState() == STATE_INITIAL) {
        ability.OnStart(want);
    }

    // Switch ACTIVE state to INACTIVE state
    if (ability.GetState() == STATE_ACTIVE) {
        ability.OnInactive();
    }

    switch (state) {
        case STATE_INITIAL: {
            if (ability.GetState() == STATE_INACTIVE) {
                ability.OnBackground();
            }
            ability.OnStop();
            break;
        }
        case STATE_INACTIVE: {
            // Not support transact from BACKGROUND to INACTIVE state
            break;
        }
        case STATE_ACTIVE: {
            ability.OnActive(want);
            break;
        }
        case STATE_BACKGROUND: {
            if (ability.GetState() == STATE_INACTIVE) {
                ability.OnBackground();
            }
            break;
        }
        default: {
            HILOG_ERROR(HILOG_MODULE_APP, "Unknown target state: %{public}d", state);
            break;
        }
    }
}

void AbilityThread::AttachBundle(uint64_t token)
{
    eventHandler_ = new AbilityEventHandler();
    abilityScheduler_ = new AbilityScheduler(*eventHandler_, *this);
    if (!AbilityMsClient::GetInstance().Initialize()) {
        HILOG_ERROR(HILOG_MODULE_APP, "ams feature is null");
        return;
    }

    identity_ = static_cast<SvcIdentity *>(AdapterMalloc(sizeof(SvcIdentity)));
    if (identity_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "ams identity is null");
        return;
    }
    int32_t ret = RegisterIpcCallback(AbilityScheduler::AmsCallback, 0, IPC_WAIT_FOREVER, identity_, abilityScheduler_);
    if (ret != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "RegisterIpcCallback failed");
        AdapterFree(identity_);
        return;
    }

    AbilityMsClient::GetInstance().ScheduleAms(nullptr, token, identity_, ATTACH_BUNDLE);
}

void AbilityThread::Run()
{
    eventHandler_->Run();
}
*/
