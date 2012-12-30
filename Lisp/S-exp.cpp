/*
 * S-exp.cpp
 *
 *  Created on: Dec 25, 2012
 *      Author: vaibhav
 */

#include"S-exp.h"
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>

using namespace std;

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

S_exp* S_exp::CONS(S_exp* a,S_exp* b)
{
	S_exp* newexp=new S_exp();
	newexp->left=a;
	newexp->right=b;
	return newexp;
}

S_exp* S_exp::CAR(S_exp* a)
{
	return a->left;
}

S_exp* S_exp::CDR(S_exp* a)
{
	return a->right;
}


S_exp* S_exp::CADR(S_exp* a)
{
	return a->right->left;
}

S_exp* S_exp::CDAR(S_exp* a)
{
	return a->left->right;
}

S_exp* S_exp::CAAR(S_exp* a)
{
	return a->left->left;
}

S_exp* S_exp::CADAR(S_exp* a)
{
	return a->left->right->left;
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
	string s=a->info;

	for(int i=0; i<s.size(); i++)
		if( !isdigit(s[i]) ) return new S_exp("NIL");

	return new S_exp("T");
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


S_exp* S_exp::EQ(S_exp* a,S_exp* b)
{
	if(a->info==b->info) return new S_exp("T");
	else return new S_exp("NIL");
}


bool S_exp::EQ(S_exp* a,std::string b)
{
	if(a->info==b) return true;
	else return false;
}


S_exp* S_exp::PLUS(S_exp* a)
{
	string s;
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
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	int num=n1 / n2;

	stringstream ss;
	ss<<num;
	return new S_exp(ss.str());
}

S_exp* S_exp::REMAINDER(S_exp* a)
{
	string s;
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	int num=n1 % n2;

	stringstream ss;
	ss<<num;
	return new S_exp(ss.str());
}

S_exp* S_exp::LESS(S_exp* a)
{
	string s;
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	if(n1 < n2 ) s="T";
	else s="NIL";

	return new S_exp(s);
}

S_exp* S_exp::GREATER(S_exp* a)
{
	string s;
	int n1=atoi((a->left->info).c_str());
	int n2=atoi((a->right->left->info).c_str());

	if(n1 > n2 ) s="T";
	else s="NIL";

	return new S_exp(s);
}
