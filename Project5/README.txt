CPU Emulator Instructions
Micah Smith

Personal project developed as a technical exercise to emulate a CPU with my own custom assembly-inspired programming language.


The Instructions class takes a set of instructions, stores it in an array ("memory"), and uses it to carry out operations with
an array of "registers" and other arrays of "memory".

Demonstrated with various program instructions including the Euler method simulation of a damped projectile 
(see files instruct1.txt, instruct2.txt, instruct3.txt and euler.txt for programs)


-----REGISTERS AND MEMORY:

64 registers storing long integers are available for client use ("register 0" through "register 63"), stored in the member array *regs, which 
has a length of 64.

64 registers storing double precision floats are available client use, stored in the member array *regsd, which has a length of 64.

Instructions taken from client input are stored in an array of strings, of length 4096. 

Other arrays and member data exist for internal use.



-----TO USE:

- Write a text file or istream with valid instructions (see below).
- Create an instance of the class Instructions.
- Call the member function readFile(istream& is), with the file or istream as a parameter.
- Call the member function run().

Note: run() may be called multiple times. Data is not reset between calls.

See main.cpp for examples using the files instruct1.txt, instruct2.txt, instruct3.txt, and euler.txt.



-----AVAILABLE INSTRUCTIONS:

return - return a value*
mov - set a register (or array item) equal to a value
add - add a value to a register
sub - subtract a value from a register
mul - multiply a register by a value
div - divide a register by a value
mod - modulus: set a register equal to the remainder of its division by another number
print - print a register or string
func - declare a function
call - call a function
if - execute an if statement
while - execute a while loop
new - allocate an array

--PRE RUN-TIME INSTRUCTIONS:

#include - include another file



*(Note: "Return" in the context of this class is equivalent to setting the return value of the member function run(), ending the instructions,
and printing the return value. The default return register is register 0.)



-----SYNTAX:


---In general:

One instruction consists in a series of strings separated by spaces.

- The first string in the series indicates the operation type and is referred to as the "instruction key".

- The instructions "print", "func", "while", and "if" have required ending strings (e.g. "endprint" for print, "endfunc" for func, etc. - see 
detailed syntax below) 

- For all other instructions it is recommended for visual clarity, but in no way required, to end each complete instruction with "end" and/or 
a new line.

- To write comments: write space, semicolon, space, (" ; ") and the rest of the line will be ignored. This will not work without the spaces.

- The instructions are case sensitive.




---Error Checking: 


Error checking is limited, so incorrect syntax could result in program errors.


-- Errors which will print an error message and end the program:

- If an instruction key is not recognized.

- If the first parameter in a basic arithmetic operation is not a register or array item.

- If a function is declared within another function declaration.

- If a double is used on the modulus instruction.

- If an array is referenced which does not exist.

- If an array index is out of range.

- If a function is called which does not exist.

- If the stack surpasses its maximum depth of 4096 through function calls and/or while loops. (Note: in practice, the program may crash before this depth
is reached).



-- Known errors which may cause the program to crash: 

- If, where a number is expected, the compiler cannot convert the string to a number. For example, "mov reg A 17 end", or "add reg 1 Number end" - the 
string "A" cannot be converted to an unsigned integer, and the string "Number" cannot be converted to a long  integer, so in each case the program would 
crash (see detailed syntax of each instruction below).

- If a correct ending string is missing from an instruction which requires one (see individual instruction syntax below).

- Infinite recursion (even though the program is terminated when the stack depth is exceeded, the program may crash before this happens).





---Data types:

- All arithmetic operations listed can be used with either long integers or doubles, except for "mod", which accepts only long integers.
The instruction key is the same regardless of number type. The type is determined by the operand (first term in the operation). The second term
must match the operand in type.

- Conditional (if/while) statements can take long integers and/or doubles. By default, they convert all values to longs for the comparison. But if
either operand is a double register or double array ("regd" or "arrd"), then both operands are converted to doubles. See more information in the
individual instruction syntax below. 

- In the syntax in general, "reg" is used for long registers and "regd" is used for double registers. Likewise "arr" is used for an array of longs,
and "arrd" is used for an array of doubles. 




--Register and memory access: 

- Unless otherwise noted, in the following individual instructions, "reg [i]" may be replaced with:
"regd [i]" - acces double register (i)
"arr [name] [i]" - access array [name] element (i)
"arrd [name] [i]" - access double array [name] element (i)

- Likewise, [long] should be replaced with [double] if it is used in an instruction with a double register or array.

- A register may be used for an array index (e.g. "arr [name] reg [i]" - access an item of array [name] using register (i) as the index). But
another array item may not be used as an array index. 




---Syntax of individual instructions:

--return:

***Form 1:

"return reg [i]"

- Sets register (0) to register (i) and returns register (0)

***Form 2:

"return [long]"

- Sets register (0) equal to the long integer [long] and returns register (0)

NOTE: In this case, [long] may not be replaced with [double]. Form 1 must be used to return a double.

***Form 3:

"return" (at end of file)

- Returns register (0)

- This third form is only valid at the very end of the file. 

NOTE: An error may result if Form 3 is used and this file is included in another file using #include (see detailed syntax for "#include" below).


NOTE:

-- If the end of the file is reached before any return statement, the program will automatically return register 0.

**Examples:

return reg 3 --- result: returns the value stored in register 3 (i.e. sets register 0 to register 3 and returns register 0)
return 89 --- result: returns 89 (i.e. sets register 0 to 89 and returns register 0)
return --- returns the value stored in register 0
return arr myArry 3 --- returns the value stored in element 3 of the array myArray



--mov:

***Form 1: 

"mov reg [i] reg [j] end"

- Sets register(i) equal to register(j)


***Form 2:

"mov reg [i] [long] end"

- Sets register(i) equal to the value [long]


***Form 3: 

"mov reg [i] input end"

- Waits for input, then sets register (i) equal to the input value.


**Examples:

mov reg 1 reg 2 end --- (result: register 1 == register 2)
mov reg 2 17 end --- (result: register 2 == 17)
mov reg 2 input end --- (result: register 2 == input value)
mov reg 2 arr myArray 3 end --- (result: register 3 == the value stored in element 3 of myArray)
mov arr myArray 15 75 end --- (result: element 15 of myArray == 75)



--add:

***Form 1: 

"add reg [i] reg [j] end"

- Adds register(j) to register(i)

***Form 2:

"add reg [i] [long] end"

- Adds [long] to register(i)

***Form 3: 

"add reg [i] input end"

- Waits for input, then adds the input value to register (i).

**Examples:

add reg 1 reg 2 --- (result: register 1 == (register 1) + (register 2))
add reg 2 17 --- (result: register 2 == (register 2) + 17)
add reg 2 input --- (result: register 2 == (register 2) + input value)



--sub:

Identical syntax to "add". Replace "add" with "sub".

- Subtraction operator

**Examples:

sub reg 1 reg 2 --- (result: register 1 == (register 1) - (register 2))
sub reg 2 17 --- (result: register 2 == (register 2) - 17)



--mul:

Identical syntax to "add". Replace "add" with "mul".

- Multiplication operator

**Examples:

mul reg 1 reg 2 --- (result: register 1 == (register 1) * (register 2))
mul reg 2 17 --- (result: register 2 == (register 2) * 17)



--div:

Identical syntax to "add". Replace "add" with "div".

- Division operator

**Examples:

div reg 1 reg 2 --- (result: register 1 == (register 1) / (register 2))
div reg 2 17 --- (result: register 2 == (register 2) / 17)



--mod: 

Identical syntax to "add". Replace "add" with "mod".

- Sets the value of the first register equal to the remainder of its division by the second register or value.

NOTE: This instruction may only be used with long integers, not with doubles.

**Examples:

mod reg 1 reg 2 --- (result: register 1 == (register 1) % (register 2))
mod reg 2 17 --- (result: register 2 == (register 2) % 17)
mod arr myArray 13 2 --- (result: myArray[13] == myArray[13] % 2)



--print:

"print ... end"

- prints the strings between "print" and "endprint", ignoring spaces

- MUST end with "endprint"

SPECIAL CASES:

- "/reg [i]", "/regd [i]" prints the value of register (i)

"/arr [name] [i]", "/arrd [name] [i]" - prints the value of array [name] item (i)

- The string "_" prints a space.

- The string "newline" prints a new line.

NOTES:

-- Any instruction key words between "print" and "endprint", such as "mov", "add" or even "print", are printed like any other 
string.

**Example:

print Register _ 3 _ equals _ /reg 3 . newline
This _ will _ print _ to _ the _screen. endprint

--- (result: (assuming arbitrarily that the value of register 3 is currently 0) prints:
"Register 3 equals 0.
Instructions _ such _ as _ print _ and _ mov _ are _ just _ strings _ here.")



--func: 

"func [name] [instructions] endfunc"

- declares a function called [name] which carries out [instructions] whenever it is called.

NOTES:

-- Up to 64 functions may be declared in one program. 

-- A function cannot be declared within another function declaration

**Example:

---- (This function, foo, adds 13 to register 1 and subtracts 4 from register 2 whenever it is called:)

func foo 
add reg 1 13
sub reg 2 4
endfunc 



--call:

"call [function]"

- Calls a function, then goes back to the place of the call.

NOTES:

-- A function may be called within another function.

**Example:

---- (This code declares two functions, foo and bar, then calls bar. The function bar contains a call of foo.)

func foo 
add reg 1 13
endfunc

func bar
call foo
sub reg 2 4
endfunc

call bar



---if:
 
"if [condition statement] [instructions] endif"

- If the condition statement is true, the instructions are implemented. Otherwise the instructions are skipped.

- The if instruction MUST end with "endif"

CONDITIONAL STATEMENT SYNTAX:

"[value 1] [comparison operator] [value 2]"

- value 1 and value 2 may each be either a value stored in a register (syntax "reg [i]") or a long integer.

COMPARISON OPERATORS SUPPORTED:

">" -- greater than

"<" -- less than

"==" -- equal to

"!=" -- not equal to

"<=" -- equal to or less than

"=>" -- equal to or greater than

NOTES:

- The condition statement must be in the form above. Logical and/or statements are not supported.

- Else/elseif instructions are not currently supported.

- Nested "if" statements are supported

- By default, the values are treated as long integers. However, if either value is "regd..." or "arrd...", then both values are converted to
doubles. So, for example, if the instruction reads "if reg 3 < 5.6", 5.6 will be converted to the long integer 5. But if the instruction is "if 
regd 3 < 5.6", double register (3) will be compared with the double 5.6.

**Examples:

"if reg 2 > 100
print Register _ 2 _ is _ big. end
endif" --- (result: If the value of register 2 is greater than 100, the statement "Register 2 is big." is printed.)

"if 3.14 != regd 2"
mov regd 2 3.14 end
endif" --- (result: If 3.14 is not equal to double register 2, the instruction mov is executed to set double register 2 to 3.14.)



while:

"while [condition statement] [instructions] endwhile"

- If the condition statement is true, the instructions are implemented, then the place is returned to the beginning of the while statement. 
Otherwise the instructions are skipped.

- The while instruction MUST end with "endwhile"

- The condition statement syntax is identital to that of the "if" instruction.

NOTE: Nested "while" loops are supported

**Example:

"while reg 2 < 10
add reg 2 1 end
print Incrementing _ reg 2 end
endwhile"
--- (result: As long as the value of register 2 is less than 10, the instructions are implemented which increment Register 2 and print 
"Incrementing [register 2]".)


new:

"new arr [name] [size]"

OR

"new arrd [name] [size]" - array of doubles

- Allocates an array of [name] and [size]

NOTE: See syntax for the instruction "return" to see how to set or acces an array item.

**Example:

"new arr myArray 100" --- (result: myArray is an array of size 10)
"new arrd myArray reg 2" --- (result: myArray is an array of doubles with size equal to the value stored in register (2))
"new arrd myArray regd 2" --- (result: myArray is an array of doubles with size equal to the value stored in double register (2) converted to an unsigned
integer)


#include:

"#include [file name]"

- Implemented when the class member function readFile() is called (before run()). Writes the included file into the instructions at the point of
the #include. Equivalent to copying and pasting the text of the included file into this point of the main file.

NOTE: A fatal error will result if the last string in the included file is "return" (i.e. Form 3 of the "return" syntax above), unless the file is included 
at the very end of the main file. If "return" is followed by any string, that string will be treated as part of the return value (i.e. it will interpret
"return" as being either Form 1 or Form 2  - see "return" syntax above).

