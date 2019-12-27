#ifndef STREAM_H
#define STREAM_H

#include <inttypes.h>
#include <stddef.h>

class Stream {
private:
	//number of milliseconds to wait for next char before aborting timed read
	unsigned long timeout;
	unsigned long startMillis;
	//read stream with timeout
	int timedRead();

public:
	virtual int available() = 0;
	virtual int read() = 0;

	Stream();

	/**
	 * @brief Maximum time to wait for data
	 * @param timeout: timeout in milliseconds
	 * @retval None
	 */
	void setTimeout(unsigned long timeout);

	/**
	 * @brief Reads data from stream until target string is found
	 *  or until timeout
	 * @param target: string to be found
	 * @retval true if timed out, otherwise false
	 */
	bool find(const char *target);

	/**
	 * @brief Reads data from stream until target string is found or until
	 *  timeout
	 * @param target: string to be found
	 * @retval true if string is found, false if timed out (see setTimeout)
	 */
	bool find(uint8_t *target) {
		return find((char *) target);
	}

	/**
	 * @brief Reads data from stream until target string with given length is
	 *  found
	 * @param target: string to be found
	 * @param length: length of string
	 * @retval true if string is found, false if timed out (see setTimeout)
	 */
	bool find(const char *target, size_t length);

	/**
	 * @brief Reads data from stream until target string with given length is
	 *  found
	 * @param target: string to be found
	 * @param length: length of string
	 * @retval true if string is found, false if timed out (see setTimeout)
	 */
	bool find(const uint8_t *target, size_t length) {
		return find((char *) target, length);
	}

	/**
	 * @brief Reads data from stream until target character is found
	 * @param target: character to be found
	 * @retval true if string is found, false if timed out (see setTimeout)
	 */
	bool find(char target) {
		return find (&target, 1);
	}

	/**
	 * @brief Reads data from stream until target string is found. Search ends
	 *  if terminator string is found or timeout occurs
	 * @param target: string to be found
	 * @param terminator: string to terminate search
	 * @retval true if string is found, false if terminator found or timed out
	 *  (see setTimeout)
	 */
	bool findUntil(const char *target, const char *terminator);

	/**
	 * @brief Reads data from stream until target string is found. Search ends
	 *  if terminator string is found or timeout occurs
	 * @param target: string to be found
	 * @param terminator: string to terminate search
	 * @retval true if string is found, false if terminator found or timed out
	 *  (see setTimeout)
	 */
	bool findUntil(const uint8_t *target, const char *terminator) {
		return findUntil((char *) target, terminator);
	}

	/**
	 * @brief Reads data from stream until target string with given length is
	 *  found. Search ends if terminator string with given length is found or
	 *  timeout occurs
	 * @param target: string to be found
	 * @param targetLen: length of target string
	 * @param terminator: string to terminate search
	 * @param termLen: length of terminator string
	 * @retval true if string is found, false if terminator found or timed out
	 *  (see setTimeout)
	 */
	bool findUntil(const char *target, size_t targetLen, const char *terminator,
			size_t termLen);

	/**
	 * @brief Reads data from stream until target string with given length is
	 *  found. Search ends if terminator string with given length is found or
	 *  timeout occurs
	 * @param target: string to be found
	 * @param targetLen: length of target string
	 * @param terminator: string to terminate search
	 * @param termLen: length of terminator string
	 * @retval true if string is found, false if terminator found or timed out
	 *  (see setTimeout)
	 */
	bool findUntil(const uint8_t *target, size_t targetLen,
			const char *terminator, size_t termLen) {
		return findUntil((char *) target, targetLen, terminator, termLen);
	}

	/**
	 * @brief finds first valid integer from current position
	 * @retval first valid (long) integer from stream
	 */
	long parseInt();

	/**
	 * @brief finds first valid float from current position
	 * @retval first valid float from stream
	 */
	float parseFloat();

	/**
	 * @brief Writes characters from stream to buffer. Terminates if length
	 *  reached or timeout occurs
	 * @param buffer: location for characters to be written to
	 * @param length: maximum number of characters to store in buffer
	 * @retval number of characters placed in buffer. 0 means no valid data
	 */
	virtual size_t readBytes(char *buffer, size_t length);

	/**
	 * @brief Writes characters from stream to buffer. Terminates if length
	 *  reached or timeout occurs
	 * @param buffer: location for characters to be written to
	 * @param length: maximum number of characters to store in buffer
	 * @retval number of characters placed in buffer. 0 means no valid data
	 */
	virtual size_t readBytes(uint8_t *buffer, size_t length) {
		return readBytes((char *) buffer, length);
	}

	/**
	 * @brief Writes characters from stream to buffer. Terminates if length
	 *  reached, terminator found or timeout occurs
	 * @param terminator: character to terminate write
	 * @param buffer: location for characters to be written to
	 * @param length: maximum number of characters to store in buffer
	 * @retval number of characters placed in buffer. 0 means no valid data
	 */
	size_t readBytesUntil(char terminator, char *buffer, size_t length);

	/**
	 * @brief Writes characters from stream to buffer. Terminates if length
	 *  reached, terminator found or timeout occurs
	 * @param terminator: character to terminate write
	 * @param buffer: location for characters to be written to
	 * @param length: maximum number of characters to store in buffer
	 * @retval number of characters placed in buffer. 0 means no valid data
	 */
	size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length) {
		return readBytesUntil(terminator, (char *) buffer, length);
	}

protected:
	/**
	 * @brief finds first valid integer from current position and ignores skip
	 *  character
	 * @param skipChar character to skip (typically commas)
	 * @retval first valid (long) integer from stream
	 */
	long parseInt(char skipChar);

	/**
	 * @brief finds first valid float from current position and ignores skip
	 *  character
	 * @param skipChar character to skip (typically commas)
	 * @retval first valid float from stream
	 */
	float parseFloat(char skipChar);
};

#endif
