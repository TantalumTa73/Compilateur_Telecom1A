%{
  open Ast
%}

%token SEMICOLON
%token EOF
%token LB RB LP RP EQ
%token <string> TYPE
%token <string> IDENT
%token <int> CST
%token TRUE FALSE

%token FOR WHILE
%token IF ELSE
%token RETURN

%token XOR OR AND NOT
%token LE LEQ GE GEQ EQQ NEQ
%token PLUS MINUS MULT DIV MOD

/* Définitions des priorités et associativités des tokens */
%left XOR
%left OR
%left AND
%nonassoc NOT
%nonassoc LE LEQ GE GEQ EQQ NEQ
%left PLUS MINUS 
%left MULT DIV MOD
// %nonassoc uminus

/* Point d'entr�e de la grammaire */
%start prog

/* Type des valeurs retourn�es par l'analyseur syntaxique */
%type <Ast.program> prog

%%

prog:
| p = list(global_stmt) EOF { p }
;

global_stmt:
| t = TYPE id = IDENT SEMICOLON { GVarDef(t,id, $loc) }
| t = TYPE id = IDENT EQ e = expr SEMICOLON { GVarDefS(t,id,e, $loc) }
| t = TYPE f = IDENT LP args = list(formal) RP LB body = stmt RB 
// | t = TYPE f = IDENT LP args = list(String) RP LB body = stmt RB 
  { GFunDef(t,f,args,body, $loc) }
;

formal:
| t = TYPE id = IDENT { Formal(t,id) }
;

left_value:
| s = IDENT { Var(s, $loc) }
// | l = left_value LB e = expr RB { Tab(l,e,$loc) }
;

stmt:
| LB body = list(stmt) RB { Sscope(body,$loc) }
| RETURN e = expr SEMICOLON { Sreturn(e, $loc) }

// | FOR LP RP body = stmt  { Sblock(body,$loc) }
// | WHILE LP e = expr RP LB body = stmt RB { Sblock(body,$loc) }

| t = TYPE id = IDENT SEMICOLON { SvarDef(t,id, $loc) }
| t = TYPE id = IDENT EQ e = expr SEMICOLON { SvarDefS(t,id,e, $loc) }
| id = left_value EQ e = expr SEMICOLON { SvarSet(id,e, $loc) }
// S expr

| IF LP e = expr RP LB body = stmt RB { Sif(e,body,$loc) }
| IF LP e = expr RP LB body1 = stmt RB ELSE LB body2 = stmt RB { SifElse(e,body1,body2,$loc) }
;

litteral:
| x = CST { Int(x, $loc) }
| TRUE { Bool(true, $loc) }
| FALSE { Bool(false, $loc) }
;

expr:
| x = litteral { Const(x, $loc) }
| x = left_value { VarGet(x, $loc) }
| x = IDENT LP args = list(expr) RP { FunCall(x,args, $loc) }

| e1 = expr o = op e2 = expr { Binop(o,e1,e2, $loc) }
// | NOT e = expr { Uniop("not",e, $loc) }
// | MINUS e = expr %prec uminus { Uniop("minus",e, $loc) }
;

%inline op:
| PLUS  { Add }
| MINUS { Sub }
| MULT { Mul }
| DIV   { Div }
| MOD   { Mod }
| LEQ   { Leq }
| GEQ   { Geq }
| GE    { Ge  }
| LE    { Le  }
| NEQ   { Neq }
| EQQ   { Eq  }
| AND   { And }
| OR    { Or  } 
| XOR   { Xor } 
;