#ifndef TOK
#	define TOK(x)
#endif

TOK(ERROR)
// native types (keywords)
TOK(INT)
TOK(UINT)
TOK(FLOAT)
TOK(STRING)
TOK(VECTOR)
TOK(BOOL)
TOK(TRUE)
TOK(FALSE)
TOK(VOID)

// Keywords
TOK(IF)
TOK(WHILE)
TOK(FOR)
TOK(BREAK)
TOK(CONTINUE)
TOK(ELSE)

// Values
TOK(IDENT)
TOK(INTVAL)
TOK(FLOATVAL)
TOK(STRINGVAL)
TOK(VECTORVAL)
TOK(BOOLVAL)

// PUNCTUATION
TOK(SEMICOLON) // ;
TOK(LPAREN) // (
TOK(RPAREN) // )
TOK(LBRACE) // {
TOK(RBRACE) // }
TOK(COMMA)  // ,
TOK(DOT)    // .

// Comparison ops
TOK(ASSIGN) // =
TOK(EQUAL)  // ==
TOK(NOT)    // !
TOK(NEQUAL) // !=
TOK(LT)     // <
TOK(GT)     // >
TOK(LTE)    // <=
TOK(GTE)    // >=

// Logic Ops
TOK(OR)     // || or 'or'
TOK(AND)    // && or 'and'

// Bitwise ops
TOK(BNOT)         // ~
TOK(BOR)          // |
TOK(BAND)         // &
TOK(BXOR)         // ^
TOK(LSHIFT)       // <<
TOK(RSHIFT)       // >>
TOK(BORASSIGN)    // |=
TOK(BANDASSIGN)   // &=
TOK(BXORASSIGN)   // ^=
TOK(LSHIFTASSIGN) // <<=
TOK(RSHIFTASSIGN) // >>=

// Math Ops
TOK(ADD)       // +
TOK(SUB)       // -
TOK(MUL)       // *
TOK(DIV)       // /
TOK(INC)       // ++
TOK(DEC)       // --
TOK(ADDASSIGN) // +=
TOK(SUBASSIGN) // -=
TOK(MULASSIGN) // *=
TOK(DIVASSIGN) // /=


TOK(NOP) // ALWAYS COMES LAST!
