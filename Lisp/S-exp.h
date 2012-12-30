/*
 * s-exp.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: vaibhav
 */
#include<string>

class S_exp{


public:
	std::string info;
	S_exp *left,*right;


	S_exp();
	S_exp(std::string s);
	static S_exp* CAR(S_exp* a);
	static S_exp* CDR(S_exp* a);
	static S_exp* CADR(S_exp* a);
	static S_exp* CDAR(S_exp* a);
	static S_exp* CAAR(S_exp* a);
	static S_exp* CADAR(S_exp* a);
	static S_exp* CONS(S_exp* a,S_exp* b);
	static S_exp* INT(S_exp* a);
	static S_exp* ATOM(S_exp* a);
	static S_exp* isNULL(S_exp* exp);
	static S_exp* EQ(S_exp* a,S_exp* b);
	static bool EQ(S_exp* a,std::string b);
	static S_exp* IN(S_exp* exp,S_exp* aList);
	static S_exp* GETVAL(S_exp* exp,S_exp* aList);
	//arithmetic + - * / % < >

	static S_exp* PLUS(S_exp* a);
	static S_exp* MINUS(S_exp* a);
	static S_exp* TIMES(S_exp* a);
	static S_exp* QUOTIENT(S_exp* a);
	static S_exp* REMAINDER(S_exp* a);
	static S_exp* LESS(S_exp* a);
	static S_exp* GREATER(S_exp* a);
};


