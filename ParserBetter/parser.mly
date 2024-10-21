%{
  open Ast
%}

%token SEMICOLON COMMA COLON QMARK
%token EOF
%token LB RB LP RP LBR RBR
// { } ( ) [ ] 
%token <string> TYPE
%token <string> IDENT
%token <int> CST
%token TRUE FALSE

%token FOR WHILE
%token IF ELSE
%token RETURN

%token EQ PLUSEQ MINUSEQ MULTEQ DIVEQ MODEQ

%token AMPERSAND STAR DOT ARROW

%token PLUSPLUS MINUSMINUS
%token XOR BOR BAND INV LSHIFT RSHIFT
%token OR AND NOT
%token LE LEQ GE GEQ EQQ NEQ
%token PLUS MINUS MULT DIV MOD

%token PRIO1 PRIO2

/***********************************/
/*                                 */
/*       DEFINING PRIORITIES       */
/*                                 */
/***********************************/

// https://en.cppreference.com/w/cpp/language/operator_precedence
// https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B

%left OR
%left AND
%left BOR
%left XOR
%left BAND
%nonassoc EQQ NEQ
%nonassoc LE LEQ GE GEQ
%left LSHIFT RSHIFT
%left PLUS MINUS 
%left MULT DIV MOD
%nonassoc PRIO2
// UMINUS NOT INV PTR AMPERSAND
%left PRIO1
// PLUSPLUS MINUSMINUS PIPE DOT

/* GRAMMARY START */
%start prog


%type <Ast.program> prog

%%

prog:
  | p = list(global_stmt) EOF { p }
;

data_type:
  | t = TYPE { t }
  | t = TYPE STAR { t ^ "*" }
;

global_stmt:
  | t = data_type id = IDENT SEMICOLON { GVarDef(t,id, $loc) }
  | t = data_type id = IDENT EQ e = expr SEMICOLON { GVarDefS(t,id,e, $loc) }
  | t = data_type f = IDENT LP args = separated_list(COMMA, arg) RP body = stmt 
    { GFunDef(t,f,args,body, $loc) }
;

arg:
  | t = data_type id = IDENT { Arg(t,id, $loc) }
;

left_value:
  | s = IDENT { Var(s, $loc) }
  | l = left_value LBR e = expr RBR { Tab(l,e,$loc) }
;

stmt:
  | LB body = list(stmt) RB { Sscope(body,$loc) }
  | RETURN e = expr SEMICOLON { Sreturn(e, $loc) }
  | RETURN SEMICOLON { SreturnVoid($loc) }

  | FOR LP s1 = stmt SEMICOLON cond = expr SEMICOLON s2 = stmt RP body = stmt  
    { Sfor(s1,cond,s2,body,$loc) }
  | WHILE LP cond = expr RP body = stmt { Swhile(cond, body,$loc) }

  | t = data_type id = IDENT SEMICOLON { SvarDef(t,id, $loc) }
  | t = data_type id = IDENT EQ e = expr SEMICOLON { SvarDefS(t,id,e, $loc) }
  | id = left_value o = assignop e = expr SEMICOLON { SvarSet(id,o,e, $loc) }
  | e = expr SEMICOLON { Sexpr(e, $loc) }

  | IF LP e = expr RP body = stmt { Sif(e,body,$loc) }
  | IF LP e = expr RP body1 = stmt ELSE body2 = stmt { SifElse(e,body1,body2,$loc) }
;

litteral:
  | x = CST { Int(x, $loc) }
  | TRUE { Bool(true, $loc) }
  | FALSE { Bool(false, $loc) }
;

expr:
| x = litteral { Const(x, $loc) }
| x = left_value { VarGet(x, $loc) }
| x = IDENT LP args = separated_list(COMMA,expr) RP { FunCall(x,args, $loc) }
| LP e = expr RP { e }

| x = left_value PLUSPLUS %prec PRIO1 {LeftValOp(POSTINCR,x, $loc)}
| x = left_value MINUSMINUS %prec PRIO1 {LeftValOp(POSTDECR,x, $loc)}

// | x = expr DOT %prec PRIO1 { Uniop(StructGet,x, $loc) }
// | x = expr ARROW %prec PRIO1 { Uniop(StructPtrGet,x, $loc) }

| PLUSPLUS x = left_value %prec PRIO2 { LeftValOp(PREINCR,x, $loc) }
| MINUSMINUS x = left_value %prec PRIO2 { LeftValOp(PREDECR,x, $loc) }
| AMPERSAND x = left_value %prec PRIO2 { LeftValOp(GetAdress,x, $loc) }

| STAR x = expr %prec PRIO2  { Uniop(Dereference,x, $loc) }
| MINUS x = expr %prec PRIO2 { Uniop(Neg,x, $loc) }
| NOT x = expr %prec PRIO2 { Uniop(Not,x, $loc) }
| INV x = expr %prec PRIO2 { Uniop(Inv,x, $loc) }

| e1 = expr STAR e2 = expr %prec MULT { Binop(Mul,e1,e2, $loc) }
| e1 = expr AMPERSAND e2 = expr %prec BAND { Binop(BAnd,e1,e2, $loc) }

| e1 = expr o = binop e2 = expr { Binop(o,e1,e2, $loc) }
| e = expr QMARK e1 = expr COLON e2 = expr { Ternop(e,e1,e2, $loc) }
;


%inline binop:
  | PLUS  { Add }
  | MINUS { Sub }
  | DIV   { Div }
  | MOD   { Mod }

  | LEQ   { Leq }
  | GEQ   { Geq }
  | GE    { Ge  }
  | LE    { Le  }
  | NEQ   { Neq }
  | EQQ   { IsEq  }

  | AND   { And }
  | OR    { Or  } 

  | LSHIFT { Lshift }
  | RSHIFT { Rshift }
  | XOR    { Xor } 
  | BOR    { BOr  }
;

%inline assignop:
| EQ    { Eq }
| PLUSEQ { AddEq }
| MINUSEQ { SubEq }
| MULTEQ { MulEq }
| DIVEQ { DivEq }
| MODEQ { ModEq }
;