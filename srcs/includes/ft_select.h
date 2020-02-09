/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:47:25 by ambelghi          #+#    #+#             */
/*   Updated: 2020/02/03 20:57:43 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <sys/ioctl.h>
# include <fcntl.h>
# include <termios.h>
# include <term.h>
# define PROMPT_SIZE 16

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_line_lst
{
	struct s_line_lst	*prev;
	struct s_line_lst	*next;
	char				*str;
	int					len;
	int					nb_lines;
}				t_line_lst;

typedef struct	s_cs_line
{
	int				total_lines; // nb total des lignes utilisee par ledition
	int				this_line;
	int				nb_lines; //nb de ligne AKA '\n'
	int				line;
	int				line_col;
	int				col;
	int				row;
	int				min_col;
	int				min_row;
	int				scroll;
	int				max_scroll;
	int				tty;
	t_point			screen;
	t_line_lst		*list;
	char			*input;
	int start;
	int	end;
}				t_cs_line;

t_cs_line			*cs_master(t_line_lst *list, int init);
void			space_bar(t_cs_line *cs);
int				check_keys(char *caps);
void			arrow_up(t_cs_line *cs);
void			arrow_down(t_cs_line *cs);
void			arrow_right(t_cs_line *cs);
void			arrow_left(t_cs_line *cs);
int				my_putchar(int c);
void			get_cs_line_position(int *col, int *rows);
void			read_input(void);
void			print_col(t_line_lst *list, int print_params);
t_line_lst	*params_tolist(char **env);
int				line_listcount(t_line_lst *elem);
t_line_lst		*line_lstnew(char *var, int i);
void			line_lstaddb(t_line_lst *start, t_line_lst *new);
void			line_lstdelone(t_line_lst **lst);
void			line_lstfree(t_line_lst **lst);
t_line_lst		*line_dup(t_line_lst *list);
t_line_lst		*line_getlst(t_line_lst *list, int n);
void			print_line(t_line_lst *tmp, t_point max, int elem);
int				get_maxlen(t_line_lst *list);
void			cs_set(t_line_lst *list, int max_len);
void			ft_clear(void);
void			underline_me(t_cs_line *cs, int ue);
int				scroll_nb(t_cs_line *cs);
void			move_cs(t_cs_line **cs);
void			print_name(t_line_lst *lst, t_cs_line *cs);
int				term_init(int init, char **av);
void			size_handler(int sig);
void			pause_handler(int sig);
void			sig_handler(int sig);
void			cs_setter(int nb_elem, int max_col, t_cs_line *cs,
							struct winsize size);
void			print_hscroll(t_line_lst *list, t_cs_line *cs);
void			start_colors(t_line_lst *lst, int ue);
void			end_colors(t_line_lst *lst, int ue);
void			print_colme(t_line_lst *tmp, t_point max, t_cs_line *cs);
void			print_colmvcs(int scroll, t_point tmp_col, t_cs_line *cs);
void			putchar_n(char c, int n);
int				term_check(struct termios *new_term, struct termios *old_term,
							int tty);
void			init_signals(void);

void			input_text(t_cs_line *cs, char *input);
char			*input_master(char *in, int init);
void			print_cmdline(t_cs_line *cs);
char			*replace_cr(t_cs_line *cs, char *input);
void			line_master(t_cs_line *cs, char *input);

int				get_row(t_cs_line *cs);

void    home_key(t_cs_line *cs);
void    end_key(t_cs_line *cs);
void    maj_arrow_down(t_cs_line *cs);
void    maj_arrow_up(t_cs_line *cs);
void    line_lstinsert(t_line_lst *lst, t_line_lst *insert);
int     get_total_lines(t_cs_line *cs);

char    *get_firstline(t_cs_line *cs);

int     get_line(t_cs_line *cs);

char    *ft_prompt(void);

#endif
