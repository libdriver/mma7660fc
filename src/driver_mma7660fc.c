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
 * @file      driver_mma7660fc.c
 * @brief     driver mma7660fc source file
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

#include "driver_mma7660fc.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "NXP MMA7660FC"        /**< chip name */
#define MANUFACTURER_NAME         "NXP"                  /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.4f                   /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                   /**< chip max supply voltage */
#define MAX_CURRENT               0.294f                 /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                 /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                  /**< chip max operating temperature */
#define DRIVER_VERSION            1000                   /**< driver version */

/**
 * @brief chip address definition
 */
#define MMA7660FC_ADDRESS            0x98        /**< iic device address */

/**
 * @brief chip register definition
 */
#define MMA7660FC_REG_XOUT          0x00        /**< xout register */
#define MMA7660FC_REG_YOUT          0x01        /**< yout register */
#define MMA7660FC_REG_ZOUT          0x02        /**< zout register */
#define MMA7660FC_REG_TILT          0x03        /**< tilt register */
#define MMA7660FC_REG_SRST          0x04        /**< srst register */
#define MMA7660FC_REG_SPCNT         0x05        /**< spcnt register */
#define MMA7660FC_REG_INTSU         0x06        /**< intsu register */
#define MMA7660FC_REG_MODE          0x07        /**< mode register */
#define MMA7660FC_REG_SR            0x08        /**< sr register */
#define MMA7660FC_REG_PDET          0x09        /**< pdet register */
#define MMA7660FC_REG_PD            0x0A        /**< pd register */

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to a mma7660fc handle structure
 * @param[in]  reg iic register address
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_mma7660fc_iic_read(mma7660fc_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_read(MMA7660FC_ADDRESS, reg, buf, len) != 0)        /* read */
    {
        return 1;                                                       /* return error */
    }
    
    return 0;                                                           /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to a mma7660fc handle structure
 * @param[in] reg iic register address
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_mma7660fc_iic_write(mma7660fc_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle->iic_write(MMA7660FC_ADDRESS, reg, buf, len) != 0)        /* write */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t mma7660fc_get_tilt_status(mma7660fc_handle_t *handle, uint8_t *status)
{
    uint8_t res;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_TILT, status, 1);        /* read tilt */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read tilt failed.\n");                /* read tilt failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_auto_sleep_status(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SRST, &prev, 1);        /* read srst */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("mma7660fc: read srst failed.\n");               /* read srst failed */
        
        return 1;                                                            /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 0) & 0x01);                        /* get bool */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t mma7660fc_get_auto_wake_up_status(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SRST, &prev, 1);        /* read srst */
    if (res != 0)                                                            /* check the result */
    {
        handle->debug_print("mma7660fc: read srst failed.\n");               /* read srst failed */
        
        return 1;                                                            /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 1) & 0x01);                        /* get bool */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t mma7660fc_set_sleep_count(mma7660fc_handle_t *handle, uint8_t count)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    prev = count;                                                              /* set sleep count */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_SPCNT, &prev, 1);        /* write spcnt */
    if (res != 0)                                                              /* check the result */
    {
        handle->debug_print("mma7660fc: write spcnt failed.\n");               /* write spcnt failed */
        
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t mma7660fc_get_sleep_count(mma7660fc_handle_t *handle, uint8_t *count)
{
    uint8_t res;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SPCNT, count, 1);        /* read spcnt */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read spcnt failed.\n");               /* read spcnt failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_front_back_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 0);                                                        /* clear setting bit */
    prev |= (enable << 0);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_INTSU, &prev, 1);       /* write intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write intsu failed.\n");              /* write intsu failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_front_back_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 0) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_up_down_right_left_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 1);                                                        /* clear setting bit */
    prev |= (enable << 1);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_INTSU, &prev, 1);       /* write intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write intsu failed.\n");              /* write intsu failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_up_down_right_left_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 1) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_tap_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 2);                                                        /* clear setting bit */
    prev |= (enable << 2);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_INTSU, &prev, 1);       /* write intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write intsu failed.\n");              /* write intsu failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_tap_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 2) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_auto_sleep_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 3);                                                        /* clear setting bit */
    prev |= (enable << 3);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_INTSU, &prev, 1);       /* write intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write intsu failed.\n");              /* write intsu failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_auto_sleep_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 3) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_update_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 4);                                                        /* clear setting bit */
    prev |= (enable << 4);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_INTSU, &prev, 1);       /* write intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write intsu failed.\n");              /* write intsu failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_update_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 4) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_shake_x_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 7);                                                        /* clear setting bit */
    prev |= (enable << 7);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_INTSU, &prev, 1);       /* write intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write intsu failed.\n");              /* write intsu failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_shake_x_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 7) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_shake_y_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 6);                                                        /* clear setting bit */
    prev |= (enable << 6);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_INTSU, &prev, 1);       /* write intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write intsu failed.\n");              /* write intsu failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_shake_y_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 6) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_shake_z_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 5);                                                        /* clear setting bit */
    prev |= (enable << 5);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_INTSU, &prev, 1);       /* write intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write intsu failed.\n");              /* write intsu failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_shake_z_interrupt(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_INTSU, &prev, 1);        /* read intsu */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read intsu failed.\n");               /* read intsu failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 5) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_mode(mma7660fc_handle_t *handle, mma7660fc_mode_t mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(7 << 0);                                                        /* clear setting bit */
    prev |= (mode << 0);                                                      /* set mode */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_MODE, &prev, 1);        /* write mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write mode failed.\n");               /* write mode failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_mode(mma7660fc_handle_t *handle, mma7660fc_mode_t *mode)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    *mode = (mma7660fc_mode_t)(prev & 0x7);                                   /* get the mode */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_auto_wake_up(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 3);                                                        /* clear setting bit */
    prev |= (enable << 3);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_MODE, &prev, 1);        /* write mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write mode failed.\n");               /* write mode failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_auto_wake_up(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 3) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_auto_sleep(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 4);                                                        /* clear setting bit */
    prev |= (enable << 4);                                                    /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_MODE, &prev, 1);        /* write mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write mode failed.\n");               /* write mode failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_auto_sleep(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    *enable = (mma7660fc_bool_t)((prev >> 4) & 0x01);                         /* get bool */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_sleep_counter_prescaler(mma7660fc_handle_t *handle, mma7660fc_sleep_counter_prescaler_t prescaler)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 5);                                                        /* clear setting bit */
    prev |= (prescaler << 5);                                                 /* set prescaler */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_MODE, &prev, 1);        /* write mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write mode failed.\n");               /* write mode failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_sleep_counter_prescaler(mma7660fc_handle_t *handle, mma7660fc_sleep_counter_prescaler_t *prescaler)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    *prescaler = (mma7660fc_sleep_counter_prescaler_t)((prev >> 5) & 0x01);   /* get prescaler */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_interrupt_pin_type(mma7660fc_handle_t *handle, mma7660fc_interrupt_pin_type_t type)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 6);                                                        /* clear setting bit */
    prev |= (type << 6);                                                      /* set type */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_MODE, &prev, 1);        /* write mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write mode failed.\n");               /* write mode failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_interrupt_pin_type(mma7660fc_handle_t *handle, mma7660fc_interrupt_pin_type_t *type)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    *type = (mma7660fc_interrupt_pin_type_t)((prev >> 6) & 0x01);             /* get type */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_interrupt_active_level(mma7660fc_handle_t *handle, mma7660fc_interrupt_active_level_t level)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    prev &= ~(1 << 7);                                                        /* clear setting bit */
    prev |= (level << 7);                                                     /* set level */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_MODE, &prev, 1);        /* write mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write mode failed.\n");               /* write mode failed */
        
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_get_interrupt_active_level(mma7660fc_handle_t *handle, mma7660fc_interrupt_active_level_t *level)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 1;                                                             /* return error */
    }
    *level = (mma7660fc_interrupt_active_level_t)((prev >> 7) & 0x01);        /* get level */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_set_tap_detection_rate(mma7660fc_handle_t *handle, mma7660fc_auto_sleep_rate_t rate)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SR, &prev, 1);         /* read sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read sr failed.\n");                /* read sr failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(7 << 0);                                                      /* clear setting bit */
    prev |= (rate << 0);                                                    /* set rate */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_SR, &prev, 1);        /* write sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: write sr failed.\n");               /* write sr failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_get_tap_detection_rate(mma7660fc_handle_t *handle, mma7660fc_auto_sleep_rate_t *rate)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SR, &prev, 1);         /* read sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read sr failed.\n");                /* read sr failed */
        
        return 1;                                                           /* return error */
    }
    *rate = (mma7660fc_auto_sleep_rate_t)(prev & 0x07);                     /* set rate */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_set_auto_wake_rate(mma7660fc_handle_t *handle, mma7660fc_auto_wake_rate_t rate)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SR, &prev, 1);         /* read sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read sr failed.\n");                /* read sr failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(3 << 3);                                                      /* clear setting bit */
    prev |= (rate << 3);                                                    /* set rate */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_SR, &prev, 1);        /* write sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: write sr failed.\n");               /* write sr failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_get_auto_wake_rate(mma7660fc_handle_t *handle, mma7660fc_auto_wake_rate_t *rate)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SR, &prev, 1);         /* read sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read sr failed.\n");                /* read sr failed */
        
        return 1;                                                           /* return error */
    }
    *rate = (mma7660fc_auto_wake_rate_t)((prev >> 3) & 0x03);               /* set rate */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_set_tilt_debounce_filter(mma7660fc_handle_t *handle, mma7660fc_tilt_debounce_filter_t filter)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SR, &prev, 1);         /* read sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read sr failed.\n");                /* read sr failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(7 << 5);                                                      /* clear setting bit */
    prev |= (filter << 5);                                                  /* set filter */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_SR, &prev, 1);        /* write sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: write sr failed.\n");               /* write sr failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_get_tilt_debounce_filter(mma7660fc_handle_t *handle, mma7660fc_tilt_debounce_filter_t *filter)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SR, &prev, 1);         /* read sr */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read sr failed.\n");                /* read sr failed */
        
        return 1;                                                           /* return error */
    }
    *filter = (mma7660fc_tilt_debounce_filter_t)((prev >> 5) & 0x07);       /* set filter */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_set_tap_detection_threshold(mma7660fc_handle_t *handle, uint8_t threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    if (threshold > 31)                                                     /* check threshold */
    {
        handle->debug_print("mma7660fc: threshold > 31.\n");                /* threshold > 31 */
        
        return 4;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PDET, &prev, 1);       /* read pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read pdet failed.\n");              /* read pdet failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(0x1F << 0);                                                   /* clear setting bit */
    prev |= (threshold << 0);                                               /* set threshold */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_PDET, &prev, 1);      /* write pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: write pdet failed.\n");             /* write pdet failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_get_tap_detection_threshold(mma7660fc_handle_t *handle, uint8_t *threshold)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PDET, &prev, 1);       /* read pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read pdet failed.\n");              /* read pdet failed */
        
        return 1;                                                           /* return error */
    }
    *threshold = prev & 0x01F;                                              /* set threshold */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_set_tap_x_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PDET, &prev, 1);       /* read pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read pdet failed.\n");              /* read pdet failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(1 << 5);                                                      /* clear setting bit */
    prev |= ((!enable) << 5);                                               /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_PDET, &prev, 1);      /* write pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: write pdet failed.\n");             /* write pdet failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_get_tap_x_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PDET, &prev, 1);       /* read pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read pdet failed.\n");              /* read pdet failed */
        
        return 1;                                                           /* return error */
    }
    *enable = (mma7660fc_bool_t)(!((prev >> 5) & 0x01));                    /* set bool */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_set_tap_y_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PDET, &prev, 1);       /* read pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read pdet failed.\n");              /* read pdet failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(1 << 6);                                                      /* clear setting bit */
    prev |= ((!enable) << 6);                                               /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_PDET, &prev, 1);      /* write pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: write pdet failed.\n");             /* write pdet failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_get_tap_y_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PDET, &prev, 1);       /* read pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read pdet failed.\n");              /* read pdet failed */
        
        return 1;                                                           /* return error */
    }
    *enable = (mma7660fc_bool_t)(!((prev >> 6) & 0x01));                    /* set bool */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_set_tap_z_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PDET, &prev, 1);       /* read pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read pdet failed.\n");              /* read pdet failed */
        
        return 1;                                                           /* return error */
    }
    prev &= ~(1 << 7);                                                      /* clear setting bit */
    prev |= ((!enable) << 7);                                               /* set bool */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_PDET, &prev, 1);      /* write pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: write pdet failed.\n");             /* write pdet failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_get_tap_z_detection(mma7660fc_handle_t *handle, mma7660fc_bool_t *enable)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PDET, &prev, 1);       /* read pdet */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read pdet failed.\n");              /* read pdet failed */
        
        return 1;                                                           /* return error */
    }
    *enable = (mma7660fc_bool_t)(!((prev >> 7) & 0x01));                    /* set bool */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_set_tap_pulse_debounce_count(mma7660fc_handle_t *handle, uint8_t count)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    prev = count;                                                           /* set count */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_PD, &prev, 1);        /* write pd */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: write pd failed.\n");               /* write pd failed */
        
        return 1;                                                           /* return error */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_get_tap_pulse_debounce_count(mma7660fc_handle_t *handle, uint8_t *count)
{
    uint8_t res;
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_PD, count, 1);        /* read pd */
    if (res != 0)                                                          /* check the result */
    {
        handle->debug_print("mma7660fc: read pd failed.\n");               /* read pd failed */
        
        return 1;                                                          /* return error */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t mma7660fc_tap_pulse_debounce_convert_to_register(mma7660fc_handle_t *handle, float ms, uint8_t *reg)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    *reg = (uint8_t)((ms - 0.52f) / 0.26f) + 1;        /* convert real data to register data */
    
    return 0;                                          /* success return 0 */
}

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
uint8_t mma7660fc_tap_pulse_debounce_convert_to_data(mma7660fc_handle_t *handle, uint8_t reg, float *ms)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    if (reg == 0)                                      /* if reg = 0 */
    {
        *ms = 0.52f;                                   /* set 0.52ms */
    }
    else                                               /* common convert */
    {
        *ms = (float)(reg - 1) * 0.26f + 0.52f;        /* convert raw data to real data */
    }
    
    return 0;                                          /* success return 0 */
}

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
uint8_t mma7660fc_irq_handler(mma7660fc_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_TILT, &prev, 1);       /* read tilt */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read tilt failed.\n");              /* read tilt failed */
        
        return 1;                                                           /* return error */
    }
    if ((prev & (1 << 0)) != 0)                                             /* if lying on its front */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_FRONT);               /* run callback */
        }
    }
    if ((prev & (1 << 1)) != 0)                                             /* if lying on its back */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_BACK);                /* run callback */
        }
    }
    if ((prev & (1 << 2)) != 0)                                             /* if landscape mode to the left */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_LEFT);                /* run callback */
        }
    }
    if ((prev & (2 << 2)) != 0)                                             /* if landscape mode to the right */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_RIGHT);               /* run callback */
        }
    }
    if ((prev & (5 << 2)) != 0)                                             /* if standing vertically in inverted orientation */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_DOWN);                /* run callback */
        }
    }
    if ((prev & (6 << 2)) != 0)                                             /* if standing vertically in normal orientation */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_UP);                  /* run callback */
        }
    }
    if ((prev & (1 << 5)) != 0)                                             /* if detected a tap */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_TAP);                 /* run callback */
        }
    }
    if ((prev & (1 << 6)) != 0)                                             /* if data is invalid */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_UPDATE);              /* run callback */
        }
    }
    if ((prev & (1 << 7)) != 0)                                             /* if experiencing shake in one or more of the axes */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_SHAKE);               /* run callback */
        }
    }
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_SRST, &prev, 1);       /* read srst */
    if (res != 0)                                                           /* check the result */
    {
        handle->debug_print("mma7660fc: read srst failed.\n");              /* read srst failed */
        
        return 1;                                                           /* return error */
    }
    if ((prev & (1 << 0)) != 0)                                             /* if auto sleep */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_AUTO_SLEEP);          /* run callback */
        }
    }
    if ((prev & (1 << 1)) != 0)                                             /* if wake up */
    {
        if (handle->receive_callback != NULL)                               /* if receive callback */
        {
            handle->receive_callback(MMA7660FC_STATUS_AUTO_WAKE_UP);        /* run callback */
        }
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t mma7660fc_init(mma7660fc_handle_t *handle)
{
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->debug_print == NULL)                                          /* check debug_print */
    {
        return 3;                                                             /* return error */
    }
    if (handle->iic_init == NULL)                                             /* check iic_init */
    {
        handle->debug_print("mma7660fc: iic_init is null.\n");                /* iic_init is nul */
        
        return 3;                                                             /* return error */
    }
    if (handle->iic_deinit == NULL)                                           /* check iic_deinit */
    {
        handle->debug_print("mma7660fc: iic_deinit is null.\n");              /* iic_deinit is null */
        
        return 3;                                                             /* return error */
    }
    if (handle->iic_read == NULL)                                             /* check iic_read */
    {
        handle->debug_print("mma7660fc: iic_read is null.\n");                /* iic_read is null */
        
        return 3;                                                             /* return error */
    }
    if (handle->iic_write == NULL)                                            /* check iic_write */
    {
        handle->debug_print("mma7660fc: iic_write is null.\n");               /* iic_write is null */
        
        return 3;                                                             /* return error */
    }
    if (handle->receive_callback == NULL)                                     /* check receive_callback */
    {
        handle->debug_print("mma7660fc: receive_callback is null.\n");        /* receive_callback is null */
        
        return 3;                                                             /* return error */
    }
    if (handle->delay_ms == NULL)                                             /* check delay_ms */
    {
        handle->debug_print("mma7660fc: delay_ms is null.\n");                /* delay_ms is null */
        
        return 3;                                                             /* return error */
    }
    
    if (handle->iic_init() != 0)                                              /* iic init */
    {
        handle->debug_print("mma7660fc: iic init failed.\n");                 /* iic init failed */
        
        return 1;                                                             /* return error */
    }
    handle->inited = 1;                                                       /* flag inited */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_deinit(mma7660fc_handle_t *handle)
{
    uint8_t res;
    uint8_t prev;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_MODE, &prev, 1);         /* read mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: read mode failed.\n");                /* read mode failed */
        
        return 4;                                                             /* return error */
    }
    prev &= ~(7 << 0);                                                        /* clear setting bit */
    res = a_mma7660fc_iic_write(handle, MMA7660FC_REG_MODE, &prev, 1);        /* write mode */
    if (res != 0)                                                             /* check the result */
    {
        handle->debug_print("mma7660fc: write mode failed.\n");               /* write mode failed */
        
        return 4;                                                             /* return error */
    }
    if (handle->iic_deinit() != 0)                                            /* iic deinit */
    {
        handle->debug_print("mma7660fc: iic deinit failed.\n");               /* iic deinit failed */
        
        return 1;                                                             /* return error */
    }
    handle->inited = 0;                                                       /* flag close */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t mma7660fc_read(mma7660fc_handle_t *handle, int8_t raw[3], float g[3])
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    res = a_mma7660fc_iic_read(handle, MMA7660FC_REG_XOUT, buf, 3);        /* read data */
    if (res != 0)                                                          /* check the result */
    {
        handle->debug_print("mma7660fc: read data failed.\n");             /* read data failed */
        
        return 1;                                                          /* return error */
    }
    buf[0] &= ~(1 << 7);                                                   /* clear bit 7 */
    buf[1] &= ~(1 << 7);                                                   /* clear bit 7 */
    buf[2] &= ~(1 << 7);                                                   /* clear bit 7 */
    if ((buf[0] & (1 << 6)) != 0)                                          /* check alert bit */
    {
        handle->debug_print("mma7660fc: data is invalid.\n");              /* data is invalid */
        
        return 4;                                                          /* return error */
    }
    if ((buf[1] & (1 << 6)) != 0)                                          /* check alert bit */
    {
        handle->debug_print("mma7660fc: data is invalid.\n");              /* data is invalid */
        
        return 4;                                                          /* return error */
    }
    if ((buf[2] & (1 << 6)) != 0)                                          /* check alert bit */
    {
        handle->debug_print("mma7660fc: data is invalid.\n");              /* data is invalid */
        
        return 4;                                                          /* return error */
    }
    
    if ((buf[0] & (1 << 5)) != 0)                                          /* check negative bit */
    {
        raw[0] = (int8_t)(buf[0] | (3 << 6));                              /* extend to bit 6 and 7 */
        g[0] = (float)(raw[0] / 21.33f);                                   /* convert to real data */
    }
    else
    {
        raw[0] = (int8_t)buf[0];                                           /* copy data */
        g[0] = (float)(raw[0] / 21.33f);                                   /* convert to real data */
    }
    if ((buf[1] & (1 << 5)) != 0)                                          /* check negative bit */
    {
        raw[1] = (int8_t)(buf[1] | (3 << 6));                              /* extend to bit 6 and 7 */
        g[1] = (float)(raw[1] / 21.33f);                                   /* convert to real data */
    }
    else
    {
        raw[1] = (int8_t)buf[1];                                           /* copy data */
        g[1] = (float)(raw[1] / 21.33f);                                   /* convert to real data */
    }
    if ((buf[2] & (1 << 5)) != 0)                                          /* check negative bit */
    {
        raw[2] = (int8_t)(buf[2] | (3 << 6));                              /* extend to bit 6 and 7 */
        g[2] = (float)(raw[2] / 21.33f);                                   /* convert to real data */
    }
    else
    {
        raw[2] = (int8_t)buf[2];                                           /* copy data */
        g[2] = (float)(raw[2] / 21.33f);                                   /* convert to real data */
    }
    
    return 0;                                                              /* success return 0 */
}

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
uint8_t mma7660fc_set_reg(mma7660fc_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    } 

    return a_mma7660fc_iic_write(handle, reg, buf, len);       /* write register */
}

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
uint8_t mma7660fc_get_reg(mma7660fc_handle_t *handle, uint8_t reg, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                       /* check handle */
    {
        return 2;                                             /* return error */
    }
    if (handle->inited != 1)                                  /* check handle initialization */
    {
        return 3;                                             /* return error */
    } 

    return a_mma7660fc_iic_read(handle, reg, buf, len);       /* read register */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a mma7660fc info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t mma7660fc_info(mma7660fc_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(mma7660fc_info_t));                      /* initialize mma7660fc info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
