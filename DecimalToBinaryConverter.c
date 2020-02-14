/*
 ===================================================================================
 Name        : DecimalToBinaryConverter.c
 Author      : Nicholas Taylor
 Description : Read in decimal numbers from user input and convert to 16-bit binary
 ===================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  convertComplement is a method that takes in a binary and flips it under 2's complement rules and adds one
 *  param:	arr :: char[]
 *  return: arr :: char[]
 */
char * convertComplement(char * arr) {

	int i = 0;

	// For-loop that flips all bits
	for(i = 0 ; i < 16 ; i++) {
	        if(arr[i] == '0') {
	            arr[i] = '1';
		} else {
	            arr[i] = '0';
		}
    	}

    // Adds one when converting to 2's complement
    for(i = 15 ; i > -1 ; i--) {
        if(arr[i] == '1') {
            arr[i] = '0';
        } else {
            arr[i] = '1';
            break;
        }
    }

    return arr;

}

/**
 *  toSixteenBit is a method that takes a binary that is less than 16-bits, and makes it 16 bits
 *  param:	arr :: char[]
 *  		size :: int
 *  return: bitBinary :: char[] - 16 bits worth
 */
char * toSixteenBit(char * arr, int size) {

	char * bitBinary = malloc(17);
	int i = 0;

	// Add 0's to the start of the number to make it 16-bit, then copies the original number at the end
	for (i = 0; i < 16 ; i++) {
		if(i < 16 - size) {
			bitBinary[i] = '0';
		} else {
			bitBinary[i] = arr[i - 16 + size];
		}
	}

	bitBinary[16] = '\0';
	return bitBinary;

}

/**
 *  reverseArray is a method that reverses an array, used in the division algorithm when converting to binary
 *  param:	arr :: char[]
 *  		size :: int
 *  return: reverse :: char[] - reversed
 */
char * reverseArray(char * arr, int size) {

	char * reverse = malloc(17);
	int i = 0;

	// For-loop to reverse the array
	for(i = 0; i< size; i++) {
		reverse[i] = arr[size - 1 - i];
	}

	return reverse;

}

/**
 * integerToBinary is a method that contains the division algorithm for converting decimal numbers to binary
 * param:	num :: int
 *  		bits :: int
 * return:	binary :: char[] - returns binary of number
 */
char * integerToBinary(int num) {

	// Counter keeps track of the logical size of the binary number before 16-bit
	int counter = 0;

	char * binaryReverse = malloc(17);

	// While-loop that continues the algorithm unless the number becomes 0, which ends the process
	while(num != 0) {
		if(num % 2 == 0) {
			binaryReverse[counter] = '0';
		} else {
			binaryReverse[counter] = '1';
		}
		counter++;
	    num = num /2;
	}

	// Reverses the array computed here, then converts it to 16-bit
	char * binary = toSixteenBit(reverseArray(binaryReverse, counter), counter);
	return binary;

}

/**
 * printBinary is a method that converts a number into binary and prints it
 * param:	num :: int
 */
void printBinary(int num) {

	char *binary;

	if (num < 0) { // If negative, do 2's complement
        	binary = (convertComplement(integerToBinary(-1 * num)));
	} else { // Else, do regular procedure
        	binary = integerToBinary(num);
	}

	printf("Binary: %s\n", binary);

}

/**
 * Main Method for DecimalToBinaryConverter
 */
int main(void) {

	// Variables
	int number;

	setvbuf(stdout, NULL, _IONBF, 0); // BUG FIX for output

	// Asks user for input
	printf("Enter an integer to view it's binary form:\n");
	printf("Non-numeric input terminates program.\n");

	// While-loop to continually prompt user for integer, any other input terminates the loop
	while(scanf("%d", &number) == 1) {

		// Checks if valid integer is input; otherwise, returns to start of the while-loop
		if(number > 32767 || number < -32768) {
			printf("The number %d is too large to be held in 16-bit binary.\n", number);
			continue;
		}

		printf("Integer: %d\t", number);
		printBinary(number);

	}

	printf("Terminating");
	return EXIT_SUCCESS;

}
