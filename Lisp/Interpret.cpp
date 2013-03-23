/*
 * Interpret.cpp
 *
 *  Created on: Mar 8, 2013
 *      Author: vaibhav devekar
 */


#include"Interpret.h"
#include<iostream>
#include<stdlib.h>
#include<queue>


using namespace std;

Interpret::Interpret()
{
	dList=S_EXP("NIL");
}


S_exp* Interpret::eval(S_exp* exp, S_exp* aList)
{
	S_exp* t1;

	if((S_exp::ATOM(exp))->get_info()=="T"){
		if((S_exp::INT(exp))->get_info()=="T") return exp;
		else if( (S_exp::EQ(exp,S_EXP("T")))->get_info()=="T") return exp;
		else if( (S_exp::EQ(exp,S_EXP("NIL")))->get_info()=="T") return exp;
		else if( (S_exp::IN(exp,aList))->get_info()=="T") return S_exp::GETVAL(exp,aList);
		else {cout<<"Interpreter : Unbound variable : "<<exp->get_info()<<endl;exit(1);}
	}

	else if( (t1=S_exp::ATOM(S_exp::CAR(exp))) && t1->get_info()=="T" ) {
		if( (S_exp::EQ(S_exp::CAR(exp), S_EXP("QUOTE")))->get_info()=="T" ) {
			if((S_exp::CDR(exp))->get_info()=="NIL" || (S_exp::CDR(S_exp::CDR(exp)))->get_info()!="NIL") {cout<<"Interpreter: QUOTE Argument error\n";exit(1);}
			return CADR(exp);
		}
		else if( (S_exp::EQ(S_exp::CAR(exp), S_EXP("COND")))->get_info()=="T" ) {
			if((S_exp::CDR(exp))->get_info()=="NIL") {cout<<"Interpreter: COND Argument error\n";exit(1);}
			return evcon(S_exp::CDR(exp), aList);
		}
		else if( (S_exp::EQ(S_exp::CAR(exp), S_EXP("DEFUN")))->get_info()=="T" ) {
			return add_dList(S_exp::CDR(exp));
		}
		else {return apply( S_exp::CAR(exp), evlis(S_exp::CDR(exp), aList), aList );}
	}

	else {cout<<"Interpreter: Eval error\n";exit(1);}

}



S_exp* Interpret::evcon(S_exp* pairs, S_exp* aList)
{
	if( (S_exp::isNULL(pairs))->get_info()=="T" ) {cout<<"Interpreter: Evcon Error\n";exit(1);}
	else if( (S_exp::EQ( eval(S_exp::CAAR(pairs), aList), S_EXP("T")))->get_info()=="T" ) return eval(S_exp::CADAR(pairs), aList);
	else return evcon(S_exp::CDR(pairs), aList);
}



S_exp* Interpret::evlis(S_exp* exp, S_exp* aList)
{
	if( (S_exp::isNULL(exp))->get_info()=="T" ) return S_EXP("NIL");
	else if( (S_exp::ATOM(exp))->get_info()=="T" ) {cout<<"Interpreter: Evlis Error\n";exit(1);}
	else return S_exp::CONS( eval(S_exp::CAR(exp), aList), evlis(S_exp::CDR(exp), aList) );
}


S_exp* Interpret::apply(S_exp* f, S_exp* param, S_exp* aList)
{
	if( (S_exp::ATOM(f))->get_info()=="T" ) {
		if( (S_exp::EQ(f,S_EXP("CAR")))->get_info()=="T" ) return CAAR(param);
		else if( (S_exp::EQ(f,S_EXP("CDR")))->get_info()=="T" ) return CDAR(param);
		else if( (S_exp::EQ(f,S_EXP("CONS")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in CONS"<<endl;exit(1);}
			return S_exp::CONS(S_exp::CAR(param),CADR(param));
		}
		else if( (S_exp::EQ(f,S_EXP("ATOM")))->get_info()=="T" ) {
			if((S_exp::CDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in ATOM"<<endl;exit(1);}
			return S_exp::ATOM(S_exp::CAR(param)); //send param
		}
		else if( (S_exp::EQ(f,S_EXP("NULL")))->get_info()=="T" ){
			if((S_exp::CDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in NULL"<<endl;exit(1);}
			return S_exp::isNULL(S_exp::CAR(param));
		}
		else if( (S_exp::EQ(f,S_EXP("INT")))->get_info()=="T" ) {
			if((S_exp::CDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in INT"<<endl;exit(1);}
			return S_exp::INT(S_exp::CAR(param));
		}
		else if( (S_exp::EQ(f,S_EXP("EQ")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in EQ"<<endl;exit(1);}
			return S_exp::EQ(S_exp::CAR(param), CADR(param));
		}
		else if( (S_exp::EQ(f,S_EXP("PLUS")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in PLUS"<<endl;exit(1);}
			return S_exp::PLUS(param);
		}
		else if( (S_exp::EQ(f,S_EXP("MINUS")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in MINUS"<<endl;exit(1);}
			return S_exp::MINUS(param);
		}
		else if( (S_exp::EQ(f,S_EXP("TIMES")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in TIMES"<<endl;exit(1);}
			return S_exp::TIMES(param);
		}
		else if( (S_exp::EQ(f,S_EXP("QUOTIENT")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in QUOTIENT"<<endl;exit(1);}
			return S_exp::QUOTIENT(param);
		}
		else if( (S_exp::EQ(f,S_EXP("REMAINDER")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in REMAINDER"<<endl;exit(1);}
			return S_exp::REMAINDER(param);
		}
		else if( (S_exp::EQ(f,S_EXP("LESS")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in LESS"<<endl;exit(1);}
			return S_exp::LESS(param);}
		else if( (S_exp::EQ(f,S_EXP("GREATER")))->get_info()=="T" ) {
			if((CDDR(param))->get_info()!="NIL") {cout<<"Error: Invalid expression in GREATER"<<endl;exit(1);}
			return S_exp::GREATER(param);
		}
		else if( (S_exp::IN(f,dList))->get_info()=="T") {
			S_exp* tt=S_exp::CAR(S_exp::GETVAL(f,dList));
			aList = addpairs( tt,param, aList );
			return eval(  S_exp::CDR(S_exp::GETVAL(f,dList)) , aList );
		}
		else {cout<<"Error : Undefined function : "<<f->get_info()<<endl; exit(1);}
	}
	else {cout<<"Error\n";exit(1);}
}


S_exp* Interpret::addpairs(S_exp* tt, S_exp* param, S_exp* aList )
{
	while( (S_exp::isNULL(tt))->get_info()=="NIL" && (S_exp::isNULL(param))->get_info()=="NIL" )
	{
		S_exp *t = S_exp::CONS (S_exp::CAR(tt), S_exp::CAR(param));
		aList= S_exp::CONS (t, aList);
		tt=S_exp::CDR(tt);
		param=S_exp::CDR(param);
	}

	if( (S_exp::isNULL(tt))->get_info()=="NIL" && (S_exp::isNULL(param))->get_info()=="NIL" )
	{
		cout<<"Error: Mismatch in number of arguments\n"; exit(1);
	}

	return aList;
}


S_exp* Interpret::add_dList(S_exp* exp)
{
	//nil
	//atom fname
	//param, body
	// return error/false?
	S_exp *fname=S_exp::CAR(exp);
	if((S_exp::ATOM(fname))->get_info()=="NIL" || (S_exp::INT(fname))->get_info()=="T" || fname->get_info()=="T" || fname->get_info()=="T")
	{
		cout<<"Error: Invalid function name"<<endl;exit(1);
	}
	if((CDDR(S_exp::CDR(exp)))->get_info()!="NIL") {cout<<"Error: Invalid expression"<<endl;exit(1);}

	S_exp* temp= S_exp::CONS(CADR(exp),CADDR(exp));
	temp=S_exp::CONS(S_exp::CAR(exp), temp);
	dList=S_exp::CONS(temp,dList);

	return S_exp::CAR(exp);
}
