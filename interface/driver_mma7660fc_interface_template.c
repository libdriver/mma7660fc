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
 * @file      driver_mma7660fc_interface_template.c
 * @brief     driver mma7660fc interface template source file
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

#include "driver_mma7660fc_interface.h"

/**
 * @brief  interface iic bus init
 * @return status code
 *         - 0 success
 *         - 1 iic init failed
 * @note   none
 */
uint8_t mma7660fc_interface_iic_init(void)
{
    return 0;
}

/**
 * @brief  interface iic bus deinit
 * @return status code
 *         - 0 success
 *         - 1 iic deinit failed
 * @note   none
 */
uint8_t mma7660fc_interface_iic_deinit(void)
{
    return 0;
}

/**
 * @brief      interface iic bus read
 * @param[in]  addr iic device write address
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len length of the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t mma7660fc_interface_iic_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return 0;
}

/**
 * @brief     interface iic bus write
 * @param[in] addr iic device write address
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len length of the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t mma7660fc_interface_iic_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms time
 * @note      none
 */
void mma7660fc_interface_delay_ms(uint32_t ms)
{

}

/**
 * @brief     interface print format data
 * @param[in] fmt format data
 * @note      none
 */
void mma7660fc_interface_debug_print(const char *const fmt, ...)
{
    
}

/**
 * @brief     interface receive callback
 * @param[in] type irq type
 * @note      none
 */
void mma7660fc_interface_receive_callback(uint8_t type)
{
    switch (type)
    {
        case MMA7660FC_STATUS_FRONT :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq front.\n");
            
            break;
        }
        case MMA7660FC_STATUS_BACK :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq back.\n");
            
            break;
        }
        case MMA7660FC_STATUS_LEFT :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq left.\n");
            
            break;
        }
        case MMA7660FC_STATUS_RIGHT :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq right.\n");
            
            break;
        }
        case MMA7660FC_STATUS_DOWN :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq down.\n");
            
            break;
        }
        case MMA7660FC_STATUS_UP :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq up.\n");
            
            break;
        }
        case MMA7660FC_STATUS_TAP :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq tap.\n");
            
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
            
            break;
        }
        case MMA7660FC_STATUS_AUTO_SLEEP :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq auto sleep.\n");
            
            break;
        }
        case MMA7660FC_STATUS_AUTO_WAKE_UP :
        {
            mma7660fc_interface_debug_print("mma7660fc: irq auto wake up.\n");
            
            break;
        }
        default :
        {
            mma7660fc_interface_debug_print("mma7660fc: unknown code.\n");
            
            break;
        }
    }
}
