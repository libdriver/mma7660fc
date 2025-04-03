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
 * @file      driver_mma7660fc.h
 * @brief     driver mma7660fc header file
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

#ifndef DRIVER_MMA7660FC_H
#define DRIVER_MMA7660FC_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup mma7660fc_driver mma7660fc driver function
 * @brief    mma7660fc driver modules
 * @{
 */

/**
 * @addtogroup mma7660fc_base_driver
 * @{
 */

/**
 * @brief mma7660fc bool enumeration definition
 */
typedef enum
{
    MMA7660FC_BOOL_FALSE = 0x00,        /**< disable */
    MMA7660FC_BOOL_TRUE  = 0x01,        /**< enable */
} mma7660fc_bool_t;

/**
 * @brief mma7660fc status enumeration definition
 */
typedef enum
{
    MMA7660FC_STATUS_FRONT        = 0x00,        /**< equipment is lying on its front */
    MMA7660FC_STATUS_BACK         = 0x01,        /**< equipment is lying on its back */
    MMA7660FC_STATUS_LEFT         = 0x02,        /**< equipment is landscape mode to the left */
    MMA7660FC_STATUS_RIGHT        = 0x03,        /**< equipment is landscape mode to the right */
    MMA7660FC_STATUS_DOWN         = 0x04,        /**< equipment is standing vertically in inverted orientation */
    MMA7660FC_STATUS_UP           = 0x05,        /**< equipment is standing vertically in normal orientation */
    MMA7660FC_STATUS_TAP          = 0x06,        /**< equipment has detected a tap */
    MMA7660FC_STATUS_UPDATE       = 0x07,        /**< register data is invalid */
    MMA7660FC_STATUS_SHAKE        = 0x08,        /**< equipment is experiencing shake in one or more of the axes */
    MMA7660FC_STATUS_AUTO_SLEEP   = 0x09,        /**< auto sleep */
    MMA7660FC_STATUS_AUTO_WAKE_UP = 0x0A,        /**< auto wake up */
} mma7660fc_status_t;

/**
 * @brief mma7660fc mode enumeration definition
 */
typedef enum
{
    MMA7660FC_MODE_STANDBY = 0x00,        /**< standby mode */
    MMA7660FC_MODE_TEST    = 0x04,        /**< test mode */
    MMA7660FC_MODE_ACTIVE  = 0x01,        /**< active mode */
} mma7660fc_mode_t;

/**
 * @brief mma7660fc sleep counter prescaler enumeration definition
 */
typedef enum
{
    MMA7660FC_SLEEP_COUNTER_PRESCALER_1  = 0x00,        /**< divide-by-1 */
    MMA7660FC_SLEEP_COUNTER_PRESCALER_16 = 0x01,        /**< divide-by-16 */
} mma7660fc_sleep_counter_prescaler_t;

/**
 * @brief mma7660fc interrupt pin type enumeration definition
 */
typedef enum
{
    MMA7660FC_INTERRUPT_PIN_TYPE_OPEN_DRAIN = 0x00,        /**< open drain */
    MMA7660FC_INTERRUPT_PIN_TYPE_PUSH_PULL  = 0x01,        /**< push-pull */
} mma7660fc_interrupt_pin_type_t;

/**
 * @brief mma7660fc interrupt active level enumeration definition
 */
typedef enum
{
    MMA7660FC_INTERRUPT_ACTIVE_LEVEL_LOW  = 0x00,        /**< active low */
    MMA7660FC_INTERRUPT_ACTIVE_LEVEL_HIGH = 0x01,        /**< active high */
} mma7660fc_interrupt_active_level_t;

/**
 * @brief mma7660fc auto sleep rate enumeration definition
 *
 *  AUTO_SLEEP_RATE    SLEEP_COUNTER_PRESCALER_1    SLEEP_COUNTER_PRESCALER_16
 *                        minimum     maximum           minimum     maximum
 * AUTO_SLEEP_RATE_1      1s          256s              16s         4096s
 * AUTO_SLEEP_RATE_2      0.5s        128s              8s          2048s
 * AUTO_SLEEP_RATE_4      0.25s       64s               4s          1024s
 * AUTO_SLEEP_RATE_8      0.125s      32s               2s          512s
 * AUTO_SLEEP_RATE_16     0.0625s     16s               1s          256s
 * AUTO_SLEEP_RATE_32     0.03125s    8s                0.5s        128s
 * AUTO_SLEEP_RATE_64     0.01560s    4s                0.25s       64s
 * AUTO_SLEEP_RATE_120    0.00836s    2s                0.133s      34.24s
 */
typedef enum
{
    MMA7660FC_AUTO_SLEEP_RATE_120 = 0x00,        /**< 120 samples/second */
    MMA7660FC_AUTO_SLEEP_RATE_64  = 0x01,        /**< 64 samples/second */
    MMA7660FC_AUTO_SLEEP_RATE_32  = 0x02,        /**< 32 samples/second */
    MMA7660FC_AUTO_SLEEP_RATE_16  = 0x03,        /**< 16 samples/second */
    MMA7660FC_AUTO_SLEEP_RATE_8   = 0x04,        /**< 8 samples/second */
    MMA7660FC_AUTO_SLEEP_RATE_4   = 0x05,        /**< 4 samples/second */
    MMA7660FC_AUTO_SLEEP_RATE_2   = 0x06,        /**< 2 samples/second */
    MMA7660FC_AUTO_SLEEP_RATE_1   = 0x07,        /**< 1 samples/second */
} mma7660fc_auto_sleep_rate_t;

/**
 * @brief mma7660fc auto wake rate enumeration definition
 *
 *     WAKE_RATE         TIME
 * AUTO_WAKE_RATE_32    31.25ms
 * AUTO_WAKE_RATE_16    62.5ms
 * AUTO_WAKE_RATE_8     125ms
 * AUTO_WAKE_RATE_1     1000ms
 */
typedef enum
{
    MMA7660FC_AUTO_WAKE_RATE_32 = 0x00,        /**< 32 samples/second */
    MMA7660FC_AUTO_WAKE_RATE_16 = 0x01,        /**< 16 samples/second */
    MMA7660FC_AUTO_WAKE_RATE_8  = 0x02,        /**< 8 samples/second */
    MMA7660FC_AUTO_WAKE_RATE_1  = 0x03,        /**< 1 samples/second */
} mma7660fc_auto_wake_rate_t;

/**
 * @brief mma7660fc tilt debounce filter enumeration definition
 */
typedef enum
{
    MMA7660FC_TILT_DEBOUNCE_FILTER_DISABLE = 0x00,        /**< disabled */
    MMA7660FC_TILT_DEBOUNCE_FILTER_2       = 0x01,        /**< 2 measurement samples at the rate */
    MMA7660FC_TILT_DEBOUNCE_FILTER_3       = 0x02,        /**< 3 measurement samples at the rate */
    MMA7660FC_TILT_DEBOUNCE_FILTER_4       = 0x03,        /**< 4 measurement samples at the rate */
    MMA7660FC_TILT_DEBOUNCE_FILTER_5       = 0x04,        /**< 5 measurement samples at the rate */
    MMA7660FC_TILT_DEBOUNCE_FILTER_6       = 0x05,        /**< 6 measurement samples at the rate */
    MMA7660FC_TILT_DEBOUNCE_FILTER_7       = 0x06,        /**< 7 measurement samples at the rate */
    MMA7660FC_TILT_DEBOUNCE_FILTER_8       = 0x07,        /**< 8 measurement samples at the rate */
} mma7660fc_tilt_debounce_filter_t;

/**
 * @brief mma7660fc handle structure definition
 */
typedef struct mma7660fc_handle_s
{
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*receive_callback)(uint8_t type);                                             /**< point to a receive_callback function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
} mma7660fc_handle_t;

/**
 * @brief mma7660fc information structure definition
 */
typedef struct mma7660fc_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} mma7660fc_info_t;

/**
 * @}
 */

/**
 * @defgroup mma7660fc_link_driver mma7660fc link driver function
 * @brief    mma7660fc link driver modules
 * @ingroup  mma7660fc_driver
 * @{
 */

/**
 * @brief     initialize mma7660fc_handle_t structure
 * @param[in] HANDLE pointer to a mma7660fc handle structure
 * @param[in] STRUCTURE mma7660fc_handle_t
 * @note      none
 */
#define DRIVER_MMA7660FC_LINK_INIT(HANDLE, STRUCTURE)              memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to a mma7660fc handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_MMA7660FC_LINK_IIC_INIT(HANDLE, FUC)                (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to a mma7660fc handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_MMA7660FC_LINK_IIC_DEINIT(HANDLE, FUC)              (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE pointer to a mma7660fc handle structure
 * @param[in] FUC pointer to an iic_read function address
 * @note      none
 */
#define DRIVER_MMA7660FC_LINK_IIC_READ(HANDLE, FUC)                (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to a mma7660fc handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_MMA7660FC_LINK_IIC_WRITE(HANDLE, FUC)               (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a mma7660fc handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_MMA7660FC_LINK_DELAY_MS(HANDLE, FUC)                (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a mma7660fc handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_MMA7660FC_LINK_DEBUG_PRINT(HANDLE, FUC)             (HANDLE)->debug_print = FUC

/**
 * @brief     link receive_callback function
 * @param[in] HANDLE pointer to a mma7660fc handle structure
 * @param[in] FUC pointer to a receive_callback function address
 * @note      none
 */
#define DRIVER_MMA7660FC_LINK_RECEIVE_CALLBACK(HANDLE, FUC)        (HANDLE)->receive_callback = FUC

/**
 * @}
 */

/**
 * @defgroup mma7660fc_base_driver mma7660fc base driver function
 * @brief    mma7660fc base driver modules
 * @ingroup  mma7660fc_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a mma7660fc info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mma7660fc_info(mma7660fc_info_t *info);

/**
 * @brief     irq handler
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_irq_handler(mma7660fc_handle_t *handle);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t mma7660fc_init(mma7660fc_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t mma7660fc_deinit(mma7660fc_handle_t *handle);

/**
 * @brief      read the data
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *raw pointer to a raw pressure buffer
 * @param[out] *g pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 data is invalid
 * @note       none
 */
uint8_t mma7660fc_read(mma7660fc_handle_t *handle, int8_t raw[3], float g[3]);

/**
 * @brief      get tilt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tilt_status(mma7660fc_handle_t *handle, uint8_t *status);

/**
 * @brief      get auto sleep status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto sleep status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_auto_sleep_status(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief      get auto wake up status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto wake up status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_auto_wake_up_status(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     set sleep count
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] count sleep count
 * @return    status code
 *            - 0 success
 *            - 1 set sleep count failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_sleep_count(mma7660fc_handle_t *handle, uint8_t count);

/**
 * @brief      get sleep count
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *count pointer to a count buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sleep count failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_sleep_count(mma7660fc_handle_t *handle, uint8_t *count);

/**
 * @brief     enable or disable front back interrupt
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set front back interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_front_back_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get front back interrupt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get front back interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_front_back_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable up down right left interrupt
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set up down right left interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_up_down_right_left_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get up down right left interrupt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get up down right left interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_up_down_right_left_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable tap interrupt
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set tap interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_tap_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get tap interrupt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tap_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable auto sleep interrupt
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set auto sleep interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_auto_sleep_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get auto sleep interrupt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto sleep interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_auto_sleep_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable update interrupt status
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set update interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_update_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get update interrupt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get update interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_update_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable shake x interrupt
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set shake x interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_shake_x_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get shake x interrupt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get shake x interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_shake_x_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable shake y interrupt
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set shake y interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_shake_y_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get shake y interrupt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get shake y interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_shake_y_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable shake z interrupt
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set shake z interrupt failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_shake_z_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get shake z interrupt status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get shake z interrupt failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_shake_z_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     set mode
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_mode(mma7660fc_handle_t *handle, mma7660fc_mode_t mode);

/**
 * @brief      get mode
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *mode pointer to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_mode(mma7660fc_handle_t *handle, mma7660fc_mode_t *mode);

/**
 * @brief     enable or disable auto wake up
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set auto wake up failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_auto_wake_up(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get auto wake up status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto wak up failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_auto_wake_up(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable auto sleep
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set auto sleep failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_auto_sleep(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get auto sleep status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto sleep failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_auto_sleep(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     set sleep counter prescaler
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] prescaler sleep counter prescaler
 * @return    status code
 *            - 0 success
 *            - 1 set sleep counter prescaler failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_sleep_counter_prescaler(mma7660fc_handle_t *handle, mma7660fc_sleep_counter_prescaler_t prescaler);

/**
 * @brief      get sleep counter prescaler
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *prescaler pointer to a sleep counter prescaler buffer
 * @return     status code
 *             - 0 success
 *             - 1 get sleep counter prescaler failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_sleep_counter_prescaler(mma7660fc_handle_t *handle, mma7660fc_sleep_counter_prescaler_t *prescaler);

/**
 * @brief     set interrupt pin type
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] type interrupt pin type
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt pin type failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_interrupt_pin_type(mma7660fc_handle_t *handle, mma7660fc_interrupt_pin_type_t type);

/**
 * @brief      get interrupt pin type
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *type pointer to an interrupt pin type buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt pin type failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_interrupt_pin_type(mma7660fc_handle_t *handle, mma7660fc_interrupt_pin_type_t *type);

/**
 * @brief     set interrupt active level
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] level interrupt active level
 * @return    status code
 *            - 0 success
 *            - 1 set interrupt active level failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_interrupt_active_level(mma7660fc_handle_t *handle, mma7660fc_interrupt_active_level_t level);

/**
 * @brief      get interrupt active level
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *level pointer to an interrupt active level buffer
 * @return     status code
 *             - 0 success
 *             - 1 get interrupt active level failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_interrupt_active_level(mma7660fc_handle_t *handle, mma7660fc_interrupt_active_level_t *level);

/**
 * @brief     set tap detection rate
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] rate tap detection rate
 * @return    status code
 *            - 0 success
 *            - 1 set tap detection rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_tap_detection_rate(mma7660fc_handle_t *handle, mma7660fc_auto_sleep_rate_t rate);

/**
 * @brief      get tap detection rate
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *rate pointer to a tap detection rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap detection rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tap_detection_rate(mma7660fc_handle_t *handle, mma7660fc_auto_sleep_rate_t *rate);

/**
 * @brief     set auto wake rate
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] rate auto wake rate
 * @return    status code
 *            - 0 success
 *            - 1 set auto wake rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_auto_wake_rate(mma7660fc_handle_t *handle, mma7660fc_auto_wake_rate_t rate);

/**
 * @brief      get auto wake rate
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *rate pointer to an auto wake rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get auto wake rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_auto_wake_rate(mma7660fc_handle_t *handle, mma7660fc_auto_wake_rate_t *rate);

/**
 * @brief     set tilt debounce filter
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] filter tilt debounce filter
 * @return    status code
 *            - 0 success
 *            - 1 set tilt debounce filter failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_tilt_debounce_filter(mma7660fc_handle_t *handle, mma7660fc_tilt_debounce_filter_t filter);

/**
 * @brief      get tilt debounce filter
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *filter pointer to a tilt debounce filter buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tilt debounce filter failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tilt_debounce_filter(mma7660fc_handle_t *handle, mma7660fc_tilt_debounce_filter_t *filter);

/**
 * @brief     set tap detection threshold
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] threshold tap detection threshold
 * @return    status code
 *            - 0 success
 *            - 1 set tap detection threshold failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 threshold > 31
 * @note      0 <= threshold <= 31
 */
uint8_t mma7660fc_set_tap_detection_threshold(mma7660fc_handle_t *handle, uint8_t threshold);

/**
 * @brief      get tap detection threshold
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *threshold pointer to a tap detection threshold buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap detection threshold failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tap_detection_threshold(mma7660fc_handle_t *handle, uint8_t *threshold);

/**
 * @brief     enable or disable tap x detection
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set tap x detection failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_tap_x_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get tap x detection status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap x detection failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tap_x_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable tap y detection
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set tap y detection failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_tap_y_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get tap y detection status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap y detection failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tap_y_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     enable or disable tap z detection
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set tap z detection failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_tap_z_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t enable);

/**
 * @brief      get tap z detection status
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap z detection failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tap_z_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable);

/**
 * @brief     set tap pulse debounce count
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] count tap pulse debounce count
 * @return    status code
 *            - 0 success
 *            - 1 set tap pulse debounce count failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_tap_pulse_debounce_count(mma7660fc_handle_t *handle, uint8_t count);

/**
 * @brief      get tap pulse debounce count
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[out] *count pointer to a tap pulse debounce count buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tap pulse debounce count failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_tap_pulse_debounce_count(mma7660fc_handle_t *handle, uint8_t *count);

/**
 * @brief      convert tap pulse debounce to the register raw data
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[in]  ms time in ms
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_tap_pulse_debounce_convert_to_register(mma7660fc_handle_t *handle, float ms, uint8_t *reg);

/**
 * @brief      convert the register raw data to tap pulse debounce
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[in]  reg register raw data
 * @param[out] *ms pointer to a time buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_tap_pulse_debounce_convert_to_data(mma7660fc_handle_t *handle, uint8_t reg, float *ms);

/**
 * @}
 */

/**
 * @defgroup mma7660fc_extend_driver mma7660fc extend driver function
 * @brief    mma7660fc extend driver modules
 * @ingroup  mma7660fc_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t mma7660fc_set_reg(mma7660fc_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t mma7660fc_get_reg(mma7660fc_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
