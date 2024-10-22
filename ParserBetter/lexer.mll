{
  open Lexing
  open Parser
   
  exception Lexing_error of char

  (* Find keyword and identifiers *)
  let id_or_kwd s = match s with
  | "for" -> FOR
  | "while" -> WHILE
  | "return" -> RETURN

  | "false" -> FALSE
  | "true" -> TRUE

  | "if" -> IF
  | "else" -> ELSE

  | "void" -> TYPE "void"
  | "int" -> TYPE "int"
  | "char" -> TYPE "char"
  | "bool" -> TYPE "bool"

  | s -> IDENT s  
}

let letter = ['a'-'z' 'A'-'Z' '_']
let digit = ['0'-'9']
let int = digit+
let float = digit+ '.' digit+
let binary = '0''b' ['0' '1']+
let hexadecimal = '0''x' ['0'-'9' 'a'-'f' ]+
let ident = letter (letter | digit)*
let space = [' ' '\t']

rule token = parse
  | '/''/'[^'\n']* { token lexbuf }
  | '#'[^'\n']* { token lexbuf }
  | '\n'    { new_line lexbuf; token lexbuf }
  | space+  { token lexbuf }
  | '\"' ([^'\"']* as s) '\"' { STRING s }
  | '\'' (_ as c) '\'' { CHAR c }
  | int as n
  | binary as n 
  | hexadecimal as n { CST (int_of_string n) }
  | ident as id { id_or_kwd id }

  | ';'      { SEMICOLON }
  | ','      { COMMA }
  | '{'      { LB }
  | '}'      { RB }
  | '('      { LP }
  | ')'      { RP }
  | '['      { LBR }
  | ']'      { RBR }

  | '<''<'     { LSHIFT }
  | '>''>'     { RSHIFT }

  | '+''+'   { PLUSPLUS }
  | '-''-'   { MINUSMINUS }

  | '+''='   { PLUSEQ }
  | '-''='   { MINUSEQ }
  | '*''='   { MULTEQ }
  | '/''='   { DIVEQ }
  | '%''='   { MODEQ }

  | '!''='   { NEQ }
  | '=''='   { EQQ }
  | '<''='   { LEQ }
  | '>''='   { GEQ }

  | '-''>'   { ARROW }
  | '&''&'   { AND }
  | '|''|'   { OR }

  | '='      { EQ }
  | '<'      { LE }
  | '>'      { GE }

  | '+'      { PLUS }
  | '-'      { MINUS }
  | '/'      { DIV }
  | '%'      { MOD }

  | '!'      { NOT }
  | '~'      { INV }
  | '^'      { XOR }
  | '|'      { BOR }

  | '&'      { AMPERSAND }
  | '*'      { STAR }
  | '.'      { DOT }
  

  | eof      { EOF }
  | _ as c   { raise (Lexing_error c) }
 

