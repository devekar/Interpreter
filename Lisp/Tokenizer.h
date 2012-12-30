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
	std::vector<std::string> gramtoks;
	std::vector<std::string> ftoks;
	int ft;
	std::string curr_token;
	int curr_token_no;
	static Tokenizer* onlycopy;
	Tokenizer(char* inputfile);
public:
	static Tokenizer* instance();
	static void instance(char* inputfile);
	bool skip_token();
	int get_token_no();
	std::string get_token();
	int issimpletoken(std::string s);
	int iscomplextoken(std::string &s);
	bool isint(std::string s);
	bool isidentifier(std::string s);

	~Tokenizer();
};

#endif
