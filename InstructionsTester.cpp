#include <iostream>
#include "instructions.h"

int main()
{
	InstructionsClass instructions = InstructionsClass();
	instructions.PushValue(1000);
	instructions.PopAndWrite();
	instructions.Finish();
	instructions.Execute();
	/*
	unsigned char mCode[] = {0x55, 0x8B, 0xEC, 0x5D, 0xC3};
	std::cout<<"Finna execute machine code..."<<std::endl;
	void * ptr = mCode;
	void (*f)(void);
	f = (void (*)(void)) ptr;
	f(); //call the array as if it were a function
	std::cout << "There and back again! " <<std::endl<<std::endl;
	*/
	std::cout << "END OF PROGRAM. YOU ARE NOT DEAD. CELEBRATE!" << std::endl;
	return 0;
}
