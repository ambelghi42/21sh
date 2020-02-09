/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */

/*   Created: 2020/01/13 16:11:17 by ambelghi          #+#    #+#             */
/*   Updated: 2020/02/09 18:38:14 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_select.h"

void	cs_setter(int nb_elem, int max_col, t_cs_line *cs, struct winsize size)
{
	max_col = 0;
	cs = NULL;
	size.ws_row = size.ws_row;
	/*
	   if (cs && cs->screen.x < cs->max_len)
	   cs->max_len = cs->screen.x - 1;
	   if (cs && nb_elem >= size.ws_row - cs->min_row)
	   {
	   cs->max_row = cs->min_row - 1
	   + (nb_elem / max_col + (nb_elem % max_col == 0 ? 0 : 1));
	   cs->max_row = (cs->max_row > size.ws_row ? size.ws_row - 1
	   : cs->max_row);
	   cs->lines_col = nb_elem / max_col + (nb_elem % max_col == 0 ? 0 : 1);
	   }
	   else if (cs)
	   {
	   cs->max_row = cs->min_row - 1 + cs->nb_elem;
	   cs->lines_col = cs->nb_elem;
	   }
	   if (cs && cs->lines_col == 0)
	   cs->lines_col = 1;
	   if (cs)
	   cs->max_row = cs->col_command / cs->screen.x;
	 */
	nb_elem = 0;
}

void	cs_set(t_line_lst *list, int max_len)
{
	int				z;
	int				max_col;
	struct winsize	size;
	t_cs_line			*cs;

	if ((cs = cs_master(NULL, 0)))
	{
		list = NULL;
		ioctl(cs->tty, TIOCGWINSZ, &size);
		max_col = (max_len > 0 && max_len < size.ws_col
				? size.ws_col / (max_len + 1) : 1);
		cs->screen.x = size.ws_col;
		cs->screen.y = size.ws_row;
		cs->tty = ttyslot();
		z = ft_strlen(cs->input);
		cs->total_lines = z / cs->screen.x + (z % cs->screen.x > 0 ? 1 : 0);
		cs->max_scroll = cs->total_lines - (cs->screen.y - cs->min_row);
		char    *prompt = "minishell-1.0$ ";
        int     ew = 0;
        if (cs->screen.x <= 16)
        {
            ew = 16 - cs->screen.x - 1;
            if (cs->screen.x <= 16)
                ft_putstr_fd("$", cs->tty);
            else
                ft_putstr_fd(&prompt[ew], cs->tty);
        }
        else
            ft_putstr_fd(&prompt[ew], cs->tty);
	}
}

int		get_total_lines(t_cs_line *cs)
{
	t_line_lst  *lst;
	int         i;
	int         row;

	i = 0;
	if ((lst = cs->list))
	{
		row = cs->min_row;
		row += cs->line_col / cs->screen.x;
		while ((lst = lst->next))
		{
			lst->len = ft_strlen(lst->str);
			if (lst->len / cs->screen.x > 0)
				row += lst->len / cs->screen.x + (lst->len % cs->screen.x > 0
						? 1 : 0);
			else
				row += 1;
		}
		i = row;
	}
	return (i);
}
/*
int		get_row(t_cs_line *cs2)
{
	//	t_line_lst	*lst;
	int			i;
	//	int			row;
	int			z;
	int			oc;
	char		*ocu;
	t_cs_line	*cs;

	cs2 = NULL;
	i = 0;
	if ((cs = cs_master(NULL, 0)) && cs->input)
	{
		oc = (int)cs->input[cs->line_col];
		cs->input[cs->line_col] = '\0';
		ocu = cs->input;
		while ((ocu = ft_strchr(ocu, '\n')))
		{
			ocu++;
			i++;
		}
		z = ft_strlen(cs->input) / cs->screen.x + i;
		cs->input[cs->line_col] = (char)oc;
		return (cs->min_row + z);
	}
	return (cs ? cs->min_row : i);
}
*/
void	move_cs(t_cs_line **cs)
{
	t_cs_line	*tmp;
	t_point		pos;

	if (cs && (tmp = *cs) && tmp->input && tmp->input[0])
	{
		pos = cs_pos(tmp);
		tmp->col = pos.x;
		tmp->row = pos.y;
		tputs(tgoto(tgetstr("cm", NULL), tmp->col, tmp->row), 1, &my_putchar);
	}
}

t_cs_line	*cs_master(t_line_lst *list, int init)
{
	static t_cs_line	cs = {0};

	if (init == 1)
	{
		get_cs_line_position(&cs.min_col, &cs.min_row);
		cs.col = 0;
		cs.row = cs.min_row;
		cs.list = list;
		cs.scroll = 0;
		cs.line_col = 0;
		cs.max_scroll = 0;
		cs.input = ft_strnew(0);
		cs.list = line_lstnew(NULL, 0);
		//	line_lstaddb(cs.list, line_lstnew(NULL, 0));
	}
	return (&cs);
}
