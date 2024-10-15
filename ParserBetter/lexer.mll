{
  open Lexing
  open Parser
   
  exception Lexing_error of char

  (* Sert à récupérer les identifiants ou les mots clef qui pourraient être des id*)
  let id_or_kwd s = match s with
  | "for" -> FOR
  | "while" -> WHILE
  | "return" -> RETURN

  | "false" -> FALSE
  | "true" -> TRUE

  | "if" -> IF
  | "else" -> ELSE

  | "int" -> TYPE "int"

  | s -> IDENT s  
}

let letter = ['a'-'z' 'A'-'Z' '_']
let digit = ['0'-'9']
let ident = letter (letter | digit)*
let space = [' ' '\t']


rule token = parse
  | '\n'    { new_line lexbuf; token lexbuf }
  | space+  { token lexbuf }
  | ident as id { id_or_kwd id }
  | digit+ as d { CST (int_of_string d) }
  | ';'      { SEMICOLON }
  (* | ','      { COMMA } *)
  | '{'      { LB }
  | '}'      { RB }
  | '('      { LP }
  | ')'      { RP }

  | '!''='   { NEQ }
  | '=''='   { EQQ }
  | '='      { EQ }
  | '<''='   { LEQ }
  | '>''='   { GEQ }
  | '<'      { LE }
  | '>'      { GE }

  | '*'      { MULT }
  | '+'      { PLUS }
  | '-'      { MINUS }
  | '/'      { DIV }
  | '%'      { MOD }

  | '&''&'   { AND }
  | '|''|'   { OR }
  | '!'      { NOT }

  (* | '^'      { XOR } *)
  (* | '~'      { INV } *)

  | eof      { EOF }
  | _ as c   { raise (Lexing_error c) }
 

