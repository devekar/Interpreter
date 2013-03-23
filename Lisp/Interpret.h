/*
 * Interpret.h
 *
 *  Created on: Mar 8, 2013
 *      Author: vaibhav devekar
 */
#include "S-exp.h"


#define S_EXP(exp) S_exp::createS_exp(exp)

#define CADR(exp) S_exp::CAR(S_exp::CDR(exp))
#define CDDR(exp) S_exp::CDR(S_exp::CDR(exp))
#define CDAR(exp) S_exp::CDR(S_exp::CAR(exp))
#define CAAR(exp) S_exp::CAR(S_exp::CAR(exp))
#define CADAR(exp) S_exp::CAR(S_exp::CDR(S_exp::CAR(exp)))
#define CADDR(exp) S_exp::CAR(S_exp::CDR(S_exp::CDR(exp)))

class Interpret
{
	S_exp* dList;

public:
	Interpret();
	S_exp* eval(S_exp* exp, S_exp * aList);
	S_exp* evlis(S_exp* exp, S_exp * aList);
	S_exp* evcon(S_exp* pairs, S_exp * aList);
	S_exp* apply(S_exp* f, S_exp* param, S_exp * aList);
	S_exp* addpairs(S_exp* tt, S_exp* param, S_exp* aList );
	S_exp* add_dList(S_exp* exp);
};
