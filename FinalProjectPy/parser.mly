/* Analyseur syntaxique pour PtiPython */

%{
  open Ast;;
%}
 
%token <string> CST
%token <string> STR
%token <string> IDENT
%token AND DEF FOR TRUE FALSE IN NOT OR RETURN NONE IF ELIF ELSE
%token EOF COLON SEMICOLON
%token LP RP COMMA LB RB
%token PLUS MINUS TIMES DIV MOD
%token EQ EQQ
%token NEWLINE BEGIN END
%token LEQ GEQ LE GE NEQ
%token WHILE
%token INT

/* Définitions des priorités et associativités des tokens */
%left OR
%left AND
%nonassoc NOT
%nonassoc LE LEQ GE GEQ EQQ NEQ
%left PLUS MINUS 
%left TIMES DIV MOD
%nonassoc uminus

/* Point d'entrée de la grammaire */
%start prog

/* Type des valeurs retournées par l'analyseur syntaxique */
%type <Ast.program> prog

%%

prog:
| p = list(stmt) EOF { p }
;

stmt:
| s = stmt_node { Stmt(s, $loc) }
;

stmt_node:
| vartype = IDENT ; id = IDENT SEMICOLON { Svardef(vartype, id) }
| vartype = IDENT ; f = IDENT ; LP ; a = list(args) ; RP ; body = stmt { Sfundef(f, a, body) }
// | id = IDENT EQ e = expr SEMICOLON {  }
// | f = IDENT LP e = expr RP SEMICOLON {  }
// | RETURN e = expr SEMICOLON {  }
// | READ id = IDENT RP {  }
;

expr:
| c = const                      { Const(c, $loc) }
| l = left_value                 { Val(l, $loc)}
| e1 = expr o = op e2 = expr     { BinOp(o,e1,e2, $loc) }
| MINUS e = expr %prec uminus    { Moins(e, $loc) } 
| NOT e = expr                   { Not(e, $loc) } 
| s = IDENT ; LP ; args = separated_list(COMMA,expr) ; RP { Ecall(s,args, $loc) }
| LP ; e = expr ; RP { e }
;

left_value:
| s = IDENT { Var(s, $loc) }
| l = expr; LB ; e = expr ; RB { Tab(l,e,$loc) }
;

args:
| var_type = IDENT ; var_name = IDENT { TypeVar(var_type, var_name) }
;

const:
| i = CST { Int(i, $loc) }
| s = STR { Str(s, $loc) }
| TRUE    { Bool(true, $loc)}
| FALSE   { Bool(false, $loc)}
| NONE    { Non($loc) }
;

%inline op:
| PLUS  { Add }
| MINUS { Sub }
| TIMES { Mul }
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
;


// file:
// | NEWLINE? ; d = global_stmt+ ; NEWLINE ? ; EOF { d }
// | NEWLINE* ; EOF { [] }
// ;
  
// global_stmt:
// | DEF ; name = IDENT ; LP ; args = separated_list(COMMA,IDENT) ; RP ; COLON ; bod =  suite  
//         { GFunDef(name, args, bod, $loc) }
// | s = stmt  { Gstmt(s, $loc) }
// ;

// suite: b = simple_stmt ; NEWLINE { b }
//   | NEWLINE ; BEGIN ; s = stmt+ ; END { Sblock(s, $loc) }
// ;

// left_value:
// | s = IDENT { Var(s, $loc) }
// | l = expr; LB ; e = expr ; RB { Tab(l,e,$loc) }
// ;

// simple_stmt: 
//   | RETURN ; e = expr { Sreturn(e, $loc) } 
//   | l = left_value ; EQ ; e = expr { Sassign(l,e, $loc) } 
//   | e = expr { Sval(e, $loc) } 
// ;

// stmt:
// | s = simple_stmt ; NEWLINE  { s }
// | FOR ; s = IDENT ; IN ; e = expr ; COLON ; b = suite  {Sfor(s,e,b, $loc) }
// | IF ; e = expr ; COLON ; b = suite { Sif(e, b, $loc) }
// | ELIF ; e = expr ; COLON ; b = suite { Selif(e, b, $loc) }
// | ELSE ; COLON ; b = suite { Selse(b, $loc) }
// | WHILE ; e = expr ; COLON ; b = suite { Swhile(e, b, $loc) }
// ;

// expr:
// | c = const                      { Const(c, $loc) }
// | l = left_value                 { Val(l, $loc)}
// | e1 = expr o = op e2 = expr     { Op(o,e1,e2, $loc) }
// | MINUS e = expr %prec uminus    { Moins(e, $loc) } 
// | NOT e = expr                   { Not(e, $loc) } 
// | s = IDENT ; LP ; args = separated_list(COMMA,expr) ; RP { Ecall(s,args, $loc) }
// | LB ; args = separated_list(COMMA,expr) ; RB { List(args, $loc)}
// | LP ; e = expr ; RP { e }
// | LB ; e = expr ; FOR ; s = IDENT ; IN ; l = expr ; RB { ListCompr(e,s,l, $loc) }
// ;

// %inline op:
// | PLUS  { Add}
// | MINUS { Sub }
// | TIMES { Mul }
// | DIV   { Div }
// | MOD   { Mod }
// | LEQ   { Leq }
// | GEQ   { Geq }
// | GE    { Ge  }
// | LE    { Le  }
// | NEQ   { Neq }
// | EQQ   { Eq  }
// | AND   { And }
// | OR    { Or  } 
// ;

// const:
// | i = CST { Int(i, $loc) }
// | s = STR { Str(s, $loc) }
// | TRUE    { Bool(true, $loc)}
// | FALSE   { Bool(false, $loc)}
// | NONE    { Non($loc) }
// ;


(*
prog:
| p = list(loc) EOF { p }
;

loc:
| INT id = IDENT SEMICOLON { Def(Gvar(id, $loc)) }
| INT f = IDENT LP INT x = IDENT RP LB body = list(loc) RB { Def(Gfun(f, x, body, $loc)) }
| id = IDENT EQ e = expr SEMICOLON { Stmt(Set(id, e, $loc)) }
| f = IDENT LP e = expr RP SEMICOLON { Stmt(StmtFunc(f, e, $loc)) }
| RET e = expr SEMICOLON { Stmt(Return(e, $loc)) }
// | READ id = IDENT RP { Stmt(StmtRead(id, $loc)) }
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

*)