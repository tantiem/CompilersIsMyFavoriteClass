#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Node.h"

class ParserClass
{
	public:
		ParserClass(ScannerClass* scannerClass, SymbolTableClass* symbolTable);
		StartNode* Start(); // -> <Program> ENDFILE
	protected:
		TokenClass Match(TokenType expectedType);
		
		ExpressionNode* Expression(); //-> <Relational>

		ExpressionNode* Or();
		ExpressionNode* And();

		ExpressionNode* Relational(); //-> <PlusMinus> <RelationalTail>
		ExpressionNode* RelationalTail(ExpressionNode*); 
		// <RelationalTail> -> LESS_TOKEN <PlusMinus>
		// <RelationalTail> -> LESSEQUAL_TOKEN <PlusMinus>
		// <RelationalTail> -> GREATER_TOKEN <PlusMinus>
		// <RelationalTail> -> GREATEREQUAL_TOKEN <PlusMinus>
		// <RelationalTail> -> EQUAL_TOKEN <PlusMinus>
		// <RelationalTail> -> NOTEQUAL_TOKEN <PlusMinus>
		// <RelationalTail> -> {empty}

		ExpressionNode* PlusMinus(); // <TimesDivide> <PlusMinusTail>
		ExpressionNode* PlusMinusTail(ExpressionNode* current);
		// <PlusMinusTail> -> PLUS_TOKEN <TimesDivide> <PlusMinusTail>
		// <PlusMinusTail> -> MINUS_TOKEN <TimesDivide> <PlusMinusTail>
		// <PlusMinusTail> -> {empty}

		ExpressionNode* TimesDivide(); // -> <Factor> <TimesDivideTail>
		ExpressionNode* TimesDivideTail(ExpressionNode* current);
		// <TimesDivideTail> -> TIMES_TOKEN <Factor> <TimesDivideTail>
		// <TimesDivideTail> -> DIVIDE_TOKEN <Factor> <TimesDivideTail>
		// <TimesDivideTail> -> {empty}

		ExpressionNode* Factor();
		// <Factor> → <Identifier>
		// <Factor> → <Integer>
		// <Factor> → LPAREN_TOKEN <Expression> RPAREN_TOKEN
		IdentifierNode* Identifier(); // -> IDENTIFIER_TOKEN
		IntegerNode* Integer(); // -> INTEGER_TOKEN

		IfClauseNode* IfClause();
		WhileClauseNode* WhileClause();

		ProgramNode* Program(); // -> VOID MAIN LPAREN RPAREN <Block>
		BlockNode* Block(); // -> LCURLY <StatementGroup> RCURLY
		StatementNode* Statement();
		StatementGroupNode* StatementGroup();
		// <StatementGroup> -> {empty}
		// <StatementGroup> -> <DeclarationStatement> <StatementGroup>
		// <StatementGroup> -> <AssignmentStatement> <StatementGroup>
		// <StatementGroup> -> <CoutStatement> <StatementGroup>
		// <StatementGroup> -> <Block> <StatementGroup>
		DeclarationStatementNode* DeclarationStatement(); // -> INT <Identifier> SEMICOLON
		AssignmentStatementNode* AssignmentStatement(); // -> <Identifier> ASSIGNMENT <Expression> SEMICOLON
		CoutStatementNode* CoutStatement(); // -> COUT INSERTION <Expression> SEMICOLON
		
	private:
		ScannerClass* scannerClass;
		SymbolTableClass* symbolTable;
};

#endif
