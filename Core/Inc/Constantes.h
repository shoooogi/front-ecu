/*
 *
 * Structs Placa Central
 *
*/

#ifndef CONSTANTES_H
#define CONSTANTES_H

// Serial

#include "Debug.h"

// Constantes

#define INTERVALO_TIMER_MS 1000
#define TEMPERATURA_CRITICA_CVT 200
#define RAIO_PNEU 22
#define QTD_SENSORES_PNEU 4
#define MINUTO_EM_MICROSSEGUNDOS 60000000

static const long MINUTO = 60 * (1000 / INTERVALO_TIMER_MS);

enum Nivel {
    BAIXO,
    MEDIO,
    ALTO
};

#define SERIAL_BAUD 115200 // Serial Debug

// AVISO: Todos os ports e pins abaixo são placeholders

// Telemetria Serial1 UART
#define TELEMETRIA_RX_PORT GPIOB
#define TELEMETRIA_RX_PIN GPIO_PIN_7

#define TELEMETRIA_TX_PORT GPIOB
#define TELEMETRIA_TX_PIN GPIO_PIN_6

#define TELEMETRIA_AUX_PORT GPIOB
#define TELEMETRIA_AUX_PIN GPIO_PIN_10

// Temp CVT

// 4 e 5 são do MLX, revisar Pinout e Setup

// I2C
#define I2C_SDA_PORT GPIOB
#define I2C_SDA_PIN GPIO_PIN_9

#define I2C_SCL_PORT GPIOB
#define I2C_SCL_PIN GPIO_PIN_8

// GPS Serial1 UART
#define GPS_RX_PORT GPIOA
#define GPS_RX_PIN GPIO_PIN_10

#define GPS_TX_PORT GPIOA
#define GPS_TX_PIN GPIO_PIN_9

#define GPS_BAUD 9600

// SD SPI1
#define SD_MISO_PORT GPIOB
#define SD_MISO_PIN GPIO_PIN_14

#define SD_CSP_PORT GPIOA
#define SD_CSP_PIN GPIO_PIN_8

#define SD_SCK_PORT GPIOB
#define SD_SCK_PIN GPIO_PIN_13

#define SD_MOSI_PORT GPIOB
#define SD_MOSI_PIN GPIO_PIN_15

// Combustível
#define COMB_INFERIOR_PORT GPIOB
#define COMB_INFERIOR_PIN GPIO_PIN_0

#define COMB_SUPERIOR_PORT GPIOB
#define COMB_SUPERIOR_PIN GPIO_PIN_1

// CAN SPI1
#define CAN_SCK_PORT GPIOA
#define CAN_SCK_PIN GPIO_PIN_5

#define CAN_MOSI_PORT GPIOA
#define CAN_MOSI_PIN GPIO_PIN_7

#define CAN_MISO_PORT GPIOA
#define CAN_MISO_PIN GPIO_PIN_6

#define CAN_CSP_PORT GPIOA
#define CAN_CSP_PIN GPIO_PIN_1

#define CAN_IN_PORT GPIOA
#define CAN_IN_PIN GPIO_PIN_0

// Freio
#define NIVEL_FREIO_PORT GPIOA
#define NIVEL_FREIO_PIN GPIO_PIN_12

#define PRESSAO_FREIO_PORT GPIOA
#define PRESSAO_FREIO_PIN GPIO_PIN_11

// Habilitar canal ADC no CubeMX
extern ADC_HandleTypeDef hadc1; 
#define PRESSAO_FREIO_ADC_HANDLE hadc1

// Divisor Tensão
#define DIV_TENSAO_PORT GPIOB
#define DIV_TENSAO_PIN GPIO_PIN_11

#define BATERIA_TENSAO_MAX_PORT 13.3

// RPM
#define RPM_INTERRUPT_PORT GPIOB
#define RPM_INTERRUPT_PIN GPIO_PIN_13

// Velocidade
#define VEL_INTERRUPT_PORT GPIOB
#define VEL_INTERRUPT_PIN GPIO_PIN_14

// Pedal Acelerador
#define PEDAL_ACELERADOR_PORT GPIOB
#define PEDAL_ACELERADOR_PIN GPIO_PIN_15


typedef struct DadosCompartilhamento {
    short nivelComb;
    int nivelFreio;
    float pressaoFreio;
    float pedal;
    float tensaoBat;
    double tmpCvt;
    double tmpAmb;
    double rpm;
    double vel;
    float latitude;
    float longitude;
    bool errorCan;
    bool fix_gps;
    bool sdrw;
} DadosCompartilhamento;

typedef struct DadosLight {
    double rpm;
    double vel;
    double tensaoBat;
} DadosLight;

#endif //CONSTANTES_H
