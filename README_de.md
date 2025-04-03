[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MMA7660FC

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mma7660fc/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der MMA7660FC ist ein 3-Achsen-Beschleunigungssensor mit ±1,5 g und digitalem Ausgang (I²C). Er ist ein kapazitiver MEMS-Sensor mit sehr geringem Stromverbrauch und flachem Profil. Er verfügt über einen Tiefpassfilter, Kompensation von 0-g-Offset- und Verstärkungsfehlern sowie die Konvertierung in 6-Bit-Digitalwerte mit benutzerkonfigurierbaren Abtastwerten pro Sekunde. Das Gerät kann für Sensordatenänderungen, Produktausrichtung und Gestenerkennung über einen Interrupt-Pin (INT) verwendet werden. Das Gerät ist in einem kleinen DFN-Gehäuse (3 mm x 3 mm x 0,9 mm) untergebracht.

LibDriver MMA7660FC ist der vollfunktionale Treiber für mma7660fc von LibDriver. Er bietet Beschleunigungsmessung, Erschütterungs-, Tipp- und Bewegungserkennung sowie weitere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example motion](#example-motion)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MMA7660FC-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MMA7660FC IIC.

/test enthält den Testcode des LibDriver MMA7660FC-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MMA7660FC-Beispielcode.

/doc enthält das LibDriver MMA7660FC-Offlinedokument.

/Datenblatt enthält MMA7660FC-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC- Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/mma7660fc/index.html](https://www.libdriver.com/docs/mma7660fc/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.