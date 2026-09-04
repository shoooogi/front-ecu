/*
 *
 * Structs Placa Central
 *
 * Obtenção do nível do líquido de freio e da pressão de freio
 *
 * Pressão:
 * 0.5V à 4.5V
 * 0 MPa à 60 MPa
 *
 * FreeRTOS:
 * - Todas as funções são seguras para chamada concorrente por múltiplas tasks
 *   (o estado interno é protegido por seções críticas e o acesso ao ADC é
 *   serializado por um mutex).
 * - As funções são destinadas a contexto de task; não chamar a partir de ISR.
 *
*/

#ifndef FREIO_H
#define FREIO_H

#include "main.h"
#include "Constantes.h"
#include <stdbool.h>

typedef struct Freio Freio;

Freio *Freio_GetInstance(void);

bool Freio_Debug(void);

void Freio_SetValoresDeTeste(void);
int Freio_SetNivelAtual(void);
int Freio_SetPressaoAtual(void);
double Freio_CalculaPressao(void);

int Freio_GetNivelAtual(void);
double Freio_GetPressaoAtual(void);

#endif //FREIO_H
