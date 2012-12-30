/*
 * Tokenizer.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: vaibhav
 */

using namespace std;

#include "Tokenizer.h"
Tokenizer* Tokenizer::onlycopy=0;

void Tokenizer::instance(char* inputfile){
	if(!onlycopy) onlycopy=new Tokenizer(inputfile);
}

Tokenizer* Tokenizer::instance(){
	if(!onlycopy) {cout<<"Tokenizer not instantiated";exit(1);}
	return onlycopy;
}


//Reads core grammar to build a list of reserved words and special symbols
//Calls skip_token() to have the first token ready
Tokenizer::Tokenizer(char* inputfile)
{
	curr_token='\0';
	/*
	curr_token_no=0;
	stringstream ss;
	ss<<"program begin end int if then else while loop read write ; , = ! [ ] && || ( ) + - * != == < > <= >=";
	( )

	string s;

	while(ss.good())
	{
		ss>>s;
		gramtoks.push_back(s);
	}
	 */

	string s;
	ifstream in(inputfile);
	if(!in) {cout<<"Input program file not found or error reading file.";exit(1);}
	while(in>>s) ftoks.push_back(s);
	in.close();

	cout<<ftoks.size()<<endl;

	ft=0;
	if(!skip_token()) {cout<<"No content in input file";exit(1);}
}


bool Tokenizer::skip_token()
{
	string s;int x;
	vector<string>::iterator vit;

	if(ft==ftoks.size()) {;curr_token_no=33;curr_token="\0";return false;}
	s=ftoks.at(ft);

	curr_token=s;

	ft++;
	return true;
}



/*
//Gets the next space-delimited token from input stream and
//identifies if entirely a valid token or concatenated sequence of tokens
bool Tokenizer::skip_token()
{
	string s;int x;
	vector<string>::iterator vit;

	if(ft==ftoks.size()) {;curr_token_no=33;curr_token='\0';return false;}
	s=ftoks.at(ft);

	if( (x=issimpletoken(s)) ) {curr_token_no=x;curr_token=s;}
	else if( (x=iscomplextoken(s)) ) {curr_token_no=x;curr_token=s;} //pass s by reference
	else {cout<<"Illegal Token: "<<s<<"\n";exit(2);}

	ft++;
	return true;
}
*/

//Returns current token number
int Tokenizer::get_token_no()
{
	return curr_token_no;
}


//Returns current token name
string Tokenizer::get_token()
{
	return curr_token;
}


//Identify if token is either a reserved word or an integer or an identifier
int Tokenizer::issimpletoken(string s)
{
	vector<string>::iterator vit;
	int x=0;

	if( ((vit=find(gramtoks.begin(),gramtoks.end(),s))-gramtoks.begin()) < 30) x=vit-gramtoks.begin()+1;
	else if(isint(s)) x=31;
	else if(isidentifier(s)) x=32;

	return x;
}


//Identifies first valid token in the concatenated string, moves input-stream pointer to just after the identified token
int Tokenizer::iscomplextoken(string &s)
{
	string sub;
	int i=0;

	//checks if first possible token in string is a token other than special symbol
	if( (s[0]>='0'&&s[0]<='9') || (s[0]>='A'&&s[0]<='Z') || (s[0]>='a'&&s[0]<='z')) {

		for(i=1; i<s.size(); i++)
			if( !((s[i]>='0'&&s[i]<='9') || (s[i]>='A'&&s[i]<='Z') || (s[i]>='a'&&s[i]<='z'))) break;

		ftoks[ft]=s.substr(0,i);		//replace concatenated token by first token detected in it
		if(i<s.size()) 	ftoks.insert(ftoks.begin()+ft+1, s.substr(i));  //Insert remaining part of token

		s=s.substr(0,i);
		return issimpletoken(s);
	}


	//Identify if the first possible token in string is a special symbol
	int x=0;
	for(i=1; i<s.size(); i++)
		if( (s[i]>='0'&&s[i]<='9') || (s[i]>='A'&&s[i]<='Z') || (s[i]>='a'&&s[i]<='z')) break;

	sub=s.substr(0,i);

	for(i=sub.size(); i>0; i--)
		if( (x=issimpletoken(sub.substr(0,i))) ) break;		//Find largest symbol possible

	if(i==0) return 0;
	ftoks[ft]=s.substr(0,i);
	if(i<s.size()) 	ftoks.insert(ftoks.begin()+ft+1,s.substr(i));

	s=s.substr(0,i);
	return x;
}


//Identify if token is integer
bool Tokenizer::isint(string s)
{
	for(int i=0; i<s.size(); i++)
		if( !isdigit(s[i]) ) return false;

	return true;
}


//Identify if token is an identifier
bool Tokenizer::isidentifier(string s)
{
	if(s[0]<65 || s[0]>90) return false;

	int i;
	for(i=1; i<s.size() && s[i]>='A' && s[i]<='Z'; i++);
	if(i==s.size()) return true;

	for(; i<s.size() && isdigit(s[i]); i++);
	if(i==s.size()) return true;

	return false;
}

