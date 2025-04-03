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
 * @file      driver_mma7660fc_motion_test.c
 * @brief     driver mma7660fc motion test source file
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

#include "driver_mma7660fc_motion_test.h"

static mma7660fc_handle_t gs_handle;        /**< mma7660fc handle */
static volatile uint16_t gs_flag = 0;       /**< motion flag */

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
 * @brief  motion test irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t mma7660fc_motion_test_irq_handler(void)
{
    if (mma7660fc_irq_handler(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     motion test
 * @param[in] timeout timeout in ms
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t mma7660fc_motion_test(uint32_t timeout)
{
    uint8_t res;
    uint8_t count;
    uint32_t i;
    mma7660fc_info_t info;
    
    /* link interface function */
    DRIVER_MMA7660FC_LINK_INIT(&gs_handle, mma7660fc_handle_t); 
    DRIVER_MMA7660FC_LINK_IIC_INIT(&gs_handle, mma7660fc_interface_iic_init);
    DRIVER_MMA7660FC_LINK_IIC_DEINIT(&gs_handle, mma7660fc_interface_iic_deinit);
    DRIVER_MMA7660FC_LINK_IIC_READ(&gs_handle, mma7660fc_interface_iic_read);
    DRIVER_MMA7660FC_LINK_IIC_WRITE(&gs_handle, mma7660fc_interface_iic_write);
    DRIVER_MMA7660FC_LINK_DELAY_MS(&gs_handle, mma7660fc_interface_delay_ms);
    DRIVER_MMA7660FC_LINK_DEBUG_PRINT(&gs_handle, mma7660fc_interface_debug_print);
    DRIVER_MMA7660FC_LINK_RECEIVE_CALLBACK(&gs_handle, a_receive_callback);
    
    /* get mma7660fc info */
    res = mma7660fc_info(&info);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print mma7660fc */
        mma7660fc_interface_debug_print("mma7660fc: chip is %s.\n", info.chip_name);
        mma7660fc_interface_debug_print("mma7660fc: manufacturer is %s.\n", info.manufacturer_name);
        mma7660fc_interface_debug_print("mma7660fc: interface is %s.\n", info.interface);
        mma7660fc_interface_debug_print("mma7660fc: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        mma7660fc_interface_debug_print("mma7660fc: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        mma7660fc_interface_debug_print("mma7660fc: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        mma7660fc_interface_debug_print("mma7660fc: max current is %0.2fmA.\n", info.max_current_ma);
        mma7660fc_interface_debug_print("mma7660fc: max temperature is %0.1fC.\n", info.temperature_max);
        mma7660fc_interface_debug_print("mma7660fc: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start motion test */
    mma7660fc_interface_debug_print("mma7660fc: start motion test.\n");
    
    /* init */
    res = mma7660fc_init(&gs_handle);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: init failed.\n");
       
        return 1;
    }
    
    /* enable front back interrupt */
    res = mma7660fc_set_front_back_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set front back interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable up down right left interrupt */
    res = mma7660fc_set_up_down_right_left_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set up down right left interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable tap interrupt */
    res = mma7660fc_set_tap_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable auto sleep interrupt */
    res = mma7660fc_set_auto_sleep_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* disable update interrupt */
    res = mma7660fc_set_update_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set update interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable shake x interrupt */
    res = mma7660fc_set_shake_x_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake x interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable shake y interrupt */
    res = mma7660fc_set_shake_y_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake y interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable shake z interrupt */
    res = mma7660fc_set_shake_z_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake z interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set sleep counter prescaler 1 */
    res = mma7660fc_set_sleep_counter_prescaler(&gs_handle, MMA7660FC_SLEEP_COUNTER_PRESCALER_1);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set sleep counter prescaler failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set tap detection rate 120 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_120);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set auto wake rate 32 */
    res = mma7660fc_set_auto_wake_rate(&gs_handle, MMA7660FC_AUTO_WAKE_RATE_32);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set sleep count 127 */
    res = mma7660fc_set_sleep_count(&gs_handle, 127);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set sleep count failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable auto wake up */
    res = mma7660fc_set_auto_wake_up(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake up failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable auto sleep */
    res = mma7660fc_set_auto_sleep(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* interrupt pin type push-pull */
    res = mma7660fc_set_interrupt_pin_type(&gs_handle, MMA7660FC_INTERRUPT_PIN_TYPE_PUSH_PULL);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set interrupt pin type failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set interrupt active level low */
    res = mma7660fc_set_interrupt_active_level(&gs_handle, MMA7660FC_INTERRUPT_ACTIVE_LEVEL_LOW);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set interrupt active level failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set tilt debounce filter 8 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_8);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set tap detection threshold 2 */
    res = mma7660fc_set_tap_detection_threshold(&gs_handle, 2);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection threshold failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable tap x detection */
    res = mma7660fc_set_tap_x_detection(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap x detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable tap y detection */
    res = mma7660fc_set_tap_y_detection(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap y detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable tap z detection */
    res = mma7660fc_set_tap_z_detection(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap z detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* tap pulse debounce 10ms */
    res = mma7660fc_tap_pulse_debounce_convert_to_register(&gs_handle, 10.0f, &count);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: tap pulse debounce convert to register failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set tap pulse debounce count */
    res = mma7660fc_set_tap_pulse_debounce_count(&gs_handle, count);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap pulse debounce count failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set active mode */
    res = mma7660fc_set_mode(&gs_handle, MMA7660FC_MODE_ACTIVE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set mode failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
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
    
    /* finish motion test */
    mma7660fc_interface_debug_print("mma7660fc: finish motion test.\n");
    (void)mma7660fc_deinit(&gs_handle); 
    
    return 0;
}
