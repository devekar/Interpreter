/*
 * S-exp.cpp
 *
 *  Created on: Dec 25, 2012
 *      Author: vaibhav devekar
 */

#include"S-exp.h"
#include"Tokenizer.h"
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>

using namespace std;

S_exp* S_exp::idPointers[50]={0};

S_exp::S_exp()
{
	info="\0";
	left=0;
	right=0;
}

S_exp::S_exp(std::string s)
{
	info=s;
	left=0;
	right=0;
}


S_exp* S_exp::createS_exp(string s)
{
	S_exp* head;
	Tokenizer* t=Tokenizer::instance();
	if(t->isInt(s) || s=="T" || s=="NIL") {
		head=new S_exp(s);
	}
	else {
		for(int i=0;i<50;i++)
			if(idPointers[i] && idPointers[i]->info==s) return idPointers[i];

		head=new S_exp(s);
		head->left=0;
		head->right=0;

		int i;
		for(i=0;i<50;i++)
			if(!idPointers[i]) {idPointers[i]=head;break;}
		//overflow of idPointers?

		if(i==50) {cout<<"Error: Overflow of IdPointer Table"<<endl;exit(1);}
	}

	return head;

}


string S_exp::get_info()
{
	return info;
}


S_exp* S_exp::CONS(S_exp* a,S_exp* b)
{
	S_exp* newexp=new S_exp();
	newexp->left=a;
	newexp->right=b;
	return newexp;
}

S_exp* S_exp::CAR(S_exp* a)
{
	if(!a || !a->left) {cout<<"Error: Incorrect argument for CAR"<<endl;exit(1);}
	return a->left;
}

S_exp* S_exp::CDR(S_exp* a)
{
	if(!a || !a->right) {cout<<"Error: Incorrect argument for CDR"<<endl;exit(1);}
	return a->right;
}

S_exp* S_exp::ATOM(S_exp* a)
{
	if(a->info!="\0") return new S_exp("T");
	else return new S_exp("NIL");
}

S_exp* S_exp::isNULL(S_exp *exp)
{
	if(exp->info=="NIL") return new S_exp("T");
	else return new S_exp("NIL");
}

S_exp* S_exp::INT(S_exp* a)
{
	if((ATOM(a))->get_info()=="NIL") {
		return new S_exp("NIL");
		//cout<<"Error:Function applied on non-atomic argument\n";exit(1);
	}

	string s=a->info;
	int i=0;
		if(s[i]=='-') i++;

	for(; i<s.size(); i++)
		if( !isdigit(s[i]) ) return new S_exp("NIL");

	return new S_exp("T");
}



S_exp* S_exp::EQ(S_exp* a,S_exp* b)
{
	if((ATOM(a))->get_info()=="NIL" || (ATOM(b))->get_info()=="NIL") {cout<<"Error: Function applied on non-atomic argument for EQ\n";exit(1);}


	if(a->info==b->info) return new S_exp("T");
	else return new S_exp("NIL");
}



S_exp* S_exp::PLUS(S_exp* a)
{
	string s;
	if((INT(CAR(a)))->info=="NIL" || (INT(CAR(CDR(a))))->info=="NIL") {cout<<"Interpreter: Non-numeric arguments for PLUS"<<endl;exit(1);}
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	int num=n1 + n2;

	stringstream ss;
	ss<<num;
	return new S_exp(ss.str());
}


S_exp* S_exp::MINUS(S_exp* a)
{
	string s;
	if((INT(CAR(a)))->info=="NIL" || (INT(CAR(CDR(a))))->info=="NIL") {cout<<"Interpreter: Non-numeric arguments for MINUS"<<endl;exit(1);}
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	int num=n1 - n2;


	stringstream ss;
	ss<<num;
	return new S_exp(ss.str());
}

S_exp* S_exp::TIMES(S_exp* a)
{
	string s;
	if((INT(CAR(a)))->info=="NIL" || (INT(CAR(CDR(a))))->info=="NIL") {cout<<"Interpreter: Non-numeric arguments for TIMES"<<endl;exit(1);}

	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	int num=n1 * n2;

	stringstream ss;
	ss<<num;
	return new S_exp(ss.str());
}

S_exp* S_exp::QUOTIENT(S_exp* a)
{
	string s;
	if((INT(CAR(a)))->info=="NIL" || (INT(CAR(CDR(a))))->info=="NIL") {cout<<"Interpreter: Non-numeric arguments"<<endl;exit(1);}

	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	if(n2==0) {cout<<"Error: Divide by zero\n";exit(1);}
	int num=n1 / n2;

	stringstream ss;
	ss<<num;
	return new S_exp(ss.str());
}

S_exp* S_exp::REMAINDER(S_exp* a)
{
	string s;
	if((INT(CAR(a)))->info=="NIL" || (INT(CAR(CDR(a))))->info=="NIL") {cout<<"Interpreter: Non-numeric arguments"<<endl;exit(1);}
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	if(n2==0) {cout<<"Error: Divide by zero\n";exit(1);}
	int num=n1 % n2;

	stringstream ss;
	ss<<num;
	return new S_exp(ss.str());
}

S_exp* S_exp::LESS(S_exp* a)
{
	string s;
	if((INT(CAR(a)))->info=="NIL" || (INT(CAR(CDR(a))))->info=="NIL") {cout<<"Interpreter: Non-numeric arguments"<<endl;exit(1);}
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	if(n1 < n2 ) s="T";
	else s="NIL";

	return new S_exp(s);
}

S_exp* S_exp::GREATER(S_exp* a)
{
	string s;
	if((INT(CAR(a)))->info=="NIL" || (INT(CAR(CDR(a))))->info=="NIL") {cout<<"Interpreter: Non-numeric arguments"<<endl;exit(1);}
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	if(n1 > n2 ) s="T";
	else s="NIL";

	return new S_exp(s);
}


S_exp* S_exp::IN(S_exp* exp,S_exp* aList)
{
	string s=exp->info;

	while(aList->info!="NIL" && aList->left->left->info!=s)
		aList=aList->right;

	if(aList->info!="NIL" && aList->left->left->info==s) return new S_exp("T");
	else return new S_exp("NIL");
}


S_exp* S_exp::GETVAL(S_exp* exp,S_exp* aList)
{
	string s=exp->info;

	while(aList->info!="NIL" && aList->left->left->info!=s)
		aList=aList->right;

	if(aList->info!="NIL" && aList->left->left->info==s) return aList->left->right;
	else return new S_exp("NIL");
}


