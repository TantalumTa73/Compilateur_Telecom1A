type ppos = Lexing.position * Lexing.position

type program = gdef list 

and gdef =
  | Gvar of string*ppos
  | Gfun of string*string*stmt list*ppos

and stmt =
  | Set of string * expr * ppos

and expr =
  | Cst of int * ppos

val toJSON : program -> Yojson.t
  
