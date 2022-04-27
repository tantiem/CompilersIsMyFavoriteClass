#include "StateMachine.h"
#include "Debug.h"

StateMachineClass::StateMachineClass() : curState(START_ST)
{
	MSG("Building state machine...");
	// First, initialize all the mLegalMoves to CANTMOVE_STATE
	// Then, reset the mLegalMoves that are legitimate
	int i,j;
	for(i = 0; i < LAST_ST; i++)
	{
		for(j = 0; j < LAST_CH; j++)
		{
			this->legalMoves[i][j] = CANT_MOVE_ST;
		}
	}
	this->legalMoves[START_ST][DIGIT_CH] = NUM_ST;
	this->legalMoves[NUM_ST][DIGIT_CH] = NUM_ST;
	this->legalMoves[START_ST][LETTER_CH] = ID_ST;
	this->legalMoves[ID_ST][LETTER_CH] = ID_ST;
	this->legalMoves[ID_ST][DIGIT_CH] = ID_ST;
	this->legalMoves[ID_ST][UNDER_CH] = ID_ST;
	this->legalMoves[START_ST][DIGIT_CH] = NUM_ST;
	this->legalMoves[NUM_ST][DIGIT_CH] = NUM_ST;
	this->legalMoves[START_ST][SEMI_CH] = SEMI_ST;
	this->legalMoves[START_ST][L_PAREN_CH] = L_PAREN_ST;
	this->legalMoves[START_ST][R_PAREN_CH] = R_PAREN_ST;
	this->legalMoves[START_ST][L_CURL_CH] = L_CURL_ST;
	this->legalMoves[START_ST][R_CURL_CH] = R_CURL_ST;
	this->legalMoves[START_ST][EXCL_CH] = NOT_ST;
	this->legalMoves[NOT_ST][EQ_CH] = NE_ST;
	this->legalMoves[START_ST][ASTER_CH] = MULT_ST;
	this->legalMoves[START_ST][SLASH_CH] = DIV_ST;
	this->legalMoves[START_ST][MINUS_CH] = SUB_ST;
	this->legalMoves[START_ST][PLUS_CH] = PL_ST;
	this->legalMoves[START_ST][EQ_CH] = ASN_ST;
	this->legalMoves[ASN_ST][EQ_CH] = EQ_ST;	
	this->legalMoves[START_ST][GT_CH] = GT_ST;
	this->legalMoves[GT_ST][EQ_CH] = GE_ST;
	this->legalMoves[START_ST][LT_CH] = LT_ST;
	this->legalMoves[LT_ST][EQ_CH] = LE_ST;
	this->legalMoves[LT_ST][LT_CH] = INS_ST;
	this->legalMoves[START_ST][END_CH] = END_ST;
	this->legalMoves[START_ST][WS_CH] = START_ST;
	//block comment and comment stuffs
	this->legalMoves[DIV_ST][SLASH_CH] = L_COM_ST;
	this->legalMoves[DIV_ST][ASTER_CH] = B_COM_ST;
	//or / and
	this->legalMoves[START_ST][BAR_CH] = BIT_OR_ST;
	this->legalMoves[BIT_OR_ST][BAR_CH] = OR_ST;
	this->legalMoves[START_ST][AMP_CH] = BIT_AND_ST;
	this->legalMoves[BIT_AND_ST][AMP_CH] = AND_ST;
	//plus eq and sub eq
	this->legalMoves[PL_ST][EQ_CH] = PLEQ_ST;
	this->legalMoves[SUB_ST][EQ_CH] = SUBEQ_ST;

	for(int i = 0; i < LAST_CH; i++)
	{
		this->legalMoves[L_COM_ST][i] = L_COM_ST;
		this->legalMoves[B_COM_ST][i] = B_COM_ST;
		this->legalMoves[B_COM_ST_2][i] = B_COM_ST;
	}
	this->legalMoves[L_COM_ST]['\n'] = START_ST;
	this->legalMoves[B_COM_ST][ASTER_CH] = B_COM_ST_2;
	this->legalMoves[B_COM_ST_2][SLASH_CH] = START_ST;

	
	
	// Then, reset the end states to correspond to the correct token types.
	for(i = 0; i < LAST_ST; i++)
	{
		this->correspondingTokenTypes[i] = BAD_TOKEN;
	}
	this->correspondingTokenTypes[COUT_ST] = COUT_TOKEN;
	this->correspondingTokenTypes[MAIN_ST] = MAIN_TOKEN;
	this->correspondingTokenTypes[INT_ST] = INT_TOKEN;
	this->correspondingTokenTypes[IF_ST] = IF_TOKEN;
	this->correspondingTokenTypes[WHILE_ST] = WHILE_TOKEN;
	this->correspondingTokenTypes[ID_ST] = IDENTIFIER_TOKEN;
	this->correspondingTokenTypes[NUM_ST] = INTEGER_TOKEN;
	this->correspondingTokenTypes[SEMI_ST] = SEMICOLON_TOKEN;
	this->correspondingTokenTypes[L_PAREN_ST] = LPAREN_TOKEN;
	this->correspondingTokenTypes[R_PAREN_ST] = RPAREN_TOKEN;
	this->correspondingTokenTypes[L_CURL_ST] = LCURLY_TOKEN;
	this->correspondingTokenTypes[R_CURL_ST] = RCURLY_TOKEN;
	this->correspondingTokenTypes[NE_ST] = NOTEQUAL_TOKEN;
	this->correspondingTokenTypes[MULT_ST] = TIMES_TOKEN;
	this->correspondingTokenTypes[DIV_ST] = DIVIDE_TOKEN;
	this->correspondingTokenTypes[SUB_ST] = MINUS_TOKEN;
	this->correspondingTokenTypes[PL_ST] = PLUS_TOKEN;
	this->correspondingTokenTypes[ASN_ST] = ASSIGNMENT_TOKEN;
	this->correspondingTokenTypes[EQ_ST] = EQUAL_TOKEN;
	this->correspondingTokenTypes[GT_ST] = GREATER_TOKEN;
	this->correspondingTokenTypes[GE_ST] = GREATEREQUAL_TOKEN;
	this->correspondingTokenTypes[LT_ST] = LESS_TOKEN;
	this->correspondingTokenTypes[LE_ST] = LESSEQUAL_TOKEN;
	this->correspondingTokenTypes[INS_ST] = INSERTION_TOKEN;
	this->correspondingTokenTypes[OR_ST] = OR_TOKEN;
	this->correspondingTokenTypes[AND_ST] = AND_TOKEN;
	this->correspondingTokenTypes[PLEQ_ST] = PLUSEQUAL_TOKEN;
	this->correspondingTokenTypes[SUBEQ_ST] = MINUSEQUAL_TOKEN;
	this->correspondingTokenTypes[END_ST] = ENDFILE_TOKEN;
}
MachineState StateMachineClass::UpdateState(char currentChar, TokenType& correspondingTokenType)
{
	MSG("Updating state...");
	CharacterType charType = BAD_CH;
	
	if(currentChar >= '0' && currentChar <= '9')
	{
		charType = DIGIT_CH;
	}
	else if(currentChar >= 'A' && currentChar <= 'z')
	{
		charType = LETTER_CH;
	}

	switch(currentChar)
	{
		case '\n':
		case ' ':
		case '\t':
			charType = WS_CH;
			break;
		case '+':
			charType = PLUS_CH;
			break;
		case '-':
			charType = MINUS_CH;
			break;
		case '*':
			charType = ASTER_CH;
			break;
		case '/':
			charType = SLASH_CH;
			break;
		case '<':
			charType = LT_CH;
			break;
		case '>':
			charType = GT_CH;
			break;
		case '=':
			charType = EQ_CH;
			break;
		case '_':
			charType = UNDER_CH;
			break;
		case ';':
			charType = SEMI_CH;
			break;
		case '(':
			charType = L_PAREN_CH;
			break;
		case ')':
			charType = R_PAREN_CH;
			break;
		case '{':
			charType = L_CURL_CH;
			break;
		case '}':
			charType = R_CURL_CH;
			break;
		case '!':
			charType = EXCL_CH;
			break;
		case '|':
			charType = BAR_CH;
			break;
		case '&':
			charType = AMP_CH;
			break;
		case -1:
			charType = END_CH;
			break;

	}
	correspondingTokenType = this->correspondingTokenTypes[this->curState];
	this->curState = this->legalMoves[this->curState][charType];
	return this->curState;
}
