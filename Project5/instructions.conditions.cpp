// instructions.conditions.cpp
// Micah Smith

// Implements conditional statements for Instructions class

#include "instructions.h"


// Condition module: returns true or false based on whether the condition is met 
// (NOTE: as an example, comments show implementation with the instruction "if")
bool Instructions::condition(){
	long_mem[1023] = long_mem[1024] = long_mem[1025] = 0;
	++place;
	if (*place == "reg")
	{
		++place; // --- if reg *[index]*... endif
		index[0] = std::stoi(*place); // store index of first register
		long_mem[10] = regs[index[0]]; // set the first operand equal to the value of the first register
	}
	else if (*place == "regd")
	{
		++place;
		index[1] = std::stoi(*place); // store index of first double register
		double_mem[10] = regsd[index[1]]; // set the first operand equal to the value of the first double register
		long_mem[1025] = 1; // set compare doubles flag
		long_mem[1024] = 1; // flag that first term is a double
	}
	else if (*place == "arr")
	{
		arrayItem(); // get value of array item
		long_mem[10] = long_mem[0]; // set the first operand equal to the value of the array item
	}
	else if (*place == "arrd")
	{
		arrayItemDouble();
		double_mem[10] = double_mem[0];
		long_mem[1025] = 1; // set compare doubles flag
		long_mem[1024] = 1; // flag that first term is a double
	}
	else // if the first operand is a number
	{
		long_mem[10] = std::stol(*place);
		double_mem[10] = std::stod(*place);
		long_mem[1024] = 1; // flag that conversion to double is unneccessary
	}
	++place; // to conditional operator --- if reg [index] *[operator]* reg [index] ... endif
	string_mem[1027] = *place;
	++place; // to second operand
	if (*place == "reg")
	{
		++place;
		index[1] = std::stoi(*place); // store index of second register
		long_mem[20] = regs[index[1]]; // set the second operand equal to the value of the second register
	}
	else if (*place == "regd")
	{
		++place;
		index[1] = std::stoi(*place); // store index of second register
		double_mem[20] = regsd[index[1]]; // set the second operand equal to the value of the second register
		long_mem[1025] = 1; // set compare doubles flag
		long_mem[1023] = 1; // flag that conversion to double is unneccessary
	}
	else if (*place == "arr")
	{
		arrayItem(); // get value of array item
		long_mem[20] = long_mem[0]; // set the first operand equal to the value of the array item
	}
	else if (*place == "arrd")
	{
		arrayItemDouble();
		double_mem[20] = double_mem[0];
		long_mem[1025] = 1; // set compare doubles flag
		long_mem[1023] = 1; // flag that conversion to double is unneccessary
	}
	else // if the first operand is a number
	{
		long_mem[20] = std::stol(*place); // set the operand equal to the number
		double_mem[20] = std::stod(*place);
		long_mem[1023] = 1; // flag that conversion to double is unneccessary
	}
	++place; // go to the spot past the compare
	compare();
	if (string_mem[1027] == "<") // less than
	{
		if (long_mem[1027] == 1) // long_mem[1027] is reserved to store the comparison value
			return true;
		else
			return false;
	}
	if (string_mem[1027] == ">") // greater than
	{
		if (long_mem[1027] == 3)
			return true;
		else
			return false;
	}
	if (string_mem[1027] == "==") // equal to
	{
		if (long_mem[1027] == 2)
			return true;
		else
			return false;
	}
	if (string_mem[1027] == "<=") // less than or equal to
	{
		if (long_mem[1027]< 3)
			return true;
		else
			return false;
	}
	if (string_mem[1027] == ">=") // greater than or equal to
	{
		if (long_mem[1027] > 1)
			return true;
		else
			return false;
	}
	if (string_mem[1027] == "!=") // not equal to
	{
		if (long_mem[1027] != 2)
			return true;
		else
			return false;
	}
}

// Compare module: compares long_mem[10] to long_mem[20]
// Indicates the results of the comparison by setting long_mem[1027] equal to 1, 2, or 3
void Instructions::compare()
{
	if (long_mem[1025] == 1)
	{
		if (long_mem[1024] == 0)
		{
			double_mem[10] = long_mem[10];
		}
		else if (long_mem[1023] == 0)
		{
			double_mem[20] = long_mem[20];
		}
		if (double_mem[10] > double_mem[20]) //  3 if greater than
			long_mem[1027] = 3;
		else if (double_mem[10] == double_mem[20]) //  2 if equal
			long_mem[1027] = 2;
		else if (double_mem[10] < double_mem[20]) // 1 if less than
			long_mem[1027] = 1;
	}
	else
	{
		if (long_mem[10] > long_mem[20]) //  3 if greater than
			long_mem[1027] = 3;
		else if (long_mem[10] == long_mem[20]) //  2 if equal
			long_mem[1027] = 2;
		else if (long_mem[10] < long_mem[20]) // 1 if less than
			long_mem[1027] = 1;
	}
}