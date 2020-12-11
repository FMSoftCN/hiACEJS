# hiAceJS

hiAceJS is a runtime for the HybridOS.

- [Introduction](#introduction)
- [How to Build](#how-to-build)
- [Copying](#copying)
   + [For the Server and the Command Line](#for-the-server-and-the-command-line)
   + [For the Library](#for-the-library)
   + [Commercial License](#commercial-license)
   + [Special Statement](#special-statement)

## Introduction

The hiAceJS is a derivative from the OpenHarmony ACE JS.
In HybridOS, hiAce is one of the runtimes, and the
other runtime is webkit.


## How to Build

- build thirdpart

```
$ ./build/scripts/build_third_party.sh
```

- build hiace

```
$ ./build/scripts/build_ace.sh
```

- run app

```
$ source ./build/scripts/env.sh
$ hiacejs_run app com.example.helloworld app/fonts/
```


## Copying

Copyright (C) 2020 FMSoft <https://www.fmsoft.cn>

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

### Commercial License

If you cannot accept GPLv3, you need to be licensed from FMSoft.

For more information about the commercial license, please refer to
<https://hybridos.fmsoft.cn/blog/hybridos-licensing-policy>.

### Special Statement

The above open source or free software license(s) does
not apply to any entity in the Exception List published by
Beijing FMSoft Technologies Co., Ltd.

If you are or the entity you represent is listed in the Exception List,
the above open source or free software license does not apply to you
or the entity you represent. Regardless of the purpose, you should not
use the software in any way whatsoever, including but not limited to
downloading, viewing, copying, distributing, compiling, and running.
If you have already downloaded it, you MUST destroy all of its copies.

The Exception List is published by FMSoft and may be updated
from time to time. For more information, please see
<https://www.fmsoft.cn/exception-list>.

