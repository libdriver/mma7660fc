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
 * @file      driver_mma7660fc_motion.c
 * @brief     driver mma7660fc motion source file
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

#include "driver_mma7660fc_motion.h"

static mma7660fc_handle_t gs_handle;        /**< mma7660fc handle */

/**
 * @brief  motion irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t mma7660fc_motion_irq_handler(void)
{
    if (mma7660fc_irq_handler(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief     motion example init
 * @param[in] *callback pointer to a callback address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t mma7660fc_motion_init(void (*callback)(uint8_t type))
{
    uint8_t res;
    uint8_t count;
    
    /* link interface function */
    DRIVER_MMA7660FC_LINK_INIT(&gs_handle, mma7660fc_handle_t); 
    DRIVER_MMA7660FC_LINK_IIC_INIT(&gs_handle, mma7660fc_interface_iic_init);
    DRIVER_MMA7660FC_LINK_IIC_DEINIT(&gs_handle, mma7660fc_interface_iic_deinit);
    DRIVER_MMA7660FC_LINK_IIC_READ(&gs_handle, mma7660fc_interface_iic_read);
    DRIVER_MMA7660FC_LINK_IIC_WRITE(&gs_handle, mma7660fc_interface_iic_write);
    DRIVER_MMA7660FC_LINK_DELAY_MS(&gs_handle, mma7660fc_interface_delay_ms);
    DRIVER_MMA7660FC_LINK_DEBUG_PRINT(&gs_handle, mma7660fc_interface_debug_print);
    DRIVER_MMA7660FC_LINK_RECEIVE_CALLBACK(&gs_handle, callback);
    
    /* mma7660fc init */
    res = mma7660fc_init(&gs_handle);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: init failed.\n");
        
        return 1;
    }
    
    /* set default front back interrupt */
    res = mma7660fc_set_front_back_interrupt(&gs_handle, MMA7660FC_MOTION_DEFAULT_FRONT_BACK_INTERRUPT);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set front back interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default up down right left interrupt */
    res = mma7660fc_set_up_down_right_left_interrupt(&gs_handle, MMA7660FC_MOTION_DEFAULT_UP_DOWN_RIGHT_LEFT_INTERRUPT);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set up down right left interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default tap interrupt */
    res = mma7660fc_set_tap_interrupt(&gs_handle, MMA7660FC_MOTION_DEFAULT_TAP_INTERRUPT);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default auto sleep interrupt */
    res = mma7660fc_set_auto_sleep_interrupt(&gs_handle, MMA7660FC_MOTION_DEFAULT_AUTO_SLEEP_INTERRUPT);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default update interrupt */
    res = mma7660fc_set_update_interrupt(&gs_handle, MMA7660FC_MOTION_DEFAULT_UPDATE_INTERRUPT);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set update interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default shake x interrupt */
    res = mma7660fc_set_shake_x_interrupt(&gs_handle, MMA7660FC_MOTION_DEFAULT_SHAKE_X);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake x interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default shake y interrupt */
    res = mma7660fc_set_shake_y_interrupt(&gs_handle, MMA7660FC_MOTION_DEFAULT_SHAKE_Y);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake y interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default shake z interrupt */
    res = mma7660fc_set_shake_z_interrupt(&gs_handle, MMA7660FC_MOTION_DEFAULT_SHAKE_Z);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set shake z interrupt failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default sleep counter prescaler */
    res = mma7660fc_set_sleep_counter_prescaler(&gs_handle, MMA7660FC_MOTION_DEFAULT_SLEEP_COUNTER_PRESCALER);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set sleep counter prescaler failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default tap detection rate */
    res = mma7660fc_set_tap_detection_rate(&gs_handle, MMA7660FC_MOTION_DEFAULT_AUTO_SLEEP_RATE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default auto wake rate */
    res = mma7660fc_set_auto_wake_rate(&gs_handle, MMA7660FC_MOTION_DEFAULT_AUTO_WAKE_RATE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake rate failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default sleep count */
    res = mma7660fc_set_sleep_count(&gs_handle, MMA7660FC_MOTION_DEFAULT_SLEEP_COUNT);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set sleep count failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default auto wake up */
    res = mma7660fc_set_auto_wake_up(&gs_handle, MMA7660FC_MOTION_DEFAULT_AUTO_WAKE_UP);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto wake up failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default auto sleep */
    res = mma7660fc_set_auto_sleep(&gs_handle, MMA7660FC_MOTION_DEFAULT_AUTO_SLEEP);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set auto sleep failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default interrupt pin type */
    res = mma7660fc_set_interrupt_pin_type(&gs_handle, MMA7660FC_MOTION_DEFAULT_INTERRUPT_PIN_TYPE);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set interrupt pin type failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default interrupt active level */
    res = mma7660fc_set_interrupt_active_level(&gs_handle, MMA7660FC_MOTION_DEFAULT_INTERRUPT_ACTIVE_LEVEL);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set interrupt active level failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default tilt debounce filter */
    res = mma7660fc_set_tilt_debounce_filter(&gs_handle, MMA7660FC_MOTION_DEFAULT_TILT_DEBOUNCE_FILTER);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tilt debounce filter failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default tap detection threshold */
    res = mma7660fc_set_tap_detection_threshold(&gs_handle, MMA7660FC_MOTION_DEFAULT_TAP_DETECTION_THRESHOLD);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap detection threshold failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default tap x detection */
    res = mma7660fc_set_tap_x_detection(&gs_handle, MMA7660FC_MOTION_DEFAULT_TAP_X);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap x detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default tap y detection */
    res = mma7660fc_set_tap_y_detection(&gs_handle, MMA7660FC_MOTION_DEFAULT_TAP_Y);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap y detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default tap z detection */
    res = mma7660fc_set_tap_z_detection(&gs_handle, MMA7660FC_MOTION_DEFAULT_TAP_Z);
    if (res != 0)
    {
        mma7660fc_interface_debug_print("mma7660fc: set tap z detection failed.\n");
        (void)mma7660fc_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set default tap pulse debounce */
    res = mma7660fc_tap_pulse_debounce_convert_to_register(&gs_handle, MMA7660FC_MOTION_DEFAULT_TAP_PULSE_DEBOUNCE, &count);
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
    
    return 0;
}

/**
 * @brief      motion example read
 * @param[out] *g pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t mma7660fc_motion_read(float g[3])
{
    uint8_t res;
    int8_t raw[3];
    
    res = mma7660fc_read(&gs_handle, raw, g);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  motion example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mma7660fc_motion_deinit(void)
{
    /* close mma7660fc */
    if (mma7660fc_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
