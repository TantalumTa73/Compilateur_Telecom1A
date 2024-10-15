(* Syntaxe abstraite pour le langage ppython *)
open Yojson

type program = stmt list

and ppos = Lexing.position*Lexing.position

and stmt = 
| Stmt of stmt_node*ppos


and stmt_node =
| Sif of expr*stmt*stmt
| Sblock of stmt list
| Sreturn of expr
| Sassign of expr*expr
| Sval of expr
| Svardef of string*string
| Sfundef of string*args list*stmt

and left_value =
| Var of string

and expr =
| Const of int
| Val of left_value
| UnOp of expr
| BinOp of binop * expr*expr
| Ecall of string*expr list

and args =
| TypeVar of string*string

and binop = 
| Add 
| Sub 
| Mul 
| Div 
| Mod 
| Leq 
| Le 
| Geq 
| Ge 
| Neq 
| Eq 
| And 
| Or

(* type ppos = Lexing.position * Lexing.position

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
  | Tab of expr*expr * ppos
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
  | Or -> "||" *)
