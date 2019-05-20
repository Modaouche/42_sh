#ifndef _SHELL_GRM_H_
#define _SHELL_GRM_H_

#include <stdint.h>
#include <stdbool.h>

#define _ONLY_STATE_TOKEN_	
#include "shell.lex.h"
#undef	_ONLY_STATE_TOKEN_

enum {
	N_complete_command,
	N_list,
	N_linebreak,
	N_and_or,
	N_list_PRIME,
	N_separator_op,
	N_list_PRIME_PRIME,
	N_pipeline,
	N_and_or_PRIME,
	N_and_or_op,
	N_bang_opt,
	N_pipe_sequence,
	N_command,
	N_pipe_sequence_PRIME,
	N_newline_list,
	N_newline_list_PRIME,
};

#define TOTAL_NTER	16

enum {
	P_LHS_Ncomplete_command_RHS_Nlist_Nlinebreak,
	P_LHS_Nlist_RHS_Nand_or_Nlist_PRIME,
	P_LHS_Nlist_PRIME_RHS_Nseparator_op_Nlist_PRIME_PRIME,
	P_LHS_Nlist_PRIME_RHS,
	P_LHS_Nlist_PRIME_PRIME_RHS_Nand_or_Nlist_PRIME,
	P_LHS_Nlist_PRIME_PRIME_RHS,
	P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME,
	P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME,
	P_LHS_Nand_or_PRIME_RHS,
	P_LHS_Nand_or_op_RHS_TAND_IF,
	P_LHS_Nand_or_op_RHS_TOR_IF,
	P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence,
	P_LHS_Nbang_opt_RHS_TBANG,
	P_LHS_Nbang_opt_RHS,
	P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME,
	P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME,
	P_LHS_Npipe_sequence_PRIME_RHS,
	P_LHS_Ncommand_RHS_TWORD,
	P_LHS_Nlinebreak_RHS_Nnewline_list,
	P_LHS_Nlinebreak_RHS,
	P_LHS_Nseparator_op_RHS_TAMPER,
	P_LHS_Nseparator_op_RHS_TSEMI,
	P_LHS_Nnewline_list_RHS_TNEWLINE_Nnewline_list_PRIME,
	P_LHS_Nnewline_list_PRIME_RHS_TNEWLINE_Nnewline_list_PRIME,
	P_LHS_Nnewline_list_PRIME_RHS,
};

#define TOTAL_PROD	26

static int
shell_rhs_prod_table[TOTAL_PROD] = {
	[P_LHS_Ncomplete_command_RHS_Nlist_Nlinebreak] = 2,
	[P_LHS_Nlist_RHS_Nand_or_Nlist_PRIME] = 2,
	[P_LHS_Nlist_PRIME_RHS_Nseparator_op_Nlist_PRIME_PRIME] = 2,
	[P_LHS_Nlist_PRIME_RHS] = 0,
	[P_LHS_Nlist_PRIME_PRIME_RHS_Nand_or_Nlist_PRIME] = 2,
	[P_LHS_Nlist_PRIME_PRIME_RHS] = 0,
	[P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME] = 2,
	[P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME] = 4,
	[P_LHS_Nand_or_PRIME_RHS] = 0,
	[P_LHS_Nand_or_op_RHS_TAND_IF] = 1,
	[P_LHS_Nand_or_op_RHS_TOR_IF] = 1,
	[P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence] = 2,
	[P_LHS_Nbang_opt_RHS_TBANG] = 1,
	[P_LHS_Nbang_opt_RHS] = 0,
	[P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME] = 2,
	[P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME] = 4,
	[P_LHS_Npipe_sequence_PRIME_RHS] = 0,
	[P_LHS_Ncommand_RHS_TWORD] = 1,
	[P_LHS_Nlinebreak_RHS_Nnewline_list] = 1,
	[P_LHS_Nlinebreak_RHS] = 0,
	[P_LHS_Nseparator_op_RHS_TAMPER] = 1,
	[P_LHS_Nseparator_op_RHS_TSEMI] = 1,
	[P_LHS_Nnewline_list_RHS_TNEWLINE_Nnewline_list_PRIME] = 2,
	[P_LHS_Nnewline_list_PRIME_RHS_TNEWLINE_Nnewline_list_PRIME] = 2,
	[P_LHS_Nnewline_list_PRIME_RHS] = 0,
};

static int
shell_lhs_prod_table[TOTAL_PROD] = {
	[P_LHS_Ncomplete_command_RHS_Nlist_Nlinebreak] = N_complete_command,
	[P_LHS_Nlist_RHS_Nand_or_Nlist_PRIME] = N_list,
	[P_LHS_Nlist_PRIME_RHS_Nseparator_op_Nlist_PRIME_PRIME] = N_list_PRIME,
	[P_LHS_Nlist_PRIME_RHS] = N_list_PRIME,
	[P_LHS_Nlist_PRIME_PRIME_RHS_Nand_or_Nlist_PRIME] = N_list_PRIME_PRIME,
	[P_LHS_Nlist_PRIME_PRIME_RHS] = N_list_PRIME_PRIME,
	[P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME] = N_and_or,
	[P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME] = N_and_or_PRIME,
	[P_LHS_Nand_or_PRIME_RHS] = N_and_or_PRIME,
	[P_LHS_Nand_or_op_RHS_TAND_IF] = N_and_or_op,
	[P_LHS_Nand_or_op_RHS_TOR_IF] = N_and_or_op,
	[P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence] = N_pipeline,
	[P_LHS_Nbang_opt_RHS_TBANG] = N_bang_opt,
	[P_LHS_Nbang_opt_RHS] = N_bang_opt,
	[P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME] = N_pipe_sequence,
	[P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME] = N_pipe_sequence_PRIME,
	[P_LHS_Npipe_sequence_PRIME_RHS] = N_pipe_sequence_PRIME,
	[P_LHS_Ncommand_RHS_TWORD] = N_command,
	[P_LHS_Nlinebreak_RHS_Nnewline_list] = N_linebreak,
	[P_LHS_Nlinebreak_RHS] = N_linebreak,
	[P_LHS_Nseparator_op_RHS_TAMPER] = N_separator_op,
	[P_LHS_Nseparator_op_RHS_TSEMI] = N_separator_op,
	[P_LHS_Nnewline_list_RHS_TNEWLINE_Nnewline_list_PRIME] = N_newline_list,
	[P_LHS_Nnewline_list_PRIME_RHS_TNEWLINE_Nnewline_list_PRIME] = N_newline_list_PRIME,
	[P_LHS_Nnewline_list_PRIME_RHS] = N_newline_list_PRIME,
};

#define ERROR_SLOT	0
#define START_SYMBOL	N_complete_command

static int
shell_ll_table[TOTAL_NTER][TOTAL_TOKEN] = {
	[N_complete_command][T_BANG]=P_LHS_Ncomplete_command_RHS_Nlist_Nlinebreak, [N_complete_command][T_WORD]=P_LHS_Ncomplete_command_RHS_Nlist_Nlinebreak, 
	[N_list][T_BANG]=P_LHS_Nlist_RHS_Nand_or_Nlist_PRIME, [N_list][T_WORD]=P_LHS_Nlist_RHS_Nand_or_Nlist_PRIME, 
	[N_linebreak][T_EOF]=P_LHS_Nlinebreak_RHS, [N_linebreak][T_BANG]=P_LHS_Nlinebreak_RHS, [N_linebreak][T_WORD]=P_LHS_Nlinebreak_RHS, [N_linebreak][T_NEWLINE]=P_LHS_Nlinebreak_RHS_Nnewline_list, 
	[N_and_or][T_BANG]=P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME, [N_and_or][T_WORD]=P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME, 
	[N_list_PRIME][T_EOF]=P_LHS_Nlist_PRIME_RHS, [N_list_PRIME][T_NEWLINE]=P_LHS_Nlist_PRIME_RHS, [N_list_PRIME][T_SEMI]=P_LHS_Nlist_PRIME_RHS_Nseparator_op_Nlist_PRIME_PRIME, [N_list_PRIME][T_AMPER]=P_LHS_Nlist_PRIME_RHS_Nseparator_op_Nlist_PRIME_PRIME, 
	[N_separator_op][T_SEMI]=P_LHS_Nseparator_op_RHS_TSEMI, [N_separator_op][T_AMPER]=P_LHS_Nseparator_op_RHS_TAMPER, 
	[N_list_PRIME_PRIME][T_EOF]=P_LHS_Nlist_PRIME_PRIME_RHS, [N_list_PRIME_PRIME][T_NEWLINE]=P_LHS_Nlist_PRIME_PRIME_RHS, [N_list_PRIME_PRIME][T_BANG]=P_LHS_Nlist_PRIME_PRIME_RHS_Nand_or_Nlist_PRIME, [N_list_PRIME_PRIME][T_WORD]=P_LHS_Nlist_PRIME_PRIME_RHS_Nand_or_Nlist_PRIME, 
	[N_pipeline][T_BANG]=P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence, [N_pipeline][T_WORD]=P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence, 
	[N_and_or_PRIME][T_EOF]=P_LHS_Nand_or_PRIME_RHS, [N_and_or_PRIME][T_SEMI]=P_LHS_Nand_or_PRIME_RHS, [N_and_or_PRIME][T_AMPER]=P_LHS_Nand_or_PRIME_RHS, [N_and_or_PRIME][T_NEWLINE]=P_LHS_Nand_or_PRIME_RHS, [N_and_or_PRIME][T_OR_IF]=P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME, [N_and_or_PRIME][T_AND_IF]=P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME, 
	[N_and_or_op][T_OR_IF]=P_LHS_Nand_or_op_RHS_TOR_IF, [N_and_or_op][T_AND_IF]=P_LHS_Nand_or_op_RHS_TAND_IF, 
	[N_bang_opt][T_WORD]=P_LHS_Nbang_opt_RHS, [N_bang_opt][T_BANG]=P_LHS_Nbang_opt_RHS_TBANG, 
	[N_pipe_sequence][T_WORD]=P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME, 
	[N_command][T_WORD]=P_LHS_Ncommand_RHS_TWORD, 
	[N_pipe_sequence_PRIME][T_EOF]=P_LHS_Npipe_sequence_PRIME_RHS, [N_pipe_sequence_PRIME][T_OR_IF]=P_LHS_Npipe_sequence_PRIME_RHS, [N_pipe_sequence_PRIME][T_AND_IF]=P_LHS_Npipe_sequence_PRIME_RHS, [N_pipe_sequence_PRIME][T_SEMI]=P_LHS_Npipe_sequence_PRIME_RHS, [N_pipe_sequence_PRIME][T_AMPER]=P_LHS_Npipe_sequence_PRIME_RHS, [N_pipe_sequence_PRIME][T_NEWLINE]=P_LHS_Npipe_sequence_PRIME_RHS, [N_pipe_sequence_PRIME][T_PIPE]=P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME, 
	[N_newline_list][T_NEWLINE]=P_LHS_Nnewline_list_RHS_TNEWLINE_Nnewline_list_PRIME, 
	[N_newline_list_PRIME][T_EOF]=P_LHS_Nnewline_list_PRIME_RHS, [N_newline_list_PRIME][T_BANG]=P_LHS_Nnewline_list_PRIME_RHS, [N_newline_list_PRIME][T_WORD]=P_LHS_Nnewline_list_PRIME_RHS, [N_newline_list_PRIME][T_NEWLINE]=P_LHS_Nnewline_list_PRIME_RHS_TNEWLINE_Nnewline_list_PRIME, 
};

#if 0

enum {
	_SHIFT	= 0x1000,
	_REDUCE	= 0x2000,
	_GOTO	= 0x4000,
};

#define SHIFT(x)	(x | _SHIFT)
#define REDUCE(x)	(x | _REDUCE)
#define GOTO(x)	(x | _GOTO)
#define ACCEPT	(~0)

#define LR_START_STATE	0

static int
shell_lr_action_table[35][TOTAL_TOKEN] = {
/*   0 */	{[T_BANG]=SHIFT(6), [T_WORD]=REDUCE(P_LHS_Nbang_opt_RHS)},
/*   1 */	{[T_EOF]=ACCEPT,},
/*   2 */	{[T_NEWLINE]=SHIFT(14), [T_EOF]=REDUCE(P_LHS_Nlinebreak_RHS)},
/*   3 */	{[T_SEMI]=SHIFT(30), [T_AMPER]=SHIFT(29), [T_EOF]=REDUCE(P_LHS_Nlist_PRIME_RHS), [T_NEWLINE]=REDUCE(P_LHS_Nlist_PRIME_RHS)},
/*   4 */	{[T_OR_IF]=SHIFT(23), [T_AND_IF]=SHIFT(22), [T_EOF]=REDUCE(P_LHS_Nand_or_PRIME_RHS), [T_SEMI]=REDUCE(P_LHS_Nand_or_PRIME_RHS), [T_AMPER]=REDUCE(P_LHS_Nand_or_PRIME_RHS), [T_NEWLINE]=REDUCE(P_LHS_Nand_or_PRIME_RHS)},
/*   5 */	{[T_WORD]=SHIFT(9)},
/*   6 */	{[T_WORD]=REDUCE(P_LHS_Nbang_opt_RHS_TBANG)},
/*   7 */	{[T_EOF]=REDUCE(P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence), [T_OR_IF]=REDUCE(P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence), [T_AND_IF]=REDUCE(P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence), [T_SEMI]=REDUCE(P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence), [T_AMPER]=REDUCE(P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence), [T_NEWLINE]=REDUCE(P_LHS_Npipeline_RHS_Nbang_opt_Npipe_sequence)},
/*   8 */	{[T_PIPE]=SHIFT(11), [T_EOF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_OR_IF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_AND_IF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_SEMI]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_AMPER]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_NEWLINE]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS)},
/*   9 */	{[T_EOF]=REDUCE(P_LHS_Ncommand_RHS_TWORD), [T_PIPE]=REDUCE(P_LHS_Ncommand_RHS_TWORD), [T_OR_IF]=REDUCE(P_LHS_Ncommand_RHS_TWORD), [T_AND_IF]=REDUCE(P_LHS_Ncommand_RHS_TWORD), [T_SEMI]=REDUCE(P_LHS_Ncommand_RHS_TWORD), [T_AMPER]=REDUCE(P_LHS_Ncommand_RHS_TWORD), [T_NEWLINE]=REDUCE(P_LHS_Ncommand_RHS_TWORD)},
/*  10 */	{[T_EOF]=REDUCE(P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME), [T_OR_IF]=REDUCE(P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME), [T_AND_IF]=REDUCE(P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME), [T_SEMI]=REDUCE(P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME), [T_AMPER]=REDUCE(P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME), [T_NEWLINE]=REDUCE(P_LHS_Npipe_sequence_RHS_Ncommand_Npipe_sequence_PRIME)},
/*  11 */	{[T_NEWLINE]=SHIFT(14), [T_WORD]=REDUCE(P_LHS_Nlinebreak_RHS)},
/*  12 */	{[T_WORD]=SHIFT(9)},
/*  13 */	{[T_EOF]=REDUCE(P_LHS_Nlinebreak_RHS_Nnewline_list), [T_BANG]=REDUCE(P_LHS_Nlinebreak_RHS_Nnewline_list), [T_WORD]=REDUCE(P_LHS_Nlinebreak_RHS_Nnewline_list)},
/*  14 */	{[T_NEWLINE]=SHIFT(16), [T_EOF]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS), [T_BANG]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS), [T_WORD]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS)},
/*  15 */	{[T_EOF]=REDUCE(P_LHS_Nnewline_list_RHS_TNEWLINE_Nnewline_list_PRIME), [T_BANG]=REDUCE(P_LHS_Nnewline_list_RHS_TNEWLINE_Nnewline_list_PRIME), [T_WORD]=REDUCE(P_LHS_Nnewline_list_RHS_TNEWLINE_Nnewline_list_PRIME)},
/*  16 */	{[T_NEWLINE]=SHIFT(16), [T_EOF]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS), [T_BANG]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS), [T_WORD]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS)},
/*  17 */	{[T_EOF]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS_TNEWLINE_Nnewline_list_PRIME), [T_BANG]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS_TNEWLINE_Nnewline_list_PRIME), [T_WORD]=REDUCE(P_LHS_Nnewline_list_PRIME_RHS_TNEWLINE_Nnewline_list_PRIME)},
/*  18 */	{[T_PIPE]=SHIFT(11), [T_EOF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_OR_IF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_AND_IF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_SEMI]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_AMPER]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS), [T_NEWLINE]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS)},
/*  19 */	{[T_EOF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME), [T_OR_IF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME), [T_AND_IF]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME), [T_SEMI]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME), [T_AMPER]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME), [T_NEWLINE]=REDUCE(P_LHS_Npipe_sequence_PRIME_RHS_TPIPE_Nlinebreak_Ncommand_Npipe_sequence_PRIME)},
/*  20 */	{[T_EOF]=REDUCE(P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME), [T_SEMI]=REDUCE(P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME), [T_AMPER]=REDUCE(P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME), [T_NEWLINE]=REDUCE(P_LHS_Nand_or_RHS_Npipeline_Nand_or_PRIME)},
/*  21 */	{[T_NEWLINE]=SHIFT(14), [T_BANG]=REDUCE(P_LHS_Nlinebreak_RHS), [T_WORD]=REDUCE(P_LHS_Nlinebreak_RHS)},
/*  22 */	{[T_BANG]=REDUCE(P_LHS_Nand_or_op_RHS_TAND_IF), [T_NEWLINE]=REDUCE(P_LHS_Nand_or_op_RHS_TAND_IF), [T_WORD]=REDUCE(P_LHS_Nand_or_op_RHS_TAND_IF)},
/*  23 */	{[T_BANG]=REDUCE(P_LHS_Nand_or_op_RHS_TOR_IF), [T_NEWLINE]=REDUCE(P_LHS_Nand_or_op_RHS_TOR_IF), [T_WORD]=REDUCE(P_LHS_Nand_or_op_RHS_TOR_IF)},
/*  24 */	{[T_BANG]=SHIFT(6), [T_WORD]=REDUCE(P_LHS_Nbang_opt_RHS)},
/*  25 */	{[T_OR_IF]=SHIFT(23), [T_AND_IF]=SHIFT(22), [T_EOF]=REDUCE(P_LHS_Nand_or_PRIME_RHS), [T_SEMI]=REDUCE(P_LHS_Nand_or_PRIME_RHS), [T_AMPER]=REDUCE(P_LHS_Nand_or_PRIME_RHS), [T_NEWLINE]=REDUCE(P_LHS_Nand_or_PRIME_RHS)},
/*  26 */	{[T_EOF]=REDUCE(P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME), [T_SEMI]=REDUCE(P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME), [T_AMPER]=REDUCE(P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME), [T_NEWLINE]=REDUCE(P_LHS_Nand_or_PRIME_RHS_Nand_or_op_Nlinebreak_Npipeline_Nand_or_PRIME)},
/*  27 */	{[T_EOF]=REDUCE(P_LHS_Nlist_RHS_Nand_or_Nlist_PRIME), [T_NEWLINE]=REDUCE(P_LHS_Nlist_RHS_Nand_or_Nlist_PRIME)},
/*  28 */	{[T_BANG]=SHIFT(6), [T_WORD]=REDUCE(P_LHS_Nbang_opt_RHS), [T_EOF]=REDUCE(P_LHS_Nlist_PRIME_PRIME_RHS), [T_NEWLINE]=REDUCE(P_LHS_Nlist_PRIME_PRIME_RHS)},
/*  29 */	{[T_EOF]=REDUCE(P_LHS_Nseparator_op_RHS_TAMPER), [T_BANG]=REDUCE(P_LHS_Nseparator_op_RHS_TAMPER), [T_NEWLINE]=REDUCE(P_LHS_Nseparator_op_RHS_TAMPER), [T_WORD]=REDUCE(P_LHS_Nseparator_op_RHS_TAMPER)},
/*  30 */	{[T_EOF]=REDUCE(P_LHS_Nseparator_op_RHS_TSEMI), [T_BANG]=REDUCE(P_LHS_Nseparator_op_RHS_TSEMI), [T_NEWLINE]=REDUCE(P_LHS_Nseparator_op_RHS_TSEMI), [T_WORD]=REDUCE(P_LHS_Nseparator_op_RHS_TSEMI)},
/*  31 */	{[T_EOF]=REDUCE(P_LHS_Nlist_PRIME_RHS_Nseparator_op_Nlist_PRIME_PRIME), [T_NEWLINE]=REDUCE(P_LHS_Nlist_PRIME_RHS_Nseparator_op_Nlist_PRIME_PRIME)},
/*  32 */	{[T_SEMI]=SHIFT(30), [T_AMPER]=SHIFT(29), [T_EOF]=REDUCE(P_LHS_Nlist_PRIME_RHS), [T_NEWLINE]=REDUCE(P_LHS_Nlist_PRIME_RHS)},
/*  33 */	{[T_EOF]=REDUCE(P_LHS_Nlist_PRIME_PRIME_RHS_Nand_or_Nlist_PRIME), [T_NEWLINE]=REDUCE(P_LHS_Nlist_PRIME_PRIME_RHS_Nand_or_Nlist_PRIME)},
/*  34 */	{[T_EOF]=REDUCE(P_LHS_Ncomplete_command_RHS_Nlist_Nlinebreak)},
};

static int
shell_lr_goto_table[35][TOTAL_NTER] = {
/*   0 */	{[N_bang_opt]=GOTO(5), [N_pipeline]=GOTO(4), [N_and_or]=GOTO(3), [N_list]=GOTO(2), [N_complete_command]=GOTO(1)},
/*   1 */	{},
/*   2 */	{[N_newline_list]=GOTO(13), [N_linebreak]=GOTO(34)},
/*   3 */	{[N_separator_op]=GOTO(28), [N_list_PRIME]=GOTO(27)},
/*   4 */	{[N_and_or_op]=GOTO(21), [N_and_or_PRIME]=GOTO(20)},
/*   5 */	{[N_command]=GOTO(8), [N_pipe_sequence]=GOTO(7)},
/*   6 */	{},
/*   7 */	{},
/*   8 */	{[N_pipe_sequence_PRIME]=GOTO(10)},
/*   9 */	{},
/*  10 */	{},
/*  11 */	{[N_newline_list]=GOTO(13), [N_linebreak]=GOTO(12)},
/*  12 */	{[N_command]=GOTO(18)},
/*  13 */	{},
/*  14 */	{[N_newline_list_PRIME]=GOTO(15)},
/*  15 */	{},
/*  16 */	{[N_newline_list_PRIME]=GOTO(17)},
/*  17 */	{},
/*  18 */	{[N_pipe_sequence_PRIME]=GOTO(19)},
/*  19 */	{},
/*  20 */	{},
/*  21 */	{[N_newline_list]=GOTO(13), [N_linebreak]=GOTO(24)},
/*  22 */	{},
/*  23 */	{},
/*  24 */	{[N_pipeline]=GOTO(25), [N_bang_opt]=GOTO(5)},
/*  25 */	{[N_and_or_PRIME]=GOTO(26), [N_and_or_op]=GOTO(21)},
/*  26 */	{},
/*  27 */	{},
/*  28 */	{[N_and_or]=GOTO(32), [N_list_PRIME_PRIME]=GOTO(31), [N_bang_opt]=GOTO(5), [N_pipeline]=GOTO(4)},
/*  29 */	{},
/*  30 */	{},
/*  31 */	{},
/*  32 */	{[N_list_PRIME]=GOTO(33), [N_separator_op]=GOTO(28)},
/*  33 */	{},
/*  34 */	{},
};

#endif

static int
shell_sync_token[TOTAL_NTER][8] = {
	[N_complete_command] = { T_EOF, -1 },
	[N_list] = { T_NEWLINE, T_EOF, -1 },
	[N_linebreak] = { T_WORD, T_BANG, T_EOF, -1 },
	[N_and_or] = { T_NEWLINE, T_AMPER, T_SEMI, T_EOF, -1 },
	[N_list_PRIME] = { T_NEWLINE, T_EOF, -1 },
	[N_separator_op] = { T_WORD, T_NEWLINE, T_BANG, T_EOF, -1 },
	[N_list_PRIME_PRIME] = { T_NEWLINE, T_EOF, -1 },
	[N_pipeline] = { T_NEWLINE, T_AMPER, T_SEMI, T_AND_IF, T_OR_IF, T_EOF, -1 },
	[N_and_or_PRIME] = { T_NEWLINE, T_AMPER, T_SEMI, T_EOF, -1 },
	[N_and_or_op] = { T_WORD, T_NEWLINE, T_BANG, -1 },
	[N_bang_opt] = { T_WORD, -1 },
	[N_pipe_sequence] = { T_NEWLINE, T_AMPER, T_SEMI, T_AND_IF, T_OR_IF, T_EOF, -1 },
	[N_command] = { T_NEWLINE, T_AMPER, T_SEMI, T_AND_IF, T_OR_IF, T_PIPE, T_EOF, -1 },
	[N_pipe_sequence_PRIME] = { T_NEWLINE, T_AMPER, T_SEMI, T_AND_IF, T_OR_IF, T_EOF, -1 },
	[N_newline_list] = { T_WORD, T_BANG, T_EOF, -1 },
	[N_newline_list_PRIME] = { T_WORD, T_BANG, T_EOF, -1 },
};

#endif /* _SHELL_GRM_H_ */
