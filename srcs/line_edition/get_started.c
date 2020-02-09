/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_started.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:01:55 by ambelghi          #+#    #+#             */
/*   Updated: 2020/02/09 18:17:28 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termios.h>
#include <term.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "ft_select.h"
#include <time.h>
#include <stdio.h>
void	h_scroll(t_cs_line *cs)
{
//	static int		tmp = 0;
//	t_line_lst	*lst;

	if (cs)
	{
	/*	if (tmp - (clock() / (CLOCKS_PER_SEC / 4)) > 1
				&& (lst = slct_getlst(cs->list, cs->elem + 1))
				&& ft_strlen(lst->name) > cs->screen.x)
		{
			tmp = (clock() / (CLOCKS_PER_SEC / 4));
			if (cs->h_scroll < cs->max_hscroll)
				cs->h_scroll += 1;
			else
				cs->h_scroll = 0;
			move_cs(&cs);
		}*/
	}
}

void	read_input(void)
{
	int		len;
	int		stop;
	char	*buf;
	t_cs_line	*cs;

	stop = 0;
	len = 0;
	cs = cs_master(NULL, 0);
	//underline_me(cs, 1);
	while (stop >= 0)
	{
		ioctl(cs->tty, FIONREAD, &len);
		h_scroll(cs);
		if (cs->sig_int == 0 && len <= 0)
			continue ;
		if (cs->sig_int == 1 || !(buf = ft_strnew(len + 1)))
			break ;
		if (buf[0] == EOF || read(cs->tty, buf, len) != len)
			stop = -1;
		stop = (stop >= 0 ? check_keys(buf) : stop);
	//	ft_strdel(&buf);
	}
}

void	ft_clear(int del_prompt)
{
	t_point			col;
	t_cs_line			*cs;
	struct winsize	ws;

	if ((cs = cs_master(NULL, 0)))
	{
		col.x = cs->min_col;
		col.y = cs->min_row;
		ioctl(cs->tty, TIOCGWINSZ, &ws);
		tputs(tgoto(tgetstr("cm", NULL), cs->min_col, cs->min_row),
				1, &my_putchar);
		while (col.y < ws.ws_row)
		{
			if (col.y++ == cs->min_row)
			{
				if (del_prompt == 1)
					tputs(tgetstr("ce", NULL), 1, &my_putchar);
				tputs(tgoto(tgetstr("cm", NULL), 0, cs->min_row + 1),
                1, &my_putchar);
			}
			else if (col.y - 1 != cs->min_row && col.y < ws.ws_row)
				tputs(tgetstr("dl", NULL), ws.ws_col, &my_putchar);
		}
		tputs(tgoto(tgetstr("cm", NULL), cs->min_col, cs->min_row),
				1, &my_putchar);
	}
}

char	*ft_prompt(void)
{
	char		*ret;
	t_cs_line	*cs;

	ret = NULL;
	if (term_init(1, NULL) == 1 && (cs = cs_master(NULL, 0)))
	{
		cs->sig_int = 0;
		get_cs_line_position(&cs->min_col, &cs->min_row);
		read_input();
		init_signals();
		term_init(0, NULL);
		ft_putstr_fd("\n", cs->tty);
		ret = cs->input;
	}
	if (!ret)
		ret = ft_strnew(0);
	return (ret);
}
/*
int		main(void)
{
	ft_putstr(ft_prompt());//ft_itoa(cs->max_scroll));
	ft_putstr("\n");
	return (0);
}*/
