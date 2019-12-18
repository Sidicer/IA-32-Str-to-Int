#include <iostream>
#include <stdio.h>

int main(int argument_count, char** argument_values) {
	int output;
	if (argument_count < 2) {
		printf("Missing values in arguments\n");
		return 0;
	}

	char* input= argument_values[1]; // 0 - file name, 1,2,3,... - argument values

	__asm {
		// Creating (pushing) registers (like variables):
		push eax
		push ebx
		push ecx

		xor ebx, ebx // Zeros out ebx register
		mov ecx, input // Move C++ variable "input" into assembler register "ecx"
		dec ecx // Decrements the ecx value by 1 (to start the upcoming loop from the beginning)

		my_loop :
			inc ecx // Increments ecx value by 1
			mov al, byte ptr[ecx] // Moving a symbol from ecx byte into "al" registry

			cmp al, 0 // Compares the "al" registry to 0
			jz loop_ending // If there are no more values - jumps to the end

			sub al, '0' // Subtracts a '0' from 'al' (al = al - '0')
			imul ebx, 10 // Multiplies ebx registry by 10
			add ebx, eax // Adds eax to ebx registry
			jmp my_loop // Loops to the beginning

		loop_ending:
			mov output, ebx // Moves ebx registry value to c++ "output" variable

			pop ecx
			pop ebx
			pop eax

	}

	printf("String to int converted: %i\n", output);
	return 0;
}
