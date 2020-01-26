#ifndef SERIAL_H
#define SERIAL_H

#include "usart.h"
#include "dma.h"
#include "stream.h"

#define SERIAL_BUFFER_SIZE 256

class Serial : public Stream {
private:
	long baud;
	UART_HandleTypeDef *uartHandle;
	DMA_HandleTypeDef dmaTxHandle;
	DMA_HandleTypeDef dmaRxHandle;
	uint8_t txBuffer[SERIAL_BUFFER_SIZE];
	uint8_t rxBuffer[SERIAL_BUFFER_SIZE];
	int bufferStartIndex;
	int bufferEndIndex;
	int numAvailable;

	void initDMA();
public:
	Serial(UART_HandleTypeDef *uartHandle);
	~Serial();
	void begin(long baud);
	int available() override;
	int read() override;
	int print(const char *str);
	void end();

};


#endif
