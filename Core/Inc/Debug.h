/*
 *
 * Structs Placa Central
 *
*/

#ifndef DEBUG_H
#define DEBUG_H

#include "main.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <stdint.h>

#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef DEBUG_BUF_SIZE
#define DEBUG_BUF_SIZE 128
#endif

#if DEBUG

// Inicialização
void D_SerialBegin(UART_HandleTypeDef *huart);

// Substitui Serial.print
void D_print(const char *fmt, ...);

// Substitui Serial.println
void D_println(const char *fmt, ...);

// Substitui Serial.write
void D_write(const uint8_t *data, uint16_t size);

#else

#define D_SerialBegin(huart)   ((void)0)
#define D_print(...)           ((void)0)
#define D_println(...)         ((void)0)
#define D_write(data, size)    ((void)0)

#endif // DEBUG
#endif // DEBUG_H
