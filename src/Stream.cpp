/*
 * Stream.cpp
 *
 *  Created on: Dec 24, 2019
 *      Author: Jennyston
 */

#include "Stream.h"
#include "ctype.h"
#include "hal.h"
static const unsigned long DEFAULT_TIMEOUT = 1000;

Stream::Stream() {
	timeout = DEFAULT_TIMEOUT;
}

int Stream::timedRead() {
	int character;
	unsigned long counter = timeout;
	do {
		character = read();
		if(character >= 0) {
			return character;
		}

		HAL_Delay(1);
		counter--;
	} while(counter > 0);

	return -1;
}

void Stream::setTimeout(unsigned long timeout) {
	this->timeout = timeout;
}


bool Stream::find(const char *target) {
	int character;
	int targetIndex = 0;
	while(target[targetIndex] != 0) {
		character = timedRead();
		//character matches
		if(character == target[targetIndex]) {
			targetIndex++;
		}
		//timed out
		else if(character < 0) {
			return false;
		}
		//character does not match
		else {
			targetIndex = 0;
		}
	}
	return true;
}


bool Stream::find(const char *target, size_t length) {
	int character;
	size_t targetIndex = 0;
	while(targetIndex < length) {
		character = timedRead();
		//character matches
		if(character == target[targetIndex]) {
			targetIndex++;
		}
		//timed out
		else if(character < 0) {
			return false;
		}
		//character does not match
		else {
			targetIndex = 0;
		}
	}
	return true;
}

bool Stream::findUntil(const char *target, const char *terminator) {
	int character;
	size_t targetIndex = 0;
	size_t termIndex = 0;
	while(target[targetIndex] != 0 && terminator[termIndex] != 0) {
		character = timedRead();
		//character matches
		if(character == target[targetIndex]) {
			targetIndex++;
		}
		else if(character == terminator[termIndex]) {
			termIndex++;
		}
		//timed out
		else if(character < 0) {
			return false;
		}
		//character does not match
		else {
			targetIndex = 0;
			termIndex = 0;
		}
	}

	//target terminated loop
	if(target[targetIndex] == 0) {
		return true;
	}
	//terminator terminated loop
	else {
		return false;
	}
}

bool Stream::findUntil(const char *target, size_t targetLen,
		const char *terminator, size_t termLen) {
	int character;
	size_t targetIndex = 0;
	size_t termIndex = 0;
	while(targetIndex < targetLen && termIndex < termLen) {
		character = timedRead();
		//character matches
		if(character == target[targetIndex]) {
			targetIndex++;
		}
		else if(character == terminator[termIndex]) {
			termIndex++;
		}
		//timed out
		else if(character < 0) {
			return false;
		}
		//character does not match
		else {
			targetIndex = 0;
			termIndex = 0;
		}
	}

	//target terminated loop
	if(targetIndex == targetLen) {
		return true;
	}
	//terminator terminated loop
	else {
		return false;
	}
}

long Stream::parseInt() {
	int number = 0;
	int character;
	bool numberFound = false;
	do {
		character = read();
		if(isdigit(character)) {
			numberFound = true;
			do {
				number = (number * 10) + (character - '0');
				character = read();
			} while(isdigit(character));
		}
	} while(!numberFound);
	return number;
}

float Stream::parseFloat() {
	float number = 0;
	float fraction = 0;
	float currentFractionDigit = 1;
	int character;
	bool numberFound = false;
	do {
		character = read();
		if(isdigit(character)) {
			numberFound = true;
			do {
				number = (number * 10) + (character - '0');
				character = read();
			} while(isdigit(character));

			if(character != '.') {
				continue;
			}

			character = read();
			do {
				currentFractionDigit /= 10;
				fraction += currentFractionDigit * (character - '0');
				character = read();
			} while(isdigit(character));
		}
	} while(!numberFound);
	return number + fraction;
}

size_t Stream::readBytes(char *buffer, size_t length) {
	int character;
	size_t  numCharactersRead;
	for(numCharactersRead = 0; numCharactersRead < length;
			numCharactersRead++) {
		character = timedRead();

		if(character < 0) {
			return numCharactersRead;
		}

		buffer[numCharactersRead] = character;
	}
	return numCharactersRead;
}

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length) {
	int character;
	size_t  numCharactersRead;
	for(numCharactersRead = 0; numCharactersRead < length;
			numCharactersRead++) {
		character = timedRead();

		if(character < 0 || character == terminator) {
			return numCharactersRead;
		}

		buffer[numCharactersRead] = character;
	}
	return numCharactersRead;
}
