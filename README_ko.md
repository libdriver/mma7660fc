[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MMA7660FC

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mma7660fc/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

MMA7660FC는 디지털 출력(I2C)이 있는 ±1.5g 3축 가속도계입니다. 저역 통과 필터, 0g 오프셋 및 이득 오류에 대한 보상, 사용자가 구성 가능한 초당 샘플에서 6비트 디지털 값으로 변환하는 기능을 갖춘 매우 낮은 전력, 낮은 프로파일 용량성 MEMS 센서입니다. 이 장치는 센서 데이터 변경, 제품 방향 및 인터럽트 핀(INT)을 통한 제스처 감지에 사용할 수 있습니다. 이 장치는 작은 3mm x 3mm x 0.9mm DFN 패키지에 들어 있습니다.

LibDriver MMA7660FC는 LibDriver에서 출시한 mma7660fc의 전체 기능 드라이버입니다. 가속도 판독, 흔들림 감지, 탭 감지, 동작 감지 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example motion](#example-motion)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver MMA7660FC의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver MMA7660FC용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver MMA7660FC드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver MMA7660FC프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver MMA7660FC오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 MMA7660FC데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

```c
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

### 문서

온라인 문서: [https://www.libdriver.com/docs/mma7660fc/index.html](https://www.libdriver.com/docs/mma7660fc/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.