/*
 * Tokenizer.h
 *
 *  Created on: Sep 29, 2012
 *      Author: vaibhav
 */

#ifndef __TOKENIZER_H_INCLUDED__
#define __TOKENIZER_H_INCLUDED__


#include<stdio.h>
#include <iostream>
#include<fstream>
#include<vector>
#include <string>
#include<algorithm>
#include<sstream>

class Tokenizer{
	std::vector<std::string> ftoks;
	int curr_index;
	std::string curr_token;
	static Tokenizer* onlycopy;
	Tokenizer();
public:
	static Tokenizer* instance();
	void reset();
	bool skip_token();
	std::string get_token();

	void process_tok(std::string s);
	bool isInt(std::string s);
	bool isIdentifier(std::string s);
	bool isCompound(std::string s);

	~Tokenizer();
};

#endif
