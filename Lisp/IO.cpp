/*
 * IO.cpp
 *
 *  Created on: Dec 24, 2012
 *      Author: vaibhav devekar
 */

#include"IO.h"
using namespace std;

IO::IO()
{
	t=Tokenizer::instance();
}


S_exp* IO::input()
{
	S_exp *head,*left,*right;
	while(t->get_token()==" ") t->skip_token(); //skip whitespace

	if(t->get_token()!="(" && t->get_token()!=")" && t->get_token()!=".") {
		head=S_exp::createS_exp(t->get_token());
		t->skip_token(); //skip token
	}
	else if(t->get_token()=="(") {
		t->skip_token(); // skip (

		while(t->get_token()==" ") t->skip_token(); //skip whitespace


		if(t->get_token()==")") {
			head=S_exp::createS_exp("NIL");
			t->skip_token(); //skip )
		}
		else {
			left=input();

			while(t->get_token()==" ") t->skip_token(); //skip whitespace

			if(t->get_token()==".") {
				t->skip_token(); // skip .
				right=input();

				while(t->get_token()==" ") t->skip_token(); //skip whitespace

				if(t->get_token()==")") t->skip_token(); // skip )
				else {cout<<"IO: Invalid S-expression\n";exit(1);}
			}
			else{
				right=input2();
			}

			head=S_exp::CONS(left,right);
		}
	}
	else {cout<<"IO: Invalid S-expression\n";exit(1);}

	return head;

}


S_exp* IO::input2()
{
	S_exp *head,*left,*right;

	while(t->get_token()==" ") t->skip_token(); //skip whitespace

	if(t->get_token()==")") {
		head=S_exp::createS_exp("NIL");
		t->skip_token(); // skip )
	}
	else {
		left=input();
		right=input2();
		head=S_exp::CONS(left,right);
	}

	return head;
}


void IO::output(S_exp *s)
{
	if(s->get_info()!="\0") cout<<s->get_info();
	else {
		cout<<"(";
		output(S_exp::CAR(s));
		cout<<" . ";
		output(S_exp::CDR(s));
		cout<<")";
	}
}


