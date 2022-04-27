#include "Token.h"

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

TokenClass::TokenClass() {}
TokenClass::TokenClass(TokenType type, const std::string& lexeme) : mType(type), mLexeme(lexeme) {}
TokenType TokenClass::GetTokenType() const { return this->mType;}
const std::string& TokenClass::GetTokenTypeName() const { return gTokenTypeNames[mType]; }
std::string TokenClass::GetLexeme() const { return this->mLexeme;}
void TokenClass::CheckReserved()
{
	if(this->mLexeme == "void")
	{
		this->mType = VOID_TOKEN;
	}
	else if(this->mLexeme == "main")
	{
		this->mType = MAIN_TOKEN;
	}
	else if(this->mLexeme == "int")
	{
		this->mType = INT_TOKEN;
	}
	else if(this->mLexeme == "cout")
	{
		this->mType = COUT_TOKEN;
	}
	else if(this->mLexeme == "if")
	{
		this->mType = IF_TOKEN;
	}
	else if(this->mLexeme == "while")
	{
		this->mType = WHILE_TOKEN;
	}
	else if(this->mLexeme == "else")
	{
		this->mType = ELSE_TOKEN;
	}
}
//static const std::string& TokenClass::GetTokenTypeName(TokenType type) { return gTokenTypeNames[type]; }

std::ostream& operator<<(std::ostream& out, const TokenClass& tc)
{
	out << "TOKEN NAME:\t" << tc.GetTokenTypeName() << "\tLEXEME:\t" << tc.GetLexeme() << std::endl;
	return out;
}
