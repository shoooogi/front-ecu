/*
 *
 * Instances Placa Central
 *
 * Obtenção do nível do líquido de freio e da pressão de freio
 *
 * Pressão:
 * 0.5V à 4.5V
 * 0 MPa à 60 MPa
 *
*/

#include "Freio.h"
#include "Constantes.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct Freio
{
    int nivelAtual;
    double pressaoAtual;
};

static Freio instance;
static bool initialized = false;

static SemaphoreHandle_t adcMutex = NULL;

static SemaphoreHandle_t Freio_ObterMutexAdc(void)
{
    if (adcMutex == NULL)
    {
        taskENTER_CRITICAL();
        if (adcMutex == NULL)
        {
            adcMutex = xSemaphoreCreateMutex();
            configASSERT(adcMutex != NULL);
        }
        taskEXIT_CRITICAL();
    }
    return adcMutex;
}

Freio *Freio_GetInstance(void)
{
    Freio_ObterMutexAdc();

    if (!initialized)
    {
        taskENTER_CRITICAL();
        if (!initialized)
        {
            instance.nivelAtual = 0;
            instance.pressaoAtual = 0.0;

            GPIO_InitTypeDef gpioInit = {0};
            gpioInit.Mode = GPIO_MODE_INPUT;
            gpioInit.Pull = GPIO_NOPULL;

            gpioInit.Pin = NIVEL_FREIO_PIN;
            HAL_GPIO_Init(NIVEL_FREIO_PORT, &gpioInit);

            gpioInit.Pin = PRESSAO_FREIO_PIN;
            HAL_GPIO_Init(PRESSAO_FREIO_PORT, &gpioInit);

            initialized = true;
        }
        taskEXIT_CRITICAL();
    }
    return &instance;
}

bool Freio_Debug(void)
{
    return false;
}

void Freio_SetValoresDeTeste(void)
{
    taskENTER_CRITICAL();
    instance.pressaoAtual = (((double)(rand() % 255) / 146.25) * 2.1428);
    instance.nivelAtual = rand() % 1;
    taskEXIT_CRITICAL();
}

int Freio_SetNivelAtual(void)
{
    taskENTER_CRITICAL();
    instance.nivelAtual =
    (HAL_GPIO_ReadPin(NIVEL_FREIO_PORT, NIVEL_FREIO_PIN) == GPIO_PIN_SET) ? 1 : 0;
    int nivel = instance.nivelAtual;
    taskEXIT_CRITICAL();
    return nivel;
}

int Freio_SetPressaoAtual(void)
{
    double pressao = Freio_CalculaPressao();
    taskENTER_CRITICAL();
    instance.pressaoAtual = pressao;
    int retorno = (int)instance.pressaoAtual;
    taskEXIT_CRITICAL();
    return retorno;
}

double Freio_CalculaPressao(void)
{
    // 3.3V = 4095 = 60 MPA
    // < 0.5V? = 0 = 0 MPA
    // +/- 0.1V = 146,25 = 2.1428 MPA
    SemaphoreHandle_t mutexAdc = Freio_ObterMutexAdc();
    xSemaphoreTake(mutexAdc, portMAX_DELAY);

    HAL_ADC_Start(&PRESSAO_FREIO_ADC_HANDLE);
    HAL_ADC_PollForConversion(&PRESSAO_FREIO_ADC_HANDLE, HAL_MAX_DELAY);
    uint32_t leitura = HAL_ADC_GetValue(&PRESSAO_FREIO_ADC_HANDLE);
    HAL_ADC_Stop(&PRESSAO_FREIO_ADC_HANDLE);

    xSemaphoreGive(mutexAdc);

    return (((double)leitura / 146.25) * 2.1428);
}

int Freio_GetNivelAtual(void)
{
    taskENTER_CRITICAL();
    int nivel = instance.nivelAtual;
    taskEXIT_CRITICAL();
    return nivel;
}

double Freio_GetPressaoAtual(void)
{
    taskENTER_CRITICAL();
    double pressao = instance.pressaoAtual;
    taskEXIT_CRITICAL();
    return pressao;
}
