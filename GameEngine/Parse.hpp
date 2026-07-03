#ifndef PARSE_H
#define PARSE_H

#include "Program.hpp"
#include <cstdint>

// DATA TYPES
// SYNTAX CONSTANTS
constexpr char INLINE_COMMENT = '#';
constexpr char MEM_PREFIX = 'M';
constexpr char ARG_DELIM = ',';

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
constexpr STRING NOT = "NOT";
constexpr STRING AND = "AND";
constexpr STRING OR = "OR";

// Keywords
constexpr STRING IF = "IF";
constexpr STRING THEN = "THEN";
constexpr STRING WHILE = "WHILE";
constexpr STRING DO = "DO";
constexpr STRING ELSE = "ELSE";
constexpr STRING END = "END";
constexpr STRING CALL = "CALL";
constexpr STRING DEFINE = "DEFINE";
constexpr STRING FUNC = "FUNC";
constexpr STRING BEGIN = "BEGIN";
constexpr STRING DISPLAY = "DISPLAY";
constexpr STRING INPUT = "INPUT";

// Control Keywords
constexpr STRING JOYSTICK_X = "JOY_X";
constexpr STRING JOYSTICK_Y = "JOY_Y";
constexpr STRING JOYSTICK_BUTTON = "JOY_BTN";
constexpr STRING BUTTON_A = "BTN_A";

// Parsing and Interpreting
extern uint8_t NestingLevel; // Track the level of nesting
extern uint8_t RecursionDepth;
constexpr INTEGER MAX_RECURSION_DEPTH = 10;

// HELPERS
INTEGER stringToInt(STRING line);
INTEGER stringToInt(STRING line, STRING end);
STRING trimLeft(STRING value);
STRING findEnd(STRING line);
bool isWhiteSpace(const char& value);
bool consume(STRING value, STRING& line, bool whitespace=true);
bool find(STRING value, STRING& line, STRING start);

// Expression Parsing
// Derived from: http://craftinginterpreters.com/parsing-expressions.html
// Operators act in hierarcies
// We use recursion to go down the heirarch until a number and then bubble going back up
// evaluating operators

// Operator function calls defined in heirarichal order
// Pass pointer by reference to have a global 'current' character tracker
INTEGER logicalOr(STRING& line, STRING& end);
INTEGER logicalAnd(STRING& line, STRING& end);
INTEGER equality(STRING& line, STRING& end); 						
INTEGER comparison(STRING& line, STRING& end);
INTEGER term(STRING& line, STRING& end);
INTEGER factor(STRING& line, STRING& end);
INTEGER unary(STRING& line, STRING& end);
INTEGER primary(STRING& line, STRING& end);
INTEGER parseExpression(STRING& line, STRING& end);
INTEGER parseExpression(STRING& line);

void parseCodeBlock(bool execute=true);
void parseIfBlock(bool execute=true);
void parseWhileBlock(bool execute=true);

// Function Parsing
void parseFuncDef(bool execute=true);
void parseFuncArgs(int expectedArgs, bool execute=true);
void parseFuncCall(bool execute=true);

void parse(bool execute=true); 

#endif
