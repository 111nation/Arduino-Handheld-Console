#include "GameEngine.hpp"

// UNIVERSAL IMPLEMENTATION

INTEGER* Heap = new INTEGER[HEAP_SIZE];
uint8_t nestingLevel = 0; 

bool consume(STRING value, STRING& line) {
	// Move pointer past IMMEDIATE matched word
	// Used for searching keyword like 'if' or 'else'
	// Do not move pointer if match not found
	// Only match immediate characters
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
	if (*(currentLine) == '\0' || isWhiteSpace(*(currentLine))) {
		line = trimLeft(currentLine);
		return true;
	}

	return false;
}

bool find(STRING value, STRING& line, STRING start) {
	// Similar to consume
	// We check whole line for first occurence
	// Return pointer pointing to characters before
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

bool validAddress(INTEGER address) {
	// We accept a INTEGER instead of ADDR on purpose
	// Prevents silent downcasting/truncation overflow bugs
	// Ensures that numbers that overflow ADDR are not accepted as  
	// valid addresses due to truncation
	return address >= 0 && address < HEAP_SIZE;
}

void write(ADDR address, INTEGER value) {
	// Write value at specified heap address
	if (!validAddress(address)) return;
	Heap[address] = value;
}

INTEGER read(ADDR address) {
	// Return value at specified heap address
	return validAddress(address) ? Heap[address] : 0;
}

bool isWhiteSpace(const char& value) {
	return value == '\t' || value == '\n' || value == ' ' 
		|| value == '\r' || value == '\v' || value =='\f';
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

	// Unary '!'
	if (*line == BANG) {
		++line;
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

void parse(STRING line, bool execute) {
	// Parse a single line
	
	// Skip leading whitespace
	line = trimLeft(line);

	// Skip blank lines and comments
	if (*line == '\0') return;
	if (*line == INLINE_COMMENT) return;


	STRING start = line;

	// Determine Top-Level Command (Statement Identification)
	while (*line != '\0') { 
		bool assignment = *line == EQUAL && *(line-1) != EQUAL;
		if (execute && assignment) {
			++line;
			// ASSIGNMENT MODE
			// Expect {ADDRESS} = {EXPRESSION}
			
			// You can only assign to memory addresses
			// Skip line if not referecing address
			if (*start != MEM_PREFIX) return;

			// Grab address number
			STRING end = ++start;
			while (*end >= '0' && *end <= '9') ++end;
			
			INTEGER address = stringToInt(start, end);
			write(address, parseExpression(line));

			return;
		} else if (consume(IF, line)) {
			// IF statement
			start = line;

			if (!find(THEN, line, start)) {
				// Syntax Error: 'THEN' Missing
				return;
			}

			if (!execute) {
				parseCodeBlock(false);
				return;
			}
			
			INTEGER expression = parseExpression(start, line);

			if (expression) {
				parseCodeBlock();
			} else {
				parseCodeBlock(false); // Do not execute code block
			}

			return;
		} else if (consume(END, line)) {
			return;
		}

		++line;
	}

	if (*line == '\0') return; // Drop lines without a useful command
}

#ifdef EMULATE 

using namespace std;

ifstream File;

void interpret() {
	// Read file and return its string data
	string line;	

	// Read File Contents
	while (getline(File, line)) {
		parse(line.c_str());
	}

	File.close();
}

void parseCodeBlock(bool execute) {
	// Parse code block layer until you reach 'END'
	++nestingLevel;
	string line;
	while (getline(File, line)) {
		STRING cLine = line.c_str();

		if (find(END, cLine, cLine)) {
			--nestingLevel;
			return;
		} else if (find(ELSE, cLine, cLine)) {
			--nestingLevel;
			return;
		}

		// Parse line within code block
		// Recursively calls if more code blocks exist
		parse(line.c_str(), execute);	
	}
	--nestingLevel;
}

void initDebugHeap() {
	// Set all heap values to "null" by setting a large negative number
	for (int i = 0; i < HEAP_SIZE; i++) {
		Heap[i] = NULL_INT;
	}
}

void printHeap() {
	// Print heap and skip empty contents
	cout << "Heap:\t[ ";
	
	bool allowEllips = true;
	for (int i = 0; i < HEAP_SIZE; i++) {
		if (Heap[i] == NULL_INT) {
			if (allowEllips) cout << "... , ";
			allowEllips = false;
			continue;
		} 

		cout << Heap[i] << " , ";
		allowEllips = true;
	}

	cout << "\b\b ]\n";
}

void debugConsume(STRING value, STRING& line) {
	STRING start = line;
	std::cout << "Consuming keyword \"" << value << "\" immediately in \"" << line << "\"\n";

	if (consume(value, line)) {
		std::cout << "\"" << value << "\" was found\n";
		std::cout << "\"" << *line << "\" at position " << line-start << "\n";
	} else {
		std::cout << "\"" << value << "\" was not found\n";
	}
}

void debugFind(STRING value, STRING& line, STRING start) {
	std::cout << "Finding keyword \"" << value << "\" in \"" << start << "\"\n";
	
	if (find(value, line, start)) {
		std::cout << "\"" << value << "\" was found\n";
		std::cout << "\"" << *line << "\" at position " << line-start << "\n";
	} else {
		std::cout << "\"" << value << "\" was not found\n";
	}

}

int main() {
	File.open("programs/main");

	initDebugHeap();
	interpret();
	printHeap();

	File.close();

	/*
	STRING line = "IF M1 != M5 UTHEN";
	STRING match = THEN;
	//debugConsume(match, line);
	debugFind(match, line, line);
	*/

	return 0;
}

#else

#endif 
