/*
 * InputData.h
 *
 *  Created on: Sep 29, 2012
 *      Author: vaibhav
 */
#ifndef __INPUTDATA_H_INCLUDED__
#define __INPUTDATA_H_INCLUDED__

#include<stdio.h>
#include <iostream>
#include<fstream>
#include<vector>
#include <string>
#include <stdlib.h>

class InputData{
	std::vector<int> ipitems;
	int curr_ipitem;
	int iter;
	static InputData* onlycopy;
	InputData(char* inputfile);

public:
	static InputData* instance();
	static void instance(char* inputfile);
	int get_next_input();
};


#endif
