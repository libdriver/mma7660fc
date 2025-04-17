[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MMA7660FC

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mma7660fc/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The MMA7660FC is a ±1.5 g 3-Axis Accelerometer with Digital Output(I2C). It is a very low power, low profile capacitive MEMS sensor featuring a low pass filter, compensation for 0g offset and gain errors, and conversion to 6-bit digital values at a user configurable samples per second. The device can be used for sensor data changes, product orientation, and gesture detection through an interrupt pin (INT). The device is housed in a small 3mm x 3mm x 0.9mm DFN package.

LibDriver MMA7660FC is a full-featured driver of MMA7660FC launched by LibDriver. It provides acceleration reading, shake detection, tap detection, motion detection and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example motion](#example-motion)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver MMA7660FC source files.

/interface includes LibDriver MMA7660FC IIC platform independent template.

/test includes LibDriver MMA7660FC driver test code and this code can test the chip necessary function simply.

/example includes LibDriver MMA7660FC sample code.

/doc includes LibDriver MMA7660FC offline document.

/datasheet includes MMA7660FC datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_mma7660fc_basic.h"

uint8_t res;
uint32_t i;
float g[3];

/* basic init */
res = mma7660fc_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    mma7660fc_interface_delay_ms(1000);

    /* read data */
    res = mma7660fc_basic_read(g);
    if (res != 0)
    {
        (void)mma7660fc_basic_deinit();

        return 1;
    }
    
    ...
        
    /* output */
    mma7660fc_interface_debug_print("mma7660fc: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
    mma7660fc_interface_debug_print("mma7660fc: x is %0.2fg.\n", g[0]);
    mma7660fc_interface_debug_print("mma7660fc: y is %0.2fg.\n", g[1]);
    mma7660fc_interface_debug_print("mma7660fc: z is %0.2fg.\n", g[2]);
}

...
    
/* deinit */
(void)mma7660fc_basic_deinit();

return 0;
```

#### example motion

```C
#include "driver_mma7660fc_motion.h"

uint8_t res;
uint32_t i;
uint32_t timeout = 10000;
uint8_t (*g_gpio_irq)(void) = NULL;
volatile uint16_t gs_flag = 0;

static void a_receive_callback(uint8_t type)
{
    switch (type)
    {
        case MMA7660FC_STATUS_FRONT :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq front.\n");
            gs_flag |= 1 << 0;
            
            break;
        }
        case MMA7660FC_STATUS_BACK :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq back.\n");
            gs_flag |= 1 << 1;
            
            break;
        }
        case MMA7660FC_STATUS_LEFT :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq left.\n");
            gs_flag |= 1 << 2;
            
            break;
        }
        case MMA7660FC_STATUS_RIGHT :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq right.\n");
            gs_flag |= 1 << 3;
            
            break;
        }
        case MMA7660FC_STATUS_DOWN :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq down.\n");
            gs_flag |= 1 << 4;
            
            break;
        }
        case MMA7660FC_STATUS_UP :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq up.\n");
            gs_flag |= 1 << 5;
            
            break;
        }
        case MMA7660FC_STATUS_TAP :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq tap.\n");
            gs_flag |= 1 << 6;
            
            break;
        }
        case MMA7660FC_STATUS_UPDATE :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq update.\n");
            
            break;
        }
        case MMA7660FC_STATUS_SHAKE :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq shake.\n");
            gs_flag |= 1 << 7;
            
            break;
        }
        case MMA7660FC_STATUS_AUTO_SLEEP :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq auto sleep.\n");
            gs_flag |= 1 << 8;
            
            break;
        }
        case MMA7660FC_STATUS_AUTO_WAKE_UP :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq auto wake up.\n");
            gs_flag |= 1 << 9;
            
            break;
        }
        default :
        {
            mma7660fc_interface_debug_print("mma7660fc: unknown code.\n");
            
            break;
        }
    }
}

/* interrupt init */
g_gpio_irq = mma7660fc_motion_irq_handler;
res = gpio_interrupt_init();
if (res != 0)
{
    g_gpio_irq = NULL;

    return 1;
}

/* run motion test */
res = mma7660fc_motion_init(a_receive_callback);
if (res != 0)
{
    gpio_interrupt_deinit();
    g_gpio_irq = NULL;

    return 1;
}

...
    
/* init 0 */
gs_flag = 0;

/* loop */
for (i = 0; i < timeout; i++)
{
    if (gs_flag == 0x3FF)
    {
        break;
    }

    /* delay 1ms */
    mma7660fc_interface_delay_ms(1);
    
    ...
}

if (timeout != 0)
{
    /* finish motion */
    mma7660fc_interface_debug_print("mma7660fc: finish motion.\n");
}
else
{
    /* timeout */
    mma7660fc_interface_debug_print("mma7660fc: timeout.\n");
}

...
    
mma7660fc_motion_deinit();
gpio_interrupt_deinit();
g_gpio_irq = NULL;

return 0;
```


### Document

Online documents: [https://www.libdriver.com/docs/mma7660fc/index.html](https://www.libdriver.com/docs/mma7660fc/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.