#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Program.hpp"
#include <cstdint>

// DATA TYPES

// SYNTAX CONSTANTS
constexpr char INLINE_COMMENT = '#';
constexpr char MEM_PREFIX = 'M';

// OPERATORS
constexpr char ADDITION = '+';
constexpr char SUBTRACTION = '-';
constexpr char MULTIPLICATION = '*';
constexpr char DIVISION = '/';
constexpr char GREATER = '>';
constexpr char LESS = '<';
constexpr char BANG = '!';
constexpr char EQUAL = '=';
constexpr char LEFT_BRACKET = '('; 
constexpr char RIGHT_BRACKET = ')'; 

// Keywords
constexpr STRING IF = "IF";
constexpr STRING THEN = "THEN";
constexpr STRING ELSE = "ELSE";
constexpr STRING END = "END";

// ========================
// UNIVERSAL IMPLEMENTATION
// ========================

// Helpers
INTEGER stringToInt(STRING line);
INTEGER stringToInt(STRING line, STRING end);
STRING trimLeft(STRING value);
STRING findEnd(STRING line);
bool isWhiteSpace(const char& value);
bool validAddress(INTEGER address); 
bool consume(STRING value, STRING& line);
bool find(STRING value, STRING& line, STRING start);

// Basic I/O
void write(ADDR address, INTEGER value);
INTEGER read(ADDR address);

// Parsing and Interpreting
extern uint8_t nestingLevel; // Track the level of nesting

// Expression Parsing
// Derived from: http://craftinginterpreters.com/parsing-expressions.html
// Operators act in hierarcies
// We use recursion to go down the heirarch until a number and then bubble going back up
// evaluating operators

// Operator function calls defined in heirarichal order
// Pass pointer by reference to have a global 'current' character tracker
INTEGER equality(STRING& line, STRING& end); 						
INTEGER comparison(STRING& line, STRING& end);
INTEGER term(STRING& line, STRING& end);
INTEGER factor(STRING& line, STRING& end);
INTEGER unary(STRING& line, STRING& end);
INTEGER primary(STRING& line, STRING& end);

INTEGER parseExpression(STRING& line, STRING& end);
INTEGER parseExpression(STRING& line);
void skipCodeBlock();
void parseCodeBlock(bool execute=true);
void parse(STRING line, bool execute=true); 

/* 
 * SWITCH BETWEEN EMULATING LANGUAGE ON 
 * PERSONAL COMPUTER AND ARDUINO HARDWARE
 */
#ifdef EMULATE 
	#include <iostream>
	
	constexpr INTEGER NULL_INT = 1 << (sizeof(INTEGER) * 8 - 1);

	using namespace std;

	void interpret();

	// Debug Functions
	void initDebugHeap();
	void printHeap();
	void debugConsume(STRING value, STRING& line, STRING& start);
	void debugFind(STRING value, STRING& line, STRING start);
#else

#endif 



#endif
