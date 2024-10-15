open Yojson

type ppos = Lexing.position * Lexing.position

type program = 
  global_stmt list

and global_stmt =
  | GFunDef of string * string * formal list * stmt * ppos
  | GVarDef of string * string * ppos
  | GVarDefS of string * string * expr * ppos

and formal =
  | Formal of string * string

and stmt =  
  | Sscope of stmt list  * ppos
  | Sreturn of expr * ppos

  | Sfor of string * expr * stmt * ppos
  | Swhile of expr * stmt * ppos

  | SvarDef of string * string * ppos
  | SvarDefS of string * string * expr * ppos
  | SvarSet of left_value * expr * ppos
  | Sexpr of expr * ppos

  | Sif of expr*stmt*ppos
  | SifElse of expr*stmt*stmt*ppos

and litteral = 
  | Int of int * ppos
  | Char of string * ppos
  | Bool of bool * ppos

and left_value = 
  | Tab of left_value*expr * ppos
  | Var of string * ppos

and expr =
  | Const of litteral * ppos
  | VarGet of left_value * ppos
  | List of expr list * ppos
  | FunCall of string * expr list * ppos

  | Uniop of uniop * expr * ppos
  | Binop of binop * expr * expr * ppos

and binop = 
  Add | Sub | Mul | Div | Mod | 
  Leq | Le | Geq | Ge | Neq | Eq | 
  And | Or | Xor

and uniop =
  | Neg 
  | Not
  | Inv

let str_binop = function
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
  | Xor -> "^"

let str_uniop = function
  | Neg -> "-"
  | Not -> "!"
  | Inv -> "~"

let pos ((s,e):ppos) =
  [ "start_line",`Int s.pos_lnum ;
    "start_char",`Int (s.pos_cnum-s.pos_bol) ;
    "end_line",`Int e.pos_lnum ;
    "end_char",`Int (e.pos_cnum-e.pos_bol) ]

let rec toJSONexpr = function
  | Const(c, p) -> `Assoc ([
    "type", `String "const" ;
    "value", toJSONlitteral c ] @ pos p)
  | VarGet(lv, p) -> `Assoc ([
    "type", `String "var_get" ;
    "value", toJSONleft_value lv ] @ pos p)
  | List(l, p) -> `Assoc ([
    "type", `String "list" ;
    "content", `List (List.map toJSONexpr l) ] @ pos p)
  | FunCall(f, l, p) -> `Assoc ([
    "type", `String "fun_call" ;
    "name", `String f ;
    "args", `List (List.map toJSONexpr l) ] @ pos p)
  | Uniop(o, e, p) -> `Assoc ([
    "type", `String "uniop" ;
    "uniop", `String (str_uniop o) ;
    "value", toJSONexpr e ] @ pos p)
  | Binop(o, e1, e2, p) -> `Assoc ([
    "type", `String "binop" ;
    "binop", `String (str_binop o) ;
    "v1", toJSONexpr e1 ;
    "v2", toJSONexpr e2 ] @ pos p)

and toJSONlitteral = function
  | Int(i, p) -> `Assoc ([
    "type", `String "int" ;
    "value", `Int i ] @ pos p)
  | Char(s, p) -> `Assoc ([
    "type", `String "char" ;
    "value", `String s ] @ pos p)
  | Bool(b, p) -> `Assoc ([
    "type", `String "bool" ;
    "value", `Bool b ] @ pos p)

                          
and toJSONstmt = function
  | Sscope(l, p) -> `Assoc ([
    "type", `String "scope" ;
    "body", `List (List.map toJSONstmt l) ] @ pos p)
  | Sreturn(e, p) -> `Assoc ([
    "type", `String "return" ;
    "value", toJSONexpr e ] @ pos p)
  | Sfor(v, e, s, p) -> `Assoc ([
    "type", `String "for" ;
    "varname", `String v ;
    "in_set", toJSONexpr e ;
    "body", toJSONstmt s ] @ pos p)
  | Swhile(e, s, p) -> `Assoc ([
    "type", `String "while" ;
    "condition", toJSONexpr e ;
    "body", toJSONstmt s ] @ pos p)
  | SvarDef(t, n, p) -> `Assoc ([
    "type", `String "vardef" ;
    "var_type", `String t ;
    "name", `String n ;
    "value", `String "" ] @ pos p)
  | SvarDefS(t, n, e, p) -> `Assoc ([
    "type", `String "vardef" ;
    "var_type", `String t ;
    "name", `String n ;
    "value", toJSONexpr e ] @ pos p)
  | SvarSet(l, e, p) -> `Assoc ([
    "type", `String "varset" ;
    "left_value", toJSONleft_value l ;
    "value", toJSONexpr e ] @ pos p)
  | Sexpr(e, p) -> `Assoc ([
    "type", `String "expr" ;
    "value", toJSONexpr e ] @ pos p)
  | Sif(e, s, p) -> `Assoc ([
    "type", `String "if" ;
    "condition", toJSONexpr e ;
    "body", toJSONstmt s ] @ pos p)
  | SifElse(e, s1, s2, p) -> `Assoc ([
    "type", `String "if_else" ;
    "condition", toJSONexpr e ;
    "body", toJSONstmt s1 ;
    "else", toJSONstmt s2 ] @ pos p)
  

and toJSONgstmt = function
  | GFunDef(t,n, a, b, p) -> `Assoc ([
    "type", `String "fundef" ;
    "return_type", `String t ;
    "name", `String n ;
    (* "args", `List (List.map (fun x -> `String x) a) ; *)
    "body", toJSONstmt b ] @ pos p)
  | GVarDef(t, n, p) -> `Assoc ([
    "type", `String "vardef" ;
    "var_type", `String t ;
    "name", `String n ;
    "value", `String "" ] @ pos p)
  | GVarDefS(t, n, e, p) -> `Assoc ([
    "type", `String "vardef" ;
    "var_type", `String t ;
    "name", `String n ;
    "value", toJSONexpr e ] @ pos p)

and toJSONleft_value = function
  | Var(n, p) -> `Assoc ([
    "type", `String "var" ;
    "name", `String n ] @ pos p)
  | Tab(l, e, p) -> `Assoc ([
    "type", `String "tab" ;
    "left_value", toJSONleft_value l ;
    "index", toJSONexpr e ] @ pos p)

     
                 
let toJSON (p:program) : Yojson.t =
  `List (List.map toJSONgstmt p)


  
