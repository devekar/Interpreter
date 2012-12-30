/*
 * Interpreter.cpp
 *
 *  Created on: Dec 24, 2012
 *      Author: vaibhav
 */

#include"Interpreter.h"
#include<queue>

using namespace std;

Interpreter::Interpreter()
{
	dList=new S_exp("NIL");
	aList=new S_exp("NIL");
	t=Tokenizer::instance();
}


S_exp* Interpreter::eval(S_exp* exp)
{
	S_exp* t1;

	if((S_exp::ATOM(exp))->info=="T"){
		if((S_exp::INT(exp))->info=="T") return exp;
		else if(S_exp::EQ(exp,"T")) return new S_exp("T");
		else if(S_exp::EQ(exp,"NIL")) return new S_exp("NIL");
		else if( (S_exp::IN(exp,aList))->info=="T") return S_exp::GETVAL(exp,aList);
		else {cout<<"\nError : Unbound variable\n";exit(1);}
	}
	else if( (t1=S_exp::ATOM(S_exp::CAR(exp))) && t1->info=="T" ) {
		if(S_exp::EQ(S_exp::CAR(exp),"QUOTE")) {return S_exp::CADR(exp); }
		else if(S_exp::EQ(S_exp::CAR(exp),"COND")) return evcon(S_exp::CDR(exp));
		else {return apply(S_exp::CAR(exp), evlis(S_exp::CDR(exp)));}
	}
	else {cout<<"\nError\n";exit(1);}

}

S_exp* Interpreter::evlis(S_exp* exp)
{
	if((S_exp::isNULL(exp))->info=="T" ) return new S_exp("NIL");
	else return S_exp::CONS( eval(S_exp::CAR(exp)), evlis(S_exp::CDR(exp)) );
}


S_exp* Interpreter::evcon(S_exp* pairs)
{
	if((S_exp::isNULL(pairs))->info=="T") {cout<<"\nError\n";exit(1);}
	else if( S_exp::EQ( eval(S_exp::CAAR(pairs)), new S_exp("T")) ) return eval(S_exp::CADAR(pairs));
	else return evcon(S_exp::CDR(pairs));
}



S_exp* Interpreter::apply(S_exp* f, S_exp* param)
{
	if(S_exp::ATOM(f)) {
		if(S_exp::EQ(f,"CAR")) return S_exp::CAAR(param);
		else if(S_exp::EQ(f,"CDR")) return S_exp::CDAR(param);
		else if(S_exp::EQ(f,"CONS")) return S_exp::CONS(S_exp::CAR(param),S_exp::CDR(param));
		else if(S_exp::EQ(f,"ATOM")) return S_exp::ATOM(S_exp::CAR(param));
		else if(S_exp::EQ(f,"NULL")) return S_exp::isNULL(S_exp::CAR(param));
		else if(S_exp::EQ(f,"EQ")) return S_exp::EQ(S_exp::CAR(param),S_exp::CADR(param));
		else if(S_exp::EQ(f,"PLUS")) return S_exp::PLUS(param);
		else if(S_exp::EQ(f,"MINUS")) return S_exp::MINUS(param);
		else if(S_exp::EQ(f,"TIMES")) return S_exp::TIMES(param);
		else if(S_exp::EQ(f,"QUOTIENT")) return S_exp::QUOTIENT(param);
		else if(S_exp::EQ(f,"REMAINDER")) return S_exp::REMAINDER(param);
		else if(S_exp::EQ(f,"LESS")) return S_exp::LESS(param);
		else if(S_exp::EQ(f,"GREATER")) return S_exp::GREATER(param);
		else {
			S_exp* tt=S_exp::CAR(S_exp::GETVAL(f,dList));
			addpairs2aList( tt,param );
			return eval(  S_exp::CDR(S_exp::GETVAL(f,dList))  );
		};
	}
	else {cout<<"\nError\n";exit(1);}
}


void Interpreter::addpairs2aList(S_exp* pList,S_exp* arg)
{
	if(pList->info=="NIL") return;

	S_exp* root=new S_exp();
	S_exp* exp=new S_exp();

	root->right=aList;
	aList=root;

	root->left=exp;
	exp->left=pList->left;
	exp->right=arg->left;
	addpairs2aList(pList->right,arg->right);
}

void Interpreter::output()
{
	cout<<"=============================================="<<endl;
	while(t->get_token()!="\0")
	{
		t->skip_token();   //skip (

		if(t->get_token()=="DEFUN") {
			DEFUN();
			//dfs();
		}
		else {
			S_exp* execstree=buildexecstree();
			//cout<<endl;  dfs(execstree);
			S_exp* result=eval(execstree);
			print(result);
		}

		t->skip_token(); //skip )
	}
}


void Interpreter::DEFUN()
{
	S_exp* newexp=new S_exp();

	newexp->right=dList;
	dList=newexp;

	newexp->left=new S_exp();
	newexp=newexp->left;

	t->skip_token();t->skip_token(); //skip define (

	newexp->left=new S_exp(t->get_token()); //function name
	t->skip_token(); //funct name

	newexp->right=new S_exp();
	newexp=newexp->right;


	if(t->get_token()==")") {
		//do nothing
	}
	else newexp->left=buildparamstree();
	t->skip_token(); //skip )

	newexp->right=buildbodystree();
}


S_exp* Interpreter::buildparamstree()
{
	string s;

	S_exp* root=new S_exp();
	S_exp* newexp=root;
	while((s=t->get_token())!=")")
	{
		newexp->left=new S_exp(s);
		newexp->right=new S_exp();
		newexp=newexp->right;
		t->skip_token();
	}
	newexp->info="NIL";

	return root;
}


S_exp* Interpreter::buildbodystree()
{
	t->skip_token(); //skip body (
	string s;

	S_exp* root=new S_exp();
	S_exp* newexp=root;
	while((s=t->get_token())!=")")
	{
		if(s=="(") newexp->left=buildbodystree();
		else newexp->left=new S_exp(s);

		newexp->right=new S_exp();
		newexp=newexp->right;
		t->skip_token();
	}
	newexp->info="NIL";

	t->skip_token(); //skip body )

	return root;
}


S_exp* Interpreter::buildexecstree()
{
	string s;
	S_exp* root=new S_exp();
	S_exp* exp=root;
	while((s=t->get_token())!=")")
	{
		if(s=="(") {t->skip_token(); exp->left=buildexecstree();}
		else exp->left=new S_exp(s);

		exp->right=new S_exp();
		exp=exp->right;
		t->skip_token();
	}
	exp->info="NIL";

	return root;
}


void Interpreter::print(S_exp* result)
{
	if(result->info=="NIL") cout<<"'()\n";
	else if(result->info!="\0") cout<<result->info<<endl;
	else {
		cout<<"( ";
		while(result->info!="NIL")
		{
			cout<<result->left->info<<" ";
			result=result->right;
		}
		cout<<" )\n";
	}
}




void Interpreter::dfs(S_exp* t)
{
	if(!t) return;
	cout<<t->info<<" ";
	dfs(t->left);
	dfs(t->right);
}

/*
void Interpreter::bfs()
{
	S_exp* t;
	queue<S_exp*> q;
	q.push(dList);
	cout<<endl;
	while(!q.empty())
	{
		t=q.front(); q.pop();
		cout<<t->info<<" ";
		if(t->left) q.push(t->left);
		if(t->right) q.push(t->right);
	}
}
*/
