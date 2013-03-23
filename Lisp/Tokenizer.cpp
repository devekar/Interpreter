/*
 * Tokenizer.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: vaibhav devekar
 */

using namespace std;

#include "Tokenizer.h"
Tokenizer* Tokenizer::onlycopy=0;

Tokenizer* Tokenizer::instance(){
	if(!onlycopy) onlycopy=new Tokenizer();
	return onlycopy;
}


Tokenizer::Tokenizer()
{
	ftoks.clear();
	curr_index=0;
}

//Calls skip_token() to have the first token ready
void Tokenizer::reset()
{
	ftoks.clear();
	curr_index=0;
	skip_token();
}

bool Tokenizer::skip_token()
{
	string s="",s1="";

	if(curr_index==ftoks.size())  {
		ftoks.clear();
		curr_index=0;

		do{
			getline(cin,s);
			stringstream ss1(s);
			ss1>>s1;
		}while(s1=="");

		istringstream is(s);
		while(is>>s)
		{
			process_tok(s);
		}

	}

	curr_token=ftoks.at(curr_index);

	curr_index++;
	return true;
}


//Returns current token name
string Tokenizer::get_token()
{
	return curr_token;
}

void Tokenizer::process_tok(string s)
{
	if(s=="(" || s==")" || s==".") {ftoks.push_back(s);ftoks.push_back(" ");}
	else if(isInt(s)) {
		char s1[15];
		sprintf(s1,"%d",atoi(s.c_str()));
		string ss(s1);
		ftoks.push_back(ss);ftoks.push_back(" ");}
	else if(isIdentifier(s)) {ftoks.push_back(s);ftoks.push_back(" ");}
	else if(isCompound(s)) {
		// processed in isCompund()
	}

	else {cout<<"Tokenizer: Invalid token.\n";cout<<s<<endl; exit(1);}
}


bool Tokenizer::isInt(string s)
{
	int i=0;
	if(s[i]=='-'||s[i]=='+') i++;

	for(; i<s.size(); i++)
		if( !isdigit(s[i]) ) return false;

	return true;
}


bool Tokenizer::isIdentifier(string s)
{
	if(s[0]<'A' || s[0]>'Z') return false;

	int i;
	for(i=1; i<s.size() && ((s[i]>='A' && s[i]<='Z') ||isdigit(s[i])); i++);
	//if(i==s.size()) return true;

	//for(; i<s.size() && isdigit(s[i]); i++);

	if(i==s.size()) return true;
	else return false;
}


bool Tokenizer::isCompound(string s)
{
	if(s[0]=='('||s[0]==')'||s[0]=='.') {
		ftoks.push_back(s.substr(0,1));
		ftoks.push_back(" ");
		process_tok(s.substr(1));
	}
	else if(s[0]=='-'||s[0]=='+'||isdigit(s[0])) {
		int i;
		for(i=1;i<s.size() && isdigit(s[i]); i++);

		if(isInt(s.substr(0,i))) {

			char s1[15];
			sprintf(s1,"%d",atoi(s.substr(0,i).c_str()));
			string ss(s1);

			ftoks.push_back(ss);
			ftoks.push_back(" ");
		}
		else {cout<<"Tokenizer: Invalid token.\n";cout<<s<<endl; exit(1);} //error


		if(s[i]=='('||s[i]==')'||s[i]=='.') process_tok(s.substr(i));
		else {cout<<"Tokenizer: Invalid token.\n"; cout<<s<<endl;exit(1);} //error
	}
	else if(s[0]>='A' && s[0]<='Z') {
		int i;
		for(i=1;i<s.size() && ((s[i]>='A' && s[i]<='Z')||isdigit(s[i])); i++);

		ftoks.push_back(s.substr(0,i)); ftoks.push_back(" ");

		if(s[i]=='('||s[i]==')'||s[i]=='.') process_tok(s.substr(i));
		else {cout<<"Tokenizer: Invalid token.\n"; cout<<s<<endl;exit(1);} //error
	}
	else return false;


	return true;
}

