//============================================================================
// Name        : Lisp.cpp
// Author      : Vaibhav Devekar
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<exception>
#include "Tokenizer.h"
#include "IO.h"
#include "Interpret.h"
using namespace std;

int main(int argc,char* args[] ) {

	//if(argc!=2) {cout<<"Incorrect commandline parameters, provide filepath for input as argument.\n";exit(1);}
	//freopen("c:\\input.txt","r",stdin);

	Tokenizer *t=Tokenizer::instance();
	IO *io=new IO();
	Interpret *i=new Interpret();

	S_exp *s;

	try
	{
		while(1)
		{
			cout<<">  ";
			t->reset();

			s=io->input();
			s=i->eval(s,S_EXP("NIL"));
			io->output(s);
			cout<<endl<<endl;
		}
	}
	catch(exception& e)
	{
		cout << "Exception: Invalid S-expression.\n " << e.what() << endl;
	}

	return 0;
}
