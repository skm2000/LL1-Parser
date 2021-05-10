%Tokens id increment decrement + - equals notequals lessthan lessthanequals greaterthan greaterthanequals eof char string while charToken stringToken void , ( ) { } ; EPSILON
%Non-terminals <PROGRAM> <FUNCTION> <TYPE> <ARGS> <BLOCK> <ARGS1> <STATEMENTS> <STATEMENT> <DECLARATION> <A> <ASSIGNMENT> <INC_DEC_STMT> <WHILE_STMT> <IDENTIFIERS> <OTHER_IDENTIFIERS> <RIGHT_HAND_SIDE> <ADD_OP> <RELN_OP> <EXPR> <NUM_EXPR> <NUM_EXPR_> <T> <BOOL_EXPR> <DECASSIGN> <B> <C>
%Start <PROGRAM>
%Rules
<PROGRAM> : <FUNCTION> eof
<FUNCTION> : <TYPE> id ( <ARGS> ) <BLOCK>
<ARGS> : <TYPE> id <ARGS1> | EPSILON
<ARGS1> : , <TYPE> id <ARGS1> | EPSILON
<TYPE> : void | char | string
<BLOCK> : { <STATEMENTS> } <STATEMENTS> | { <BLOCK> } <STATEMENTS>
<STATEMENTS> : <STATEMENT> ; <C> | <WHILE_STMT> | EPSILON 
<C> : <STATEMENTS> | <BLOCK>
<STATEMENT> : <DECASSIGN> | <INC_DEC_STMT> | <EXPR>
<DECASSIGN> : <TYPE> id <B>
<B> : <DECLARATION> | <ASSIGNMENT>
<DECLARATION> : <A>
<A> : <IDENTIFIERS> | EPSILON
<IDENTIFIERS> : <OTHER_IDENTIFIERS>
<OTHER_IDENTIFIERS> : , id <OTHER_IDENTIFIERS> | EPSILON
<ASSIGNMENT> : equals <RIGHT_HAND_SIDE>
<RIGHT_HAND_SIDE> : charToken | stringToken | <EXPR>
<INC_DEC_STMT> : increment id | decrement id
<WHILE_STMT> : while ( <BOOL_EXPR> ) <BLOCK>
<ADD_OP> : + | -
<RELN_OP> : notequals | lessthan | lessthanequals | greaterthan | greaterthanequals
<EXPR> : <NUM_EXPR> | <BOOL_EXPR>
<NUM_EXPR> : <T> <NUM_EXPR_>
<NUM_EXPR_> : <ADD_OP> <NUM_EXPR> | EPSILON
<T> : id
<BOOL_EXPR> : id <RELN_OP> id | id <RELN_OP> charToken
