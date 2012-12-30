/*
 * Interpreter.h
 *
 *  Created on: Dec 25, 2012
 *      Author: vaibhav
 */
#include"S-exp.h"
#include"Tokenizer.h"

class Interpreter{
	S_exp* dList;
	S_exp* aList;
	Tokenizer *t;
public:
	Interpreter();
	void output();
	S_exp* eval(S_exp* exp);
	S_exp* evlis(S_exp* exp);
	S_exp* evcon(S_exp* pairs);
	S_exp* apply(S_exp* f, S_exp* param);
	void addpairs2aList(S_exp* pList,S_exp* arg);
	void DEFUN();
	S_exp* buildparamstree();
	S_exp* buildbodystree();
	S_exp* buildexecstree();

	void dfs(S_exp* t);
	void print(S_exp* result);
};


