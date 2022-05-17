# CFUL
![](https://flat.badgen.net/badge/Lang/C/blue)

Colorful console output in C

![](imgs/cful.gif)

## Language
  - [한국어](/README.ko.md)
  - [English](/README.md)



## What is CFUL?
CFUL is functions for colorful console output.
It is support RGB system.

## Support
  - Linux
  - Windows 10
  - MacOS

If your OS is not support true color, can use ansi color.


## How to use?
You want this functions, then include only `cful.h` on your project.

```c
#include "cful.h"
```

<br><br>

Get foreground color string
```c
FG_COLOR(r, g, b);
_F(r, g, b);
```

Example
```c
#include <stdio.h>
#include "cful.h"

int main ( void )
{
    printf(FG_COLOR(255, 0, 0)"Change font color red" RESET "\n");
    printf(_F(0, 255, 0) "Green" _F(0, 0, 255) "Blue" RESET "\n");
    return 0;
}
```
![](imgs/ex-1.png)

<br><br>


Get background color string

```c
BG_COLOR(r, g, b);
_B(r, g, b);
```

Example
```c
#include <stdio.h>
#include "cful.h"

int main ( void )
{
    printf(_F(255, 255, 255) BG_COLOR(255, 0, 0)"Change back color red" RESET "\n");
    printf(_F(255, 255, 255) _B(0, 255, 0) "Green" _B(0, 0, 255) "Blue" RESET "\n");
    return 0;
}
```
![](imgs/ex-2.png)

<br><br>

Set color

```c
SET_COLOR(type, r, g, b);
SET_FG_COLOR(r, g, b);
SET_BG_COLOR(r, g, b);
```

Type is `FOREGROUND` or `BACKGROUND` define.

```c
#define FOREGROUND  "38"
#define BACKGROUND  "48"
```


Example
```c
#include <stdio.h>
#include "cful.h"

int main ( void )
{
    SET_COLOR(FOREGROUND, 255, 0, 0);
    printf("Set font color red");

    SET_BG_COLOR(0, 255, 0);
    printf("Set background color green");
    printf(RESET "\n");
    return 0;
}
```
![](imgs/ex-3.png)

<br><br>

Use ansi color

If your OS is not support true color, then use `SET_ANSI_MODE(1)` and you must use only `SET_COLOR`, `SET_FG_COLOR`, `SET_BG_COLOR` function.

```c
SET_ANSI_COLOR(mode); // 1: enable, 0: disable
```


Example
```c
#include <stdio.h>
#include "cful.h"

int main ( void )
{
    printf(_F(255, 0, 0) "Red true color" RESET "\n");

    SET_ANSI_MODE(1);
    SET_FG_COLOR(255, 0, 0); 
    printf("Red ansi color" RESET "\n");
    return 0;
}

```
![](imgs/ex-4.png)


## Compile

When compile your project by gcc, then add library option for `math.h` in command.
```sh
gcc -o cful main.c -lm
```


<br><br><br>
Thanks.