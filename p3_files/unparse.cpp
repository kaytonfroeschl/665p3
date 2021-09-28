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

//StmtNode???

//TypeNode

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

void CallExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->MyId->unparse(out,0);
	out<<"(";
	for (auto element : *myList)
	{
		element->unparse(out, 0);
	}
	out<<")";
}

void LValNode::unparse(std::ostream& out, int indent){
	//doIndent(out,indent);
	this->unparse(out,0);
}

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
}

void UnaryExpNode::unparse(std::ostream& out, int indent){
	this->MyExp->unparse(out,0);
}

void AssignStmtNode::unparse(std::ostream& out, int indent){
	this->MyAssign->unparse(out,0);
}

void CallStmtNode::unparse(std::ostream& out, int indent){
	this->myCall->unparse(out,0);
}

//DeclNode???

void IfElseStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<"if (";
	this->MyExp->unparse(out,0);
	out<<"){\n";
	for(auto element : myTBranch*){
		element->unparse(out, 0);
	}
	out<<"else {\n";
	for(auto element : myRBranch*){
		element->unparse(out, 0);
	}
	out<<"}\n";
}

void IfStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<"if (";
	this->MyExp->unparse(out, 0);
	out<<"){\n";
	for(auto element : myList*){
		element->unparse(out, 0);
	}
	out<<"}\n";	
}

void PostDecStmtNode::unparse(std::ostream& out, int indent){
	this->myLVal->unparse(out,0);
}

void PostIncStmtNode::unparse(std::ostream& out, int indent){
	this->myLVal->unparse(out,0);
}

void ReceiveStmtNode::unparse(std::ostream& out, int indent){
	this->myLVal->unparse(out,0);
}

void ReportStmtNode::unparse(std::ostream& out, int indent){
	this->myExp->unparse(out,0);
}

void WhileStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<"while(";
	this->MyExp->unparse(out,0);
	out<<"){\n";
	for(auto element : my_List){
		element->unparse(out,0);
	}
	out<<"}\n";
}

void ReturnStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<"return(";
	this->myExp->unparse(out,0);
	out<<");\n";
}

void BoolTypeNode::unparse(std::ostream& out, int indent){
	out<<"bool";
}

void RecordTypeNode::unparse(std::ostream& out, int indent){
	this->MyId->unparse(out,0);
}

void StringTypeNode::unparse(std::ostream& out, int indent){
	out<<"string";
}

void VoidTypeNode::unparse(std::ostream& out, int indent){
	out<<"void";
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
	this->MyId1->unparse(out, 0);
	out << "[";
	this->MyId2->unparse(out, 0);
	out << "]";
	out << ";\n";
}

void NegNode::unparse(std::ostream& out, int indent){
	out<<"-";
}

void NotNode::unparse(std::ostream& out, int indent){
	out<<"!";
}

void VarDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myType->unparse(out, 0);
	out << " ";
	this->myId->unparse(out, 0);
	out << ";\n";
}

void FnDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<this->myType;
	out<<" ";
	out<<this->myId;
	out<<"(";
	for(auto element : MyFormalList*){
		element->unparse(out,0);
	}
	out<<"){\n";
	for(auto element : MyStmtList*){
		element->unparse(out,0);
	}
	out<<"}\n";
}

void FormalDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<this->myType;
	out<<" ";
	out<<this->myId;
}


} // End namespace cshanty
