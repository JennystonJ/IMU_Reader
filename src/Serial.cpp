/*
 * Serial.cpp
 *
 *  Created on: Dec 24, 2019
 *      Author: Jennyston
 */

#include "Serial.h"
#include "string.h"
#include "hal.h"

Serial::Serial(UART_HandleTypeDef *uartHandle) {
	this->uartHandle = uartHandle;
	bufferStartIndex = -1;
	bufferEndIndex = -1;
	numAvailable = 0;

	USART2_UART_Init(9600);
}

Serial::~Serial() {
	HAL_UART_DeInit(uartHandle);
}

void Serial::begin(long baud) {
	USART2_UART_Init(baud);
	HAL_UART_Receive_DMA(uartHandle, rxBuffer, SERIAL_BUFFER_SIZE);
}

int Serial::available() {
	return numAvailable;
}

int Serial::read() {
	uint8_t data;
	bool timeout = HAL_UART_Receive(uartHandle, &data, 1, 1) == HAL_TIMEOUT;
	if(!timeout) {
		return (int)data;
	}
	else {
		return -1;
	}
}

int Serial::print(const char *str) {
	HAL_UART_Transmit(uartHandle, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void Serial::end() {
	HAL_UART_DMAStop(uartHandle);
}

//
//void Serial::initDMA() {
//
//	dmaTxHandle.Init.Direction = DMA_MEMORY_TO_PERIPH;
//	dmaTxHandle.Init.PeriphInc = DMA_PINC_DISABLE;
//	dmaTxHandle.Init.MemInc = DMA_MINC_ENABLE;
//	dmaTxHandle.Init.Mode = DMA_NORMAL;
//	dmaTxHandle.Init.Priority = DMA_PRIORITY_MEDIUM;
//
//	dmaTxHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
//	dmaTxHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
//
//	HAL_StatusTypeDef status = HAL_DMA_Init(&dmaTxHandle);
//	//TODO: implement error for status != HAL_OK
//
//}
