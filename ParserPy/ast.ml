(* Syntaxe abstraite pour le langage ppython *)

type ppos = Lexing.position * Lexing.position

type program = global_stmt list
 and global_stmt =
   | GFunDef of string * string list * stmt * ppos
   | Gstmt of stmt * ppos
and stmt =  
  | Sfor of string*expr*stmt * ppos
  | Sblock of stmt list  * ppos
  | Sreturn of expr * ppos
  | Sassign of left_value*expr * ppos
  | Sval of expr * ppos
  | Sif of expr*stmt*ppos
  | Selif of expr*stmt*ppos
  | Selse of stmt*ppos
  | Swhile of expr*stmt*ppos
and const = 
  | Int of string * ppos
  | Str of string * ppos
  | Bool of bool * ppos
  | Non of ppos

and left_value = 
  | Tab of left_value*expr * ppos
  | Var of string * ppos

and expr =
  | Const of const * ppos
  | Val of left_value *  ppos
  | Moins of expr * ppos
  | Not of expr * ppos
  | Op of binop * expr*expr * ppos
  | List of expr list * ppos
  | Ecall of string*expr list * ppos
and binop = Add | Sub | Mul | Div | Mod | Leq | Le | Geq | Ge | Neq | Eq | And | Or

let str_op = function
  | Add -> "Add"
  | Sub -> "Sub"
  | Mul -> "Mul"
  | Div -> "Div"
  | Mod -> "Mod"
  | Leq -> "<="
  | Le -> "<"
  | Geq -> ">="
  | Ge -> ">"
  | Neq -> "!="
  | Eq -> "=="
  | And -> "&&"
  | Or -> "||"
