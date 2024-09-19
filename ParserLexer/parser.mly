%{
  open Ast
%}

%token SEMICOLON INT
%token EOF
%token LB RB LP RP EQ
%token <string> IDENT
%token <int> CST

/* Point d'entrée de la grammaire */
%start prog

/* Type des valeurs retournées par l'analyseur syntaxique */
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
;

expr:
| c = CST { Cst(c, $loc)}
;
