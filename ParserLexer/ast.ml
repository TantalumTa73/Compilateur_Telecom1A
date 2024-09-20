open Yojson

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

let pos ((s,e):ppos) =
  [ "start_line",`Int s.pos_lnum ;
    "start_char",`Int (s.pos_cnum-s.pos_bol) ;
    "end_line",`Int e.pos_lnum ;
    "end_char",`Int (e.pos_cnum-e.pos_bol) ]

let rec toJSONexpr = function
  | ExprSingle(t, p) ->   `Assoc (["type", `String "expr-single" ; 
                                   "term", toJSONterm t] @ pos p)
  | ExprDouble(t, operator, e, p) -> `Assoc (["type", `String "expr-double" ;
                                           "term", toJSONterm t ;
                                           "operator", `String operator ;
                                           "expr", toJSONexpr e] @ pos p)
and toJSONterm = function
  | TermSingle(f, p) -> `Assoc (["type", `String "term-single" ;
                                 "factor", toJSONfactor f] @ pos p)
  | TermDouble(f, operator, t, p) -> `Assoc (["type", `String "term-double" ;
                                              "factor", toJSONfactor f ;
                                              "operator", `String operator ;
                                              "term", toJSONterm t] @ pos p) 
and toJSONfactor = function
  | Cst(c, p) -> `Assoc (["type", `String "cst" ;
                          "value", `Int c] @ pos p)
  | Parenthesis(expr, p) -> `Assoc (["type", `String "cst" ;
                                     "inner", toJSONexpr expr] @ pos p) 
                             
let toJSONstmt = function
  | Set(varname, e, p) -> `Assoc (["action",`String "varset";
                               "name", `String varname;
                               "expr", toJSONexpr e ] @
                                pos p)

let toJSONdef = function
  | Gvar(name, p)  -> `Assoc (["action",`String "gvardef";
                               "name", `String name ] @
                                pos p)
  | Gfun(name, arg, body, p)  -> `Assoc (["action",`String "gfundef";
                                    "name", `String name ;
                                    "arg", `String arg; 
                                    "body", `List (List.map toJSONstmt body) ] @
                                pos p)

     
                 
let toJSON (p:program) : Yojson.t =
  `List (List.map toJSONdef p)


  
