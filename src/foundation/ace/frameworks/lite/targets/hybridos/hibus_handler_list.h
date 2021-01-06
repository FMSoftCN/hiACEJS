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


#ifndef HIBUS_HANDLER_LIST_H
#define HIBUS_HANDLER_LIST_H

#include "acelite_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <jerryscript.h>
#include "memory_heap.h"
#include "non_copyable.h"

typedef void *hibusHandlerHandle_t;

namespace OHOS {

class HiBusHandlerList {
public:
    HiBusHandlerList() : hibusHandlerListHead_(nullptr) {}

    ~HiBusHandlerList() = default;

    void ClearHiBusHandlerList();

    // the struct of hibusHandler task arguments
    struct Arguments {
        jerry_length_t argsNum = 0;
        jerry_value_t func;
        jerry_value_t context;
        jerry_value_t *args = nullptr;
    };

    // the struct of hibusHandler
    struct HiBusHandlerNode {
        char endpoint[512] = {0};
        // method_name, bubble_name
        char name[128] = {0};
        // 0 method, 1 bubble
        int type;
        hibusHandlerHandle_t hibusHandlerId;
        Arguments *arguments;
        struct HiBusHandlerNode *next;
    };

    HiBusHandlerNode* AddHiBusHandler(const char* endpoint, const char* name, int type, Arguments *&arguments);

    HiBusHandlerNode* GetHiBusHandler(const char* endpoint, const char* name, int type);

    void DeleteHiBusHandler(HiBusHandlerNode* hibusHandler);

    void ReleaseArguments(Arguments *&argument);

private:
    void ReleaseHiBusHandler(HiBusHandlerNode *&current);

    HiBusHandlerNode *hibusHandlerListHead_;
};

} //  namespace OHOS
#endif // HIBUS_HANDLER_LIST_H
