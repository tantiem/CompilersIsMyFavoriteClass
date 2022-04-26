// Bart Stander
// CS 4550 Compiler Class
// April, 2004
// This program demonstrates the following:
// 1. How to make an array for holding Intel instructions.
// 2. How to trick the C++ compiler to jump from main() into the array, as if it were a function.
// 3. How to code Intel instructions that call a C function that prints.
// 4. How to code Intel instructions that successfully return to control back to main().
//
// Add these VC++ compiler options so debugging assembly works properly:
// /Zi /FAs
//

#include <stdio.h>
#include <iostream>
#include "instructions.h"


int main( void )
{
	InstructionsClass instructions = InstructionsClass();
	instructions.PushValue(1000);
	instructions.PopAndWrite();

	instructions.PushVariable(10);
	instructions.PopAndStore(11);

	instructions.PushVariable(10);
	instructions.PushVariable(11);
	instructions.PopPopAddPush();
	instructions.PopAndWrite();

	instructions.PushValue(10);
	instructions.PushVariable(10);
	instructions.PopPopMulPush();
	instructions.PopAndWrite();

	instructions.PushValue(999);
	instructions.PopAndStore(10);

	instructions.PushValue(10);
	instructions.PushVariable(10);
	instructions.PopPopMulPush();
	instructions.PopAndWrite();

	instructions.Finish();
	instructions.PrintAllMachineCodes();
	instructions.Execute();

	
	/*
        unsigned char mCode[] = {0x55, 0x8B, 0xEC, 0X5d, 0XC3};
	std::cout << "About to Execute the machine code...\n";
        void * ptr = mCode;
        void (*f)(void);
        f = (void (*)(void)) ptr ;
        f(); // call the array as if it were a function
	std::cout << "There and back again!\n\n";
*/

	return 0;
}

