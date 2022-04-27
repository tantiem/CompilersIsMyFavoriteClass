#include "Parser.h"

#include "Debug.h"
#include <stdlib.h>
#include <cstdlib>
#include <string>


////VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN,
// Relational Operators:
////LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN,
////EQUAL_TOKEN, NOTEQUAL_TOKEN,
// Other Operators:
////INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN,
////TIMES_TOKEN, DIVIDE_TOKEN,
// Other Characters:
////SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
////RCURLY_TOKEN,
// Other Token Types:
////IDENTIFIER_TOKEN, INTEGER_TOKEN,
////BAD_TOKEN, ENDFILE_TOKEN


//public methods
ParserClass::ParserClass(ScannerClass* scannerClass, SymbolTableClass* symbolTable) : scannerClass(scannerClass), symbolTable(symbolTable) {MSG("Constructor for parserclass");}
StartNode* ParserClass::Start() // -> <Program> ENDFILE
{
	MSG("Building a program node..");
	ProgramNode *pn = Program();
	MSG("Matching for endfile");
	Match(ENDFILE_TOKEN);
	MSG("Building a start node..");
	StartNode* sn = new StartNode(pn);
	return sn;
}
//protected methods
TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass curToken = this->scannerClass->GetNextToken();
	if(curToken.GetTokenType() != expectedType)
	{
		std::cerr << "Error in ParserClass::Match. " << std::endl;
		std::cerr << "Expected token type " << TokenClass::GetTokenTypeName(expectedType)
		<< ", but got type " << curToken.GetTokenTypeName() << std::endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " << curToken.GetTokenTypeName() << ". Lexeme: \"" <<
	curToken.GetLexeme() << "\"");
	return curToken;
	
}
		
ExpressionNode* ParserClass:: Expression() //-> <Or>
{
	MSG("Building a or node..");
	ExpressionNode* en = Or();
	return en;
}
ExpressionNode* ParserClass::Or()
{
	MSG("Building an or comparison node");
	ExpressionNode* current = And();
	TokenType tt = this->scannerClass->PeekNextToken().GetTokenType();
	if(tt == OR_TOKEN)
	{
		Match(tt);
		MSG("Building an orNode by finding OR_TOKEN..");
		current = new OrNode(current,And());
	}
	return current;
}
ExpressionNode* ParserClass::And()
{
	MSG("Building an and comparison node");
	ExpressionNode* current = Relational();
	TokenType tt = this->scannerClass->PeekNextToken().GetTokenType();
	if(tt == AND_TOKEN)
	{
		Match(tt);
		MSG("Building an andNode by finding AND_TOKEN..");
		current = new AndNode(current,Relational());
	}
	return current;
}

ExpressionNode* ParserClass::Relational() //-> <PlusMinus> <RelationalTail>
{
	MSG("Building plusMinus relational node..");
	ExpressionNode* current = PlusMinus();
	return RelationalTail(current);
}
ExpressionNode* ParserClass::RelationalTail(ExpressionNode* current)
// <RelationalTail> -> LESS_TOKEN <PlusMinus>
// <RelationalTail> -> LESSEQUAL_TOKEN <PlusMinus>
// <RelationalTail> -> GREATER_TOKEN <PlusMinus>
// <RelationalTail> -> GREATEREQUAL_TOKEN <PlusMinus>
// <RelationalTail> -> EQUAL_TOKEN <PlusMinus>
// <RelationalTail> -> NOTEQUAL_TOKEN <PlusMinus>
// <RelationalTail> -> {empty}
{
	// Now handle the tail
	MSG("Handling relational tail of plus minus node..");
	TokenType tt = this->scannerClass->PeekNextToken().GetTokenType();
	switch(tt)
	{
		case LESS_TOKEN:
		{
			Match(tt);
			MSG("Building a lessNode by finding LESS_TOKEN..");
			current = new LessNode(current, PlusMinus());
			break;
		}
		case LESSEQUAL_TOKEN:
		{
			Match(tt);
			MSG("Building a lessEqual node by finding a LESSEQUAL_TOKEN");
			current = new LessEqualNode(current, PlusMinus());
			break;
		}
		case GREATER_TOKEN:
		{
			Match(tt);
			MSG("Building a greater node by finding a GREATER_TOKEN");
			current = new GreaterNode(current, PlusMinus());
			break;
		}
		case GREATEREQUAL_TOKEN:
		{
			Match(tt);
			MSG("Building a greaterEqual node by finding a GREATEREQUAL_TOKEN");
			current = new GreaterEqualNode(current, PlusMinus());
			break;
		}
		case EQUAL_TOKEN:
		{
			Match(tt);
			MSG("Building a Equal node by finding a EQUAL_TOKEN");
			current = new EqualNode(current, PlusMinus());
			break;
		}
		case NOTEQUAL_TOKEN:
		{
			Match(tt);
			MSG("Building a notEqual node by finding a NOTEQUAL_TOKEN");
			current = new NotEqualNode(current,PlusMinus());
			break;
		}
		default:
			return current;
	}
	return current;

}

ExpressionNode*  ParserClass:: PlusMinus() // <TimesDivide> <PlusMinusTail>
{
	MSG("Building a Plus minus relational node for times divide");
	ExpressionNode* current = TimesDivide();
	return PlusMinusTail(current);
}
ExpressionNode* ParserClass:: PlusMinusTail(ExpressionNode* current)
// <PlusMinusTail> -> PLUS_TOKEN <TimesDivide> <PlusMinusTail>
// <PlusMinusTail> -> MINUS_TOKEN <TimesDivide> <PlusMinusTail>
// <PlusMinusTail> -> {empty}
{
	MSG("Evaluating PlusMinus tail and moving on to Times Divide maybe");
	while(true)
	{
		TokenType tt = this->scannerClass->PeekNextToken().GetTokenType();
		switch(tt)
		{
			case PLUS_TOKEN:
				Match(tt);
				MSG("Found PLUS_TOKEN, diving into PlusNode and calling TimesDivide");
				current = new PlusNode(current,TimesDivide());
				break;
			case MINUS_TOKEN:
				Match(tt);
				MSG("Found MINUS_TOKEN, diving into MinusNode and calling TimesDivide");
				current = new MinusNode(current, TimesDivide());
				break;
			default:
				return current;
		}
	}
}

ExpressionNode* ParserClass:: TimesDivide() // -> <Factor> <TimesDivideTail>
{
	MSG("Building a TimesDivide relational node for Factor");
	ExpressionNode* current = Factor();
	return TimesDivideTail(current);
}
ExpressionNode* ParserClass:: TimesDivideTail(ExpressionNode* current)
// <TimesDivideTail> -> TIMES_TOKEN <Factor> <TimesDivideTail>
// <TimesDivideTail> -> DIVIDE_TOKEN <Factor> <TimesDivideTail>
// <TimesDivideTail> -> {empty}
{
	MSG("Beginning evaluating TimesDivideTail");
	while(true)
	{
		TokenType tt = this->scannerClass->PeekNextToken().GetTokenType();
		switch(tt)
		{
			case TIMES_TOKEN:
				Match(tt);
				MSG("Found TIMES_TOKEN, building TimesNode and calling Factor..");
				current = new TimesNode(current, Factor());
				break;
			case DIVIDE_TOKEN:
				Match(tt);
				MSG("Found DIVIDE_TOKEN, building DivideNode and calling Factor..");
				current = new DivideNode(current, Factor());
				break;
			default:
				return current;
		}

	}
}

ExpressionNode* ParserClass:: Factor()
// <Factor> → <Identifier>
// <Factor> → <Integer>
// <Factor> → LPAREN_TOKEN <Expression> RPAREN_TOKEN
{
	MSG("Evaluating Factor..");
	TokenType tt = this->scannerClass->PeekNextToken().GetTokenType();
	switch(tt)
	{
		case IDENTIFIER_TOKEN:
		{
			MSG("Found IDENTIFIER_TOKEN, building IdentifierNode by calling Identifier..");
			IdentifierNode* id = Identifier();
			return id;
		}
		case INTEGER_TOKEN:
		{
			IntegerNode* i = Integer();
			return i;
		}
		case LPAREN_TOKEN:
		{
			ExpressionNode* en = Expression();
			Match(RPAREN_TOKEN);
			return en;
		}
		default:
		{
			std::cerr << "In Factor matching, no valid token (ID, INTEGER, LPAREN) was found. QUitting..." << std::endl;
			exit(-1);
			return 0;
		}
	}
}
IdentifierNode* ParserClass:: Identifier() // -> IDENTIFIER_TOKEN
{
	TokenClass tc = Match(IDENTIFIER_TOKEN);
	IdentifierNode* id = new IdentifierNode(tc.GetLexeme(),this->symbolTable);
	return id;
}
IntegerNode* ParserClass::Integer() // -> INTEGER_TOKEN
{
	TokenClass tc = Match(INTEGER_TOKEN);
	IntegerNode* i = new IntegerNode(atoi((tc.GetLexeme().c_str())));
	return i;
}
IfClauseNode* ParserClass::IfClause()
{
	MSG("Matching IF_TOKEN");
	Match(IF_TOKEN);
	MSG("MATCHING LPAREN TOKEN for if expression");
	Match(LPAREN_TOKEN);
	MSG("Calling expression to make ExpressionNode for condition");
	ExpressionNode* condition = Expression();
	MSG("Matching R_PAREN token");
	Match(RPAREN_TOKEN);
	MSG("Building if block statement node");
	StatementNode* ifBlock = Statement();
	StatementNode* elseBlock = NULL;
	TokenType tt = this->scannerClass->PeekNextToken().GetTokenType();
	if(tt == ELSE_TOKEN)
	{
		MSG("Found else, matching that shiz");
		Match(ELSE_TOKEN);
		MSG("Building else block statement");
		elseBlock = Statement();
	}
	IfClauseNode* ifNode = new IfClauseNode(condition,ifBlock,elseBlock);
	return ifNode;
	

	//check tt for a else, if so match another statement. Otherwise, a new if node with null for else block
	//check the token type
}
WhileClauseNode* ParserClass::WhileClause()
{
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* condition = Expression();
	Match(RPAREN_TOKEN);
	StatementNode* whileBlock = Statement();
	WhileClauseNode* whileNode = new WhileClauseNode(condition,whileBlock);
	return whileNode;

}
ProgramNode* ParserClass::Program() // -> VOID MAIN LPAREN RPAREN <Block>
{
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	MSG("Building a blocknode for Program()");
	BlockNode* bn = Block();
	MSG("making a new ProgramNode()");
	ProgramNode* pn = new ProgramNode(bn);
	return pn;
}
BlockNode* ParserClass::Block() // -> LCURLY <StatementGroup> RCURLY
{
	MSG("Matching an LCURLY_TOKEN insode Block()");
	Match(LCURLY_TOKEN);
	MSG("Building a StatementGroupNode by calling StatementGroup()");
	StatementGroupNode* sgn = StatementGroup();
	MSG("Matching an RCURLY_TOKEN");
	Match(RCURLY_TOKEN);
	BlockNode* bn = new BlockNode(sgn);
	return bn;
}
StatementNode* ParserClass::Statement()
{
	StatementNode* sn;
	TokenClass peekedToken = this->scannerClass->PeekNextToken();
	switch(peekedToken.GetTokenType())
	{
		case INT_TOKEN:
			MSG("Matched int inside of statement!");
			sn = DeclarationStatement();
			break;

		case IDENTIFIER_TOKEN:
			MSG("Matched ID inside of statement!");
			sn = AssignmentStatement();
			break;

		case COUT_TOKEN:
			MSG("Matches cout inside of statement!");
			sn = CoutStatement();
			break;
		case IF_TOKEN:
			MSG("Matched if inside of statement!");
			sn = IfClause();
			break;
		case WHILE_TOKEN:
			MSG("Matched while inside of statement!");
			sn = WhileClause();
			break;
		case LCURLY_TOKEN:
			MSG("Matched LCURLY inside of statement, calling block!");
			sn = Block();
			break;
		default:
			return NULL;
	}
	return sn;
}
StatementGroupNode* ParserClass::StatementGroup()
{
	StatementGroupNode* sgn = new StatementGroupNode();
	StatementNode* sn = Statement();
	while(sn) {sgn->AddStatement(sn); sn = Statement();}
	return sgn;
}
// <StatementGroup> -> {empty}
// <StatementGroup> -> <DeclarationStatement> <StatementGroup>
// <StatementGroup> -> <AssignmentStatement> <StatementGroup>
// <StatementGroup> -> <CoutStatement> <StatementGroup>
// <StatementGroup> -> <Block> <StatementGroup>
DeclarationStatementNode* ParserClass:: DeclarationStatement() // -> INT <Identifier> SEMICOLON
{
	Match(INT_TOKEN);
	IdentifierNode* id = Identifier();
	DeclarationStatementNode* dsn = new DeclarationStatementNode(id);
	Match(SEMICOLON_TOKEN);
	return dsn;
}
AssignmentStatementNode* ParserClass:: AssignmentStatement() // -> <Identifier> ASSIGNMENT <Expression> SEMICOLON
{
	IdentifierNode* id = Identifier();
	Match(ASSIGNMENT_TOKEN);
	ExpressionNode* en = Expression();
	Match(SEMICOLON_TOKEN);
	AssignmentStatementNode* asn = new AssignmentStatementNode(id,en);
	return asn;
}
CoutStatementNode* ParserClass:: CoutStatement() // -> COUT INSERTION <Expression> SEMICOLON
{
	std::vector<ExpressionNode*> expressions;
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	TokenClass peekedToken = this->scannerClass->PeekNextToken();

	ExpressionNode* en = Expression();
	expressions.push_back(en);
	Match(SEMICOLON_TOKEN);
	CoutStatementNode* con = new CoutStatementNode(expressions);
	return con;
}

