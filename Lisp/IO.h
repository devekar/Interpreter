/*
 * IO.h
 *
 *  Created on: Dec 25, 2012
 *      Author: vaibhav devekar
 */
#include"S-exp.h"
#include"Tokenizer.h"

class IO{
	Tokenizer *t;
public:
	IO();
	S_exp* input();
	S_exp* input2();
	void output(S_exp* s);
};

