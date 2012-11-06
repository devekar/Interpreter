/*
 * classes.h
 *
 *  Created on: Oct 13, 2012
 *      Author: vaibhav
 */


#ifndef __CLASSES_H_INCLUDED__
#define __CLASSES_H_INCLUDED__

#include<stdio.h>
#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>

#include "Tokenizer.h"
#include "InputData.h"

#define GARBAGE 99999999

//============================================================
class Id{
	std::string name;
	int val;
	bool declared;
	bool initialised;
	static Id* eIds[];
	static int count;
	Id(std::string n);
public:
	void printId();
	static Id* parseId(std::string s);
	int getIdVal();
	void setIdVal(int i);
	void declId();
};


//============================================================
class IdList{
	Id* id; IdList* idl;
	Tokenizer* t; InputData* ip;
public:
	IdList();
	void parseIdList();
	void printIdList();
	void readIdList();
	void writeIdList();
	void declIdList();
};



//============================================================
class Exp;
class Op{
	int i; Id* id; Exp* exp;
	int alt;
	Tokenizer* t;
public:
	Op();
	void parseOp();
	void printOp();
	int execOp();
};


//============================================================
class Fac{
	Op *op; Fac* f;
	int alt;
	Tokenizer* t;
public:
	Fac();
	void parseFac();
	void printFac();
	int execFac();
};


//============================================================
class Exp{
	Fac* f;	Exp* exp;
	int alt;
	Tokenizer* t;
public:
	Exp();
	void parseExp();
	void printExp();
	int execExp();
};


//============================================================
class Comp{
	Op *op1,*op2;
	int alt;
	std::string cop;
	Tokenizer *t;
public:
	Comp();
	void parseComp();
	void printComp();
	bool execComp();
};


//============================================================
class Cond{
	Comp *cp; Cond *c1,*c2;
	int alt;
	Tokenizer* t;
public:
	Cond();
	void parseCond();
	void printCond();
	bool execCond();
};


//============================================================
class Assign{
	Id* id;
	Exp* exp;
	Tokenizer* t;
public:
	Assign();
	void parseAssign();
	void printAssign();
	void execAssign();
};


//============================================================
class SS;
class If{
	Cond* c; SS *s1,*s2;
	int alt;
	Tokenizer* t;
public:
	If();
	void parseIf();
	void printIf();
	void execIf();
};


//============================================================
class Loop{
	Cond* c; SS* s;
	Tokenizer* t;
public:
	Loop();
	void parseLoop();
	void printLoop();
	void execLoop();
};


//============================================================
class Input{
	IdList* idl;
	Tokenizer* t;
public:
	Input();
	void parseInput();
	void printInput();
	void execInput();
};


//============================================================
class Output{
	IdList* idl;
	Tokenizer* t;
public:
	Output();
	void parseOutput();
	void printOutput();
	void execOutput();
};


//============================================================
class Stmt{
	int alt;
	Assign* s1; If* s2; Loop* s3;
	Input* s4; Output * s5;
	Tokenizer* t;
public:
	Stmt();
	void parseStmt();
	void printStmt();
	void execStmt();
};


//============================================================
class SS{
	Stmt* s; SS* ss;
	Tokenizer* t;
public:
	SS();
	void parseSS();
	void printSS();
	void execSS();
};


//==============================================
class Decl{
	IdList* idl;
	Tokenizer* t;
public:
	Decl();
	void parseDecl();
	void printDecl();
	void execDecl();
};


//===============================================
class DS{
	Decl* d;DS * ds;
	Tokenizer* t;
public:
	DS();
	void parseDS();
	void printDS();
	void execDS();
};


//===============================================
class Prog{
	DS *ds;
	SS *ss;
	Tokenizer* t;
public:
	Prog();
	void parseProg();
	void printProg();
	void execProg();
};

#endif
