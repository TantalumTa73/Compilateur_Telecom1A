type ppos = Lexing.position * Lexing.position

type program = gdef list 

and gdef =
  | Gvar of string*ppos
  | Gfun of string*string*stmt list*ppos

and stmt =
  | Set of string * expr * ppos

and expr =
  | ExprSingle of term*ppos
  | ExprDouble of term*string*expr*ppos

and term =
  | TermSingle of factor*ppos
  | TermDouble of factor*string*term*ppos

and factor =
  | Cst of int*ppos
  | Parenthesis of expr*ppos



val toJSON : program -> Yojson.t
  
