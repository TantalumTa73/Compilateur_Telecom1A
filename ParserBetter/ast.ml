open Yojson

type ppos = Lexing.position * Lexing.position

type program = 
  global_stmt list

and global_stmt =
  | GFunDef of string * string * arg list * stmt * ppos
  | GVarDef of string * string * int * expr option * ppos

and arg =
  | Arg of string * string * ppos

and stmt =  
  | Sscope of stmt list  * ppos
  | Sreturn of expr option * ppos
  (* | SreturnVoid of ppos *)

  | Sfor of stmt * expr * stmt * stmt * ppos (* s1 ; cond ; s2 {} *)
  | Swhile of expr * stmt * ppos

  (* | SvarDef of string * string * ppos *)
  | SvarDef of string * string * int * expr option * ppos
  | SvarSet of left_value * assingop * expr * ppos
  | Sexpr of expr * ppos

  | Skeyword of string * ppos

  | Sif of expr * stmt * ppos
  | SifElse of expr * stmt * stmt * ppos

and litteral = 
  | Void of ppos
  | Int of int * ppos
  | Bool of bool * ppos
  | Char of char * ppos
  | String of string * ppos

and left_value = 
  | ArrayGet of left_value * expr * ppos
  | VarGet of string * ppos
  | LLop of llop * left_value * ppos
  | RLop of rlop * expr * ppos

and expr =
  | Litteral of litteral * ppos
  | ValueGet of left_value * ppos
  | List of expr list * ppos
  | FunCall of string * expr list * ppos

  | LRop of lrop * left_value * ppos
  | Uniop of uniop * expr * ppos
  | Binop of binop * expr * expr * ppos
  | Ternop of expr * expr * expr * ppos

(**************************)
(*        OPERATOR        *)
(**************************)
(*
  A left value is a value that can be assigned to.
  A right value is a value that cannot be assigned to.

  LeftVal are left values
  Litteral, List, FunCall are right values

  LLop are operators : Left Value -> Left Value
  LRop are operators : Left Value -> Right Value
  RLop are operators : Right Value -> Left Value
  
  We will assume that you cannot modify the inner
  value of a right value `{1}.x`.

  We will also assume that you cannot get a left
  value with a ternary operator `cond ? x : y = 1 ;`.
*)

and llop =
  | PreIncr
  | PreDecr
  | StructGet 
  | StructPtrGet

and lrop =
  | PostIncr
  | PostDecr
  | GetAddress

and rlop =
  | Dereference

and uniop =
  | Neg 
  | Not
  | Inv

and binop = 
  Add | Sub | Mul | Div | Mod | 
  Leq | Le | Geq | Ge | Neq | IsEq | 
  And | Or | 
  BitXor |  BitAnd | BitOr |
  Lshift | Rshift
  
and assingop =
  | Eq
  | AddEq
  | SubEq
  | MulEq
  | DivEq
  | ModEq



  
