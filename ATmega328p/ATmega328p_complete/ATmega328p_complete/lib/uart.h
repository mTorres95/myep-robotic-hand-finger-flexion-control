#ifndef UART_H
#define UART_H

#include "main.h"
//#include "uartInterpreter.h"

void UART_init(uint32_t baudrate, uint8_t interrupcionRx, uint8_t interrupcionTx);
int mi_putc(char, FILE *stream);
int mi_getc(FILE *stream);

#define getc() mi_getc(&uart_io)		// redefinicion de la primitiva de entrada para recibir por UART
#define putc(x) mi_putc(x, &uart_io)	// redefinicion de la primitiva de salida para transmitir por UART


#endif
