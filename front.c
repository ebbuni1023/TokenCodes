/*
Make the lexical analyzer given in front.c better. In this problem you will rewrite that code to take in to recognize the following list of reserved words and special symbols and return their respective token codes:

for (FOR_CODE, 30),
if (IF_CODE, 31),  
else (ELSE_CODE, 32),  
while(WHILE_CODE, 33), 
do (DO_CODE, 34), 
int (INT_CODE, 35), 
float (FLOAT_CODE, 36), 
switch (SWITCH_CODE, 37) ,
> (LESS_THAN_OP, 38) , 
>= (LESS_EQUAL_OP, 39) ,
< (GREATER_THAN_OP, 40) , 
<= (GREATER_ EQUAL_OP, 40) ,
== (IS_ EQUAL_OP, 40) , 
== (NOT_ EQUAL_OP, 40) , 

This code should also be modified to identify floating point literals and separate them from integer literals.

*/
/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

void lessEqual(void);
void greaterEqual(void);
void isEqual(void);
//void notEqual(void);
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define EXCLAMATION 9
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

#define FOR_CODE 30
#define IF_CODE 31
#define ELSE_CODE 32
#define WHILE_CODE 33
#define DO_CODE 34
#define INT_CODE 35
#define FLOAT_CODE 36
#define SWITCH_CODE 37
#define LESS_THAN_OP 38
#define LESS_EQUAL_OP 39
#define GREATER_THAN_OP 40
#define GREATER_EQUAL_OP 41
#define IS_EQUAL_OP 42
#define NOT_EQUAL_OP 43

/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else {
	 	getChar();
	 do {
	 	lex();
	 } while (nextToken != EOF);
	 }
	 return 0;
}
/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LEFT_PAREN;
			 break;
		 case ')':
			 addChar();
			 nextToken = RIGHT_PAREN;
			 break;
		 case '+':
			 addChar();
			 nextToken = ADD_OP;
			 break;
		 case '-':
			 addChar();
			 nextToken = SUB_OP;
			 break;
		 case '*':
			 addChar();
			 nextToken = MULT_OP;
			 break;
		 case '/':
			 addChar();
			 nextToken = DIV_OP;
			 break;
		 case '>':
		 	addChar();
			 nextToken = LESS_THAN_OP;
			 break;
		 case '<':
		 	addChar();
			 nextToken = GREATER_THAN_OP;
			 break;
		 case '=':
		 	addChar();
			 nextToken = ASSIGN_OP;
			 break;
		 case '!':
		 	addChar();
			 nextToken = EXCLAMATION;
			 break;

		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	} else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar))
		 	charClass = DIGIT;
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}
/******************************************************/
/* lessEqual - check if > have = so it is >= */
void lessEqual(void){
	if(nextToken == LESS_THAN_OP){
		getChar();
		if (charClass != UNKNOWN){
			getNonBlank();
			return;
		}else{
			lookup(nextChar);
			if(nextToken == ASSIGN_OP){
				nextToken = LESS_EQUAL_OP;
				return;
			}
			return;
		}
	}
}
/******************************************************/
/* greaterEqual - check if < have = so it is <= */
void greaterEqual(void){
	if (nextToken == GREATER_THAN_OP){
		getChar();
		if(charClass != UNKNOWN){
			getNonBlank();
			return;
		}else{
			lookup(nextChar);
			if(nextToken == ASSIGN_OP){
				nextToken = GREATER_EQUAL_OP;
				return;
			}
			return;
		}
	}
}

/******************************************************/
/* isEqual - check if = have = so it is == */
void isEqual(void) {
	if (nextToken == ASSIGN_OP) {
		getChar();
		if (charClass != UNKNOWN) {
			getNonBlank();
			return;
		}else {
			lookup(nextChar);
			if (nextToken == ASSIGN_OP) {
				nextToken = IS_EQUAL_OP;
				return;
			}
			return;
		}
	}
}

/******************************************************/
/* notEqual - check if ! have = && =so it is !== */
void notEqual(void){
	if (nextToken == EXCLAMATION) {
		getChar();
		if (charClass != UNKNOWN) {
			getNonBlank();
			return;
		}else {
			lookup(nextChar);
			if (nextToken == ASSIGN_OP) {
				nextToken = NOT_EQUAL_OP;
				return;
			}
			return;
		}
	}
}
/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
	getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
 int x;
int lex(void) {
	 lexLen = 0;
	 getNonBlank();
	 int x;
	 switch (charClass) {
		/* Identifiers */
		 case LETTER:
			 addChar();
			 getChar();
			 while (charClass == LETTER || charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 // FOR_CODE
			 if(lexeme[0]=='f' && lexeme[1] =='o' && lexeme[2]=='r'){
				 nextToken = FOR_CODE;
				 break;
			 }

			 // IF_CODE
			 if(lexeme[0]=='i' && lexeme[1] =='f'){
				 nextToken = IF_CODE;
				 break;
			 }

			// ELSE_CODE
			 if(lexeme[0]=='e' && lexeme[1]=='l' && lexeme[2]=='s' && lexeme[3]=='e'){
				 nextToken = ELSE_CODE;
				 break;
			 }

			 // WHILE_CODE
			 if(lexeme[0]=='w' && lexeme[1]=='h' && lexeme[2]=='i' && lexeme[3]=='l' && lexeme[4] == 'e'){
				 nextToken = WHILE_CODE;
				 break;
			 }
			 
			 // DO_CODE
			 if(lexeme[0]=='d'&&lexeme[1]=='o'){
				 nextToken = DO_CODE;
				 break;
			 }

			 // INT_CODE
			 if(lexeme[0]=='i' && lexeme[1]=='n' && lexeme[2] == 't'){
				 nextToken = INT_CODE;
				 break;
			 }

			 // FLOAT_CODE
			 if(lexeme[0]=='f' && lexeme[1]=='l' && lexeme[2]=='o' && lexeme[3]=='a' && lexeme[4]=='t'){
				 nextToken = FLOAT_CODE;
				 break;
			 }

			 // SWITCH_CODE
			 if(lexeme[0]=='s' && lexeme[1]=='w' && lexeme[2]=='i' && lexeme[3]=='t' && lexeme[4] == 'c' && lexeme[5]=='h'){
				 nextToken = SWITCH_CODE;
				 break;
			 }
			 nextToken = IDENT;
			 break;

		/* Integer literals */
		 case DIGIT:
			 addChar();
			 getChar();
			 while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }
			 nextToken = INT_LIT;
		 	break;
		/* Parentheses and operators */
		 case UNKNOWN:
			 lookup(nextChar);
			 lessEqual();
			 greaterEqual();
			 isEqual();
			 notEqual();
			 getChar();
			 break;
		 	
			/* EOF */
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 }
  /* End of switch */

	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */

// void expr(void) {
// 	 printf("Enter <expr>\n");
// 	/* Parse the first term */
// 	 term();
// 	/* As long as the next token is + or -, get
// 	 the next token and parse the next term */
// 	 while (nextToken == ADD_OP || nextToken == SUB_OP) {
// 		 lex();
// 		 term();
// 	 }
// 	 printf("Exit <expr>\n");
// }

// /* term
//  Parses strings in the language generated by the rule:
//  <term> -> <factor> {(* | / | % ) <factor>}
//  */
// void term(void) {
// 	 printf("Enter <term>\n");
// 	/* Parse the first factor */
// 	 factor();
// 	/* As long as the next token is * or /, get the
// 	 next token and parse the next factor */
// 	 while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP) {
// 		 lex();
// 		 factor();
// 	 }
// 	 printf("Exit <term>\n");
// }

// /* factor
//  Parses strings in the language generated by the rule:
//  <factor> -> id | int_constant | ( <expr> )
//  */
// void factor(void) {
// 	 printf("Enter <factor>\n");
// 	/* Determine which RHS */
// 	 if (nextToken == IDENT || nextToken == INT_LIT)
// 		/* Get the next token */
// 		 lex();
// 		/* If the RHS is ( <expr> ), call lex to pass over the
// 		 left parenthesis, call expr, and check for the right
// 		 parenthesis */
// 	 else { if (nextToken == LEFT_PAREN) {
// 		 lex();
// 		 expr();
// 		 if (nextToken == RIGHT_PAREN)
// 		 	lex();
// 		 else
// 		 	error();
// 		 }
// 		/* It was not an id, an integer literal, or a left
// 		 parenthesis */
// 		 else
// 		 error();
// 	 }
// 	 printf("Exit <factor>\n");
// }