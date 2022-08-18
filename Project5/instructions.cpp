// instructions.cpp
// Micah Smith

// Implements primary functions of the Instructions class

#include "instructions.h"

Instructions::Instructions()
{
	place = mem;
}

// Read a file or istream of instructions into memory
void Instructions::readFile(std::istream& in){ 
	instruct temp;
	i_type i = 0;
	while (in >> temp)
	{
		if (temp == ";") // comments
		{
			in.ignore(10000, '\n');
		}
		else if (temp == "#include") // include another file
		{
			if (in >> temp)
			{
				std::ifstream myfile(temp);
				readFile(myfile);
			}
		}
		else
		{
			*place = temp;
			i++;
			++place;
		}
	}
	*place = "End_Of_Instructions"; // flag the end of the instructions
}

// Execute a single instruction
void Instructions::singleInstruction(){
	if (*place == "return") // return
	{
		++place;
		if (*place == "reg") // if returning a register
		{
			++place;
			regs[0] = regs[std::stoi(*place)]; // set return value to the register at the given index
		}
		else if (*place == "regd") // if returning a register
		{
			++place;
			regsd[0] = regsd[std::stoi(*place)]; // set return value to the register at the given index
			long_mem[1026] = 1; // return type == double
		}
		else if (*place == "arr")
		{
			arrayItem();
			regs[0] = long_mem[0];
		}
		else if (*place == "arrd")
		{
			arrayItemDouble();
			regsd[0] = double_mem[0];
			long_mem[1026] = 1; // return type == double
		}
		else if (*place == "End_Of_Instructions") // if no string follows "return"
		{
			return;
		}
		else // if returning a number
		{
			regs[0] = std::stol(*place);
		}
		++place;
		*place = "End_Of_Instructions"; // End instructions after return
	}
	else if (*place == "mov") // Set a register to a value
	{
		++place;
		if (*place == "reg")
		{
			operationParams();
			regs[index[1]] = long_mem[0]; // mov
		}
		else if (*place == "regd")
		{
			operationParamsDouble();
			regsd[index[1]] = double_mem[0]; // mov double
		}
		else if (*place == "arr")
		{
			arrayParams();
			long_mem[index[0]] = long_mem[0];
		}
		else if (*place == "arrd")
		{
			arrayParamsDouble();
			double_mem[index[0]] = double_mem[0];
		}
		else
		{
			std::cout << "Invalid instruction: '" << *place << "' --- expected 'reg', 'regd', 'arr', or 'arrd'" << std::endl;
			*(place + 1) = "End_Of_Instructions";
		}
				
	}
	else if (*place == "add")
	{
		++place;
		if (*place == "reg")
		{
			operationParams();
			regs[index[1]] = regs[index[1]] + long_mem[0]; // add
		}
		else if (*place == "regd")
		{
			operationParamsDouble();
			regsd[index[1]] = regsd[index[1]] + double_mem[0]; // add double
		}
		else if (*place == "arr")
		{
			arrayParams();
			long_mem[index[0]] = long_mem[index[0]] + long_mem[0];
		}
		else if (*place == "arrd")
		{
			arrayParamsDouble();
			double_mem[index[0]] = double_mem[index[0]] + double_mem[0];
		}
		else
		{
			std::cout << "Invalid instruction: '" << *place << "' --- expected 'reg', 'regd', 'arr', or 'arrd'" << std::endl;
			*(place + 1) = "End_Of_Instructions";
		}
	}
	else if (*place == "sub")
	{
		++place;
		if (*place == "reg")
		{
			operationParams();
			regs[index[1]] = regs[index[1]] - long_mem[0]; // sub
		}
		else if (*place == "regd")
		{
			operationParamsDouble();
			regsd[index[1]] = regsd[index[1]] - double_mem[0]; // sub double
		}
		else if (*place == "arr")
		{
			arrayParams();
			long_mem[index[0]] = long_mem[index[0]] - long_mem[0];
		}
		else if (*place == "arrd")
		{
			arrayParamsDouble();
			double_mem[index[0]] = double_mem[index[0]] - double_mem[0];
		}
		else
		{
			std::cout << "Invalid instruction: '" << *place << "' --- expected 'reg', 'regd', 'arr', or 'arrd'" << std::endl;
			*(place + 1) = "End_Of_Instructions";
		}
	}
	else if (*place == "mul")
	{
		++place;
		if (*place == "reg")
		{
			operationParams();
			regs[index[1]] = regs[index[1]] * long_mem[0]; // mul
		}
		else if (*place == "regd")
		{
			operationParamsDouble();
			regsd[index[1]] = regsd[index[1]] * double_mem[0]; // mul double
		}
		else if (*place == "arr")
		{
			arrayParams();
			long_mem[index[0]] = long_mem[index[0]] * long_mem[0];
		}
		else if (*place == "arrd")
		{
			arrayParamsDouble();
			double_mem[index[0]] = double_mem[index[0]] * double_mem[0];
		}
		else
		{
			std::cout << "Invalid instruction: '" << *place << "' --- expected 'reg', 'regd', 'arr', or 'arrd'" << std::endl;
			*(place + 1) = "End_Of_Instructions";
		}
	}
	else if (*place == "div")
	{
		++place;
		if (*place == "reg")
		{
			operationParams();
			regs[index[1]] = regs[index[1]] / long_mem[0]; // div
		}
		else if (*place == "regd")
		{
			operationParamsDouble();
			regsd[index[1]] = regsd[index[1]] / double_mem[0]; // div double
		}
		else if (*place == "arr")
		{
			arrayParams();
			long_mem[index[0]] = long_mem[index[0]] / long_mem[0];
		}
		else if (*place == "arrd")
		{
			arrayParamsDouble();
			double_mem[index[0]] = double_mem[index[0]] / double_mem[0];
		}
		else
		{
			std::cout << "Invalid instruction: '" << *place << "' --- expected 'reg', 'regd', 'arr', or 'arrd'" << std::endl;
			*(place + 1) = "End_Of_Instructions";
		}
	}
	else if (*place == "mod")
	{
		++place;
		if (*place == "reg")
		{
			operationParams();
			regs[index[1]] = regs[index[1]] % long_mem[0]; // modulus
		}
		else if (*place == "arr")
		{
			arrayParams();
			long_mem[index[0]] = long_mem[index[0]] % long_mem[0]; // modulus
		}
		else if (*place == "regd" || *place == "arrd")
		{
			std::cout << "Error: mod instruction invalid with double values." << std::endl;
			*(place + 1) = "End_Of_Instructions";
		}
		else
		{
			std::cout << "Invalid instruction: '" << *place << "' --- expected 'reg' or 'arr'" << std::endl;
			*(place + 1) = "End_Of_Instructions";
		}
	}
	else if (*place == "func") // function declaration and definition
	{
		++place; // go to function name --- func *[name]* ...
		funcPlace[index[62]] = (place + 1); // store the place of the function
		string_mem[index[62]] = *place; // store the name of the function
		++index[62]; // increment the function index (to prevent the next function from overriding this one)
		while (*place != "End_Of_Instructions") // skip to the end of the function (function instructions will be implemented when the function is called)
		{
			++place;
			if (*place == "func") // Function declaration within a function: Prints error message and kills the program
			{
				std::cout << "Error: function declaration within a function." << std::endl; 
				*(place + 1) = "End_Of_Instructions";
				break;
			}
			if (*place == "endfunc")
				break;
		}
	}
	else if (*place == "call") // call function
	{
		++place; // go to function index --- call *[function]*
		long_mem[2] = 0; // stack overflow bool
		// increment the storedPlace index and store the place of the call ("push")
		++index[63];
		if (index[63] < 4097)
		{
			storedPlace[index[63]] = place;
		}
		else // stack overflow
		{
			std::cout << "Error: stack overflow." << std::endl; // display error message and end program
			*(place + 1) = "End_Of_Instructions";
			long_mem[2] = 1; // stack overflow bool
		}

		long_mem[1] = 0; // Treated as "function found" bool
		if (long_mem[2] == 0) // if no stack overflow
		{
			for (index[10] = 0; index[10] < 64; ++index[10]) // find the function
			{
				if (string_mem[index[10]] == *place)
				{
					long_mem[1] = 1; // set "function found" to true
					break;
				}
			}
			if (long_mem[1] == 0) // If the name does not exist
			{
				std::cout << "Could not find function: " << *place << std::endl; // NOTE: Print an error message and kill program
				*(place + 1) = "End_Of_Instructions";
			}
			else
			{
				place = funcPlace[index[10]]; // go to function
				while (*place != "endfunc") // carry out function
				{
					singleInstruction();
				}
				place = storedPlace[index[63]]; //go back to the place of the call 
			}
		}
		--index[63]; // decrement the storedPlace index ("pop")
	}
	else if (*place == "print") // print
	{
		++place; 
		while (*place != "endprint") // print every string between "print ... end"
		{
			if (*place == "/reg") // print the value of a register
			{
				++place; // --- print ... reg *[index]* ... end
				std::cout << regs[std::stoi(*place)]; // print the value stored in the register
			}
			else if (*place == "/regd") // print the value of a double register
			{
				++place; // --- print ... regd *[index]* ... end
				std::cout << regsd[std::stoi(*place)]; // print the value stored in the double register
			}
			else if (*place == "/arr")
			{
				arrayItem();
				std::cout << long_mem[0];
			}
			else if (*place == "/arrd")
			{
				arrayItemDouble();
				std::cout << double_mem[0];
			}
			else if (*place == "_") // print a space
				std::cout << " ";
			else if (*place == "newline") // print new line
				std::cout << std::endl;
			else
			{
				std::cout << *place; // print a string
			}
			++place;
		}
	}
	else if (*place == "if") // "if" statement
	{
		
		if (condition()) // if the condition is met
		{
			while (*place != "endif") // carry out all the instructions between "if ... endif"
			{
				singleInstruction();
			}
		}
		else
		{
			index[11] = 1;
			--place;
			while (index[11] > 0) // ignore all the instructions between "if ... endif"
			{
				++place;
				if (*place == "print") // ignore any "if" or "endif" in print statements
				{
					while (*place != "endprint") ++place;
				}
				else if (*place == "if") // in case there is an imbedded if statement
				{
					++index[11];
				}
				else if (*place == "endif")
				{
					--index[11];
				}
			}
		}
		
	}
	else if (*place == "while") // while loop
	{
		long_mem[2] = 0; // stack overflow bool
		// increment the storedPlace (stack) index and store the start of the while loop ("push")
		++index[63];
		if (index[63] < 4097)
		{
			storedPlace[index[63]] = (place - 1);
		}
		else // stack overflow
		{
			std::cout << "Error: stack overflow." << std::endl; // display error message and end program
			*(place + 1) = "End_Of_Instructions";
			long_mem[2] = 1; // stack overflow bool
		}
		if (long_mem[2] == 0) // if no stack overflow
		{
			if (condition())
			{

				while (*place != "endwhile") // carry out the while statement
				{
					singleInstruction();
				}
				place = storedPlace[index[63]]; // return to the start of the while loop
			}
			else
			{
				index[11] = 1;
				--place;
				while (index[11] > 0) // ignore all the instructions between "if ... endwhile"
				{
					++place;
					if (*place == "print") // ignore any "while" or "endwhile" in print statements
					{
						while (*place != "endprint") ++place;
					}
					if (*place == "while") // in case there is an imbedded while loop
					{
						++index[11];
					}
					if (*place == "endwhile")
					{
						--index[11];
					}
				}
			}
		}
		--index[63]; // decrement the storedPlace (stack) index 
	}
	else if (*place == "new")
	{
		++place; // new *arr* [name] [size]
		if (*place == "arr")
		{
			++place; //new arr *[name]* [size]
			arr_name[index[61]] = *place; // store name of array
			++place; // new arr [name] *[size]*
			if (*place == "reg")
			{
				++place;
				arr_size[index[61]] = regs[std::stoi(*place)]; // store size of array
			}
			else
			{
				arr_size[index[61]] = std::stoi(*place);  // store size of array
			}
			++index[61]; //increment array index

			// Allocate memory for the array by storing the starting position in memory of the next array
			arr_start[index[61]] = arr_start[index[61] - 1] + arr_size[index[61] - 1]; 
		}
		else if (*place == "arrd")
		{
			++place; //new arr *[name]* [size]
			arrd_name[index[60]] = *place; // store name of array
			++place; // new arr [name] *[size]*
			if (*place == "reg")
			{
				++place;
				arrd_size[index[60]] = regs[std::stoi(*place)]; // store size of array
			}
			else if (*place == "regd")
			{
				++place;
				arrd_size[index[60]] = regsd[std::stoi(*place)];
			}
			else
			{
				arrd_size[index[60]] = std::stoi(*place);  // store size of array
			}
			++index[60]; //increment array index

			// Allocate memory for the array by storing the starting position in memory of the next array
			arrd_start[index[60]] = arrd_start[index[60] - 1] + arrd_size[index[60] - 1];
		}
		else
		{
			std::cout << "Invalid instruction: '" << *place << "' --- expected 'arr' or 'arrd'" << std::endl;
			*(place + 1) = "End_Of_Instructions";
		}
	}
	else // In case of an invalid instruction
	{
		std::cout << "Invalid instruction: " << *place << std::endl; // print an error message
		*(place + 1) = "End_Of_Instructions"; // end the instructions
	}
	if (*place != "End_Of_Instructions") // if End Of Instructions is reached, don't step forward in instructions
	{
		++place;
	}
	if (*place == "end") // if ending instruction with "end"
	{
		++place; // skip "end"
	}
}



// Run the instructions
int Instructions::run(bool print_return){
	place = mem; // start at the beginning of the instructions
	index[63] = 0; // the storedPlace (stack) index
	index[62] = 0; // function index
	index[61] = 0; // array index
	index[60] = 0; // double array index
	arr_start[0] = 1028; // start arrays at point 1028 in memory (leaving room for the internal use of items 0-1027)
	arrd_start[0] = 64; // start double arrays at point 64 in memory
	long_mem[1027] = 0; // compare flag
	long_mem[1026] = 0; // return type flag
	long_mem[1025] = 0; // compare doubles flag
	long_mem[1024] = 0; // compare doubles flag - first term
	long_mem[1023] = 0; // compare doubles flag - second term
	// string_mem[1027] =  conditional statement operator
	while (*place != "End_Of_Instructions")
	{
		singleInstruction();
	}
	if (long_mem[1026] == 1) // return double
	{ 
		if (print_return) {
			std::cout << "Return value: " << regsd[0] << std::endl; // Return statement
		}
	}
	else // return long
	{
		if (print_return) {
			std::cout << "Return value: " << regs[0] << std::endl; // Return statement
		}
	}
	return regs[0];
}


