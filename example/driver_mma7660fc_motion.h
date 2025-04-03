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
 * @file      driver_mma7660fc_motion.h
 * @brief     driver mma7660fc motion header file
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

#ifndef DRIVER_MMA7660FC_MOTION_H
#define DRIVER_MMA7660FC_MOTION_H

#include "driver_mma7660fc_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup mma7660fc_example_driver
 * @{
 */

/**
 * @brief mma7660fc motion example default definition
 */
#define MMA7660FC_MOTION_DEFAULT_FRONT_BACK_INTERRUPT                MMA7660FC_BOOL_TRUE                        /**< enable front back interrupt */
#define MMA7660FC_MOTION_DEFAULT_UP_DOWN_RIGHT_LEFT_INTERRUPT        MMA7660FC_BOOL_TRUE                        /**< enable up down right left interrupt */
#define MMA7660FC_MOTION_DEFAULT_TAP_INTERRUPT                       MMA7660FC_BOOL_TRUE                        /**< enable tap interrupt */
#define MMA7660FC_MOTION_DEFAULT_AUTO_SLEEP_INTERRUPT                MMA7660FC_BOOL_TRUE                        /**< enable auto sleep interrupt */
#define MMA7660FC_MOTION_DEFAULT_UPDATE_INTERRUPT                    MMA7660FC_BOOL_FALSE                       /**< disable update interrupt */
#define MMA7660FC_MOTION_DEFAULT_SHAKE_X                             MMA7660FC_BOOL_TRUE                        /**< enable shake x interrupt */
#define MMA7660FC_MOTION_DEFAULT_SHAKE_Y                             MMA7660FC_BOOL_TRUE                        /**< enable shake y interrupt */
#define MMA7660FC_MOTION_DEFAULT_SHAKE_Z                             MMA7660FC_BOOL_TRUE                        /**< enable shake z interrupt */
#define MMA7660FC_MOTION_DEFAULT_SLEEP_COUNTER_PRESCALER             MMA7660FC_SLEEP_COUNTER_PRESCALER_1        /**< sleep counter prescaler 1 */
#define MMA7660FC_MOTION_DEFAULT_AUTO_SLEEP_RATE                     MMA7660FC_AUTO_SLEEP_RATE_120              /**< tap detection rate 120 */
#define MMA7660FC_MOTION_DEFAULT_AUTO_WAKE_RATE                      MMA7660FC_AUTO_WAKE_RATE_32                /**< auto wake rate 32 */
#define MMA7660FC_MOTION_DEFAULT_SLEEP_COUNT                         127                                        /**< sleep count 127 */
#define MMA7660FC_MOTION_DEFAULT_AUTO_WAKE_UP                        MMA7660FC_BOOL_TRUE                        /**< enable auto wake up */
#define MMA7660FC_MOTION_DEFAULT_AUTO_SLEEP                          MMA7660FC_BOOL_TRUE                        /**< enable auto sleep */
#define MMA7660FC_MOTION_DEFAULT_INTERRUPT_PIN_TYPE                  MMA7660FC_INTERRUPT_PIN_TYPE_PUSH_PULL     /**< push-pull */
#define MMA7660FC_MOTION_DEFAULT_INTERRUPT_ACTIVE_LEVEL              MMA7660FC_INTERRUPT_ACTIVE_LEVEL_LOW       /**< low */
#define MMA7660FC_MOTION_DEFAULT_TILT_DEBOUNCE_FILTER                MMA7660FC_TILT_DEBOUNCE_FILTER_8           /**< filter 8 */
#define MMA7660FC_MOTION_DEFAULT_TAP_DETECTION_THRESHOLD             2                                          /**< threshold 2 */
#define MMA7660FC_MOTION_DEFAULT_TAP_X                               MMA7660FC_BOOL_TRUE                        /**< enable tap x */
#define MMA7660FC_MOTION_DEFAULT_TAP_Y                               MMA7660FC_BOOL_TRUE                        /**< enable tap y */
#define MMA7660FC_MOTION_DEFAULT_TAP_Z                               MMA7660FC_BOOL_TRUE                        /**< enable tap z */
#define MMA7660FC_MOTION_DEFAULT_TAP_PULSE_DEBOUNCE                  10.0f                                      /**< 10ms */

/**
 * @brief  motion irq
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t mma7660fc_motion_irq_handler(void);

/**
 * @brief     motion example init
 * @param[in] *callback pointer to a callback address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t mma7660fc_motion_init(void (*callback)(uint8_t type));

/**
 * @brief  motion example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mma7660fc_motion_deinit(void);

/**
 * @brief      motion example read
 * @param[out] *g pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t mma7660fc_motion_read(float g[3]);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
