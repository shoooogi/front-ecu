/*
 *
 * Instances Placa Central
 *
*/

#include "Debug.h"

#if DEBUG

#include <stdarg.h>
#include <stdio.h>

static UART_HandleTypeDef *debugUart = NULL;
static SemaphoreHandle_t debugMutex = NULL;

void D_SerialBegin(UART_HandleTypeDef *huart)
{
    debugUart = huart;
    if (debugMutex == NULL) {
        debugMutex = xSemaphoreCreateMutex();
    }
}

void D_print(const char *fmt, ...)
{
    if (debugUart == NULL || debugMutex == NULL) {
        return;
    }
    if (xSemaphoreTake(debugMutex, portMAX_DELAY) == pdTRUE) {
        char buf[DEBUG_BUF_SIZE];
        va_list args;
        va_start(args, fmt);
        int len = vsnprintf(buf, sizeof(buf), fmt, args);
        va_end(args);
        if (len > (int)sizeof(buf) - 1) {
            len = sizeof(buf) - 1; // trunca se o texto formatado for maior que o buffer
        }
        if (len > 0) {
            HAL_UART_Transmit(debugUart, (uint8_t *)buf, (uint16_t)len, HAL_MAX_DELAY);
        }
        xSemaphoreGive(debugMutex);
    }
}

void D_println(const char *fmt, ...)
{
    if (debugUart == NULL || debugMutex == NULL) {
        return;
    }
    if (xSemaphoreTake(debugMutex, portMAX_DELAY) == pdTRUE) {
        char buf[DEBUG_BUF_SIZE];
        va_list args;
        va_start(args, fmt);
        int len = vsnprintf(buf, sizeof(buf) - 2, fmt, args);
        va_end(args);
        if (len < 0) {
            len = 0;
        }
        if (len > (int)sizeof(buf) - 3) {
            len = sizeof(buf) - 3;
        }
        buf[len++] = '\r';
        buf[len++] = '\n';
        HAL_UART_Transmit(debugUart, (uint8_t *)buf, (uint16_t)len, HAL_MAX_DELAY);
        xSemaphoreGive(debugMutex);
    }
}

void D_write(const uint8_t *data, uint16_t size)
{
    if (debugUart == NULL || debugMutex == NULL) {
        return;
    }
    if (xSemaphoreTake(debugMutex, portMAX_DELAY) == pdTRUE) {
        HAL_UART_Transmit(debugUart, (uint8_t *)data, size, HAL_MAX_DELAY);
        xSemaphoreGive(debugMutex);
    }
}

#endif // DEBUG
