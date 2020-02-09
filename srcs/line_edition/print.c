/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:08:23 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/22 15:57:01 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"

void	print_hscroll(t_line_lst *list, t_cs_line *cs)
{
//	char	tmp_char;
//	int		tmp_int;

	if (ft_strlen(list->str) > cs->screen.x - 1)
	{
	/*	tmp_char = list->str[cs->h_scroll + cs->screen.x];
		list->str[cs->h_scroll + cs->screen.x] = '\0';
		ft_putstr_fd(&list->str[cs->h_scroll], cs->tty);
		list->str[cs->h_scroll + cs->screen.x] = tmp_char;
	*/}
	else
	{
	/*	tmp_int = ft_strlen(list->str);
		tmp_char = list->str[tmp_int];
		list->str[tmp_int] = '\0';
		ft_putstr_fd(&(list->str[cs->h_scroll]), cs->tty);
		list->str[tmp_int] = tmp_char;
	*/}
}

void	start_colors(t_line_lst *list, int ue)
{
	t_cs_line	*cs;

	if (list && (cs = cs_master(NULL, 0)))
	{
		if (list->len)
		{
			tputs(tgoto(tgetstr("mr", NULL), cs->col, cs->row),
					1, &my_putchar);
			ft_putstr_fd("\x1b[34;1m", cs->tty);
			ft_putstr_fd("\x1b[47;1m", cs->tty);
		}
		if (ue == 1)
		{
			tputs(tgetstr("us", NULL), 1, &my_putchar);
			ft_putstr_fd("\x1b[31m", cs->tty);
		}
		else
			ft_putstr_fd("\x1b[34;1m", cs->tty);
	}
}

void	end_colors(t_line_lst *list, int ue)
{
	t_cs_line	*cs;

	if (list && (cs = cs_master(NULL, 0)))
	{
		if (ue == 1)
		{
			ft_putstr_fd("\x1b[0m", cs->tty);
			ft_putstr_fd("\x1b[0m", cs->tty);
			tputs(tgetstr("ue", NULL), 1, &my_putchar);
		}
		if (list->len)
			ft_putstr_fd("\x1b[0m", cs->tty);
		ft_putstr_fd("\x1b[0m", cs->tty);
		tputs(tgetstr("me", NULL), 1, &my_putchar);
	}
}

void	underline_me(t_cs_line *cs, int ue)
{
	//t_line_lst	*list;

	ue = 0;
	if (cs)
	{
	/*	if ((list = line_getlst(cs->list, cs->elem + 1)))
		{
			if (ft_strlen(list->str) > cs->screen.x)
			{
				putchar_n(' ', cs->screen.x);
				tputs(tgoto(tgetstr("cm", NULL), cs->col,
							cs->row), 1, &my_putchar);
			}
			start_colors(list, ue);
			if (cs->max_len >= cs->screen.x - 1 && ft_strlen(list->str)
					> cs->h_scroll && ft_strlen(list->str) > cs->screen.x)
				print_hscroll(list, cs);
			else
				print_name(list, cs);
			end_colors(list, ue);
			tputs(tgoto(tgetstr("cm", NULL), cs->col, cs->row), 1, &my_putchar);
		}*/
	}
}
