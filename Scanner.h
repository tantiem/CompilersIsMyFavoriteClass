#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <string>
#include <iostream>
#include "Token.h"

class ScannerClass
{
	public:
		ScannerClass(std::string filename);
		~ScannerClass();
		TokenClass GetNextToken();
		TokenClass PeekNextToken();
		const int& GetCurLineNum() const;
	private:
		std::ifstream mFin;
		int curLineNumber;
};
#endif
