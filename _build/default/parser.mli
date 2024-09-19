
(* The type of tokens. *)

type token = 
  | SEMICOLON
  | RP
  | RB
  | LP
  | LB
  | INT
  | IDENT of (string)
  | EQ
  | EOF
  | CST of (int)

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val prog: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.program)
