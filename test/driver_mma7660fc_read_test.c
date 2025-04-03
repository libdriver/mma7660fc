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
 * @file      driver_mma7660fc_read_test.c
 * @brief     driver mma7660fc read test source file
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

#include "driver_mma7660fc_read_test.h"

static mma7660fc_handle_t gs_handle;        /**< mma7660fc handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t mma7660fc_read_test(uint32_t times)
{
    uint8_t res;
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
    DRIVER_MMA7660FC_LINK_RECEIVE_CALLBACK(&gs_handle, mma7660fc_interface_receive_callback);
    
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
    
    /* start read test */
    mma7660fc_interface_debug_print("mma7660fc: start read test.\n");
    
    /* init */
    res = mma7660fc_init(&gs_handle);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: init failed.\n");
       
        return 1;
    }
    
    /* set sleep count 0 */
    res = mma7660fc_set_sleep_count(&gs_handle, 0);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set sleep count failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable front back interrupt */
    res = mma7660fc_set_front_back_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set front back interrupt failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable up down right left interrupt */
    res = mma7660fc_set_up_down_right_left_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set up down right left interrupt failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable tap interrupt */
    res = mma7660fc_set_tap_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap interrupt failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable auto sleep interrupt */
    res = mma7660fc_set_auto_sleep_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
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
    
    /* disable shake x interrupt */
    res = mma7660fc_set_shake_x_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake x interrupt failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable shake y interrupt */
    res = mma7660fc_set_shake_y_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake y interrupt failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable shake z interrupt */
    res = mma7660fc_set_shake_z_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake z interrupt failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable auto wake up */
    res = mma7660fc_set_auto_wake_up(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake up failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable auto sleep */
    res = mma7660fc_set_auto_sleep(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep failed.\n");
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
    
    /* set interrupt pin type push-pull */
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
    
    /* set tap detection rate 8 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_8);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set auto wake rate 16 */
    res = mma7660fc_set_auto_wake_rate(&gs_handle, MMA7660FC_AUTO_WAKE_RATE_16);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake rate failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set tilt debounce filter 2 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_2);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set tap detection threshold 0 */
    res = mma7660fc_set_tap_detection_threshold(&gs_handle, 0);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection threshold failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable tap x detection */
    res = mma7660fc_set_tap_x_detection(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap x detection failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable tap y detection */
    res = mma7660fc_set_tap_y_detection(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap y detection failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable tap z detection */
    res = mma7660fc_set_tap_z_detection(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap z detection failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set tap pulse debounce count 0 */
    res = mma7660fc_set_tap_pulse_debounce_count(&gs_handle, 0);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap pulse debounce count failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set mode active */
    res = mma7660fc_set_mode(&gs_handle, MMA7660FC_MODE_ACTIVE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set mode failed.\n");
       (void)mma7660fc_deinit(&gs_handle);
        
        return 1;
    }
    
    for (i = 0; i < times; i++)
    {
        int8_t raw[3];
        float g[3];
        
        /* delay 1000ms */
        mma7660fc_interface_delay_ms(1000);
        
        /* read data */
        res = mma7660fc_read(&gs_handle, raw, g);
        if (res != 0)
        {
            mma7660fc_interface_debug_print("mma7660fc: read failed.\n");
            (void)mma7660fc_deinit(&gs_handle); 
            
            return 1;
        }
        mma7660fc_interface_debug_print("mma7660fc: x is %0.2fg.\n", g[0]);
        mma7660fc_interface_debug_print("mma7660fc: y is %0.2fg.\n", g[1]);
        mma7660fc_interface_debug_print("mma7660fc: z is %0.2fg.\n", g[2]);
    }
    
    /* finish read test */
    mma7660fc_interface_debug_print("mma7660fc: finish read test.\n");
    (void)mma7660fc_deinit(&gs_handle); 
    
    return 0;
}
