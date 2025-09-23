#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convert.h"

//convert any 32-bit unsigned integer to a 32-character binary string
static void to_32_bit_binary(uint32_t value, char* out) {
	//iterate to most significant bit to least
	for (int i = 31; i >= 0; i--) {
		//Shift bit at position i to the rightmost position
		uint32_t bit = ((value >> i) & 1);
		//output string left to right
		out[31 - i] =  bit ? '1' : '0';
	}
	out[32] = '\0'; //end string
}
//Direct Mapping Functions

//converts an octal string to a binary representation
void oct_to_bin(const char* oct, char* out) {
	//table for each octal digit to its binary equivalent
	const char* oct_map[] = {"000","001","010","011","100","101","110","111"};
	//start with empty string
	out[0] = '\0';
	//iterate through the characters of the octal string
	for (int i = 0; i < strlen(oct); i++) {
		//convert character digit into an integer
		int digit = oct[i] - '0';
		//Append the corresponding string to the output
		strcat(out, oct_map[digit]);
	}
}
//converts octal string to hexadecimal representation
void oct_to_hex(const char* oct, char* out) {
	//Convert octal to binary
	char binaryString[100];
	oct_to_bin(oct, binaryString);
	//Group binary string by 4 bits then conver to hex
	char paddedBinaryStr[104] = ""; //Buffer
	int len = strlen(binaryString);
	int padding = (4 - (len % 4)) % 4; //How many '0's
	//Prepend the padding
	for (int i = 0; i < padding; i++) {
		strcat(paddedBinaryStr, "0");
	}
	strcat(paddedBinaryStr, binaryString);
	//Process in 4-bit chunks
	int pos = 0;
	for (int i = 0; i < strlen(paddedBinaryStr); i += 4) {
		char chunk[5];
		strncpy(chunk, &paddedBinaryStr[i], 4);
		chunk[4] = '\0';
		//convert 4-bit chunk to respective hex character
		if (strcmp(chunk, "0000") == 0) out[pos++] = '0';
		else if (strcmp(chunk, "0001") == 0) out[pos++] = '1';
		else if (strcmp(chunk, "0010") == 0) out[pos++] = '2';
		else if (strcmp(chunk, "0011") == 0) out[pos++] = '3';
		else if (strcmp(chunk, "0100") == 0) out[pos++] = '4';
		else if (strcmp(chunk, "0101") == 0) out[pos++] = '5';
		else if (strcmp(chunk, "0110") == 0) out[pos++] = '6';
		else if (strcmp(chunk, "0111") == 0) out[pos++] = '7';
		else if (strcmp(chunk, "1000") == 0) out[pos++] = '8';
		else if (strcmp(chunk, "1001") == 0) out[pos++] = '9';
		else if (strcmp(chunk, "1010") == 0) out[pos++] = 'A';
		else if (strcmp(chunk, "1011") == 0) out[pos++] = 'B';
		else if (strcmp(chunk, "1100") == 0) out[pos++] = 'C';
		else if (strcmp(chunk, "1101") == 0) out[pos++] = 'D';
		else if (strcmp(chunk, "1110") == 0) out[pos++] = 'E';
		else if (strcmp(chunk, "1111") == 0) out[pos++] = 'F';
	}
	out[pos] = '\0';
	if (out[0] == '0' && out[1] != '\0') {
		//moves block of memory starting at out + 1  to out
		memmove(out, out + 1, strlen(out));
	}
}
//converts hexadecimal string to binary representation
void hex_to_bin(const char* hex, char* out) {
	//Start with empty string
	out[0] = '\0';
	//iterate through the characters of the hex string
	for (int i = 0; i < strlen(hex); i++) {
		//Switch handle all the values, including the lowercase characters
		switch (hex[i]) {
		case '0': strcat(out, "0000"); break;
		case '1': strcat(out, "0001"); break;
		case '2': strcat(out, "0010"); break;
		case '3': strcat(out, "0011"); break;
		case '4': strcat(out, "0100"); break;
		case '5': strcat(out, "0101"); break;
		case '6': strcat(out, "0110"); break;
		case '7': strcat(out, "0111"); break;
		case '8': strcat(out, "1000"); break;
		case '9': strcat(out, "1001"); break;
		case 'A': case 'a': strcat(out, "1010"); break;
		case 'B': case 'b': strcat(out, "1011"); break;
		case 'C': case 'c': strcat(out, "1100"); break;
		case 'D': case 'd': strcat(out, "1101"); break;
		case 'E': case 'e': strcat(out, "1110"); break;
		case 'F': case 'f': strcat(out, "1111"); break;
		}
	}
}

//Signed Number Representations

//Generates the sign-magnitude representation of a signed integer
void to_sign_magnitude(int32_t n, char* out) {
	//Get absolute value of the number (magnitude)
	uint32_t magnitude = abs(n);
	//Convert to a 32-bit binary string
	to_32_bit_binary(magnitude, out);
	//If original number was negative, se tthe sign bit to 1
	if (n < 0) {
		out[0] = '1';
	}
}
//Generates the one's complement representation of a signed integer
void to_ones_complement(int32_t n, char* out) {
	if (n >= 0) {
		//Positive numbers get the same representation as standard binary
		to_32_bit_binary(n, out);
	}
	else {
		//Negative numbers get positive representation and flip the numbers through a for loop
		uint32_t magnitude = abs(n);
		to_32_bit_binary(magnitude, out);
		for (int i = 0; i < 32; i++) {
			if (out[i] == '0') {
				out[i] = '1';
			}
			else {
				out[i] = '0';
			}
		}
	}
}
//Generates the two's complement representation of a signed integer
void to_twos_complement(int32_t n, char* out) {
	//Bit pattern of an int32_t is already in two's complement form
	//Cast the signed integer to an unsigned one to read it raw
	uint32_t bit_pattern = (uint32_t)n;
	//convert raw bit pattern to a 32-bit binary string
	to_32_bit_binary(bit_pattern, out);
}