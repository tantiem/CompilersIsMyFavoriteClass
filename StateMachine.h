#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include "Token.h"
enum MachineState {
	START_ST, COUT_ST, MAIN_ST, INT_ST, IF_ST, WHILE_ST,ID_ST, NUM_ST, SEMI_ST, L_PAREN_ST,R_PAREN_ST,L_CURL_ST,R_CURL_ST,NE_ST,MULT_ST,DIV_ST,SUB_ST,PL_ST,ASN_ST,NOT_ST,EQ_ST,GT_ST,GE_ST,LT_ST,LE_ST,INS_ST,CANT_MOVE_ST,L_COM_ST,B_COM_ST,B_COM_ST_2,BIT_OR_ST,BIT_AND_ST,OR_ST,AND_ST,PLEQ_ST,SUBEQ_ST,END_ST,LAST_ST
};
enum CharacterType {
	LETTER_CH,DIGIT_CH,WS_CH,PLUS_CH,BAD_CH,MINUS_CH,ASTER_CH,SLASH_CH,LT_CH,GT_CH,EQ_CH,UNDER_CH,SEMI_CH,L_PAREN_CH,R_PAREN_CH,L_CURL_CH,R_CURL_CH,EXCL_CH,BAR_CH,AMP_CH,END_CH,LAST_CH
};

class StateMachineClass 
{
	public:
		StateMachineClass();
		MachineState UpdateState(char currentChar, TokenType& correspondingTokenType);
	private:
		MachineState curState;
		// matrix of legal moves
		MachineState legalMoves[LAST_ST][LAST_CH];
		// Which end-machine-states correspond to which token types.
		// (non end states correspond to the BAD_TOKEN token type)
		TokenType correspondingTokenTypes[LAST_ST];
};
#endif
