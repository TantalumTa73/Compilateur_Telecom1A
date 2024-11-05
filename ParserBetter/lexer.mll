{
  open Lexing
  open Parser
   
  exception Lexing_error of char
  exception SyntaxError of string

  (* Find keyword and identifiers *)
  let id_or_kwd s = match s with
  | "if" -> IF
  | "else" -> ELSE

  | "for" -> FOR
  | "while" -> WHILE

  | "return" -> RETURN
  | "break" -> BREAK
  | "continue" -> CONTINUE

  | "const" -> CONST
  | "inline" -> INLINE
  | "struct" -> STRUCT

  | "false" -> FALSE
  | "true" -> TRUE
  | "NULL" -> NULL


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
  | "//" { single_line_comment lexbuf }
  | "/*" { multi_line_comment lexbuf }
  | '#'[^'\n']* { token lexbuf }
  | '\n'    { new_line lexbuf; token lexbuf }
  | space+  { token lexbuf }
  
  | '\"' ([^'\"']* as s) '\"' { STRING s }
  | '\'' (_ as c) '\'' { CHAR c }

  | int as n
  | binary as n 
  | hexadecimal as n { LITTERAL (int_of_string n) }
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
  | '?'      { QMARK }
  | ':'      { COLON }
  

  | eof      { EOF }
  | _ as c   { raise (Lexing_error c) }

and single_line_comment = parse
  | '\n' { new_line lexbuf; token lexbuf }
  | eof { EOF }
  | _ { single_line_comment lexbuf }

and multi_line_comment = parse
  | "*/" { token lexbuf }
  | '\n' { new_line lexbuf; multi_line_comment lexbuf }
  | eof { raise (SyntaxError ("Lexer - Unexpected EOF - please terminate your comment.")) }
  | _ { multi_line_comment lexbuf }
