%{
  open Ast
%}

%token SEMICOLON INT
%token EOF
%token LB RB LP RP EQ
%token <string> IDENT
%token <int> CST
%token MULT PLUS MINUS DIVISION MODULO
%token RET

/* Point d'entr�e de la grammaire */
%start prog

/* Type des valeurs retourn�es par l'analyseur syntaxique */
%type <Ast.program> prog

%%

prog:
| p = list(loc) EOF { p }
;

loc:
| INT id = IDENT SEMICOLON { Def(Gvar(id, $loc)) }
| INT f = IDENT LP INT x = IDENT RP LB body = list(loc) RB { Def(Gfun(f, x, body, $loc)) }
| id = IDENT EQ e = expr SEMICOLON { Stmt(Set(id, e, $loc)) }
| f = IDENT LP e = expr RP SEMICOLON { Stmt(StmtFunc(f, e, $loc)) }
| RET e = expr SEMICOLON { Stmt(Return(e, $loc)) }
;
// def:
// | INT id = IDENT SEMICOLON { Gvar(id, $loc) }
// ;

// stmt:
// | id = IDENT EQ e = expr SEMICOLON { Set(id,e, $loc) }
// | f = IDENT LP e = expr RP SEMICOLON { StmtFunc(f, e, $loc) }
// ;

// utilisation de grammaires non ambigues depuis https://en.wikipedia.org/wiki/Syntax_diagram
// mais sens renversé pour pouvoir avoir a / b * c qui fait calculer (a / b) * c et non a / (b * c)
expr:
| t = term { ExprSingle(t, $loc) }
| e = expr PLUS t = term { ExprDouble(e, "plus", t, $loc) }
| e = expr MINUS t = term { ExprDouble(e, "minus", t, $loc) }
;

term:
| f = factor { TermSingle(f, $loc) }
| t = term MULT f = factor { TermDouble(t, "mult", f, $loc) } 
| t = term DIVISION f = factor { TermDouble(t, "division", f, $loc) }
| t = term MODULO f = factor { TermDouble(t, "modulo", f, $loc) }
;

factor:
| c = CST { Cst(c, $loc) }
| id = IDENT { Var(id, $loc) }
| MINUS f = factor { Minus(f, $loc) }
| LP e = expr RP { Parenthesis(e, $loc) }
| f = IDENT LP e = expr RP { FactorFunc(f, e, $loc) }
;