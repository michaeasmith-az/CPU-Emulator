
// Condition module: returns true or false based on whether the condition is met 
// (NOTE: as an example, comments show implementation with the instruction "if")
bool Instructions::condition(){
	++place;
	if (*place == "reg")
	{
		++place; // --- if reg *[index]*... endif
		index[0] = std::stoi(*place); // store index of first register
		long_mem[0] = regs[index[0]]; // set the first operand equal to the value of the first register
	}
	else // if the first operand is a number
	{
		long_mem[0] = std::stol(*place);
	}
	++place; // to conditional operator --- if reg [index] *[operator]* reg [index] ... endif
	string_mem[1027] = *place;
	++place; // to second operand
	if (*place == "reg")
	{
		++place;
		index[1] = std::stoi(*place); // store index of second register
		long_mem[1] = regs[index[1]]; // set the second operand equal to the value of the second register
	}
	else // if the first operand is a number
	{
		long_mem[1] = std::stol(*place); // set the operand equal to the number
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

// Compare module: compares long_mem[0] to long_mem[1]
// Indicates the results of the comparison by setting long_mem[1027] equal to 1, 2, or 3
void Instructions::compare()
{
	if (long_mem[0] > long_mem[1]) //  3 if greater than
		long_mem[1027] = 3;
	else if (long_mem[0] == long_mem[1]) //  2 if equal
		long_mem[1027] = 2;
	else if (long_mem[0] < long_mem[1]) // 1 if less than
		long_mem[1027] = 1;
}