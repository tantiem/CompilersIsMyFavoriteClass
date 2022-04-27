#include <iostream>
#include "Node.h"
#include "Parser.h"
#include "instructions.h"

void Interpret(std::string filename)
{
	std::cout << "Building scannerclass" << std::endl;
	ScannerClass* scanner = new ScannerClass(filename);
	std::cout << "Building symbol table class" << std::endl;
	SymbolTableClass* symbolTable = new SymbolTableClass();
	TokenClass curTok;
	std::cout << "Building parser" << std::endl;
	ParserClass p = ParserClass(scanner,symbolTable);
	std::cout << "Building startNode" << std::endl;
	StartNode* sn = p.Start();
	sn->Interpret();
	delete sn;

}

void CodeAndExecute(std::string filename)
{
	// Create scanner, symbol table, parser objects.
	ScannerClass scanner(filename);
	SymbolTableClass symbolTable;
	ParserClass parser(&scanner, &symbolTable);
	
	// Do the parsing, which results in a parse tree.
	StartNode *root = parser.Start();

	// Create the machine code instructions from the parse tree
	InstructionsClass machineCode;
	root->Code(machineCode);
	machineCode.Finish();
	machineCode.PrintAllMachineCodes();

	// Execute the machine code instructions previously created
	machineCode.Execute();

	// cleanup recursively
	delete root;
}

int main()
{
/*
	TokenType tt = VOID_TOKEN;
	std::string lexeme = "void";
	TokenClass tok1(tt, lexeme);
	std::cout << tok1 << std::endl;
*/

	std::string filename;
	std::cout << "File to run: ";
	std::cin >> filename;
	std::cout << std::endl;

	std::string choice;
	std::cout << "Code and execute, or parse? (code || interpret): ";
	std::cin >> choice;
	std::cout << std::endl;

	if(choice == "code") { CodeAndExecute(filename); }
	else if(choice == "interpret") { Interpret(filename); }
	else { std::cout << "Fine be that way, later loser! :P" << std::endl; }
//	SymbolTableClass* sc = new SymbolTableClass();
	//do
	//{
	//	curTok = scanner.GetNextToken();
	//	std::cout << "Line: " << scanner.GetCurLineNum() << " " << curTok << std::endl;
	//}
	//while(curTok.GetTokenType() != ENDFILE_TOKEN);
	//return 0;
}


