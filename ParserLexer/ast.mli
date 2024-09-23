type ppos = Lexing.position * Lexing.position

type program = gdef list 

and gdef =
  | Gvar of string*ppos
  | Gfun of string*string*stmt list*ppos

and stmt =
  | Set of string * expr * ppos

and expr =
  | ExprSingle of term*ppos
  | ExprDouble of expr*string*term*ppos

and term =
  | TermSingle of factor*ppos
  | TermDouble of term*string*factor*ppos

and factor =
  | Cst of int*ppos
  | Parenthesis of expr*ppos



val toJSON : program -> Yojson.t
  
