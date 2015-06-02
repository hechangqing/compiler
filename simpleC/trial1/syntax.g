// this is the syntax of simpleC
// because of using recusive down algorithm, the syntax does not include 
// left-recusive syntax

program     ::= block
block       ::= '{' decls stmts '}'
decls       ::= (decl)*
decl        ::= type ID ';'
type        ::= BASIC
stmts       ::= (stmt)*
stmt        ::= loc '=' bool ';'
             |  IF '(' bool ')' stmt ELSE stmt
             |  WHILE '(' bool ')' stmt
             |  BREAK ';'
             |  block
loc         ::= ID
bool        ::= join ('||' join)*
join        ::= equality ('&&' equality)*
equality    ::= rel (('==' | '!=') rel)*
rel         ::= expr < expr
             |  expr <= expr
             |  expr >= expr
             |  expr > expr
             |  expr
expr        ::= term (('+' | '-') term)*
term        ::= unary (('*' | '/') unary)*
unary       ::= '!' unary | '-' unary | factor
factor      ::= '(' bool ')' | loc | NUM | TRUE | FALSE

