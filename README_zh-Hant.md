[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MMA7660FC

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mma7660fc/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MMA7660FC是一個帶數位輸出（I2C）的±1.5 g 3軸加速度計。 它是一種低功耗、電容式MEMS感測器，具有低通濾波器、0g偏移和增益誤差補償。 用戶可配置不同取樣速率輸出6比特數位值。 該設備可用於感測器資料獲取、產品方向檢測，手勢檢測等，並通過中斷引脚（INT）輸出。 該設備封裝在一個小的3mm x 3mm x 0.9mm DFN封裝中。

LibDriver MMA7660FC是LibDriver推出的MMA7660FC全功能驅動，該驅動提供加速度讀取、震動檢測、敲擊檢測、運動檢測等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example motion](#example-motion)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver MMA7660FC的源文件。

/interface目錄包含了LibDriver MMA7660FC與平台無關的IIC總線模板。

/test目錄包含了LibDriver MMA7660FC驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver MMA7660FC編程範例。

/doc目錄包含了LibDriver MMA7660FC離線文檔。

/datasheet目錄包含了MMA7660FC數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/mma7660fc/index.html](https://www.libdriver.com/docs/mma7660fc/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。