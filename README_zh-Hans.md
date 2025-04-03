[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MMA7660FC

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mma7660fc/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MMA7660FC是一个带数字输出（I2C）的±1.5 g 3轴加速度计。它是一种低功耗、电容式MEMS传感器，具有低通滤波器、0g偏移和增益误差补偿。用户可配置不同采样率输出6位数字值。该设备可用于传感器数据采集、产品方向检测，手势检测等，并通过中断引脚（INT）输出。该设备封装在一个小的3mm x 3mm x 0.9mm DFN封装中。

LibDriver MMA7660FC是LibDriver推出的MMA7660FC全功能驱动，该驱动提供加速度读取、震动检测、敲击检测、运动检测等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example motion](#example-motion)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver MMA7660FC的源文件。

/interface目录包含了LibDriver MMA7660FC与平台无关的IIC总线模板。

/test目录包含了LibDriver MMA7660FC驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver MMA7660FC编程范例。

/doc目录包含了LibDriver MMA7660FC离线文档。

/datasheet目录包含了MMA7660FC数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/mma7660fc/index.html](https://www.libdriver.com/docs/mma7660fc/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。