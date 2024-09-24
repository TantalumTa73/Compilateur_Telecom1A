type ppos = Lexing.position * Lexing.position

type program = loc list 

and gdef =
  | Gvar of string*ppos
  | Gfun of string*string*loc list*ppos

and stmt =
  | Set of string * expr * ppos
  | StmtFunc of string * expr * ppos
  | StmtRead of string * ppos 
  | Return of expr * ppos

and expr =
  | ExprSingle of term*ppos
  | ExprDouble of expr*string*term*ppos
  | ExprFunc of string*expr*ppos

and term =
  | TermSingle of factor*ppos
  | TermDouble of term*string*factor*ppos

and factor =
  | Cst of int*ppos
  | Var of string*ppos
  | Minus of factor*ppos
  | Parenthesis of expr*ppos

and loc = 
  | Stmt of stmt
  | Def of gdef

val toJSON : program -> Yojson.t
  
