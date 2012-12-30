/*
 * InputData.cpp

 *
 *  Created on: Oct 18, 2012
 *      Author: vaibhav
 */


#include "InputData.h"

InputData* InputData::onlycopy=0;

void InputData::instance(char* inputfile){
	if(!onlycopy) onlycopy=new InputData(inputfile);
}

InputData* InputData::instance(){
	if(!onlycopy) {std::cout<<"InputData object not instantiated";exit(1);}
	return onlycopy;
}

InputData::InputData(char* inputfile){
	curr_ipitem=-1;
	iter=-1;

	int i;
	std::ifstream in(inputfile);
	while(in>>i) ipitems.push_back(i);
	in.close();
}

int InputData::get_next_input(){
	iter++;
	if(iter>=ipitems.size()) {std::cout<<"Required input data not provided.";exit(1);}
	return ipitems[iter];
}

