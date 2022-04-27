
#ifndef NODE_H
#define NODE_H
#include "Symbol.h"
#include "instructions.h"

#include <vector>
#include <string>

class ExpressionNode
{
	public:
		virtual ~ExpressionNode();
		virtual int Evaluate();
		virtual void CodeEvaluate(InstructionsClass &machineCode)=0;
	private:
		
};
//	|
//	v
	class IntegerNode: public ExpressionNode
	{
		public:
			IntegerNode(const int& value);
			//v returns value.
			//no destructor needed
			int Evaluate() override;
			void CodeEvaluate(InstructionsClass &machineCode) override;
		private:
			int value;
	};
	class IdentifierNode: public ExpressionNode
	{
		public:
			IdentifierNode(std::string label, SymbolTableClass* symbolTable);
			//adds the IdentifierNode's label to the symbol table
			//will be called by declaration nodes interpreting themselves
			void DeclareVariable();
			//sets value into the symbol table by calling this->symbolTable->SetValue(this->label, v); This will be called by assignmentnodes interpreting themselves
			void SetValue(int v);
			//returns integer position of where this variable is being stored in the symbol table. Needed for writing machien code.
			int GetIndex();
			//when asked to evaluate itself, an id node should this->symbolTable->GetValue(this->label), and return what <-that returns.
			int Evaluate() override;
			void CodeEvaluate(InstructionsClass &machineCode) override;
		private:
			std::string label;
			SymbolTableClass* symbolTable;
	};
	class BinaryOperatorNode: public ExpressionNode
	{
		public:
			BinaryOperatorNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
			//delete children
			~BinaryOperatorNode();
		protected:
			ExpressionNode* leftNode;
			ExpressionNode* rightNode;
	};
	//	|
	//	v
		class OrNode : public BinaryOperatorNode
		{
			public:
				OrNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};
		class AndNode : public BinaryOperatorNode
		{
			public:
				AndNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};
		class PlusNode: public BinaryOperatorNode
		{
			public:
				//forward left node and right node to parent constructor
				PlusNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				//recursively call evaluate on left and right, returning sum of their return values.
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};
		class MinusNode: public BinaryOperatorNode
		{
			public:
				MinusNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};
		class TimesNode: public BinaryOperatorNode
		{
			public:
				TimesNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};	
		class DivideNode: public BinaryOperatorNode
		{
			public:
				DivideNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};
		class LessNode: public BinaryOperatorNode
		{
			public:
				LessNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};

		class LessEqualNode: public BinaryOperatorNode
		{
			public:
				LessEqualNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};

		class GreaterNode: public BinaryOperatorNode
		{
			public:
				GreaterNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};

		class GreaterEqualNode: public BinaryOperatorNode
		{
			public:
				GreaterEqualNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};

		class EqualNode: public BinaryOperatorNode
		{
			public:
				EqualNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};

		class NotEqualNode: public BinaryOperatorNode
		{
			public:
				NotEqualNode(ExpressionNode* leftNode, ExpressionNode* rightNode);
				
				int Evaluate() override;
				void CodeEvaluate(InstructionsClass &machineCode) override;
		};

class Node
{
	public:
		virtual ~Node();
		virtual int Interpret();
		virtual void Code(InstructionsClass &machineCode)=0;
	private:
		
};
// 	|_______
// 	v   	v
	class StatementNode : public Node
	{
		public:
			virtual ~StatementNode();
		private:
			
	};
	// 	|
	//	v
		class DeclarationStatementNode : public StatementNode
		{
			public:
				DeclarationStatementNode(IdentifierNode* identifierNode);
				~DeclarationStatementNode();
				int Interpret() override;
				void Code(InstructionsClass &machineCode) override;
			private:
				IdentifierNode* identifierNode;
		};
		class AssignmentStatementNode: public StatementNode
		{
			public:
				AssignmentStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode);
				//delete all ur children bro
				~AssignmentStatementNode();
				int Interpret() override;
				void Code(InstructionsClass &machineCode) override;
			private:
				IdentifierNode* identifierNode;
				ExpressionNode* expressionNode;
		};
		class PlusEqualsStatementNode: public StatementNode
		{
			public:
				PlusEqualsStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode);
				~PlusEqualsStatementNode();
				int Interpret() override;
				void Code(InstructionsClass &machineCode) override;
			private:
				IdentifierNode* identifierNode;
				ExpressionNode* expressionNode;
		};
		class MinusEqualsStatementNode: public StatementNode
		{
			public:
				MinusEqualsStatementNode(IdentifierNode* identifierNode, ExpressionNode* expressionNode);
				~MinusEqualsStatementNode();
				int Interpret() override;
				void Code(InstructionsClass &machineCode) override;
			private:
				IdentifierNode* identifierNode;
				ExpressionNode* expressionNode;
		};
		class CoutStatementNode: public StatementNode
		{
			public:
				CoutStatementNode(std::vector<ExpressionNode*> expressionNode);
				~CoutStatementNode();
				int Interpret() override;
				void Code(InstructionsClass &machineCode) override;
			private:
				std::vector<ExpressionNode*> expressionNode;
		};
	// ^
	// |
	class StatementGroupNode : public Node
	{
		public:
			StatementGroupNode();
			//loop through each pointer, delete each one.
			~StatementGroupNode();
			void AddStatement(StatementNode* toAdd);
			int Interpret() override;
			void Code(InstructionsClass &machineCode) override;
		private:
			std::vector<StatementNode*> statementNodes;
	};
	// ^
	// |
	class BlockNode : public StatementNode
	{
		public:
			BlockNode(StatementGroupNode* statementGroupNode);
			//call delete on statementGroupNode
			~BlockNode();
			int Interpret() override;
			void Code(InstructionsClass &machineCode) override;
		private:
			StatementGroupNode* statementGroupNode;
	};
	class WhileClauseNode : public StatementNode
	{
		//basically If, but interpretation loops during the true condition.
		public:
			WhileClauseNode(ExpressionNode* condition, StatementNode* whileBlock);
			~WhileClauseNode();
			int Interpret() override;
			void Code(InstructionsClass &machineCode) override;
		private:
			ExpressionNode* condition;
			StatementNode* whileBlock;
	};
	class IfClauseNode : public StatementNode
	{
		//basically a ProgramNode, but interpretation of the block is conditional.
		public:
			IfClauseNode(ExpressionNode* condition, StatementNode* ifBlock, StatementNode* elseBlock);
			~IfClauseNode();
			int Interpret() override;
			void Code(InstructionsClass &machineCode) override;
		private:
			ExpressionNode* condition;
			StatementNode* ifBlock;
			StatementNode* elseBlock;
	};
	// ^
	// |
	class ProgramNode : public Node
	{
		public:
			ProgramNode(BlockNode* blockNode);
			//call delete on blockNode
			~ProgramNode();
			int Interpret() override;
			void Code(InstructionsClass &machineCode) override;
		private:
			BlockNode* blockNode;
	};
	// ^
	// |
	class StartNode : public Node
	{
		public:
			StartNode(ProgramNode* programNode);
			//call delete on programNode
			~StartNode();
			int Interpret() override;
			void Code(InstructionsClass &machineCode) override;
		private:
			ProgramNode* programNode;	
	};
#endif
