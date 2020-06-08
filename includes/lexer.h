#ifndef LEXER_H
# define LEXER_H

# include "struct.h"

/*
**	comment.c
*/

int	l_end_comment(t_lexer *lexer, char c);
int	l_comment_line(t_lexer *lexer, char c);

/*
**	control.c
*/

int	l_delim_control(t_lexer *lexer, char c);
int	l_build_control(t_lexer *lexer, char c);

/*
**	digit.c
*/

int	l_delim_digit(t_lexer *lexer, char c);
int	l_build_digit(t_lexer *lexer, char c);

/*
**	equ.c
*/

int	l_delim_equ(t_lexer *lexer, char c);

/*
**	exp.c
*/

int	l_delim_exp(t_lexer *lexer, char c);
int	l_build_exp(t_lexer *lexer, char c);
int	l_exp_brack(t_lexer *lexer, char c);
int	l_exp_add(t_lexer *lexer, char c);

/*
**	inhib.c
*/

int	l_build_inhib(t_lexer *lexer, char c);
int	l_inhib_add(t_lexer *lexer, char c);
int	l_delim_inhib(t_lexer *lexer, char c);

/*
**	newline.c
*/

int	l_build_newline(t_lexer *lexer, char c);
int	l_delim_newline(t_lexer *lexer, char c);

/*
**	redir.c
*/

int	l_is_duplicable_redir(t_lexer *lexer);
int	l_build_redir(t_lexer *lexer, char c);
int	l_delim_redir(t_lexer *lexer, char c);
int	l_add_hyphen_redir(t_lexer *lexer, char c);

/*
**	word.c
*/

int	l_build_word(t_lexer *lexer, char c);
int	l_delim_word(t_lexer *lexer, char c);

/*
**	flag.c
*/

t_lexer_flag	l_get_last_flag(t_lexer *lexer);
int	l_add_flag(t_lexer *lexer, char c);
int	l_flag_state_add(t_lexer *lexer, char c);
int	l_delim_flag(t_lexer *lexer, char c);

/*
**	buffer.c
*/

void		l_buffer_flush(t_lexer *lexer);
int		l_buffer_add(t_lexer *lexer, char c);

/*
**	heredoc.c
*/

t_here_queue	*l_get_last_here(t_lexer *lexer);
int		l_create_flag_queue(t_lexer *lexer);
int		l_create_here_queue(t_lexer *lexer);
void	del_here_queue(void *data, size_t size);
void	l_flush_delim(t_lexer *lexer);
int	l_hd_body_flush(t_lexer *lexer, char c);

/*
**	debug/lexerdb.c
*/

void	print_debug(t_list *elem);
void	print_flag_queue(t_list *elem);
char	*get_state_str(t_lexer *lexer);
char	*get_flag_name(t_lexer_flag flag);

/*
**	tools.c
*/

void	l_set_flag(t_lexer *lexer, t_lexer_flag flag);
void	l_unset_flag(t_lexer *lexer, t_lexer_flag flag);
int	l_get_flag(t_lexer *lexer, t_lexer_flag flag);
int	l_do_nothing(t_lexer *lexer, char c);

/*
**	quote.c
*/

int	l_is_quoting(t_lexer *lexer);
int	l_bslash_add(t_lexer *lexer, char c);
int	l_dquote_add(t_lexer *lexer, char c);

/*
**	type.c
*/

int	l_set_token_type(t_lexer *lexer, char c);

/*
**	token.c
*/

void	init_token(t_token *token);
int		l_create_token(t_lexer *lexer);
int		l_delim_token(t_lexer *lexer, char c);

/*
**	free.c
*/

void	del_token(void *data, size_t size);
void	tabfree(char **tab);
void	del_str(void *data, size_t size);
void	del_flag_queue(void *data, size_t size);

/*
**	misc.c
*/

int		lex_err(t_lexer *lexer, char c);
char	l_get_char(t_lexer *lexer);
t_char_type	l_get_char_type(char c);

/*
**	prompt.c
*/

int			l_complete_str(t_lexer *lexer, char c);

/*
**	state/start.c
*/

void	init_start_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/hdbody.c
*/

void	init_heredoc_body_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/control.c
*/

void	init_amp_pipe_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/redir.c
*/

void	init_redir_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/exp.c
*/

void	init_exp_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/word.c
*/

void	init_word_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/ionumber.c
*/

void	init_io_number_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/flag.c
*/

void	init_flag_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/comment.c
*/

void	init_comment_state(int (*token_builder[9][12])(t_lexer *, char));

/*
**	state/initt.c
*/

void	init_lexer_states(int (*token_builder[9][12])(t_lexer *, char));

/*
**	lexer.c
*/

int	ft_lexer(char **str, t_lexer *lexer);
int	lex_err(t_lexer *lexer, char c);

#endif