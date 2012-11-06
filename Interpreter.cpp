//============================================================================
// Name        : proj4.cpp
// Author      : Vaibhav Devekar
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<stdio.h>
#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

#include "Tokenizer.cpp"
#include "InputData.cpp"
#include "classes.cpp"

int main(int argc,char* args[] ) {
	//freopen ("c:\\myfile.txt","w",stdout);

	if(argc!=3) {cout<<"Incorrect commandline parameters, provide filepath for input file as argument.";exit(1);}
	Tokenizer::instance(args[1]);
	InputData::instance(args[2]);

	Prog p;
	p.parseProg();
	p.printProg();
	p.execProg();

	return 0;
}
