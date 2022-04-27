#include "Node.h"
#include "Debug.h"
#include "instructions.h"

//EXPRESSION NODE ONLY
ExpressionNode::~ExpressionNode() {}
int ExpressionNode::Evaluate() {return -1;}

IntegerNode::IntegerNode(const int& value) : value(value) {}
int IntegerNode::Evaluate()
{
	return this->value;
}
void IntegerNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n an integer node.");
	machineCode.PushValue(this->value);
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass* symbolTable) : label(label), symbolTable(symbolTable) {}
void IdentifierNode::DeclareVariable()
{
	this->symbolTable->AddEntry(this->label);
}
void IdentifierNode::SetValue(int v)
{
	this->symbolTable->SetValue(this->label, v);
}
int IdentifierNode::GetIndex()
{
	return this->symbolTable->GetIndex(this->label);	
}
int IdentifierNode::Evaluate()
{
	return this->symbolTable->GetValue(this->label);
}
void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n an id node");
	machineCode.PushVariable(this->GetIndex());
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : leftNode(leftNode), rightNode(rightNode) {}
BinaryOperatorNode::~BinaryOperatorNode()
{
	delete this->leftNode;
	MSG("DELETING leftNode of BinaryOperatorNode");
	delete this->rightNode;
	MSG("DELETING rightNode of BinaryOperatorNode");
	MSG("DELETING BinaryOperatorNode");
}

//EXPRESSIONNODE -> BINARYOPERATORNODE INHERITERS
OrNode::OrNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int OrNode::Evaluate()
{
	return this->leftNode->Evaluate() || this->rightNode->Evaluate();
}
void OrNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: code eval'n an or node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopOrPush();
}
AndNode::AndNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int AndNode::Evaluate()
{
	return this->leftNode->Evaluate() && this->rightNode->Evaluate();
}
void AndNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: code eval'n the and node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopAndPush();
}

PlusNode::PlusNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int PlusNode::Evaluate()
{
	return this->leftNode->Evaluate() + this->rightNode->Evaluate();
}
void PlusNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: code eval'n the plus node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
}
MinusNode::MinusNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int MinusNode::Evaluate()
{
	return this->leftNode->Evaluate() - this->rightNode->Evaluate();
}
void MinusNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: code eval'n minus node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
}
TimesNode::TimesNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int TimesNode::Evaluate()
{
	return this->leftNode->Evaluate() * this->rightNode->Evaluate();
}
void TimesNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: code eval'n times node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopMulPush();
}
DivideNode::DivideNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int DivideNode::Evaluate()
{
	return this->leftNode->Evaluate() / this->rightNode->Evaluate();
}
void DivideNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n a div node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopDivPush();
}
LessNode::LessNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int LessNode::Evaluate()
{
	return this->leftNode->Evaluate() < this->rightNode->Evaluate();
}
void LessNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n a less node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopLessPush();
}
LessEqualNode::LessEqualNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int LessEqualNode::Evaluate()
{
	return this->leftNode->Evaluate() <= this->rightNode->Evaluate();
}
void LessEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n a less equal node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();

}
GreaterNode::GreaterNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int GreaterNode::Evaluate()
{
	return this->leftNode->Evaluate() > this->rightNode->Evaluate();
}
void GreaterNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n a greater node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopGreaterPush();
}
GreaterEqualNode::GreaterEqualNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int GreaterEqualNode::Evaluate()
{
	return this->leftNode->Evaluate() >= this->rightNode->Evaluate();
}
void GreaterEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n a greater equal node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopLessEqualPush();

}
EqualNode::EqualNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int EqualNode::Evaluate()
{
	return this->leftNode->Evaluate() == this->rightNode->Evaluate();
}
void EqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n an equal node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopEqualPush();
}
NotEqualNode::NotEqualNode(ExpressionNode* leftNode, ExpressionNode* rightNode) : BinaryOperatorNode(leftNode,rightNode) {}
int NotEqualNode::Evaluate()
{
	return this->leftNode->Evaluate() != this->rightNode->Evaluate();
}
void NotEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	MSG("CODING: eval'n a not equal node.");
	this->leftNode->CodeEvaluate(machineCode);
	this->rightNode->CodeEvaluate(machineCode);
	machineCode.PopPopNotEqualPush();
}
//NODE -> STATEMENTNODE INHERITERS
Node::~Node() {}
int Node::Interpret() {return -1; MSG("YOU SHOULD NEVER SEE THIS TEXT");}
StatementNode::~StatementNode() {}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* identifierNode) : identifierNode(identifierNode) {}
DeclarationStatementNode::~DeclarationStatementNode()
{
	delete this->identifierNode;
	MSG("DELETING identifierNode of DeclarationStatementNode");
	MSG("DELETING DeclarationStatementNode");
}
int DeclarationStatementNode::Interpret()
{
	MSG(" INTERPRET: Declaration statementnode, declaring variable.");
	this->identifierNode->DeclareVariable();
	return 1;
}
void DeclarationStatementNode::Code(InstructionsClass &machineCode)
{
	MSG("CODING: declarationstatementnode coding stuff.");
	this->identifierNode->DeclareVariable();
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode) : identifierNode(identifierNode), expressionNode(expressionNode) {}
AssignmentStatementNode::~AssignmentStatementNode()
{
	delete this->identifierNode;
	MSG("DELETING identifierNode of AssignmentStatementNode");
	delete this->expressionNode;	
	MSG("DELETING expressionNode of AssignmentStatementNode");
	MSG("DELETING AssignmentStatementNode");
}
int AssignmentStatementNode::Interpret()
{
	MSG("INTERPRET: evaluating and setting value from assign satement node.");
	int value = this->expressionNode->Evaluate();
	this->identifierNode->SetValue(value);
	return 1;
}
void AssignmentStatementNode::Code(InstructionsClass &machineCode)
{
	MSG("CODING: code eval'n an set'n values bruv.");
	this->expressionNode->CodeEvaluate(machineCode);
	int index = this->identifierNode->GetIndex();
	machineCode.PopAndStore(index);
}

/////////////pe me////////////////////////

PlusEqualsStatementNode::PlusEqualsStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode) : identifierNode(identifierNode), expressionNode(expressionNode) {}
PlusEqualsStatementNode::~PlusEqualsStatementNode()
{
	delete this->identifierNode;
	MSG("DELETING identifierNode of PlusEqualsStatementNode");
	delete this->expressionNode;	
	MSG("DELETING expressionNode of PlusEqualsStatementNode");
	MSG("DELETING PlusEqualsStatementNode");
}
int PlusEqualsStatementNode::Interpret()
{
	MSG("INTERPRET: evaluating and setting value from plus eq satement node.");
	int value = this->expressionNode->Evaluate();
	int var = this->identifierNode->Evaluate();
	this->identifierNode->SetValue(var + value);
	return 1;
}
void PlusEqualsStatementNode::Code(InstructionsClass &machineCode)
{

	MSG("CODING: code eval'n an set'n values bruv.");
	int index = this->identifierNode->GetIndex();
	machineCode.PushVariable(index);
	this->expressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopAddPush();
	machineCode.PopAndStore(index);

}


MinusEqualsStatementNode::MinusEqualsStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode) : identifierNode(identifierNode), expressionNode(expressionNode) {}
MinusEqualsStatementNode::~MinusEqualsStatementNode()
{
	delete this->identifierNode;
	MSG("DELETING identifierNode of MinusEqualsStatementNode");
	delete this->expressionNode;	
	MSG("DELETING expressionNode of MinusEqualsStatementNode");
	MSG("DELETING MinusEqualsStatementNode");
}
int MinusEqualsStatementNode::Interpret()
{
	MSG("INTERPRET: evaluating and setting value from plus eq satement node.");
	int value = this->expressionNode->Evaluate();
	int var = this->identifierNode->Evaluate();
	this->identifierNode->SetValue(var-value);
	return 1;
}
void MinusEqualsStatementNode::Code(InstructionsClass &machineCode)
{

	MSG("CODING: code eval'n an set'n values bruv.");
	int index = this->identifierNode->GetIndex();
	machineCode.PushVariable(index);
	this->expressionNode->CodeEvaluate(machineCode);
	machineCode.PopPopSubPush();
	machineCode.PopAndStore(index);

}

/////////////pe me/////////////////////////

CoutStatementNode::CoutStatementNode(std::vector<ExpressionNode*> expressionNode) : expressionNode(expressionNode) {}
CoutStatementNode::~CoutStatementNode()
{
	MSG("DELETING expressionNodes of CoutStatementNode");
	int size = this->expressionNode.size();
	for(int i = 0; i < size; i++)
	{
		delete this->expressionNode[i];
	}
	MSG("DELETING CoutStatementNode");
}
int CoutStatementNode::Interpret()
{
	MSG("INTERPRET: couting value contained");
	int size = this->expressionNode.size();
	for(int i = 0; i < size; i++)
	{
		if(this->expressionNode[i] == NULL)
		{
			std::cout<<std::endl;
		}
		else
		{
			int value = this->expressionNode[i]->Evaluate();
			std::cout<<value;
		}
	}
	return 1;
}
void CoutStatementNode::Code(InstructionsClass &machineCode)
{
	MSG("CODING: couting the bloody RURRURUR");
	int size = this->expressionNode.size();
	for(int i = 0; i < size; i++)
	{
		if(this->expressionNode[i] == NULL)
		{
			machineCode.WriteEndl();
		}
		else
		{
			this->expressionNode[i]->CodeEvaluate(machineCode);
			machineCode.PopAndWrite();	
		}
	}
}

//NODE ONLY INHERITERS
StatementGroupNode::StatementGroupNode() : statementNodes(0) {}
StatementGroupNode::~StatementGroupNode()
{
	for(int i = 0; i < (int)this->statementNodes.size(); i++)
	{
		delete this->statementNodes[i];
		MSG("DELETING statementNode *i* of StatementGroupNode. i =");
		MSG(i);
	}
}
void StatementGroupNode::AddStatement(StatementNode* toAdd)
{
	this->statementNodes.push_back(toAdd);
}
int StatementGroupNode::Interpret()
{
	MSG(" INTERPRET: Interpretting all statement nodes in this group");
	int size = this->statementNodes.size();
	for(int i = 0; i < size; i++)
	{
		this->statementNodes[i]->Interpret();
	}
	return 1;
}
void StatementGroupNode::Code(InstructionsClass &machineCode)
{
	MSG("CODING: Coding all statement nodes in this group node");
	int size = this->statementNodes.size();
	for(int i = 0; i < size; i++)
	{
		this->statementNodes[i]->Code(machineCode);
	}
}

BlockNode::BlockNode(StatementGroupNode* statementGroupNode) : statementGroupNode(statementGroupNode) {}
BlockNode::~BlockNode()
{
	delete this->statementGroupNode;
	MSG("DELETING statementGroupNode of BlockNode");
	MSG("DELETING BlockNode");
}
int BlockNode::Interpret()
{
	MSG("INTERPRET: Interpretting a block node");
	this->statementGroupNode->Interpret();
	return 1;
}
void BlockNode::Code(InstructionsClass &machineCode)
{
	MSG("CODING: Coding statementgroupnode of blocknode.");
	this->statementGroupNode->Code(machineCode);
}
WhileClauseNode::WhileClauseNode(ExpressionNode* condition, StatementNode* whileBlock) : condition(condition), whileBlock(whileBlock) {}
WhileClauseNode::~WhileClauseNode()
{
	delete this->whileBlock;
	MSG("DELETING whileBlock of WhileClauseNode");
	delete this->condition;
	MSG("DELETING condition expression of WhileClauseNode");
	MSG("DELETING WhileClauseNode");
}
int WhileClauseNode::Interpret()
{
	MSG("INTERPRET: Interpretting a while node");
	while(this->condition->Evaluate())
	{
		this->whileBlock->Interpret();
	}
	return 1;
}
void WhileClauseNode::Code(InstructionsClass &machineCode)
{
	MSG("CODING: codin the while node.");
	unsigned char* address1 = machineCode.GetAddress();
	this->condition->CodeEvaluate(machineCode);
	unsigned char* InsertAddressToSkip = machineCode.SkipIfZeroStack();
	unsigned char* address2 = machineCode.GetAddress();
	this->whileBlock->Code(machineCode);
	unsigned char* InsertAddressToJump = machineCode.Jump();
	unsigned char* address3 = machineCode.GetAddress();
	
	machineCode.SetOffset(InsertAddressToSkip,(int)(address3 - address2));
	//this next one jumps back
	machineCode.SetOffset(InsertAddressToJump,(int)(address1 - address3));
	
}
IfClauseNode::IfClauseNode(ExpressionNode* condition, StatementNode* ifBlock, StatementNode* elseBlock) : condition(condition),ifBlock(ifBlock),elseBlock(elseBlock) {}
IfClauseNode::~IfClauseNode()
{
	delete this->elseBlock;
	MSG("DELETING elseBlock of IfClauseNode");
	delete this->ifBlock;
	MSG("DELETING ifBlock of IfClauseNode");
	delete this->condition;
	MSG("DELETING condition of IfClauseNode");
	MSG("DELETING IfClauseNode");
}
int IfClauseNode::Interpret()
{
	MSG("INTERPRET: Interpretting if node");
	if(this->condition->Evaluate())
	{
		this->ifBlock->Interpret();
	}
	else
	{
		if(this->elseBlock != NULL)
		{
			this->elseBlock->Interpret();
		}
	}
	return 1;
}
void IfClauseNode::Code(InstructionsClass &machineCode)
{
	MSG("CODING: coding the rarted if node");
	this->condition->CodeEvaluate(machineCode);
	unsigned char* InsertAddress = machineCode.SkipIfZeroStack();
	unsigned char* address1 = machineCode.GetAddress();
	this->ifBlock->Code(machineCode);
	unsigned char* InsertAddress2 = machineCode.Jump();
	unsigned char* address2 = machineCode.GetAddress();
	if(elseBlock != NULL){this->elseBlock->Code(machineCode);}
	unsigned char* address3 = machineCode.GetAddress();
	machineCode.SetOffset(InsertAddress, (int)(address2-address1));
	machineCode.SetOffset(InsertAddress2, (int)(address3-address2));
	
}
ProgramNode::ProgramNode(BlockNode* blockNode) : blockNode(blockNode) {}
ProgramNode::~ProgramNode()
{
	delete this->blockNode;
	MSG("DELETING blockNode of ProgramNode");
	MSG("DELETING ProgramNode");
}
int ProgramNode::Interpret()
{
	MSG("INTERPRET: Interpretting block node from programnode");
	this->blockNode->Interpret();
	return 1;
}
void ProgramNode::Code(InstructionsClass &machineCode)
{
	MSG("CODING: Coding block node from program node.");
	this->blockNode->Code(machineCode);
}

StartNode::StartNode(ProgramNode* programNode) : programNode(programNode) {}
StartNode::~StartNode()
{
	delete this->programNode;
	MSG("DELETING programNode of StartNode");
	MSG("DELETING StartNode");
}
int StartNode::Interpret()
{
	MSG("Interpretting..");
	this->programNode->Interpret();
	return 1;
}

void StartNode::Code(InstructionsClass &machineCode)
{
	MSG("Coding..");
	this->programNode->Code(machineCode);
}

