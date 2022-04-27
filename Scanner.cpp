#include "Scanner.h"
#include "Debug.h"
#include "StateMachine.h"
#include <iostream>

ScannerClass::ScannerClass(std::string filename) 
{
	MSG("Building scanner...");
	mFin.open(filename.c_str(), std::ios::binary);
	if(!mFin)
	{
		std::cout << "Could not open file: " << filename << std::endl;
	}
	this->curLineNumber = 1;
}
ScannerClass::~ScannerClass()
{
	MSG("Killing scanner...");
	this->mFin.close();
}

TokenClass ScannerClass::GetNextToken()
{
	MSG("Scanner::Getting next token");
	StateMachineClass stateMachine;
	TokenType correspondingTokenType;
	MachineState currentState = START_ST;
	std::string lexeme;
	do
	{
		char c = mFin.get();
		if(c == '\n')
		{
			this->curLineNumber++;
		}
		//std::cout << "Character is: " << c << std::endl;
		lexeme += c;
		currentState = stateMachine.UpdateState(c, correspondingTokenType);
		MSG(currentState);
		if(currentState == START_ST || currentState == END_ST)
		{
			lexeme = "";
		}
	}
	while (currentState != CANT_MOVE_ST);	
	
	mFin.unget();
	char u = mFin.get();
	if(u == '\n')
	{
		this->curLineNumber--;
	}
	mFin.unget();
	lexeme.pop_back();

	TokenClass tc(correspondingTokenType, lexeme);

	if(correspondingTokenType == BAD_TOKEN)
	{
		std::cout << "Error: Bad token encountered! " << correspondingTokenType << " tokentype  " << "Lexeme: " << lexeme << std::endl;
		std::exit(1);
	}	

	tc.CheckReserved();
	return tc;
}
TokenClass ScannerClass::PeekNextToken()
{
	//Record get position of mFin and current line number
	std::streampos curStreamPos = this->mFin.tellg();
	int curLineNum = this->curLineNumber;
	//Call GetNextToken
	TokenClass toReturn = GetNextToken();
	//if current is curly, and next is EOF, must clear before resetting.
	if(!this->mFin) {this->mFin.clear();}
	//Reset get position of mFin and current line number
	this->mFin.seekg(curStreamPos);
	this->curLineNumber = curLineNum;

	return toReturn;
	
}
const int& ScannerClass::GetCurLineNum() const
{
	return this->curLineNumber;
}
