/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:27:29 by ambelghi          #+#    #+#             */
/*   Updated: 2020/02/09 19:07:06 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <signal.h>
#include <sys/ioctl.h>

int		scroll_nb(t_cs_line *cs)
{
	int	scroll;
	//int	i;

	scroll = 0;
	if (cs && cs->line_col > 1)
	{
		/*		i = 0;
				while (i++ < (cs->max_col / (cs->max_len + 1) + 1))
				{
				if (cs->elem > cs->line_col * (i - 1)
				+ (cs->max_row - cs->min_row + cs->scroll)
				&& cs->elem < (cs->line_col * i) + cs->scroll + 1)
				{
				scroll = cs->elem - (cs->line_col * (i - 1)
				+ (cs->max_row - cs->min_row + cs->scroll));
				break ;
				}
				}*/
	}
	return (scroll);
}

void	print_name(t_line_lst *lst, t_cs_line *cs)
{
	//char	tmp_char;

	if (lst && cs)
	{/*
		if (ft_strlen(lst->name) <= cs->screen.x)
		ft_putstr_fd(lst->name, cs->tty);
		else
		{
		tmp_char = lst->name[cs->screen.x];
		lst->name[cs->screen.x] = '\0';
		ft_putstr_fd(lst->name, cs->tty);
		lst->name[cs->screen.x] = tmp_char;
		}
	  */}
}

int		back_space(t_cs_line *cs)
{
	char			*oc;
	char			*tmp2;
	//	t_line_lst		*lst;

	if (cs)// && (lst = line_getlst(cs->list, cs->line + 1)))
	{
		if (cs->line_col > 0)
		{
			if((tmp2 = cs->input))
			{
				if (cs->line_col > 0)
				{
					oc = &tmp2[cs->line_col - 1];
					*oc = '\0';
					if (tmp2[cs->line_col] != '\0')
						cs->input = ft_strjoin(tmp2, &tmp2[cs->line_col]);
					else
						cs->input = ft_strdup(tmp2);
					ft_strdel(&tmp2);
					//		lst->len = ft_strlen(lst->str);
					//		lst->nb_lines = lst->len / cs->screen.x
					//					+ (lst->len % cs->screen.x ? 1 : 0);
				}
			//	if (cs->col == 0 && cs->line_col > 0 && cs->row == cs->min_row + 1
			//		&& cs->scroll > 0)
				int row_prompt;
				row_prompt = (PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) / cs->screen.x
					+ (((PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) % cs->screen.x) > 0
					? 1 : 0);
				if (cs->line_col > 0)
					cs->line_col -= 1;
				if (cs->col == 1 && cs->scroll && cs->row == cs->min_row
					+ (cs->screen.x > 1 ? 0 : 2))
					cs->scroll -= 2;
				if (cs->scroll < 0)
					cs->scroll = 0;
				print_cmdline(cs);
				/*	if (cs->line > 0 && (lst->len == 0 || cs->line_col == 0))
					{
					cs->line -= 1;
					oc = lst->prev->str;
					lst->prev->str = ft_strjoin(oc, lst->str);
					lst->prev->len = ft_strlen(lst->prev->str);
					lst->prev->nb_lines = lst->prev->len  / cs->screen.x
					+ (lst->prev->len % cs->screen.x > 0 ? 1 : 0);
				//	if (ft_strlen(lst->prev->str) > cs->line_col)
				cs->line_col = ft_strlen(oc);
				ft_strdel(&oc);
				line_lstdelone(&lst);
				cs->nb_lines -= 1;
				}
				else
				cs->line_col -= 1;
				 */

				/*			int cr = 0;
							int i3 = 0;
							int i = 0;
							while (i < cs->line_col)
							{
							i3++;
							if (cs->input[i] == '\n' || i3 == cs->screen.x)
							{
							i3 = 0;
							cr++;
							}
							i++;
							}
							cs->scroll = cr - (cs->screen.y - cs->min_row - 1);
							if (cs->scroll < 0)
							cs->scroll = 0;
							if (cs->line_col > 0)
							cs->line_col -= 1;
							move_cs(&cs);
				 */			//ft_clear();
				//	arrow_left(cs);
				//		move_cs(&cs);
			}
		}
		return (1);
	}
	/*
	   if (cs && (tmp = line_getlst(cs->list, cs->elem + 1)))
	   {
	   line_lstdelone(&tmp);
	   cs->nb_elem -= 1;
	   cs->elem = (cs->elem > cs->nb_elem - 1 ? cs->nb_elem - 1 : cs->elem);
	   if (cs->nb_elem == 0 || !cs->list->next)
	   return (-1);
	   print_col(cs->list, 1);
	   move_cs(&cs);
	   if (scroll_nb(cs) > 0 && cs->scroll < cs->max_scroll)
	   cs->scroll += scroll_nb(cs);
	   else if (scroll_nb(cs) > 0)
	   cs->scroll -= (cs->line_col * (cs->col / (cs->max_len + 1))
	   + cs->scroll + 1) - cs->elem;
	   if (cs->scroll > cs->max_scroll)
	   cs->scroll = cs->max_scroll;
	   if (cs->scroll < 0)
	   cs->scroll = 0;
	   print_col(cs->list, 1);
	   move_cs(&cs);
	   return (1);
	   }*/
	return (-1);
}

void	ft_enter(t_cs_line **cs)
{
	char			*ret;
	//char			*tmp_str;
	t_line_lst	*tmp;
	int				i;

	if (cs && *cs && (tmp = (*cs)->list))
	{
		ft_clear(0);
		ret = NULL;
		i = 0;
		while ((tmp = tmp->next))
		{
			/*if (tmp->is_select && ++i && (tmp_str = ret) >= 0)
			  {
			  ret = ft_strjoin(ret, " ");
			  ft_strdel(&tmp_str);
			  tmp_str = ret;
			  ret = ft_strjoin(ret, tmp->name);
			  ft_strdel(&tmp_str);
			  }*/
		}
		if (i == 0 && (tmp = line_getlst((*cs)->list, (*cs)->line_col + 1)))
			ret = ft_strdup(tmp->str);
		//(*cs)-> = ret;
	}
}

int		check_keys(char *caps)
{
	int				ret;
	struct winsize	w_term;
	t_cs_line			*cs;

	ret = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &w_term);
	cs = cs_master(NULL, 0);
	if (ft_strcmp(caps, "\e[D") == 0 && (ret = 1))
		arrow_left(cs);
	if (ft_strcmp(caps, "\e[C") == 0 && (ret = 1))
		arrow_right(cs);
	if ((ft_strcmp(caps, "\e[B") == 0 || ft_strcmp(caps, "\x09") == 0)
			&& (ret = 1))
		arrow_down(cs);
	if (ft_strcmp(caps, "\e[1;2A") == 0 && (ret = 1))
		maj_arrow_up(cs);
	if (ft_strcmp(caps, "\e[1;2B") == 0 && (ret = 1))
		maj_arrow_down(cs);
	if (ft_strcmp(caps, "\e[A") == 0 && (ret = 1))
		arrow_up(cs);
	if (ft_strcmp(caps, "\e[H") == 0 && (ret = 1))
		home_key(cs);
	if (ft_strcmp(caps, "\e[F") == 0 && (ret = 1))
		end_key(cs);
	if (ft_strcmp(caps, "\n") == 0)
    {
    //    ft_clear();
      //  ft_putstr_fd("\n", cs->tty);
        ret = -1;
    }
	if (ft_strcmp(caps, "\033[6n") == 0 || caps[0] == '[')
		ret = -1;
	if (caps[0] != 127 && ret == 0 && caps[0] != '\033' && (ret = 1))
	{
		line_master(cs, caps);
		if (ft_strchr(caps, '\n'))
			ret = -1;
		print_cmdline(cs);
		//		move_cs(&cs);
	}

	if (ft_strcmp(caps, " ") == 0 && (ret = 1))
		space_bar(cs);
	if (caps[0] == 127)
	{
		ret = back_space(cs);
		print_cmdline(cs);
	}
	if (ft_strlen(caps) == 1 && caps[0] == '\033' && (ret = -1) < 0)
		ft_clear(0);
	return (ret);
}
