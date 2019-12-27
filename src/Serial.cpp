/*
 * Serial.cpp
 *
 *  Created on: Dec 24, 2019
 *      Author: Jennyston
 */

#include "Serial.h"
#include "string.h"

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

}


