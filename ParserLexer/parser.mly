%{
  open Ast
%}

%token SEMICOLON INT
%token EOF
%token LB RB LP RP EQ
%token <string> IDENT
%token <int> CST
%token MULT PLUS

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
;

// utilisation de grammaires non ambigues depuis https://en.wikipedia.org/wiki/Syntax_diagram
expr:
| t = term { ExprSingle(t, $loc) }
| t = term PLUS e = expr { ExprDouble(t, "plus", e, $loc) }
;

term:
| f = factor { TermSingle(f, $loc) }
| f = factor MULT t = term { TermDouble(f, "mult", t, $loc) } 
;

factor:
| c = CST { Cst(c, $loc) }
| LP e = expr RP { Parenthesis(e, $loc) }
;