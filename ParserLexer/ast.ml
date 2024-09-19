open Yojson

type ppos = Lexing.position * Lexing.position

type program = gdef list 

and gdef =
  | Gvar of string*ppos
  | Gfun of string*string*stmt list*ppos

and stmt =
  | Set of string * expr * ppos

and expr =
  | Cst of int * ppos

let pos ((s,e):ppos) =
  [ "start_line",`Int s.pos_lnum ;
    "start_char",`Int (s.pos_cnum-s.pos_bol) ;
    "end_line",`Int e.pos_lnum ;
    "end_char",`Int (e.pos_cnum-e.pos_bol) ]

let toJSONexpr = function
  | Cst(c, p) ->   `Assoc (["type", `String "cst" ; "value", `Int c] @ pos p)
                                    
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


  
