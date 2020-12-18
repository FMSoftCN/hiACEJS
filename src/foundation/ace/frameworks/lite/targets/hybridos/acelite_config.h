/////////////////////////////////////////////////////////////////////////////// //
//                          IMPORTANT NOTICE
//
// The following open source license statement does not apply to any
// entity in the Exception List published by FMSoft.
//
// For more information, please visit:
//
// https://www.fmsoft.cn/exception-list
//
//////////////////////////////////////////////////////////////////////////////
/**
 \verbatim

    This file is part of HybridOS, a developing operating system based on
    MiniGUI. HybridOs will support embedded systems and smart IoT devices.

    Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */


#ifndef OHOS_ACELITE_CONFIG_H
#define OHOS_ACELITE_CONFIG_H

/**
 * ================================================================================================
 *                 hi3516_linux config for hmf
 * ================================================================================================
 */
#define OHOS_ACELITE_LINUX // NOTE: DO NOT use this macro directly

/**
 * Compile all test entry for hmf
 */
#ifdef FEATURE_TEST_IMPLEMENTATION
#error "must keep the global configuration unique"
#else
#define FEATURE_TEST_IMPLEMENTATION
#endif

/**
 * use hi log interface to trace out
 */
#ifdef FEATURE_ACELITE_HI_LOG_PRINTF
#error "must keep the global configuration unique"
#else
#define FEATURE_ACELITE_HI_LOG_PRINTF
#endif


/**
 * support storage API for JS
 */
#define FEATURE_MODULE_STORAGE

/**
 * support device API for JS
 */
#define FEATURE_MODULE_DEVICE

#define DEFAULT_PROFILER_MSG_PATH "/opt/hiacejs/"

#define PROFILER_ENABLE_FLAG_FILE "/opt/hiacejs/profiler_enable"

#define RUNTIME_MODE_FILE_PATH "/opt/hiacejs/jsparser_enable"

#endif // OHOS_ACELITE_CONFIG_H

