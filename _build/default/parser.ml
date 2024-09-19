
module MenhirBasics = struct
  
  exception Error
  
  let _eRR =
    fun _s ->
      raise Error
  
  type token = 
    | SEMICOLON
    | RP
    | RB
    | LP
    | LB
    | INT
    | IDENT of (
# 8 "parser.mly"
       (string)
# 21 "parser.ml"
  )
    | EQ
    | EOF
    | CST of (
# 9 "parser.mly"
       (int)
# 28 "parser.ml"
  )
  
end

include MenhirBasics

# 1 "parser.mly"
  
  open Ast

# 39 "parser.ml"

type ('s, 'r) _menhir_state = 
  | MenhirState00 : ('s, _menhir_box_prog) _menhir_state
    (** State 00.
        Stack shape : .
        Start symbol: prog. *)

  | MenhirState08 : (('s, _menhir_box_prog) _menhir_cell1_INT _menhir_cell0_IDENT _menhir_cell0_INT _menhir_cell0_IDENT, _menhir_box_prog) _menhir_state
    (** State 08.
        Stack shape : INT IDENT INT IDENT.
        Start symbol: prog. *)

  | MenhirState14 : (('s, _menhir_box_prog) _menhir_cell1_stmt, _menhir_box_prog) _menhir_state
    (** State 14.
        Stack shape : stmt.
        Start symbol: prog. *)

  | MenhirState21 : (('s, _menhir_box_prog) _menhir_cell1_def, _menhir_box_prog) _menhir_state
    (** State 21.
        Stack shape : def.
        Start symbol: prog. *)


and ('s, 'r) _menhir_cell1_def = 
  | MenhirCell1_def of 's * ('s, 'r) _menhir_state * (Ast.gdef)

and ('s, 'r) _menhir_cell1_stmt = 
  | MenhirCell1_stmt of 's * ('s, 'r) _menhir_state * (Ast.stmt)

and ('s, 'r) _menhir_cell1_IDENT = 
  | MenhirCell1_IDENT of 's * ('s, 'r) _menhir_state * (
# 8 "parser.mly"
       (string)
# 73 "parser.ml"
) * Lexing.position

and 's _menhir_cell0_IDENT = 
  | MenhirCell0_IDENT of 's * (
# 8 "parser.mly"
       (string)
# 80 "parser.ml"
) * Lexing.position

and ('s, 'r) _menhir_cell1_INT = 
  | MenhirCell1_INT of 's * ('s, 'r) _menhir_state * Lexing.position

and 's _menhir_cell0_INT = 
  | MenhirCell0_INT of 's * Lexing.position

and _menhir_box_prog = 
  | MenhirBox_prog of (Ast.program) [@@unboxed]

let _menhir_action_01 =
  fun _endpos__3_ _startpos__1_ id ->
    let _endpos = _endpos__3_ in
    let _startpos = _startpos__1_ in
    let _loc = (_startpos, _endpos) in
    (
# 24 "parser.mly"
                           ( Gvar(id, _loc) )
# 100 "parser.ml"
     : (Ast.gdef))

let _menhir_action_02 =
  fun _endpos__9_ _startpos__1_ body f x ->
    let _endpos = _endpos__9_ in
    let _startpos = _startpos__1_ in
    let _loc = (_startpos, _endpos) in
    (
# 25 "parser.mly"
                                                            ( Gfun(f, x, body, _loc)  )
# 111 "parser.ml"
     : (Ast.gdef))

let _menhir_action_03 =
  fun _endpos_c_ _startpos_c_ c ->
    let _endpos = _endpos_c_ in
    let _startpos = _startpos_c_ in
    let _loc = (_startpos, _endpos) in
    (
# 34 "parser.mly"
          ( Cst(c, _loc))
# 122 "parser.ml"
     : (Ast.expr))

let _menhir_action_04 =
  fun () ->
    (
# 216 "<standard.mly>"
    ( [] )
# 130 "parser.ml"
     : (Ast.program))

let _menhir_action_05 =
  fun x xs ->
    (
# 219 "<standard.mly>"
    ( x :: xs )
# 138 "parser.ml"
     : (Ast.program))

let _menhir_action_06 =
  fun () ->
    (
# 216 "<standard.mly>"
    ( [] )
# 146 "parser.ml"
     : (Ast.stmt list))

let _menhir_action_07 =
  fun x xs ->
    (
# 219 "<standard.mly>"
    ( x :: xs )
# 154 "parser.ml"
     : (Ast.stmt list))

let _menhir_action_08 =
  fun p ->
    (
# 20 "parser.mly"
                    ( p )
# 162 "parser.ml"
     : (Ast.program))

let _menhir_action_09 =
  fun _endpos__4_ _startpos_id_ e id ->
    let _endpos = _endpos__4_ in
    let _startpos = _startpos_id_ in
    let _loc = (_startpos, _endpos) in
    (
# 30 "parser.mly"
                                   ( Set(id,e, _loc) )
# 173 "parser.ml"
     : (Ast.stmt))

let _menhir_print_token : token -> string =
  fun _tok ->
    match _tok with
    | CST _ ->
        "CST"
    | EOF ->
        "EOF"
    | EQ ->
        "EQ"
    | IDENT _ ->
        "IDENT"
    | INT ->
        "INT"
    | LB ->
        "LB"
    | LP ->
        "LP"
    | RB ->
        "RB"
    | RP ->
        "RP"
    | SEMICOLON ->
        "SEMICOLON"

let _menhir_fail : unit -> 'a =
  fun () ->
    Printf.eprintf "Internal failure -- please contact the parser generator's developers.\n%!";
    assert false

include struct
  
  [@@@ocaml.warning "-4-37"]
  
  let _menhir_run_19 : type  ttv_stack. ttv_stack -> _ -> _menhir_box_prog =
    fun _menhir_stack _v ->
      let p = _v in
      let _v = _menhir_action_08 p in
      MenhirBox_prog _v
  
  let rec _menhir_run_22 : type  ttv_stack. (ttv_stack, _menhir_box_prog) _menhir_cell1_def -> _ -> _menhir_box_prog =
    fun _menhir_stack _v ->
      let MenhirCell1_def (_menhir_stack, _menhir_s, x) = _menhir_stack in
      let xs = _v in
      let _v = _menhir_action_05 x xs in
      _menhir_goto_list_def_ _menhir_stack _v _menhir_s
  
  and _menhir_goto_list_def_ : type  ttv_stack. ttv_stack -> _ -> (ttv_stack, _menhir_box_prog) _menhir_state -> _menhir_box_prog =
    fun _menhir_stack _v _menhir_s ->
      match _menhir_s with
      | MenhirState21 ->
          _menhir_run_22 _menhir_stack _v
      | MenhirState00 ->
          _menhir_run_19 _menhir_stack _v
      | _ ->
          _menhir_fail ()
  
  let rec _menhir_run_01 : type  ttv_stack. ttv_stack -> _ -> _ -> (ttv_stack, _menhir_box_prog) _menhir_state -> _menhir_box_prog =
    fun _menhir_stack _menhir_lexbuf _menhir_lexer _menhir_s ->
      let _startpos = _menhir_lexbuf.Lexing.lex_start_p in
      let _tok = _menhir_lexer _menhir_lexbuf in
      match (_tok : MenhirBasics.token) with
      | IDENT _v ->
          let _startpos_0 = _menhir_lexbuf.Lexing.lex_start_p in
          let _tok = _menhir_lexer _menhir_lexbuf in
          (match (_tok : MenhirBasics.token) with
          | SEMICOLON ->
              let _endpos = _menhir_lexbuf.Lexing.lex_curr_p in
              let _tok = _menhir_lexer _menhir_lexbuf in
              let (_endpos__3_, id, _startpos__1_) = (_endpos, _v, _startpos) in
              let _v = _menhir_action_01 _endpos__3_ _startpos__1_ id in
              _menhir_goto_def _menhir_stack _menhir_lexbuf _menhir_lexer _v _menhir_s _tok
          | LP ->
              let _menhir_stack = MenhirCell1_INT (_menhir_stack, _menhir_s, _startpos) in
              let _menhir_stack = MenhirCell0_IDENT (_menhir_stack, _v, _startpos_0) in
              let _tok = _menhir_lexer _menhir_lexbuf in
              (match (_tok : MenhirBasics.token) with
              | INT ->
                  let _startpos_1 = _menhir_lexbuf.Lexing.lex_start_p in
                  let _menhir_stack = MenhirCell0_INT (_menhir_stack, _startpos_1) in
                  let _tok = _menhir_lexer _menhir_lexbuf in
                  (match (_tok : MenhirBasics.token) with
                  | IDENT _v_2 ->
                      let _startpos_3 = _menhir_lexbuf.Lexing.lex_start_p in
                      let _menhir_stack = MenhirCell0_IDENT (_menhir_stack, _v_2, _startpos_3) in
                      let _tok = _menhir_lexer _menhir_lexbuf in
                      (match (_tok : MenhirBasics.token) with
                      | RP ->
                          let _tok = _menhir_lexer _menhir_lexbuf in
                          (match (_tok : MenhirBasics.token) with
                          | LB ->
                              let _tok = _menhir_lexer _menhir_lexbuf in
                              (match (_tok : MenhirBasics.token) with
                              | IDENT _v_4 ->
                                  _menhir_run_09 _menhir_stack _menhir_lexbuf _menhir_lexer _v_4 MenhirState08
                              | RB ->
                                  let _v_5 = _menhir_action_06 () in
                                  _menhir_run_16 _menhir_stack _menhir_lexbuf _menhir_lexer _v_5
                              | _ ->
                                  _eRR ())
                          | _ ->
                              _eRR ())
                      | _ ->
                          _eRR ())
                  | _ ->
                      _eRR ())
              | _ ->
                  _eRR ())
          | _ ->
              _eRR ())
      | _ ->
          _eRR ()
  
  and _menhir_goto_def : type  ttv_stack. ttv_stack -> _ -> _ -> _ -> (ttv_stack, _menhir_box_prog) _menhir_state -> _ -> _menhir_box_prog =
    fun _menhir_stack _menhir_lexbuf _menhir_lexer _v _menhir_s _tok ->
      let _menhir_stack = MenhirCell1_def (_menhir_stack, _menhir_s, _v) in
      match (_tok : MenhirBasics.token) with
      | INT ->
          _menhir_run_01 _menhir_stack _menhir_lexbuf _menhir_lexer MenhirState21
      | EOF ->
          let _v_0 = _menhir_action_04 () in
          _menhir_run_22 _menhir_stack _v_0
      | _ ->
          _eRR ()
  
  and _menhir_run_09 : type  ttv_stack. ttv_stack -> _ -> _ -> _ -> (ttv_stack, _menhir_box_prog) _menhir_state -> _menhir_box_prog =
    fun _menhir_stack _menhir_lexbuf _menhir_lexer _v _menhir_s ->
      let _startpos = _menhir_lexbuf.Lexing.lex_start_p in
      let _menhir_stack = MenhirCell1_IDENT (_menhir_stack, _menhir_s, _v, _startpos) in
      let _tok = _menhir_lexer _menhir_lexbuf in
      match (_tok : MenhirBasics.token) with
      | EQ ->
          let _tok = _menhir_lexer _menhir_lexbuf in
          (match (_tok : MenhirBasics.token) with
          | CST _v_0 ->
              let _startpos_1 = _menhir_lexbuf.Lexing.lex_start_p in
              let _endpos = _menhir_lexbuf.Lexing.lex_curr_p in
              let _tok = _menhir_lexer _menhir_lexbuf in
              let (_endpos_c_, _startpos_c_, c) = (_endpos, _startpos_1, _v_0) in
              let _v = _menhir_action_03 _endpos_c_ _startpos_c_ c in
              (match (_tok : MenhirBasics.token) with
              | SEMICOLON ->
                  let _endpos = _menhir_lexbuf.Lexing.lex_curr_p in
                  let _tok = _menhir_lexer _menhir_lexbuf in
                  let MenhirCell1_IDENT (_menhir_stack, _menhir_s, id, _startpos_id_) = _menhir_stack in
                  let (_endpos__4_, e) = (_endpos, _v) in
                  let _v = _menhir_action_09 _endpos__4_ _startpos_id_ e id in
                  let _menhir_stack = MenhirCell1_stmt (_menhir_stack, _menhir_s, _v) in
                  (match (_tok : MenhirBasics.token) with
                  | IDENT _v_0 ->
                      _menhir_run_09 _menhir_stack _menhir_lexbuf _menhir_lexer _v_0 MenhirState14
                  | RB ->
                      let _v_1 = _menhir_action_06 () in
                      _menhir_run_15 _menhir_stack _menhir_lexbuf _menhir_lexer _v_1
                  | _ ->
                      _eRR ())
              | _ ->
                  _eRR ())
          | _ ->
              _eRR ())
      | _ ->
          _eRR ()
  
  and _menhir_run_15 : type  ttv_stack. (ttv_stack, _menhir_box_prog) _menhir_cell1_stmt -> _ -> _ -> _ -> _menhir_box_prog =
    fun _menhir_stack _menhir_lexbuf _menhir_lexer _v ->
      let MenhirCell1_stmt (_menhir_stack, _menhir_s, x) = _menhir_stack in
      let xs = _v in
      let _v = _menhir_action_07 x xs in
      _menhir_goto_list_stmt_ _menhir_stack _menhir_lexbuf _menhir_lexer _v _menhir_s
  
  and _menhir_goto_list_stmt_ : type  ttv_stack. ttv_stack -> _ -> _ -> _ -> (ttv_stack, _menhir_box_prog) _menhir_state -> _menhir_box_prog =
    fun _menhir_stack _menhir_lexbuf _menhir_lexer _v _menhir_s ->
      match _menhir_s with
      | MenhirState08 ->
          _menhir_run_16 _menhir_stack _menhir_lexbuf _menhir_lexer _v
      | MenhirState14 ->
          _menhir_run_15 _menhir_stack _menhir_lexbuf _menhir_lexer _v
      | _ ->
          _menhir_fail ()
  
  and _menhir_run_16 : type  ttv_stack. (ttv_stack, _menhir_box_prog) _menhir_cell1_INT _menhir_cell0_IDENT _menhir_cell0_INT _menhir_cell0_IDENT -> _ -> _ -> _ -> _menhir_box_prog =
    fun _menhir_stack _menhir_lexbuf _menhir_lexer _v ->
      let _endpos = _menhir_lexbuf.Lexing.lex_curr_p in
      let _tok = _menhir_lexer _menhir_lexbuf in
      let MenhirCell0_IDENT (_menhir_stack, x, _) = _menhir_stack in
      let MenhirCell0_INT (_menhir_stack, _) = _menhir_stack in
      let MenhirCell0_IDENT (_menhir_stack, f, _) = _menhir_stack in
      let MenhirCell1_INT (_menhir_stack, _menhir_s, _startpos__1_) = _menhir_stack in
      let (_endpos__9_, body) = (_endpos, _v) in
      let _v = _menhir_action_02 _endpos__9_ _startpos__1_ body f x in
      _menhir_goto_def _menhir_stack _menhir_lexbuf _menhir_lexer _v _menhir_s _tok
  
  let _menhir_run_00 : type  ttv_stack. ttv_stack -> _ -> _ -> _menhir_box_prog =
    fun _menhir_stack _menhir_lexbuf _menhir_lexer ->
      let _tok = _menhir_lexer _menhir_lexbuf in
      match (_tok : MenhirBasics.token) with
      | INT ->
          _menhir_run_01 _menhir_stack _menhir_lexbuf _menhir_lexer MenhirState00
      | EOF ->
          let _v = _menhir_action_04 () in
          _menhir_run_19 _menhir_stack _v
      | _ ->
          _eRR ()
  
end

let prog =
  fun _menhir_lexer _menhir_lexbuf ->
    let _menhir_stack = () in
    let MenhirBox_prog v = _menhir_run_00 _menhir_stack _menhir_lexbuf _menhir_lexer in
    v
