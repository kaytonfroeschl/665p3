#include "ast.hpp"

namespace cshanty{

/*
doIndent is declared static, which means that it can 
only be called in this file (its symbol is not exported).
*/
static void doIndent(std::ostream& out, int indent){
	for (int k = 0 ; k < indent; k++){ out << "\t"; }
}

/*
In this code, the intention is that functions are grouped 
into files by purpose, rather than by class.
If you're used to having all of the functions of a class 
defined in the same file, this style may be a bit disorienting,
though it is legal. Thus, we can have
ProgramNode::unparse, which is the unparse method of ProgramNodes
defined in the same file as DeclNode::unparse, the unparse method
of DeclNodes.
*/


void ProgramNode::unparse(std::ostream& out, int indent){
	/* Oh, hey it's a for-each loop in C++!
	   The loop iterates over each element in a collection
	   without that gross i++ nonsense. 
	 */
	for (auto global : *myGlobals){
		/* The auto keyword tells the compiler
		   to (try to) figure out what the
		   type of a variable should be from 
		   context. here, since we're iterating
		   over a list of DeclNode *s, it's 
		   pretty clear that global is of 
		   type DeclNode *.
		*/
		global->unparse(out, indent);
	}
}

void AssignExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->MyLVal->unparse(out, 0);
	out << "=";
	this->MyExp->unparse(out, 0);
	out << ";\n";
}

void BinaryExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->MyLHS->unparse(out,0);
	out<<" ";
	this->MyRHS->unparse(out,0);
	out<<";\n";
}

/*void CallExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->MyId->unparse(out,0);
	out<<"(";
	
	out<<")";
}*/

void IntLitNode::unparse(std::ostream& out, int indent){
	out<<this->MyInt;
}

void StrLitNode::unparse(std::ostream& out, int indent){
	out<<this->MyString;
}

void TrueNode::unparse(std::ostream& out, int indent){
	out<<"True";
}

void FalseNode::unparse(std::ostream& out, int indent){
	out<<"False";
	//this->MyLHS->unparse(out, 0);
	//how do I say which node goes here?
	//this->MyRHS->unparse(out, 0);
}

void VarDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myType->unparse(out, 0);
	out << " ";
	this->myId->unparse(out, 0);
	out << ";\n";
}

void IDNode::unparse(std::ostream& out, int indent){
	out << this->name;
}

void IntTypeNode::unparse(std::ostream& out, int indent){
	out << "int";
}

void AndNode::unparse(std::ostream& out, int indent){
	out << "&&";
}

void DivideNode::unparse(std::ostream& out, int indent){
	out << "/";
}

void EqualsNode::unparse(std::ostream& out, int indent){
	out << "==";
}

void GreaterEqNode::unparse(std::ostream& out, int indent){
	out << ">=";
}

void GreaterNode::unparse(std::ostream& out, int indent){
	out << ">";
}

void LessEqNode::unparse(std::ostream& out, int indent){
	out << "<=";
}

void LessNode::unparse(std::ostream& out, int indent){
	out << "<";
}

void MinusNode::unparse(std::ostream& out, int indent){
	out << "-";
}

void NotEqualsNode::unparse(std::ostream& out, int indent){
	out << "!=";
}

void OrNode::unparse(std::ostream& out, int indent){
	out << "||";
}

void PlusNode::unparse(std::ostream& out, int indent){
	out << "+";
}

void TimesNode::unparse(std::ostream& out, int indent){
	out << "*";
}

void IndexNode::unparse(std::ostream& out, int indent){
	//MyId1->unparse(out, 0);
	out << "[";
	//MyId2->unparse(out, 0);
	out << "]";
	out << ";\n";
}

} // End namespace cshanty
