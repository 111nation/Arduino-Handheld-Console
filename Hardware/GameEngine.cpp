#include "GameEngine.hpp"
#include <cmath>

// UNIVERSAL IMPLEMENTATION

INTEGER* Heap = new INTEGER[HEAP_SIZE];


bool consume(STRING value, STRING& line) {
	// Move pointer past IMMEDIATE matched word
	// Used for searching keyword like 'if' or 'else'
	// Do not move pointer if match not found
	// Only match immediate characters
	line = trimLeft(line);
	STRING currentLine = line;
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

bool find(STRING value, STRING& line) {
	// Similar to consume
	// We check whole line for first occurence
	// Return pointer pointing to characters before
	// matched word
	line = trimLeft(line);
	STRING currentLine = line;
	STRING currentVal = value;

	while (*currentLine != '\0' && *currentVal != '\0') {
		if (*currentLine != *currentVal) currentVal = value;
		if (*currentVal == *currentLine) ++currentVal;
		++currentLine;
	}

	if (*currentVal != '\0') return false;

	// Ensure that matched word is padded by whitespace
	// Prevents 'if' being matched in 'ifelse'
	// 'if' is only found if its 'if else'
	// Return trimmed left to first meaningful character
	if (*currentLine == '\0' || isWhiteSpace(*currentLine)) {
		// Point to found word to allow consumption
		line = currentLine - (currentVal - value);
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

// We accept a INTEGER instead of ADDR on purpose
// Prevents silent downcasting/truncation overflow bugs
// Ensures that numbers that overflow ADDR are not accepted as  
// valid addresses due to truncation
bool validAddress(INTEGER address) {
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
INTEGER equality(STRING& line) {
	INTEGER result = comparison(line);
	line = trimLeft(line);

	while ((*line == EQUAL && *(line + 1) == EQUAL) || (*line == BANG && *(line + 1) == EQUAL)) {
		STRING operat = line;
		line += 2; // Move past both characters making up '==' and '!='

		if (*operat == EQUAL) {
			// '==' Found
			result = result == comparison(line) ? 1 : 0;
		} else {
			// '!=' Found
			result = result != comparison(line) ? 1 : 0;
		} 

		line = trimLeft(line);
	}

	return result;
}

INTEGER comparison(STRING& line) {
	INTEGER result = term(line);
	line = trimLeft(line);

	while (*line == LESS || *line == GREATER) {
		STRING operat = line;
		bool equalOperator = false;
		++line;

		if (*line == EQUAL) {
			equalOperator = true;
			++line;
		}


		if (*operat == LESS) {
			if (equalOperator) {
				result = result <= term(line) ? 1 : 0;
			} else {
				result = result < term(line) ? 1 : 0;
			}
		} else {
			if (equalOperator) {
				result = result >= term(line) ? 1 : 0;
			} else {
				result = result > term(line) ? 1 : 0;
			}
		}
	}

	return result;
}

INTEGER term(STRING& line) {
	INTEGER result = factor(line);
	line = trimLeft(line);

	while (*line == ADDITION || *line == SUBTRACTION) {
		STRING operat = line;
		++line;

		if (*operat == ADDITION) {
			result += factor(line);
		} else {
			result -= factor(line);
		}
	}

	return result;
}

INTEGER factor(STRING& line) {
	INTEGER result = unary(line);
	line = trimLeft(line);

	while (*line == MULTIPLICATION || *line == DIVISION) {
		STRING operat = line;
		++line;

		if (*operat == MULTIPLICATION) {
			result *= unary(line);
		} else {
			result /= unary(line);
		}

		line = trimLeft(line);
	}

	return result;
}

INTEGER unary(STRING& line) {
	// Recursively check for unary operators '-!5' or '!!6' or '+-!M4'
	// Returns a primary expression as soon as no
	// unary operator has been found
	line = trimLeft(line);

	// Unary '!'
	if (*line == BANG) {
		++line;
		return (unary(line) == 0 ? 1 : 0); 
	}

	// Unary '-'
	if (*line == SUBTRACTION) {
		++line;
		return -1 * unary(line);
	}

	// Unary '+'
	if (*line == ADDITION) {
		++line;
		return +1 * unary(line);
	}

	// No operator found, drop down to primary
	return primary(line);
}

INTEGER primary(STRING& line) {
	// Check for literal values, variables, or numbers
	line = trimLeft(line);

	// Handle paranthesis
	if (*line == LEFT_BRACKET) {
		// Restart heirachy because parathesized experessions
		// Are treated as sperate new expressions
		++line;

		INTEGER result = equality(line);
		line = trimLeft(line);

		// Silently forgive missing closing bracket
		// (3+4 will be evaluated just like (3+4)
		if (*line == RIGHT_BRACKET) ++line;
		return result;
	} 

	if (*line >= '0' && *line <= '9') {
		// Parse literal number and return to upper operators
		STRING start = line;
		while (*line >= '0' && * line <= '9') ++line; 
		return stringToInt(start, line); 
	} else if (*line == MEM_PREFIX) {
		// Heap Address referenced
		// Return value of the memory address
		STRING start = ++line;
		while (*line >= '0' && *line <= '9') ++line;

		// stringToInt returns INTEGER not ADDR, ensure non truncation
		INTEGER rawAddress = stringToInt(start, line);

		if (validAddress(rawAddress)) return read(rawAddress);
	}

	return 0; // Saftey fallback
}

INTEGER parseExpression(STRING& line) {
	// Parse A Maths Expression And Return its value
	// Heirarchial order algorithm defined by: 
	// http://craftinginterpreters.com/parsing-expressions.html
	line = trimLeft(line);
	if (*line == '\0') return 0;
	return equality(line);	
}

void parse(STRING line) {
	// Parse a single line
	
	// Skip leading whitespace
	line = trimLeft(line);

	// Skip blank lines and comments
	if (*line == '\0') return;
	if (*line == INLINE_COMMENT) return;

	STRING start = line;

	// Determine Top-Level Command (Statement Identification)
	while (*line != '\0') { 
		++line;
		if (*line == EQUAL && *(line-1) != EQUAL) {
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

			if (!find(THEN, line)) {
				// Invalid if statement
				// No then
			}
		
			INTEGER expression = parseExpression(start);
			write(0, expression);

			return;
		}
	}

	if (*line == '\0') return; // Drop lines without a useful command
}

#ifdef EMULATE 

using namespace std;

void interpret(std::string fileName) {
	// Read file and return its string data
	ifstream file(fileName);
	string line;	

	// Read File Contents
	while (getline(file, line)) {
		// Skip leading whitespace
		//std::cout << line.c_str() << "\n";
		parse(line.c_str());
	}

	file.close();
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

void debugFind(STRING value, STRING& line) {
	STRING start = line;
	std::cout << "Finding keyword \"" << value << "\" in \"" << line << "\"\n";
	
	if (find(value, line)) {
		std::cout << "\"" << value << "\" was found\n";
		std::cout << "\"" << *line << "\" at position " << line-start << "\n";
	} else {
		std::cout << "\"" << value << "\" was not found\n";
	}

}

int main() {
	initDebugHeap();
	interpret("programs/main");
	printHeap();

	/*
	STRING line = "IF M1 != M5 THEN";
	STRING match = THEN;
	//debugConsume(match, line);
	debugFind(match, line);
	*/

	return 0;
}

#else

#endif 
