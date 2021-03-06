/*
 *
 * Copyright Niels Post 2022.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 *
*/
#ifndef FD_HDR_STM32_HAL_SPI
#define FD_HDR_STM32_HAL_SPI

#include <fd/targets/base/spi.hpp>
#include <fd/targets/base/gpio.hpp>
#include <stm32f1xx_hal.h>

#include "fd/util/fondant_targets.hpp"

namespace fd::stm32_hal {

    fd::spi_status get_spi_status(uint32_t status);
    enum class spi_error_status: uint32_t {
        NONE = HAL_SPI_ERROR_NONE,
        ERROR_MODF = HAL_SPI_ERROR_MODF,
        ERROR_CRC = HAL_SPI_ERROR_CRC,
        ERROR_OVR = HAL_SPI_ERROR_OVR,
        ERROR_DMA = HAL_SPI_ERROR_DMA,
        ERROR_FLAG = HAL_SPI_ERROR_FLAG,
        ERROR_ABORT = HAL_SPI_ERROR_ABORT
    };

    class spi : public ::fd::spi_base {
        fd::pin_out_base &cs_pin;
        SPI_HandleTypeDef &handle;
        bool dma;
        uint32_t default_timeout;

    public:
        spi_error_status last_error;
        spi(SPI_HandleTypeDef &handle, bool dma, uint32_t defaultTimeout, fd::pin_out_base &cs_pin);

        fd::spi_status transmit_receive(uint8_t *write_data, uint8_t *read_data, size_t size) override;

        spi_status wait() override;

    };

}
#endif //FD_HDR_STM32_HAL_SPI
