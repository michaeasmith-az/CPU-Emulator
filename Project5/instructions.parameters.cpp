// instructions.parameters.cpp
// Micah Smith

// Implements functions that control operation parameters for Instructions class


#include "instructions.h"


// Get an array item.
// Sets index[0] to the index of array item in long_mem, and sets long_mem[0] to the current value stored in the item.
void Instructions::arrayItem() 
{
	++place; // arr *[name]* [index]
	long_mem[1] = 0; // array found flag
	for (index[10] = 0; index[10] < 64; ++index[10]) // find the array
	{
		if (arr_name[index[10]] == *place)
		{
			++place; // arr [name] *[index]*
			long_mem[1] = 1;
			i_type i;
			if (*place == "reg")
			{
				++place;
				i = regs[std::stoi(*place)]; // array index
			}
			else
			{
				i = std::stoi(*place); // get index
			}
			if (i < arr_size[index[10]]) // check if index less than size
			{
				index[0] = arr_start[index[10]] + i;
				long_mem[0] = long_mem[index[0]];
			}
			else
			{
				std::cout << "Error: array index out of range." << std::endl; // display error message and end program
				*(place + 1) = "End_Of_Instructions";
				long_mem[0] = 0; // dummy numbers to avoid program crash
				index[0] = 1027;
			}
			break;
		}
	}
	if (long_mem[1] == 0) // if array not found
	{
		std::cout << "Could not find array: " << *place << std::endl;
		*(place + 1) = "End_Of_Instructions";
	}
}

// Get a double array item.
// Sets index[0] to the index of array item in double_mem, and sets double_mem[0] to the current value stored in the item.
void Instructions::arrayItemDouble()
{
	++place; // arrd *[name]* [index]
	long_mem[1] = 0; // array found flag
	for (index[10] = 0; index[10] < 64; ++index[10]) // find the array
	{
		if (arrd_name[index[10]] == *place)
		{
			++place; // arrd [name] *[index]*
			long_mem[1] = 1;
			i_type i;
			if (*place == "reg")
			{
				++place;
				i = regs[std::stoi(*place)]; // array index
			}
			else
			{
				i = std::stoi(*place); // get index
			}
			if (i < arrd_size[index[10]]) // check if index less than size
			{
				index[0] = arrd_start[index[10]] + i;
				double_mem[0] = double_mem[index[0]];
			}
			else
			{
				std::cout << "Error: array index out of range." << std::endl; // display error message and end program
				*(place + 1) = "End_Of_Instructions";
				double_mem[0] = 0; // dummy numbers to avoid program crash
				index[0] = 0;
			}
			break;
		}
	}
	if (long_mem[1] == 0) // if array not found
	{
		std::cout << "Could not find double array: " << *place << std::endl;
		*(place + 1) = "End_Of_Instructions";
	}
}

void Instructions::arrayParams() // Sets index[0] to the index of the array item used as the first term. Sets long_mem[0] to the value of the second term.
{
	arrayItem();
	long_mem[1] = long_mem[0];
	++place;
	if (*place == "reg") // if the 2nd term is a register
	{
		++place; // go to index of 2nd register --- mov reg [index] reg *[index]* end
		index[10] = std::stoi(*place); // store the index of the second register
		long_mem[0] = regs[index[10]]; // set the second term equal to the value of the second register
	}
	else if (*place == "input")
	{
		std::cin >> long_mem[0];
	}
	else if (*place == "arr")
	{
		arrayItem();
	}
	else if (*place != "End_Of_Instructions") // if the 2nd term is a number
	{
		long_mem[0] = std::stol(*place);
	}
}

void Instructions::arrayParamsDouble() // Sets index[0] to the index of the array item used as the first term. Sets long_mem[0] to the value of the second term.
{
	arrayItemDouble();
	double_mem[1] = double_mem[0];
	++place;
	if (*place == "regd") // if the 2nd term is a register
	{
		++place; // go to index of 2nd register --- mov reg [index] reg *[index]* end
		index[10] = std::stoi(*place); // store the index of the second register
		double_mem[0] = regsd[index[10]]; // set the second term equal to the value of the second register
	}
	else if (*place == "input")
	{
		std::cin >> double_mem[0];
	}
	else if (*place == "arrd")
	{
		arrayItemDouble();
	}
	else if (*place != "End_Of_Instructions")// if the 2nd term is a number
	{
		double_mem[0] = std::stod(*place);
	}
}


// Set the parameters for basic operations
//(NOTE: as an example, comments show implementation with the instruction "mov")
void Instructions::operationParams(){
		++place; // go to index --- mov reg *[index]*...
		index[1] = std::stoi(*place); // store index of first register
		++place; // go to either 2nd register or number --- mov reg [index] *reg* [index] end --- OR --- mov reg index *[long]* end
		if (*place == "reg") // if the 2nd term is a register
		{
			++place; // go to index of 2nd register --- mov reg [index] reg *[index]* end
			index[2] = std::stoi(*place); // store the index of the second register
			long_mem[0] = regs[index[2]]; // set the second term equal to the value of the second register
		}
		else if (*place == "input")
		{
			std::cin >> long_mem[0];
		}
		else if (*place == "arr")
		{
			arrayItem();
		}
		else // if the 2nd term is a number
		{
			long_mem[0] = std::stol(*place);
		}
}

// Set the parameters for basic operations on doubles
// returns true for valid syntax
//(NOTE: as an example, comments show implementation with the instruction "movd")
void Instructions::operationParamsDouble(){
		++place; // go to index --- mov regd *[index]*...
		index[1] = std::stoi(*place); // store index of first register
		++place; // go to either 2nd register or number --- mov regd [index] *regd* [index] end --- OR --- mov regd index *[double]* end
		if (*place == "regd") // if the 2nd term is a double register
		{
			++place; // go to index of 2nd register --- mov regd [index] regd *[index]* end
			index[10] = std::stoi(*place); // store the index of the second register
			double_mem[0] = regsd[index[10]]; // set the second term equal to the value of the second register
		}
		else if (*place == "arrd")
		{
			arrayItemDouble();
		}
		else if (*place == "input")
		{
			std::cin >> double_mem[0];
		}
		else // if the 2nd term is a number
		{
			double_mem[0] = std::stod(*place);
		}
}