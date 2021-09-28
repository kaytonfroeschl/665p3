#ifndef CSHANTYC_AST_HPP
#define CSHANTYC_AST_HPP

#include <ostream>
#include <list>
#include "tokens.hpp"

// **********************************************************************
// ASTnode class (base class for all other kinds of nodes)
// **********************************************************************

namespace cshanty{

/* You may find it useful to forward declare AST subclasses
   here so that you can use a class before it's full definition
*/
class DeclNode;
class TypeNode;
class StmtNode;
class IDNode;
class LValNode;
class FormalDeclNode;

class ASTNode{
public:
	ASTNode(Position * p) : myPos(p){ }
	virtual void unparse(std::ostream& out, int indent) = 0;
	Position * pos() { return myPos; }
	std::string posStr() { return pos()->span(); }
protected:
	Position * myPos;
};

/**  \class ExpNode
* Superclass for expression nodes (i.e. nodes that can be used as
* part of an expression).  Nodes that are part of an expression
* should inherit from this abstract superclass.
**/
class ExpNode : public ASTNode{
protected:
	ExpNode(Position * p) : ASTNode(p){ }
};

/**
* \class ProgramNode
* Class that contains the entire abstract syntax tree for a program.
* Note the list of declarations encompasses all global declarations
* which includes (obviously) all global variables and struct declarations
* and (perhaps less obviously), all function declarations
**/
class ProgramNode : public ASTNode{
public:
	ProgramNode(std::list<DeclNode *> * globalsIn) ;
	void unparse(std::ostream& out, int indent) override;
private:
	std::list<DeclNode * > * myGlobals;
};

class StmtNode : public ASTNode{
public:
	StmtNode(Position * p) : ASTNode(p){ }
	void unparse(std::ostream& out, int indent) override = 0;
};

/**  \class TypeNode
* Superclass of nodes that indicate a data type. For example, in
* the declaration "int a", the int part is the type node (a is an IDNode
* and the whole thing is a DeclNode).
**/
class TypeNode : public ASTNode{
protected:
	TypeNode(Position * p) : ASTNode(p){
	}
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
	//virtual bool isRef(TypeNode* type);
	//TODO: consider adding an isRef to use in unparse to
	// indicate if this is a reference type
};

class AssignExpNode : public ExpNode{
public:
	AssignExpNode(Position * p, LValNode * lval, ExpNode * exp) : ExpNode(p), MyLVal(lval), MyExp(exp){}
	void unparse(std::ostream& out, int indent);
private:
	LValNode * MyLVal;
	ExpNode * MyExp;
};

class BinaryExpNode : public ExpNode{
public:
	BinaryExpNode(Position * p, ExpNode * rhs, ExpNode * lhs) : ExpNode(p), MyRHS(rhs), MyLHS(lhs){}
	void unparse(std::ostream& out, int indent) override = 0;
private:
	ExpNode * MyRHS;
	ExpNode * MyLHS;
};

class CallExpNode : public ExpNode {
public:
	CallExpNode(Position * p, IDNode* id, std::list<ExpNode*>* MyList) : ExpNode(p) { }
	void unparse(std::ostream& out, int indent);
private:
	IDNode * MyId;
	std::list<ExpNode * > * MyList;
};

class IntLitNode : public ExpNode{
public:
	IntLitNode(Position * p, int i) : ExpNode(p), MyInt(i){}
	void unparse(std::ostream& out, int indent);
private:
	int MyInt;
};

class LValNode : public ExpNode{
public:
	LValNode(Position * p) : ExpNode(p){}
	void unparse(std::ostream& out, int indent) override = 0;
};

class StrLitNode : public ExpNode{
public:
	StrLitNode(Position * p, std::string str) : ExpNode(p), MyString(str){}
	void unparse(std::ostream& out, int indent);
private:
	std::string MyString;
};

class TrueNode : public ExpNode{
	public:
		TrueNode(Position* p) : ExpNode(p){ }
		void unparse(std::ostream& out, int indent);
};

class FalseNode : public ExpNode{
	public:
		FalseNode(Position* p) : ExpNode(p){ }
		void unparse(std::ostream& out, int indent);
};

class UnaryExpNode : public ExpNode{
public:
	UnaryExpNode(Position * p) : ExpNode(p){}
	void unparse(std::ostream& out, int indent) override = 0;
private:
	ExpNode* MyExp;
};

class AssignStmtNode : public StmtNode{
public:
	AssignStmtNode(Position * p, AssignExpNode* assign) : StmtNode(p), MyAssign(assign) { }
	void unparse(std::ostream& out, int indent);
private:
	AssignExpNode * MyAssign;
};

class CallStmtNode : public StmtNode{
public:
	CallStmtNode(Position * p, CallExpNode* call) : StmtNode(p){ }
	void unparse(std::ostream& out, int indent);
private:
	CallExpNode* myCall;
};

/** \class DeclNode
* Superclass for declarations (i.e. nodes that can be used to
* declare a struct, function, variable, etc).  This base class will
**/
class DeclNode : public StmtNode{
public:
	DeclNode(Position * p) : StmtNode(p) { }
	void unparse(std::ostream& out, int indent) override = 0;
};

class IfElseStmtNode : StmtNode{
	public:
		IfElseStmtNode(Position* p, ExpNode* exp, std::list<StmtNode*>* tBranch, std::list<StmtNode*>* fBranch) : StmtNode(p), MyExp(exp), myTBranch(tBranch), myRBranch(fBranch) { }
		void unparse(std::ostream& out, int indent);
	private:
		ExpNode* MyExp;
		std::list<StmtNode*>* myTBranch;
		std::list<StmtNode*>* myRBranch;
};

class IfStmtNode : public StmtNode{
	public:
		IfStmtNode(Position* p, ExpNode* node, std::list<StmtNode*>* sList) : StmtNode(p), MyExp(node), myList(sList) { }
		void unparse(std::ostream& out, int indent);
	private:
		ExpNode* MyExp;
		std::list<StmtNode*>* myList;
};

class PostDecStmtNode : public StmtNode{
	public:
		PostDecStmtNode(Position* p, LValNode* lval) : StmtNode(p) { }
		void unparse(std::ostream& out, int indent);
	private:
		LValNode* myLVal;
};

class PostIncStmtNode : public StmtNode{
	public:
		PostIncStmtNode(Position* p, LValNode* lval) : StmtNode(p) { }
		void unparse(std::ostream& out, int indent);
	private:
		LValNode* myLVal;
};

class ReceiveStmtNode : public StmtNode{
	public:
		ReceiveStmtNode(Position* p, LValNode* lval) : StmtNode(p) { }
		void unparse(std::ostream& out, int indent);
	private:
		LValNode* myLVal;
};

class ReportStmtNode : public StmtNode{
	public:
		ReportStmtNode(Position* p, ExpNode* exp) : StmtNode(p){ }
		void unparse(std::ostream& out, int indent);
	private:
		ExpNode* myExp;
};

class WhileStmtNode : public StmtNode{
	public:
		WhileStmtNode(Position* p, ExpNode* exp, std::list<StmtNode*>* sList) : StmtNode(p) { }
		void unparse(std::ostream& out, int indent);
	private:
		std::list<StmtNode*>* my_List;
		ExpNode* MyExp;
};

class ReturnStmtNode : public StmtNode{
	public:
		ReturnStmtNode(Position* p, ExpNode* exp) : StmtNode(p) { }
		void unparse(std::ostream& out, int indent);
	private:
		ExpNode* myExp;
};

class BoolTypeNode : public TypeNode{
public:
	BoolTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class IntTypeNode : public TypeNode{
public:
	IntTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class RecordTypeNode : public TypeNode{
public:
	RecordTypeNode(Position * p, IDNode * id) : TypeNode(p), MyId(id) { }
	void unparse(std::ostream& out, int indent);
private:
	IDNode * MyId;
};

class StringTypeNode : public TypeNode{
public:
	StringTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class VoidTypeNode : public TypeNode{
public:
	VoidTypeNode(Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class AndNode: public BinaryExpNode{
public:
	AndNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){ }
	void unparse(std::ostream& out, int indent);
};

class DivideNode: public BinaryExpNode{
public:
	DivideNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){ }
	void unparse(std::ostream& out, int indent);
};

class EqualsNode: public BinaryExpNode{
public:
	EqualsNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){ }
	void unparse(std::ostream& out, int indent);
};

class GreaterEqNode: public BinaryExpNode{
public:
	GreaterEqNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){ }
	void unparse(std::ostream& out, int indent);
};

class GreaterNode: public BinaryExpNode{
public:
	GreaterNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){ }
	void unparse(std::ostream& out, int indent);
};

class LessEqNode: public BinaryExpNode{
public:
	LessEqNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){}
	void unparse(std::ostream& out, int indent);
};

class LessNode: public BinaryExpNode{
public:
	LessNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){}
	void unparse(std::ostream& out, int indent);
};

class MinusNode: public BinaryExpNode{
public:
	MinusNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){}
	void unparse(std::ostream& out, int indent);
};

class NotEqualsNode: public BinaryExpNode{
public:
	NotEqualsNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){}
	void unparse(std::ostream& out, int indent);
};

class OrNode: public BinaryExpNode{
public:
	OrNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){}
	void unparse(std::ostream& out, int indent);
};

class PlusNode: public BinaryExpNode{
public:
	PlusNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){}
	void unparse(std::ostream& out, int indent);
};

class TimesNode: public BinaryExpNode{
public:
	TimesNode(Position * p, ExpNode * rhs, ExpNode * lhs) : BinaryExpNode(p, rhs, lhs){}
	void unparse(std::ostream& out, int indent);
};

/** An identifier. Note that IDNodes subclass
 * ExpNode because they can be used as part of an expression.
**/
class IDNode : public LValNode{
public:
	IDNode(Position * p, std::string nameIn)
	: LValNode(p), name(nameIn){ }
	void unparse(std::ostream& out, int indent);
private:
	/** The name of the identifier **/
	std::string name;
};

class IndexNode : public LValNode{
public:
	IndexNode(Position * p, IDNode* id1, IDNode* id2)
	: LValNode(p), MyId1(id1), MyId2(id2){ }
	void unparse(std::ostream& out, int indent);
private:
	IDNode* MyId1;
	IDNode* MyId2;
};

class NegNode : public UnaryExpNode {
public:
	NegNode(Position * p) : UnaryExpNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class NotNode : public UnaryExpNode {
public:
	NotNode(Position * p) : UnaryExpNode(p){ }
	void unparse(std::ostream& out, int indent);
};


/** A variable declaration. Note that this class is intended to
 * represent a global or local variable of any type (including a struct
 * type. Note that this is not intended to represent a declaration of
 * a struct. In other words:
 * struct MyStruct {
 *   int fieldA;
 * };
 * is NOT a VarDeclNode because it introduces a new datatype, not a new
 * variable (in this case, the example is a StructDeclNode).  * However,
 * struct MyStruct instance; *is* a VarDeclNode, since it introduces a
 * new variable to the program.
**/
class VarDeclNode : public DeclNode{
public:
	VarDeclNode(Position * p, TypeNode * type, IDNode * id)
	: DeclNode(p), myType(type), myId(id){
	}
	void unparse(std::ostream& out, int indent);
private:
	TypeNode * myType;
	IDNode * myId;
};

class FnDeclNode : public DeclNode{
	public:
		FnDeclNode(Position* p, TypeNode* type, IDNode* id, std::list<FormalDeclNode*>* fList, std::list<StmtNode*>* sList)
		: DeclNode(p), myType(type), myId(id), MyFormalList(fList), MyStmtList(sList){ }
		void unparse(std::ostream& out, int indent);
	private:
		TypeNode* myType;
		IDNode* myId;
		std::list<FormalDeclNode*>* MyFormalList;
		std::list<StmtNode*>* MyStmtList;
};

class RecordTypeDeclNode : public DeclNode{
public:
	RecordTypeDeclNode(Position * p, IDNode * id, std::list<VarDeclNode*>* decl)
	: DeclNode(p), myId(id), MyVarDeclList(decl){ }
	void unparse(std::ostream& out, int indent);
private:
	TypeNode * myType;
	IDNode * myId;
	std::list<VarDeclNode*>* MyVarDeclList;
};

class FormalDeclNode : public VarDeclNode{
	public:
		FormalDeclNode(Position* p, TypeNode* type, IDNode* id)
		: VarDeclNode(p, type, id), myType(type), myId(id){ }
		void unparse(std::ostream& out, int indent);
	private:
		TypeNode* myType;
		IDNode* myId;
};

} //End namespace cshanty

#endif
