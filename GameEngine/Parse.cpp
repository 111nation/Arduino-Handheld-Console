#include "Parse.hpp"
#include "Display.hpp"
#include "Program.hpp"
#include "Types.hpp"
#include <execution>

uint8_t NestingLevel = 0; 
uint8_t RecursionDepth = 0;

// ============ HELPERS ==============
bool isWhiteSpace(const char& value) {
	return value == '\t' || value == '\n' || value == ' ' 
		|| value == '\r' || value == '\v' || value =='\f';
}

bool consume(STRING value, STRING& line, bool whitespace) {
	// Move pointer past IMMEDIATE matched word
	// Used for searching keyword like 'if' or 'else'
	// Do not move pointer if match not found
	// Only match immediate characters
	// Word must be padded by whitespace if whitespace == true
	STRING currentLine = trimLeft(line);
	STRING currentVal = value;
	
	// Immediate characters must match otherwise 
	// stop searching
	while (*currentLine != '\0' && *currentVal != '\0') {
		if (*currentLine != *currentVal) return false;
		++currentVal;
		++currentLine;
	}

	if (*currentVal != '\0') return false;

	// Ensure that matched word is padded by whitespace
	// Prevents 'if' being matched in 'ifelse'
	// 'if' is only found if its 'if else'
	if (!whitespace || *currentLine == '\0' || isWhiteSpace(*currentLine)) {
		line = trimLeft(currentLine);
		return true;
	}

	return false;
}

bool find(STRING value, STRING& line, STRING start) {
	// Similar to consume
	// We check whole line for first occurence
	// Move pointer pointing to characters before
	// matched word
	if (line < start) return false;

	STRING currentLine = trimLeft(line);
	STRING currentVal = value;

	while (*currentLine != '\0' && *currentVal != '\0') {
		if (*currentLine != *currentVal) currentVal = value;
		if (*currentVal == *currentLine) ++currentVal;
		++currentLine;
	}

	if (*currentVal != '\0') return false;

	// Ensure that found word is a stand alone token
	// Padded by leading and trailing whitespace
	bool validTrailing = *currentLine == '\0' || isWhiteSpace(*currentLine);

	// Move to front of token
	currentLine = currentLine - (currentVal - value); 
	bool validLeading = currentLine == start || isWhiteSpace(*(currentLine-1));

	if (validLeading && validTrailing) {
		line = currentLine;
		return true;
	}

	return false;
}

INTEGER stringToInt(STRING line) {
	INTEGER result = 0;

	while (*line != '\0') {
		result *= 10;
		result += *line - '0';
		++line;
	}

	return result;
}

// Parse string to a number
// Starting from line (inclusive)
// Ending at end (exclusive)
INTEGER stringToInt(STRING line, STRING end) {
	INTEGER result = 0;

	while (line < end) {
		result *= 10;
		result += *line - '0';
		++line;
	}

	return result;
}


STRING trimLeft(STRING line) {
	while (isWhiteSpace(*line) && *line != '\0') ++line;
	return line;
}

STRING findEnd(STRING line) {
	while (*(line+1) != '\0') ++line;
	return line;
}

// ============ PARSING ==============
INTEGER equality(STRING& line, STRING& end) {
	INTEGER result = comparison(line, end);
	line = trimLeft(line);

	while (line < end && ((*line == EQUAL && *(line + 1) == EQUAL) || (*line == BANG && *(line + 1) == EQUAL))) {
		STRING operat = line;
		line += 2; // Move past both characters making up '==' and '!='

		if (*operat == EQUAL) {
			// '==' Found
			result = result == comparison(line, end) ? 1 : 0;
		} else {
			// '!=' Found
			result = result != comparison(line, end) ? 1 : 0;
		} 

		line = trimLeft(line);
	}

	return result;
}

INTEGER comparison(STRING& line, STRING& end) {
	INTEGER result = term(line, end);
	line = trimLeft(line);

	while (line < end && (*line == LESS || *line == GREATER)) {
		STRING operat = line;
		bool equalOperator = false;
		++line;

		if (*line == EQUAL) {
			equalOperator = true;
			++line;
		}


		if (*operat == LESS) {
			if (equalOperator) {
				result = result <= term(line, end) ? 1 : 0;
			} else {
				result = result < term(line, end) ? 1 : 0;
			}
		} else {
			if (equalOperator) {
				result = result >= term(line, end) ? 1 : 0;
			} else {
				result = result > term(line, end) ? 1 : 0;
			}
		}
	}

	return result;
}

INTEGER term(STRING& line, STRING& end) {
	INTEGER result = factor(line, end);
	line = trimLeft(line);

	while (line < end && (*line == ADDITION || *line == SUBTRACTION)) {
		STRING operat = line;
		++line;

		if (*operat == ADDITION) {
			result += factor(line, end);
		} else {
			result -= factor(line, end);
		}
	}

	return result;
}

INTEGER factor(STRING& line, STRING& end) {
	INTEGER result = unary(line, end);
	line = trimLeft(line);

	while (line < end && (*line == MULTIPLICATION || *line == DIVISION)) {
		STRING operat = line;
		++line;

		if (*operat == MULTIPLICATION) {
			result *= unary(line, end);
		} else {
			result /= unary(line, end);
		}

		line = trimLeft(line);
	}

	return result;
}

INTEGER unary(STRING& line, STRING& end) {
	// Recursively check for unary operators '-!5' or '!!6' or '+-!M4'
	// Returns a primary expression as soon as no
	// unary operator has been found
	line = trimLeft(line);
	if (line >= end) return 0;

	// Unary 'NOT'
	if (consume(NOT, line)) {
		return (unary(line, end) == 0 ? 1 : 0); 
	}

	// Unary '-'
	if (*line == SUBTRACTION) {
		++line;
		return -1 * unary(line, end);
	}

	// Unary '+'
	if (*line == ADDITION) {
		++line;
		return +1 * unary(line, end);
	}

	// No operator found, drop down to primary
	return primary(line, end);
}

INTEGER primary(STRING& line, STRING& end) {
	// Check for literal values, variables, or numbers
	line = trimLeft(line);
	if (line >= end) return 0;

	// Handle paranthesis
	if (*line == LEFT_BRACKET) {
		// Restart heirachy because parathesized experessions
		// Are treated as sperate new expressions
		++line;

		INTEGER result = equality(line, end);
		line = trimLeft(line);

		// Silently forgive missing closing bracket
		// (3+4 will be evaluated just like (3+4)
		if (*line == RIGHT_BRACKET) ++line;
		return result;
	} 

	if (*line >= '0' && *line <= '9') {
		// Parse literal number and return to upper operators
		STRING start = line;
		while (line < end && (*line >= '0' && * line <= '9')) ++line; 
		return stringToInt(start, line); 
	} else if (*line == MEM_PREFIX) {
		// Heap Address referenced
		// Return value of the memory address
		STRING start = ++line;
		while (line < end && (*line >= '0' && *line <= '9')) ++line;

		// stringToInt returns INTEGER not ADDR, ensure non truncation
		INTEGER rawAddress = stringToInt(start, line);
		return read(rawAddress);
	} else if (consume(JOYSTICK_X, line)) {
		return control.joystick.x;
	} else if (consume(JOYSTICK_Y, line)) {
		return control.joystick.y;
	} else if (consume(JOYSTICK_BUTTON, line)) {
		return control.joystick.clicked ? 1 : 0;
	} else if (consume(BUTTON_A, line)) {
		return control.buttonA ? 1 : 0;
	}

	return 0; // Saftey fallback
}

INTEGER parseExpression(STRING& line, STRING& end) {
	// Parse A Maths Expression And Return its value
	// Heirarchial order algorithm defined by: 
	// http://craftinginterpreters.com/parsing-expressions.html
	// Parse till the end (excluded)
	line = trimLeft(line);
	if (*line == '\0') return 0;
	return equality(line, end);	
}

INTEGER parseExpression(STRING& line) {
	// Parse A Maths Expression And Return its value
	// Heirarchial order algorithm defined by: 
	// http://craftinginterpreters.com/parsing-expressions.html
	// Parse till the end of the line
	line = trimLeft(line);
	if (*line == '\0') return 0;
	STRING end = findEnd(line)+1; // Indicate EOL
	return equality(line, end);	
}

void parseIfBlock(bool execute) {
	// Handle Parsing of whole IF block
	// Assumes the IF keyword was consumed Prior
	// Grabs expression and determines to run specific IF block
	// IF statement
	
	STRING start = PC;

	if (!find(THEN, PC, start)) {
		// Syntax Error: 'THEN' Missing
		return;
	}

	INTEGER expression = execute ? parseExpression(start, PC) : 0;

	parseCodeBlock(expression && execute);

	// parseCodeBlock terminates while
	// having cursor on the END or ELSE keyword 
	// that terminated it
	
	if (!consume(ELSE, PC)) return;

	// Else code block detected
	
	if (consume(IF, PC)) {
		parseIfBlock(!expression && execute); // Recursively calls to the next else if
	} else {
		parseCodeBlock(!expression && execute);
	}
}

void parseWhileBlock(bool execute) {
	// Handle Parsing of whole WHILE block
	// Assumes the WHILE keyword was consumed Prior
	// Grabs expression and determines to run specific WHILE block
	// WHILE statement
	STRING start = PC;
	CURSOR curStart = checkpoint();

	if (!find(DO, PC, start)) {
		// Syntax Error: 'DO' Missing
		return;
	}

	INTEGER expression = execute ? parseExpression(start, PC) : 0;

	if (execute && expression) {
		while (isRunning && expression) {
			parseCodeBlock();

			// Move cursor back to While loop
			jump(curStart);

			find(WHILE, PC, start);
			consume(WHILE, PC);

			start = PC;

			find(DO, PC, start); // Assume 'DO' Exists from prior check

			expression = parseExpression(start, PC);
		}

		parseCodeBlock(false);
	} else {
		// Skip while loop
		parseCodeBlock(false);
	}

}

void parseCodeBlock(bool execute) {
	// Parse code block layer until you reach 'END'
	++NestingLevel;
	while (next()) {
		if (find(END, PC, PC)) {
			// END 
			--NestingLevel;
			return;
		} else if (find(ELSE, PC, PC)) {
			// ELSE BLOCK 
			--NestingLevel;
			return;
		}

		// Parse line within code block
		// Recursively calls if more code blocks exist
		parse(execute);	
	}
	--NestingLevel;
}

void parseFuncDef(bool execute) {
	// Add Function to Registry by
	// Storing the current line cursor 
	// So we can jump back to function

	if (!execute) {
		parseCodeBlock(false);
		return;
	}

	if (!consume(FUNC, PC, false)) {
		// Syntax Error: Expected Function Name
		return;
	}

	STRING start = PC;

	while (*PC >= '0' && *PC <= '9') ++PC;
	INTEGER regAddress = stringToInt(start, PC);


	if (!consume(BEGIN, PC)) {
		// Syntax Error: Expected 'BEGIN'
		return;
	}



	writeRegistry(regAddress, checkpoint());
	parseCodeBlock(false); // Skip function body for defenitions
}

void parseFuncArgs(int expectedArgs, bool execute) {
	// Go through all the argument list and overwrite
	// argument list structure with the arguments
	// Expects expressions delimited by ARG_DELIM
	if (!execute) return;

	int arg = -1; // Argument count
	STRING start = PC;
	while (*PC != '\0') {
		++PC;

		if (!(*PC == ARG_DELIM || *PC == '\0')) continue;

		// If we hit the delimeter
		// Parse the argument and move to the next argument

		++arg;
		if (arg >= MAX_ARGUMENTS) {
			// Syntax Error: Max arguments reached
			return;
		} 

		if (arg >= expectedArgs) {
			// Syntax Error: More arguments supplied than expected
			// Ignore other arguments and skip
			return;
		}

		ArgumentList[arg] = parseExpression(start, PC);
	
		if (*PC == '\0') return; // No more arguments

		++PC;
		start = PC;
	}

	return;
}

void parseFuncCall(bool execute) {
	// Parse function call and execute function body
	if (!execute) return;

	if (consume(FUNC, PC, false)) {
		// Protect from Stack OverFlow Errors
		// Due to Infinite Recursion
		++RecursionDepth;
		if (RecursionDepth > MAX_RECURSION_DEPTH) {
			// Runtime Error: Maximum Recursion Met
			--RecursionDepth;
			return; 
		}

		// Run Custom Function
		STRING start = PC;

		while (*PC >= '0' && *PC <= '9') ++PC;
		INTEGER regAddress = stringToInt(start, PC);

		CURSOR curLine = checkpoint();
		
		// Jump to function
		jump(readRegistry(regAddress));
		
		parseCodeBlock(execute);

		// Jump back to current line
		jump(curLine);

		--RecursionDepth;
	} else if (consume(DISPLAY, PC)) {
		// Update Screen
		display();
	} else if (consume(INPUT, PC)) {
		// Update Input
		input();
	} else {
		// Syntax Error: Expected Function name/ Function does not exist
		return;
	} 

}


void parse(bool execute) {
	if (!isRunning) return;
	if (PC == NULL) return;

	// Parse a single line
	
	// Skip leading whitespace
	PC = trimLeft(PC);

	// Skip blank lines and comments
	if (*PC == '\0') return;
	if (*PC == INLINE_COMMENT) return;

	STRING start = PC;

	// Determine Top-Level Command (Statement Identification)
	while (*PC != '\0') { 
		if (*PC == INLINE_COMMENT) return;

		bool assignment = *PC == EQUAL && *(PC-1) != EQUAL;
		if (execute && assignment) {
			++PC;
			// ASSIGNMENT MODE
			// Expect {ADDRESS} = {EXPRESSION}
			
			// You can only assign to memory addresses
			// Skip line if not referecing address
			if (*start != MEM_PREFIX) return;

			// Grab address number
			STRING end = ++start;
			while (*end >= '0' && *end <= '9') ++end;
			
			INTEGER address = stringToInt(start, end);
			write(address, parseExpression(PC));

			return;
		} else if (consume(IF, PC)) {
			parseIfBlock(execute);
			return;
		} else if (consume(WHILE, PC)) {
			parseWhileBlock(execute);
			return;
		} else if (consume(DEFINE, PC)) {
			parseFuncDef(execute);
			return;
		} else if (consume(CALL, PC)) {
			parseFuncCall(execute);
			return;
		}

		++PC;
	}

	if (*PC == '\0') return; // Drop lines without a useful command
}
