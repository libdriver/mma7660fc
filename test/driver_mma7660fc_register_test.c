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
 * @file      driver_mma7660fc_register_test.c
 * @brief     driver mma7660fc register test source file
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
#include <stdlib.h>

static mma7660fc_handle_t gs_handle;        /**< mma7660fc handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t mma7660fc_register_test(void)
{
    uint8_t res;
    uint8_t status;
    uint8_t count;
    uint8_t count_check;
    uint8_t threshold;
    uint8_t threshold_check;
    uint8_t reg;
    float ms;
    float ms_check;
    mma7660fc_bool_t enable;
    mma7660fc_mode_t mode;
    mma7660fc_info_t info;
    mma7660fc_sleep_counter_prescaler_t prescaler;
    mma7660fc_interrupt_pin_type_t type;
    mma7660fc_interrupt_active_level_t level;
    mma7660fc_auto_sleep_rate_t sleep_rate;
    mma7660fc_auto_wake_rate_t wake_rate;
    mma7660fc_tilt_debounce_filter_t filter;
    
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
    
    /* start register test */
    mma7660fc_interface_debug_print("mma7660fc: start register test.\n");
    
    /* init */
    res = mma7660fc_init(&gs_handle);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: init failed.\n");
       
        return 1;
    }
    
    /* mma7660fc_get_tilt_status test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_get_tilt_status test.\n");
    
    /* get tilt status */
    res = mma7660fc_get_tilt_status(&gs_handle, &status);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt status failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: tilt status is 0x%02X.\n", status);
    mma7660fc_interface_debug_print("mma7660fc: check tilt status %s.\n", res == 0 ? "ok" : "error");
    
    /* mma7660fc_get_auto_sleep_status test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_get_auto_sleep_status test.\n");
    
    /* get auto sleep status */
    res = mma7660fc_get_auto_sleep_status(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto sleep status failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: auto sleep status is %s.\n", enable == MMA7660FC_BOOL_TRUE ? "true" : "false");
    mma7660fc_interface_debug_print("mma7660fc: check auto sleep status %s.\n", res == 0 ? "ok" : "error");
    
    /* mma7660fc_get_auto_wake_up_status test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_get_auto_wake_up_status test.\n");
    
    /* get auto wake up status */
    res = mma7660fc_get_auto_wake_up_status(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto wake up status failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: auto wake up status is %s.\n", enable == MMA7660FC_BOOL_TRUE ? "true" : "false");
    mma7660fc_interface_debug_print("mma7660fc: check auto wake up status %s.\n", res == 0 ? "ok" : "error");
    
    /* mma7660fc_set_sleep_count/mma7660fc_get_sleep_count test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_sleep_count/mma7660fc_get_sleep_count test.\n");
    
    count = rand() % 256;
    res = mma7660fc_set_sleep_count(&gs_handle, count);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set sleep count failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set sleep count %d.\n", count);
    res = mma7660fc_get_sleep_count(&gs_handle, &count_check);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get sleep count failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check sleep count %s.\n", count == count_check ? "ok" : "error");
    
    /* mma7660fc_set_front_back_interrupt/mma7660fc_get_front_back_interrupt test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_front_back_interrupt/mma7660fc_get_front_back_interrupt test.\n");
    
    /* enable front back interrupt */
    res = mma7660fc_set_front_back_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set front back interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable front back interrupt.\n");
    res = mma7660fc_get_front_back_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get front back interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check front back interrupt %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable front back interrupt */
    res = mma7660fc_set_front_back_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set front back interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable front back interrupt.\n");
    res = mma7660fc_get_front_back_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get front back interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check front back interrupt %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_up_down_right_left_interrupt/mma7660fc_get_up_down_right_left_interrupt test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_up_down_right_left_interrupt/mma7660fc_get_up_down_right_left_interrupt test.\n");
    
    /* enable up down right left interrupt */
    res = mma7660fc_set_up_down_right_left_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set up down right left interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable up down right left interrupt.\n");
    res = mma7660fc_get_up_down_right_left_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get up down right left interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check up down right left interrupt %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable up down right left interrupt */
    res = mma7660fc_set_up_down_right_left_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set up down right left interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable up down right left interrupt.\n");
    res = mma7660fc_get_up_down_right_left_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get up down right left interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check up down right left interrupt %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_tap_interrupt/mma7660fc_get_tap_interrupt test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_tap_interrupt/mma7660fc_get_tap_interrupt test.\n");
    
    /* enable tap interrupt */
    res = mma7660fc_set_tap_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable tap interrupt.\n");
    res = mma7660fc_get_tap_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap interrupt %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable tap interrupt */
    res = mma7660fc_set_tap_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable tap interrupt.\n");
    res = mma7660fc_get_tap_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap interrupt %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_auto_sleep_interrupt/mma7660fc_get_auto_sleep_interrupt test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_auto_sleep_interrupt/mma7660fc_get_auto_sleep_interrupt test.\n");
    
    /* enable auto sleep interrupt */
    res = mma7660fc_set_auto_sleep_interrupt(&gs_handle,MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable auto sleep interrupt.\n");
    res = mma7660fc_get_auto_sleep_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto sleep interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto sleep interrupt %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable auto sleep interrupt */
    res = mma7660fc_set_auto_sleep_interrupt(&gs_handle,MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable auto sleep interrupt.\n");
    res = mma7660fc_get_auto_sleep_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto sleep interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto sleep interrupt %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_update_interrupt/mma7660fc_get_update_interrupt test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_update_interrupt/mma7660fc_get_update_interrupt test.\n");
    
    /* enable update interrupt */
    res = mma7660fc_set_update_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set update interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable update interrupt.\n");
    res = mma7660fc_get_update_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get update interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check update interrupt %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable update interrupt */
    res = mma7660fc_set_update_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set update interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable update interrupt.\n");
    res = mma7660fc_get_update_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get update interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check update interrupt %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_shake_x_interrupt/mma7660fc_get_shake_x_interrupt test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_shake_x_interrupt/mma7660fc_get_shake_x_interrupt test.\n");
    
    /* enable shake x interrupt */
    res = mma7660fc_set_shake_x_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake x interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable shake x interrupt.\n");
    res = mma7660fc_get_shake_x_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get shake x interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check shake x interrupt %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable shake x interrupt */
    res = mma7660fc_set_shake_x_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake x interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable shake x interrupt.\n");
    res = mma7660fc_get_shake_x_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get shake x interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check shake x interrupt %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_shake_y_interrupt/mma7660fc_get_shake_y_interrupt test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_shake_y_interrupt/mma7660fc_get_shake_y_interrupt test.\n");
    
    /* enable shake y interrupt */
    res = mma7660fc_set_shake_y_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake y interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable shake y interrupt.\n");
    res = mma7660fc_get_shake_y_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get shake y interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check shake y interrupt %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable shake y interrupt */
    res = mma7660fc_set_shake_y_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake y interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable shake y interrupt.\n");
    res = mma7660fc_get_shake_y_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get shake y interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check shake y interrupt %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_shake_z_interrupt/mma7660fc_get_shake_z_interrupt test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_shake_z_interrupt/mma7660fc_get_shake_z_interrupt test.\n");
    
    /* enable shake z interrupt */
    res = mma7660fc_set_shake_z_interrupt(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake z interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable shake z interrupt.\n");
    res = mma7660fc_get_shake_z_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get shake z interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check shake z interrupt %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable shake z interrupt */
    res = mma7660fc_set_shake_z_interrupt(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake z interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable shake z interrupt.\n");
    res = mma7660fc_get_shake_z_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get shake z interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check shake z interrupt %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_mode/mma7660fc_get_mode test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_mode/mma7660fc_get_mode test.\n");
    
    /* set mode test */
    res = mma7660fc_set_mode(&gs_handle, MMA7660FC_MODE_TEST);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set mode failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set mode test.\n");
    res = mma7660fc_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get mode failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check mode %s.\n", mode == MMA7660FC_MODE_TEST ? "ok" : "error");
    
    /* set mode standby */
    res = mma7660fc_set_mode(&gs_handle, MMA7660FC_MODE_STANDBY);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set mode failed.\n");
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
    mma7660fc_interface_debug_print("mma7660fc: set mode active.\n");
    res = mma7660fc_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get mode failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check mode %s.\n", mode == MMA7660FC_MODE_ACTIVE ? "ok" : "error");
    
    /* set mode standby */
    res = mma7660fc_set_mode(&gs_handle, MMA7660FC_MODE_STANDBY);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set mode failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set mode standby.\n");
    res = mma7660fc_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get mode failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check mode %s.\n", mode == MMA7660FC_MODE_STANDBY ? "ok" : "error");
    
    /* mma7660fc_set_auto_wake_up/mma7660fc_get_auto_wake_up test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_auto_wake_up/mma7660fc_get_auto_wake_up test.\n");
    
    /* enable auto wake up */
    res = mma7660fc_set_auto_wake_up(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake up failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable auto wake up.\n");
    res = mma7660fc_get_auto_wake_up(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto wake up failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto wake up %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable auto wake up */
    res = mma7660fc_set_auto_wake_up(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake up failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable auto wake up.\n");
    res = mma7660fc_get_auto_wake_up(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto wake up failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto wake up %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_auto_sleep/mma7660fc_get_auto_sleep test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_auto_sleep/mma7660fc_get_auto_sleep test.\n");
    
    /* enable auto sleep */
    res = mma7660fc_set_auto_sleep(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable auto sleep.\n");
    res = mma7660fc_get_auto_sleep(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto sleep failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto sleep %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable auto sleep */
    res = mma7660fc_set_auto_sleep(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable auto sleep.\n");
    res = mma7660fc_get_auto_sleep(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto sleep failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto sleep %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_sleep_counter_prescaler/mma7660fc_get_sleep_counter_prescaler test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_sleep_counter_prescaler/mma7660fc_get_sleep_counter_prescaler test.\n");
    
    /* set sleep counter prescaler 1 */
    res = mma7660fc_set_sleep_counter_prescaler(&gs_handle, MMA7660FC_SLEEP_COUNTER_PRESCALER_1);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set sleep counter prescaler failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set sleep counter prescaler 1.\n");
    res = mma7660fc_get_sleep_counter_prescaler(&gs_handle, &prescaler);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get sleep counter prescaler failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check sleep counter prescaler %s.\n", prescaler == MMA7660FC_SLEEP_COUNTER_PRESCALER_1 ? "ok" : "error");
    
    /* set sleep counter prescaler 16 */
    res = mma7660fc_set_sleep_counter_prescaler(&gs_handle, MMA7660FC_SLEEP_COUNTER_PRESCALER_16);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set sleep counter prescaler failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set sleep counter prescaler 16.\n");
    res = mma7660fc_get_sleep_counter_prescaler(&gs_handle, &prescaler);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get sleep counter prescaler failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check sleep counter prescaler %s.\n", prescaler == MMA7660FC_SLEEP_COUNTER_PRESCALER_16 ? "ok" : "error");
    
    /* mma7660fc_set_interrupt_pin_type/mma7660fc_get_interrupt_pin_type test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_interrupt_pin_type/mma7660fc_get_interrupt_pin_type test.\n");
    
    /* set interrupt pin type open drain */
    res = mma7660fc_set_interrupt_pin_type(&gs_handle, MMA7660FC_INTERRUPT_PIN_TYPE_OPEN_DRAIN);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set interrupt pin type failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set interrupt pin type open drain.\n");
    res = mma7660fc_get_interrupt_pin_type(&gs_handle, &type);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get interrupt pin type failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check interrupt pin type %s.\n", type == MMA7660FC_INTERRUPT_PIN_TYPE_OPEN_DRAIN ? "ok" : "error");
    
    /* set interrupt pin type push-pull */
    res = mma7660fc_set_interrupt_pin_type(&gs_handle, MMA7660FC_INTERRUPT_PIN_TYPE_PUSH_PULL);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set interrupt pin type failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set interrupt pin type push pull.\n");
    res = mma7660fc_get_interrupt_pin_type(&gs_handle, &type);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get interrupt pin type failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check interrupt pin type %s.\n", type == MMA7660FC_INTERRUPT_PIN_TYPE_PUSH_PULL ? "ok" : "error");
    
    /* mma7660fc_set_interrupt_active_level/mma7660fc_get_interrupt_active_level test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_interrupt_active_level/mma7660fc_get_interrupt_active_level test.\n");
    
    /* set interrupt active level low */
    res = mma7660fc_set_interrupt_active_level(&gs_handle, MMA7660FC_INTERRUPT_ACTIVE_LEVEL_LOW);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set interrupt active level failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set interrupt active level low.\n");
    res = mma7660fc_get_interrupt_active_level(&gs_handle, &level);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get interrupt active level failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check interrupt active level %s.\n", level == MMA7660FC_INTERRUPT_ACTIVE_LEVEL_LOW ? "ok" : "error");
    
    /* set interrupt active level high */
    res = mma7660fc_set_interrupt_active_level(&gs_handle, MMA7660FC_INTERRUPT_ACTIVE_LEVEL_HIGH);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set interrupt active level failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set interrupt active level high.\n");
    res = mma7660fc_get_interrupt_active_level(&gs_handle, &level);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get interrupt active level failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check interrupt active level %s.\n", level == MMA7660FC_INTERRUPT_ACTIVE_LEVEL_HIGH ? "ok" : "error");
    
    /* mma7660fc_set_tap_detection_rate/mma7660fc_get_tap_detection_rate test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_tap_detection_rate/mma7660fc_get_tap_detection_rate test.\n");
    
    /* set tap detection rate 120 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_120);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection rate 120.\n");
    res = mma7660fc_get_tap_detection_rate(&gs_handle, &sleep_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection rate %s.\n", sleep_rate == MMA7660FC_AUTO_SLEEP_RATE_120 ? "ok" : "error");
    
    /* set tap detection rate 64 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_64);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection rate 64.\n");
    res = mma7660fc_get_tap_detection_rate(&gs_handle, &sleep_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection rate %s.\n", sleep_rate == MMA7660FC_AUTO_SLEEP_RATE_64 ? "ok" : "error");
    
    /* set tap detection rate 32 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_32);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection rate 32.\n");
    res = mma7660fc_get_tap_detection_rate(&gs_handle, &sleep_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection rate %s.\n", sleep_rate == MMA7660FC_AUTO_SLEEP_RATE_32 ? "ok" : "error");
    
    /* set tap detection rate 16 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_16);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection rate 16.\n");
    res = mma7660fc_get_tap_detection_rate(&gs_handle, &sleep_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection rate %s.\n", sleep_rate == MMA7660FC_AUTO_SLEEP_RATE_16 ? "ok" : "error");
    
    /* set tap detection rate 8 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_8);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection rate 8.\n");
    res = mma7660fc_get_tap_detection_rate(&gs_handle, &sleep_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection rate %s.\n", sleep_rate == MMA7660FC_AUTO_SLEEP_RATE_8 ? "ok" : "error");
    
    /* set tap detection rate 4 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_4);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection rate 4.\n");
    res = mma7660fc_get_tap_detection_rate(&gs_handle, &sleep_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection rate %s.\n", sleep_rate == MMA7660FC_AUTO_SLEEP_RATE_4 ? "ok" : "error");
    
    /* set tap detection rate 2 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_2);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection rate 2.\n");
    res = mma7660fc_get_tap_detection_rate(&gs_handle, &sleep_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection rate %s.\n", sleep_rate == MMA7660FC_AUTO_SLEEP_RATE_2 ? "ok" : "error");
    
    /* set tap detection rate 1 */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_AUTO_SLEEP_RATE_1);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection rate 1.\n");
    res = mma7660fc_get_tap_detection_rate(&gs_handle, &sleep_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection rate %s.\n", sleep_rate == MMA7660FC_AUTO_SLEEP_RATE_1 ? "ok" : "error");
    
    /* mma7660fc_set_auto_wake_rate/mma7660fc_get_auto_wake_rate test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_auto_wake_rate/mma7660fc_get_auto_wake_rate test.\n");
    
    /* set auto wake rate 32 */
    res = mma7660fc_set_auto_wake_rate(&gs_handle, MMA7660FC_AUTO_WAKE_RATE_32);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set auto wake rate 32.\n");
    res = mma7660fc_get_auto_wake_rate(&gs_handle, &wake_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto wake rate %s.\n", wake_rate == MMA7660FC_AUTO_WAKE_RATE_32 ? "ok" : "error");
    
    /* set auto wake rate 16 */
    res = mma7660fc_set_auto_wake_rate(&gs_handle, MMA7660FC_AUTO_WAKE_RATE_16);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set auto wake rate 16.\n");
    res = mma7660fc_get_auto_wake_rate(&gs_handle, &wake_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto wake rate %s.\n", wake_rate == MMA7660FC_AUTO_WAKE_RATE_16 ? "ok" : "error");
    
    /* set auto wake rate 8 */
    res = mma7660fc_set_auto_wake_rate(&gs_handle, MMA7660FC_AUTO_WAKE_RATE_8);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set auto wake rate 8.\n");
    res = mma7660fc_get_auto_wake_rate(&gs_handle, &wake_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto wake rate %s.\n", wake_rate == MMA7660FC_AUTO_WAKE_RATE_8 ? "ok" : "error");
    
    /* set auto wake rate 1 */
    res = mma7660fc_set_auto_wake_rate(&gs_handle, MMA7660FC_AUTO_WAKE_RATE_1);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set auto wake rate 1.\n");
    res = mma7660fc_get_auto_wake_rate(&gs_handle, &wake_rate);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check auto wake rate %s.\n", wake_rate == MMA7660FC_AUTO_WAKE_RATE_1 ? "ok" : "error");
    
    /* mma7660fc_set_tilt_debounce_filter/mma7660fc_get_tilt_debounce_filter test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_tilt_debounce_filter/mma7660fc_get_tilt_debounce_filter test.\n");
    
    /* set tilt debounce filter disabled */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_DISABLE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter disabled.\n");
    res = mma7660fc_get_tilt_debounce_filter(&gs_handle, &filter);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tilt debounce filter %s.\n", filter == MMA7660FC_TILT_DEBOUNCE_FILTER_DISABLE ? "ok" : "error");
    
    /* set tilt debounce filter 2 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_2);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter 2.\n");
    res = mma7660fc_get_tilt_debounce_filter(&gs_handle, &filter);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tilt debounce filter %s.\n", filter == MMA7660FC_TILT_DEBOUNCE_FILTER_2 ? "ok" : "error");
    
    /* set tilt debounce filter 3 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_3);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter 3.\n");
    res = mma7660fc_get_tilt_debounce_filter(&gs_handle, &filter);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tilt debounce filter %s.\n", filter == MMA7660FC_TILT_DEBOUNCE_FILTER_3 ? "ok" : "error");
    
    /* set tilt debounce filter 4 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_4);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter 4.\n");
    res = mma7660fc_get_tilt_debounce_filter(&gs_handle, &filter);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tilt debounce filter %s.\n", filter == MMA7660FC_TILT_DEBOUNCE_FILTER_4 ? "ok" : "error");
    
    /* set tilt debounce filter 5 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_5);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter 5.\n");
    res = mma7660fc_get_tilt_debounce_filter(&gs_handle, &filter);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tilt debounce filter %s.\n", filter == MMA7660FC_TILT_DEBOUNCE_FILTER_5 ? "ok" : "error");
    
    /* set tilt debounce filter 6 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_6);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter 6.\n");
    res = mma7660fc_get_tilt_debounce_filter(&gs_handle, &filter);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tilt debounce filter %s.\n", filter == MMA7660FC_TILT_DEBOUNCE_FILTER_6 ? "ok" : "error");
    
    /* set tilt debounce filter 7 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_7);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter 7.\n");
    res = mma7660fc_get_tilt_debounce_filter(&gs_handle, &filter);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tilt debounce filter %s.\n", filter == MMA7660FC_TILT_DEBOUNCE_FILTER_7 ? "ok" : "error");
    
    /* set tilt debounce filter 8 */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_TILT_DEBOUNCE_FILTER_8);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter 8.\n");
    res = mma7660fc_get_tilt_debounce_filter(&gs_handle, &filter);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tilt debounce filter %s.\n", filter == MMA7660FC_TILT_DEBOUNCE_FILTER_8 ? "ok" : "error");
    
    /* mma7660fc_set_tap_detection_threshold/mma7660fc_get_tap_detection_threshold test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_tap_detection_threshold/mma7660fc_get_tap_detection_threshold test.\n");
    
    threshold = rand() % 32;
    res = mma7660fc_set_tap_detection_threshold(&gs_handle, threshold);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection threshold failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap detection threshold %d.\n", threshold);
    res = mma7660fc_get_tap_detection_threshold(&gs_handle, &threshold_check);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap detection threshold failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap detection threshold %s.\n", threshold == threshold_check ? "ok" : "error");
    
    /* mma7660fc_set_tap_x_detection/mma7660fc_get_tap_x_detection test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_tap_x_detection/mma7660fc_get_tap_x_detection test.\n");
    
    /* enable tap x detection */
    res = mma7660fc_set_tap_x_detection(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap x detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable tap x detection.\n");
    res = mma7660fc_get_tap_x_detection(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap x detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap x detection %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable tap x detection */
    res = mma7660fc_set_tap_x_detection(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap x detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable tap x detection.\n");
    res = mma7660fc_get_tap_x_detection(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap x detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap x detection %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* enable tap y detection */
    res = mma7660fc_set_tap_y_detection(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap y detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable tap y detection.\n");
    res = mma7660fc_get_tap_y_detection(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap y detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap y detection %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable tap y detection */
    res = mma7660fc_set_tap_y_detection(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap y detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable tap y detection.\n");
    res = mma7660fc_get_tap_y_detection(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap y detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap y detection %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* enable tap z detection */
    res = mma7660fc_set_tap_z_detection(&gs_handle, MMA7660FC_BOOL_TRUE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap z detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: enable tap z detection.\n");
    res = mma7660fc_get_tap_z_detection(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap z detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap z detection %s.\n", enable == MMA7660FC_BOOL_TRUE ? "ok" : "error");
    
    /* disable tap z detection */
    res = mma7660fc_set_tap_z_detection(&gs_handle, MMA7660FC_BOOL_FALSE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap z detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: disable tap z detection.\n");
    res = mma7660fc_get_tap_z_detection(&gs_handle, &enable);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap z detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap z detection %s.\n", enable == MMA7660FC_BOOL_FALSE ? "ok" : "error");
    
    /* mma7660fc_set_tap_pulse_debounce_count/mma7660fc_get_tap_pulse_debounce_count test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_set_tap_pulse_debounce_count/mma7660fc_get_tap_pulse_debounce_count test.\n");
    
    count = rand() % 256;
    res = mma7660fc_set_tap_pulse_debounce_count(&gs_handle, count);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap pulse debounce count failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: set tap pulse debounce count %d.\n", count);
    res = mma7660fc_get_tap_pulse_debounce_count(&gs_handle, &count_check);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: get tap pulse debounce count failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap pulse debounce count %s.\n", count == count_check ? "ok" : "error");
    
    /* mma7660fc_tap_pulse_debounce_convert_to_register/mma7660fc_tap_pulse_debounce_convert_to_data test */
    mma7660fc_interface_debug_print("mma7660fc: mma7660fc_tap_pulse_debounce_convert_to_register/mma7660fc_tap_pulse_debounce_convert_to_data test.\n");
    
    ms = (float)(rand() % 100) / 10.0f;
    res = mma7660fc_tap_pulse_debounce_convert_to_register(&gs_handle, ms, &reg);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: tap pulse debounce convert to register failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: tap pulse debounce %0.2fms.\n", ms);
    res = mma7660fc_tap_pulse_debounce_convert_to_data(&gs_handle, reg, &ms_check);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: tap pulse debounce convert to data failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    mma7660fc_interface_debug_print("mma7660fc: check tap pulse debounce %0.2fms.\n", ms_check);
    
    /* finish register test */
    mma7660fc_interface_debug_print("mma7660fc: finish register test.\n");
    (void)mma7660fc_deinit(&gs_handle); 

    return 0;
}
