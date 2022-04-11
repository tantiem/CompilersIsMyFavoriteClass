#include <iostream>
#include "Instructions.h"
#include "InstructionsCopy.h"


void test_problem_13() {
    InstructionsClass instructions;
    instructions.PushValue(1000);
    instructions.PopAndWrite();
    instructions.Finish();
    instructions.PrintAllMachineCodes();
    instructions.Execute();
    std::cout << "Success on problems 1-13!" << std::endl;
}

void test_problem_14() {
    InstructionsClassCopy instructionsC;
    instructionsC.PushVariable(10);
    instructionsC.PopAndStore(11);
    instructionsC.PushVariable(10);
    instructionsC.PushVariable(11);
    instructionsC.PopPopAndPush();
    instructionsC.PopAndWrite();
    instructionsC.Finish();
    instructionsC.PrintAllMachineCodes();
    instructionsC.Execute();
    std::cout << "Success on number 14!" << std::endl;
}

int main() {
    //Switch case to see which problem we should be solving
    int userInput;
    std::cout << "Enter 1 to run the initial test: " << std::endl;
    std::cout << "Enter 2 to test problem 14: " << std::endl;
    std::cin >> userInput;
    switch(userInput) {
        case 1:
            test_problem_13();
            break;
        case 2:
            test_problem_14();
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            break;
    }
    return 1;
}
InstructionsClass::InstructionsClass() {}
void InstructionsClass::PushValue(int) {}
void InstructionsClass::PopAndWrite() {}
void InstructionsClass::Finish() {}
void InstructionsClass::PrintAllMachineCodes() {}
void InstructionsClass::Execute() {}
