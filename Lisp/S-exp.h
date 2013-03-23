/*
 * S-exp.h
 *
 *  Created on: Dec 20, 2012
 *      Author: vaibhav devekar
 */

#ifndef __S_EXP_H_INCLUDED__
#define __S_EXP_H_INCLUDED__


#include<string>

class S_exp{
	std::string info;
	S_exp *left,*right;
	static S_exp* idPointers[];
	S_exp(std::string s);

public:
	S_exp();
	std::string get_info();
	static::S_exp* createS_exp(std::string s);

	//Primitives
	static S_exp* CAR(S_exp* a);
	static S_exp* CDR(S_exp* a);
	static S_exp* CONS(S_exp* a,S_exp* b);
	static S_exp* INT(S_exp* a);
	static S_exp* ATOM(S_exp* a);
	static S_exp* isNULL(S_exp* exp);
	static S_exp* EQ(S_exp* a,S_exp* b);

	//arithmetic + - * / % < >
	static S_exp* PLUS(S_exp* a);
	static S_exp* MINUS(S_exp* a);
	static S_exp* TIMES(S_exp* a);
	static S_exp* QUOTIENT(S_exp* a);
	static S_exp* REMAINDER(S_exp* a);
	static S_exp* LESS(S_exp* a);
	static S_exp* GREATER(S_exp* a);

	//Helper functions for Interpreter
	static S_exp* IN(S_exp* exp,S_exp* aList);
	static S_exp* GETVAL(S_exp* exp,S_exp* aList);
};


#endif
