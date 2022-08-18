//instructions.h
// Micah Smith

// See InstructionsREADME.txt for details on how to use

#ifndef __INSTRUCTIONS_H_INCLUDED__ 
#define __INSTRUCTIONS_H_INCLUDED__

#include <iostream>
#include<cstdlib>
#include<string>
#include <sstream>
#include<fstream>
#include<ctime>

class Instructions{
	typedef std::size_t i_type; // index type
	typedef std::string instruct; // instruction string type

public:

	Instructions();
	void readFile(std::istream& in); // read instructions
	// Modules for implementing instructions:
	void singleInstruction(); 
	void arrayItem();
	void arrayItemDouble();
	void arrayParams();
	void arrayParamsDouble();
	void operationParams();
	void operationParamsDouble();
	bool condition();
	void compare();
	int run(bool print_return = true); // run the instructions

	// Data:

	// For client use:
	enum{ n_regs = 64 };
	long regs[n_regs]; // registers for client use
	double regsd[n_regs]; // double registers for client use

	// For internal use:
private:
	enum{ n_mem = 4096 };
	enum{ n_index = 64 };
	enum{ n_data_mem = 1028};
	instruct mem[n_mem]; // memory to store instructions
	i_type index[n_index]; // memory to store indices -- Reserved: index[63] is the storedPlace (stack) index, index[62] is the function index,
	//index[61] is the array index, index[60] is the double array index
	long long_mem[n_mem]; // memory to store longs -- Reserved: long_mem[1027] is the comparison flag,  and long_mem[1026] is the return type flag
	double double_mem[n_mem]; // memory to store doubles
	i_type arr_start[n_index]; // stores starting indices of arrays in long_mem
	i_type arr_size[n_index]; // stores sizes of arrays
	i_type arrd_start[n_index]; // stores starting indices of double arrays in double_mem
	i_type arrd_size[n_index]; // stores sizes of double arrays
	std::string arr_name[n_index]; // array names
	std::string arrd_name[n_index]; // double array names
	std::string string_mem[n_data_mem]; // memory to store strings -- Reserved: items 0-63 are for function names, 1027 is the conditional statement operator
	instruct *place; // pointer to store place in instructions
	instruct *storedPlace[n_mem]; // the stack
	instruct *funcPlace[n_index]; // stored function places

};

#endif