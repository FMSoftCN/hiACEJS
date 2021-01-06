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

#include <string.h>

#include "ace_mem_base.h"
#include "js_fwk_common.h"
#include "acelite_config.h"
#include "hibus_handler_list.h"

namespace OHOS {
HiBusHandlerList::HiBusHandlerNode* HiBusHandlerList::AddHiBusHandler(const char* endpoint, const char* name, int type, Arguments *&arguments)
{
    HiBusHandlerNode* hibusHandler = static_cast<HiBusHandlerNode *>(malloc(sizeof(HiBusHandlerNode)));
    if (hibusHandler == nullptr) {
        return nullptr;
    }
    strcpy(hibusHandler->endpoint, endpoint);
    strcpy(hibusHandler->name, name);
    hibusHandler->type = type;
    hibusHandler->next = hibusHandlerListHead_;
    hibusHandler->arguments = arguments;
    hibusHandlerListHead_ = hibusHandler;
    return hibusHandler;
}

HiBusHandlerList::HiBusHandlerNode* HiBusHandlerList::GetHiBusHandler(const char* endpoint, const char* name, int type)
{
    HiBusHandlerNode *current = hibusHandlerListHead_;
    while (current != nullptr) {
        if (current->type == type && strcmp(current->endpoint, endpoint) == 0 && strcmp(current->name, name) == 0)
        {
            break;
        }
        current = current->next;
    }
    return current;
}

void HiBusHandlerList::DeleteHiBusHandler(HiBusHandlerNode* hibusHandler)
{
    if (hibusHandlerListHead_ == nullptr) {
        return;
    }
    HiBusHandlerNode *current = hibusHandlerListHead_;
    HiBusHandlerNode *preNode = nullptr;
    while ((hibusHandler != current) && (current->next != nullptr)) {
        preNode = current;
        current = current->next;
    }
    if (hibusHandler == current) {
        if (current == hibusHandlerListHead_) {
            hibusHandlerListHead_ = current->next;
        } else {
            preNode->next = current->next;
        }
        ReleaseHiBusHandler(current);
    }
}

void HiBusHandlerList::ClearHiBusHandlerList()
{
    while (hibusHandlerListHead_ != nullptr) {
        HiBusHandlerNode *current = hibusHandlerListHead_;
        hibusHandlerListHead_ = hibusHandlerListHead_->next;
        ReleaseHiBusHandler(current);
    }
}

void HiBusHandlerList::ReleaseHiBusHandler(HiBusHandlerNode *&current)
{
    if (current == nullptr) {
        return;
    }
    ReleaseArguments(current->arguments);
    free(current);
    current = nullptr;
}

void HiBusHandlerList::ReleaseArguments(Arguments *&argument)
{
    if (argument) {
        ACELite::JSI::ReleaseValue(argument->func);
        if ((argument->argc > 0) && (argument->argv != nullptr)) {
            for (uint32_t i = 0; i < argument->argc; i++) {
                ACELite::JSI::ReleaseValue((argument->argv)[i]);
            }
        }
        ACELite::JSI::ReleaseValue(argument->context);
        delete argument;
        argument = nullptr;
    }
}

} // namespace OHOS
