grammar doppio;

// -----------------------------------------------------
// Expressions
// -----------------------------------------------------
expression              :   assignment_expression;

assignment_expression   :   additive_expression ('=' assignment_expression)*;

additive_expression     :   multiplicative_expression (('+'|'-') multiplicative_expression)*;

multiplicative_expression:  postfix_expression (('*'|'/'|'%'|'^') postfix_expression)*;

postfix_expression      :   primary_expression ( arguments_expression | '!' )*;

primary_expression      :   IDENTIFIER | INT | FLOAT | '(' expression ')';

arguments_expression    :   '(' assignment_expression (',' assignment_expression)* ')' | '(' ')';
	
// -----------------------------------------------------
// Tokens
// -----------------------------------------------------
IDENTIFIER  :   ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*;

INT         :   '0'..'9'+;

FLOAT       :   ('0'..'9')+ '.' ('0'..'9')* EXPONENT?
            |   '.' ('0'..'9')+ EXPONENT?
            |   ('0'..'9')+ EXPONENT
            ;

fragment
EXPONENT    :   ('e'|'E') ('+'|'-')? ('0'..'9')+ 
            ;

/* We're going to ignore all white space characters */
WS          :   (' ' | '\t' | '\r'| '\n') {$channel=HIDDEN;}
            ;
