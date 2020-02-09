/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 14:45:32 by ambelghi          #+#    #+#             */
/*   Updated: 2020/02/09 19:07:25 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <sys/ioctl.h>

char	*replace_cr(t_cs_line *cs, char *input)
{
	char	*in;
	char	*spaces;
	char	*oc;
	char	oc2;
	int		len;

	if ((in = input))
	{
		while ((oc = ft_strchr(input, '\n')))
		{
			//oc++;
			oc2 = *oc;
			*oc = '\0';
			if ((len = ft_strlen(input)) > cs->screen.x)
				len = cs->screen.x - len % cs->screen.x;
			else
				len = cs->screen.x - len;
			spaces = ft_strdup(input);
			while (len-- > 0)
			{
				in = spaces;
				spaces = ft_strjoin(spaces, " ");
				ft_strdel(&in);
			}
			in = input;
			*oc = oc2;
			input = ft_strjoin(spaces, oc + 1);
			ft_strdel(&spaces);
			ft_strdel(&in);
			in = ft_strdup(input);
			//	ft_strdel(&oc);
		}
		//	input_master(input, 1);
	}
	return (in);
}

char	*input_master(char *in, int init)
{
	static char	*input = NULL;

	if (init == 1)
	{
		//ft_strdel(&input);
		input = in;
	}
	return (input);
}

char	*get_firstline(t_cs_line *cs)
{
	char		*oc;
	t_line_lst	*tmp;
	int			x;

	oc = NULL;
	if (cs && (tmp = cs->list))
	{
		x = 1;
		if (tmp->next)
			oc = tmp->next->str;
		while (cs->scroll > 0 && (tmp = tmp->next) && x <= cs->scroll)
		{
			x += tmp->nb_lines;
			if (x > cs->scroll)
			{
				x = cs->scroll - (x - tmp->nb_lines);
				return (&tmp->str[x * (cs->screen.x - 1) + 1]);
			}
		}
	}
	return (oc);
}

t_point	trim_input(t_cs_line *cs)
{
	t_point z;
	int		cr;
	int		line;
	int		i;
	int		ew;
	char	*tmp;
	int		i2;
	int		line2;

	z.x = 0;
	z.y = ft_strlen(cs->input);
	if (cs)
	{
		ew = 0;
		i = 0;
		line = 0;
		tmp = cs->input;
		cr = 0;
		i2 = 0;
		int i3 = 0;
		line2 = 0;
		static int	scrolled = 0;
		int row_prompt;
        row_prompt = PROMPT_SIZE / cs->screen.x
            + (cs->scroll > 0 ? 5 / cs->screen.x : 0)
            + (5 % cs->screen.x > 0 ? 1 : 0);

		while (tmp[i])
		{
			i3++;
			if (tmp[i] == '\n' || i3 == cs->screen.x
					|| (line == 0 && i3 + cs->min_col >= cs->screen.x - 1))
			{
				i3 = 0;
				line++;
			}
			if ((cs->scroll > 0 && line > cs->scroll && ew == 0))
			{
				char *more = "^";
			//	if (cs->screen.x - cs->min_col >= 0 && cs->screen.x - cs->min_col < 4)
			//		more[cs->screen.x - cs->min_col] = '\0';
				ft_putstr_fd("\e[0;31m\e[47m", cs->tty);
				ft_putstr_fd("\e[1m\e[4m\e[7m", cs->tty);
				ft_putstr_fd(more, cs->tty);
				ft_putstr_fd("\e[0m", cs->tty);
			//	if (cs->screen.x > 3)
					ft_putstr_fd("\n", cs->tty);
				ew = 1;
				scrolled = 1;
				z.x = i + 1;
				//sleep(1);
			}
		/*	else if (cs->scroll == 0 && scrolled == 1
				&& cs->min_row > (PROMPT_SIZE + 5) / cs->screen.x)
			{
				cs->min_row -= (PROMPT_SIZE + 5) / cs->screen.x
					+ ((PROMPT_SIZE + 5) / cs->screen.x > 0 ? 1 : 0);
			}
		*/	if (line - cs->scroll + cs->min_row + 1 > cs->screen.y)
			{
				z.y = i - 1;//i;
				break ;
			}
			i++;
		}
		cs->start = z.x;
		cs->end = z.y;
	}
	return (z);
}

void	print_cmdline(t_cs_line *cs)
{
	//	t_line_lst	*tmp;
	int			i;
	int			row;
	int			z;
	int			x;
	int			start;
	int			end;
	//	char		*tmp2;
	//	int			row_start;
	char		oc;

	oc = 0;
	ft_clear(1);
	if (cs && cs->input && cs->line_col >= 0)
	{
		i = 1;
		tputs(tgoto(tgetstr("cm", NULL), 0, cs->min_row),
                1, &my_putchar);
		char	*prompt = "minishell-1.0$ ";
		int		ew = 0;
		if (cs->screen.x <= 16)
		{
			ew = 17 - cs->screen.x;
			if (cs->screen.x <= 16)
				ft_putstr_fd("$", cs->tty);
			else
				ft_putstr_fd(&prompt[ew], cs->tty);
		}
		else
			ft_putstr_fd(&prompt[ew], cs->tty);
//		tputs(tgoto(tgetstr("cm", NULL), cs->min_col, cs->min_row),
//				1, &my_putchar);
	//	cs->min_row = (PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) / cs->screen.x
      //      + (((PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) % cs->screen.x) > 0
        //    ? 1 : 0) - 1;
		row = 0;
		z = 0;
		i = 0;
		x = 0;
		row = 0;
		t_point z = trim_input(cs);
		start = z.x;
		end = z.y;
		oc = cs->input[end + 1];
		cs->input[end + 1] = '\0';
		ft_putstr_fd(&cs->input[start], cs->tty);
		cs->input[end + 1] = oc;
		move_cs(&cs);
	}
}

void	line_master(t_cs_line *cs, char *input)
{
	char		*tmp;
	char		*insert;
	char		oc;
	int			i;
//	int			cr;

	if (input && cs)// && (t = ft_strsplit(input, "\n")))
	{
		if (ft_strlen(cs->input) == cs->line_col)
		{
			tmp = cs->input;
			cs->input = ft_strjoin(cs->input, input);
			ft_strdel(&tmp);
		}
		else if (cs->input && cs->input[0])
		{
			oc = cs->input[cs->line_col];
			cs->input[cs->line_col] = '\0';
			tmp = cs->input;
			cs->input = ft_strjoin(tmp, input);
			tmp[cs->line_col] = oc;
			insert = cs->input;
			cs->input = ft_strjoin(insert, &tmp[cs->line_col]);
			ft_strdel(&insert);
			ft_strdel(&tmp);
		}
		cs->line_col += ft_strlen(input);
		cs->max_scroll = ft_strlen(cs->input) / cs->screen.x
			- (cs->screen.y - cs->min_row);
		i = 0;
		cs->cr = get_line(cs);
		int	row_prompt = PROMPT_SIZE / cs->screen.x;
		int	scroll_add = 0;
		if (cs->cr + cs->min_row >= cs->screen.y && cs->min_row > row_prompt)
		{
			scroll_add = cs->cr + cs->min_row - cs->screen.y + 1;
			while (cs->min_row - scroll_add < 1)
				scroll_add--;
			cs->min_row -= scroll_add;
			tputs(tgoto(tgetstr("SF", NULL), 0, scroll_add), 1, &my_putchar);
		}
		if (cs->cr - cs->scroll + cs->min_row >= cs->screen.y)
			cs->scroll = cs->cr - (cs->screen.y - cs->min_row - 1);
		if (cs->scroll < 0)
			cs->scroll = 0;
	}
}

int		get_cs_linecol(t_cs_line *cs)
{
	int	i;
	int	z;
	int	x;
	int	cr;

	i = 0;
	z = 0;
	cr = 0;
	x = cs->line_col;
	if (cs)
	{
		while (x > 0 && cr == 0)
		{
			z++;
			if (cs->input[--x] == '\n' || z == cs->screen.x)
				cr++;
		}
		int w = z;
		z = 0;
		while (x > 0 && cr == 1)
		{
			z++;
			if (cs->input[--x] == '\n' || z == cs->screen.x)
				cr++;
		}
		if (w > 0 && w <= z)
			cs->line_col = x + w;
		else
			cs->line_col = x + z;
		cs->line_col = (cs->line_col < 0 ? 0 : cs->line_col);
		i = cs->line_col;
	}
	return (i);
}

int     get_cs_linecol2(t_cs_line *cs)
{
	int i;
	int z;
	int	w;
	int x;
	int cr;

	i = 0;
	z = 0;
	cr = 0;
	x = cs->line_col;
	if (cs)
	{
		w = 0;
		int	col = cs->col;
		while (x > 0 && cr == 0)
		{
			if (col-- == 0 || w == cs->screen.x)
				cr++;
			w++;
			x--;
		}
		//w--;
		x++;
	//	x = 0;//cs->line_col;
		//cr = 0;
		z = 0;//w;
		while (x <= ft_strlen(cs->input) && cr <= 2)
		{
			if (z == cs->screen.x)
			{
				cr++;
				z = 0;
			}
			z++;
			x++;
		}
		z--;
		x--;
		if (w > 0 && w < z)
			cs->line_col = x + w;
		else
			cs->line_col = x;
		i = cs->line_col;
	}
	return (i);
}

t_point	cs_pos(t_cs_line *cs)
{
	t_point	ew;
	int i = 0;
    int cr = 0;
    int i3 = 0;

	ew.x = 0;
	ew.y = 0;
	if (cs && cs->input && cs->input[0])
	{
		while (i < cs->line_col || (i == cs->line_col && cs->scroll > 0))
        {
            //i3++;
            if (cs->input[i] == '\n' || i3 == cs->screen.x
                || (cr == 0 && i3 + cs->min_col >= cs->screen.x))
            {
                i3 = 0;
                cr++;
            }
			i3++;
            i++;
        }
		if (i3 > cs->line_col)
			i3 = cs->line_col;
		int row_prompt;
        row_prompt = (PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) / cs->screen.x
				+ (((PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) % cs->screen.x) > 0
                ? 1 : 0);
		ew.x = i3 + (cr == 0 ? cs->min_col : 0);
		ew.y = cr - cs->scroll + cs->min_row;
	}
	return (ew);
}

int		get_col(t_cs_line *cs)
{
	int i = 0;
    int cr = 0;
    int i3 = 0;

    if (cs->input && cs->input[0])
    {
        while (i <= cs->line_col)
        {
            if (cs->input[i] == '\n' || i3 == cs->screen.x
				|| (cr == 0 && i3 + cs->min_col >= cs->screen.x))
            {
                i3 = -1;
                cr++;
            }
			i3++;
            i++;
        }
    }
    return (i3 + (cr == 0 ? cs->min_col : 0));
}

int     get_row(t_cs_line *cs)
{
    int i = 0;
    int cr = 0;
    int i3 = 0;

    if (cs->input && cs->input[0])
    {
        while (i < cs->line_col)
        {
            i3++;
            if (cs->input[i] == '\n' || i3 == cs->screen.x
                || (cr == 0 && i3 + cs->min_col >= cs->screen.x))
            {
                i3 = 0;
                cr++;
            }
            i++;
        }
    }
    return (cr - cs->scroll + cs->min_row);
}

int		get_line(t_cs_line *cs)
{
	int i = 0;
	int cr = 0;
	int i3 = 0;
	int i4 = cs->line_col;
	int	cr2 = 0;

	if (cs->input && cs->input[0])
	{
		while (cs->input[i4] && cr == 0)
		{
			i3++;
			if (cs->input[i4] == '\n' || i3 == cs->screen.x)
			{
				i3 = 0;
				cr++;
			}
			i4++;
		}
		i3 = 0;
		cr2 = cr;
		while (i <= cs->line_col)
		{
			i3++;
			if (cs->input[i] == '\n' || i3 == cs->screen.x
					|| (cr2 == cr && i3 + cs->min_col >= cs->screen.x))
			{
				i3 = 0;
				cr++;
			}
			i++;
		}
	}
	return (cr);
}

void	arrow_up(t_cs_line *cs)
{
	//t_line_lst  *lst;
	int	scroll;
	//int	cr;

	if (cs) //&& (lst = line_getlst(cs->list, cs->line + 1)))
	{
		scroll = 0;
		scroll = cs->scroll;
		get_cs_linecol(cs);
		cs->cr = get_line(cs);
		if (cs->cr + cs->min_row - cs->scroll  - 1 <= cs->min_row 
			+ (cs->screen.x > 1 ? 0 : 2) && cs->scroll)
		{
			cs->scroll = cs->cr - (cs->screen.y - cs->min_row - 1);
			print_cmdline(cs);
		}
		if (cs->scroll < 0)
		{
			cs->scroll = 0;
			print_cmdline(cs);
		}
		move_cs(&cs);
	}
}

void	arrow_down(t_cs_line *cs)
{
	int	scroll;
	//int	cr;

	if (cs)// && (lst = line_getlst(cs->list, cs->line + 1)))
	{
		scroll = cs->scroll;
		//get_cs_linecol2(cs);
		if (cs->line_col + cs->screen.x <= ft_strlen(cs->input))
			cs->line_col += cs->screen.x;
		else
			cs->line_col = ft_strlen(cs->input);
		cs->cr = get_line(cs);
		if (cs->cr - cs->scroll + cs->min_row >= cs->screen.y)
		{
			cs->scroll = cs->cr - (cs->screen.y - cs->min_row - 1);
			print_cmdline(cs);
		}
		if (cs->scroll < 0)
			cs->scroll = 0;
		move_cs(&cs);	
	}
}

void	arrow_right(t_cs_line *cs)
{

	if (cs)// && (lst = line_getlst(cs->list, cs->line + 1)))
	{
		int row_prompt;
        row_prompt = (PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) / cs->screen.x
            + (((PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) % cs->screen.x) > 0
            ? 1 : 0);
		if (cs->line_col < ft_strlen(cs->input))
			cs->line_col += 1;
		if (cs->col == cs->screen.x && cs->row >= cs->screen.y - 1)
		{
			cs->scroll += 1;
			print_cmdline(cs);
		}
		if (cs->scroll < 0)
			cs->scroll = 0;
		move_cs(&cs);
	}	
}

void	arrow_left(t_cs_line *cs)
{

	if (cs)// && (lst = line_getlst(cs->list, cs->line + 1)))
	{
		int row_prompt;
        row_prompt = (PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) / cs->screen.x
            + (((PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) % cs->screen.x) > 0
            ? 1 : 0);
		if (cs->line_col > 0)
			cs->line_col -= 1;
		if (cs->col == 1 && cs->scroll && cs->row == cs->min_row
			+ (cs->screen.x > 1 ? 0 : 2))
		{
			cs->scroll -= 1;
			print_cmdline(cs);
		}
		if (cs->scroll < 0)
			cs->scroll = 0;
		move_cs(&cs);
		//	trim_input(cs);
	}
}

void	space_bar(t_cs_line *cs)
{
	t_line_lst	*tmp;

	if ((tmp = line_getlst(cs->list, cs->line)))
	{
		move_cs(&cs);
	}
}

void	home_key(t_cs_line *cs)
{
	int	cr;

	if (cs)
	{
		cs->line_col = 0;
		cr = get_line(cs);
		cs->scroll = cr - (cs->screen.y - cs->min_row - 1);
		if (cs->scroll < 0)
			cs->scroll = 0;
		print_cmdline(cs);
		move_cs(&cs);
	}
}

void	end_key(t_cs_line *cs)
{
	int	cr;

	if (cs)
	{
		cs->line_col = ft_strlen(cs->input);
        cr = get_line(cs);
        cs->scroll = cr - (cs->screen.y - cs->min_row - 1);
        if (cs->scroll < 0)
            cs->scroll = 0;
        print_cmdline(cs);
		move_cs(&cs);
	}
}

void	maj_arrow_down(t_cs_line *cs)
{
	t_line_lst  *tmp;

	if (cs && (tmp = line_getlst(cs->list, cs->line + 1)))
	{
		if (cs->line < cs->nb_lines && tmp->next)
		{
			cs->line += 1;
			if (cs->line_col % cs->screen.x > tmp->next->len)
				cs->line_col = tmp->next->len;
			else
				cs->line_col = cs->line_col % cs->screen.x;
		}
		move_cs(&cs);
	}
}

void	maj_arrow_up(t_cs_line *cs)
{
	t_line_lst  *tmp;

	if (cs && (tmp = line_getlst(cs->list, cs->line + 1)))
	{
		if (cs->line > 0 && tmp->prev)
		{
			if (cs->line_col % cs->screen.x > tmp->prev->len)
				cs->line_col = tmp->prev->len;
			else
				cs->line_col = cs->line_col % cs->screen.x;
			cs->line -= 1;
		}
		move_cs(&cs);
	}
}
