#ifndef SERIAL_H
#define SERIAL_H

#include "usart.h"
#include "stream.h"

#define SERIAL_BUFFER_SIZE 256

class Serial : public Stream {
private:
	long baud;
	UART_HandleTypeDef *uartHandle;
	uint8_t buffer[SERIAL_BUFFER_SIZE];
	int bufferStartIndex;
	int bufferEndIndex;
	int numAvailable;
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
