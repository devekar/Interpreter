//============================================================================
// Name        : Lisp1.cpp
// Author      : Vaibhav Devekar
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Tokenizer.h"
#include "Interpreter.h"

using namespace std;

int main() {

	char in[]="c:\\input.txt\0";
	Tokenizer::instance(in);
	Interpreter I;
	I.output();
	return 0;
}
