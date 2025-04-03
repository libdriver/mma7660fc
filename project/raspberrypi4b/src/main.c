/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-03-31
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/03/31  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_mma7660fc_register_test.h"
#include "driver_mma7660fc_read_test.h"
#include "driver_mma7660fc_motion_test.h"
#include "driver_mma7660fc_basic.h"
#include "driver_mma7660fc_motion.h"
#include "gpio.h"
#include <getopt.h>
#include <stdlib.h>

uint8_t (*g_gpio_irq)(void) = NULL;        /**< irq function address */
static volatile uint16_t gs_flag = 0;      /**< motion flag */

/**
 * @brief     receive callback
 * @param[in] type irq type
 * @note      none
 */
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

/**
 * @brief     mma7660fc full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t mma7660fc(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {"timeout", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    uint32_t timeout = 10000;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* running times */
            case 1 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* timeout */
            case 2 :
            {
                /* set the times */
                timeout = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (mma7660fc_register_test() != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (mma7660fc_read_test(times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_motion", type) == 0)
    {
        uint8_t res;
        
        /* interrupt init */
        g_gpio_irq = mma7660fc_motion_test_irq_handler;
        res = gpio_interrupt_init();
        if (res != 0)
        {
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* run motion test */
        if (mma7660fc_motion_test(timeout) != 0)
        {
            gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float g[3];
        
        /* basic init */
        res = mma7660fc_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
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
            
            /* output */
            mma7660fc_interface_debug_print("mma7660fc: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            mma7660fc_interface_debug_print("mma7660fc: x is %0.2fg.\n", g[0]);
            mma7660fc_interface_debug_print("mma7660fc: y is %0.2fg.\n", g[1]);
            mma7660fc_interface_debug_print("mma7660fc: z is %0.2fg.\n", g[2]);
        }
        
        /* deinit */
        (void)mma7660fc_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_motion", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
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
        
        mma7660fc_motion_deinit();
        gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        mma7660fc_interface_debug_print("Usage:\n");
        mma7660fc_interface_debug_print("  mma7660fc (-i | --information)\n");
        mma7660fc_interface_debug_print("  mma7660fc (-h | --help)\n");
        mma7660fc_interface_debug_print("  mma7660fc (-p | --port)\n");
        mma7660fc_interface_debug_print("  mma7660fc (-t reg | --test=reg)\n");
        mma7660fc_interface_debug_print("  mma7660fc (-t read | --test=read) [--times=<num>]\n");
        mma7660fc_interface_debug_print("  mma7660fc (-t motion | --test=motion) [--timeout=<ms>]\n");
        mma7660fc_interface_debug_print("  mma7660fc (-e read | --example=read) [--times=<num>]\n");
        mma7660fc_interface_debug_print("  mma7660fc (-e motion | --example=motion) [--timeout=<ms>]\n");
        mma7660fc_interface_debug_print("\n");
        mma7660fc_interface_debug_print("Options:\n");
        mma7660fc_interface_debug_print("  -e <read | motion>, --example=<read | motion>\n");
        mma7660fc_interface_debug_print("                                     Run the driver example.\n");
        mma7660fc_interface_debug_print("  -h, --help                         Show the help.\n");
        mma7660fc_interface_debug_print("  -i, --information                  Show the chip information.\n");
        mma7660fc_interface_debug_print("  -p, --port                         Display the pin connections of the current board.\n");
        mma7660fc_interface_debug_print("  -t <reg | read | motion>, --test=<reg | read | motion>\n");
        mma7660fc_interface_debug_print("                                     Run the driver test.\n");
        mma7660fc_interface_debug_print("      --times=<num>                  Set the running times.([default: 3])\n");
        mma7660fc_interface_debug_print("      --timeout=<ms>                 Set timeout in ms.([default: 10000])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        mma7660fc_info_t info;
        
        /* print mma7660fc info */
        mma7660fc_info(&info);
        mma7660fc_interface_debug_print("mma7660fc: chip is %s.\n", info.chip_name);
        mma7660fc_interface_debug_print("mma7660fc: manufacturer is %s.\n", info.manufacturer_name);
        mma7660fc_interface_debug_print("mma7660fc: interface is %s.\n", info.interface);
        mma7660fc_interface_debug_print("mma7660fc: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mma7660fc_interface_debug_print("mma7660fc: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mma7660fc_interface_debug_print("mma7660fc: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mma7660fc_interface_debug_print("mma7660fc: max current is %0.2fmA.\n", info.max_current_ma);
        mma7660fc_interface_debug_print("mma7660fc: max temperature is %0.1fC.\n", info.temperature_max);
        mma7660fc_interface_debug_print("mma7660fc: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        mma7660fc_interface_debug_print("mma7660fc: IIC interface SCL connected to GPIO3(BCM).\n");
        mma7660fc_interface_debug_print("mma7660fc: IIC interface SDA connected to GPIO2(BCM).\n");
        mma7660fc_interface_debug_print("mma7660fc: INT connected to GPIO17(BCM).\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = mma7660fc(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        mma7660fc_interface_debug_print("mma7660fc: run failed.\n");
    }
    else if (res == 5)
    {
        mma7660fc_interface_debug_print("mma7660fc: param is invalid.\n");
    }
    else
    {
        mma7660fc_interface_debug_print("mma7660fc: unknown status code.\n");
    }

    return 0;
}
