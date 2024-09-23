%{
  open Ast
%}

%token SEMICOLON INT
%token EOF
%token LB RB LP RP EQ
%token <string> IDENT
%token <int> CST
%token MULT PLUS MINUS DIVISION MODULO

/* Point d'entr�e de la grammaire */
%start prog

/* Type des valeurs retourn�es par l'analyseur syntaxique */
%type <Ast.program> prog

%%

prog:
| p = list(def) EOF { p }
;

def:
| INT id = IDENT SEMICOLON { Gvar(id, $loc) }
| INT f = IDENT LP INT x = IDENT RP LB body = list(stmt) RB { Gfun(f, x, body, $loc)  }
;

stmt:
| id = IDENT EQ e = expr SEMICOLON { Set(id,e, $loc) }
| f = IDENT LP e = expr RP SEMICOLON { StmtFunc(f, e, $loc) }
;

// utilisation de grammaires non ambigues depuis https://en.wikipedia.org/wiki/Syntax_diagram
// mais sens renversé pour pouvoir avoir a / b * c qui fait calculer (a / b) * c et non a / (b * c)
expr:
| t = term { ExprSingle(t, $loc) }
| e = expr PLUS t = term { ExprDouble(e, "plus", t, $loc) }
| e = expr MINUS t = term { ExprDouble(e, "minus", t, $loc) }
| f = IDENT LP e = expr RP { ExprFunc(f, e, $loc) }
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
| LP e = expr RP { Parenthesis(e, $loc) }
;