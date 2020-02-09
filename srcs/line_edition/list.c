/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:04:24 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/27 13:45:42 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

t_line_lst	*params_tolist(char **av)
{
	int				i;
	t_line_lst	*new;

	new = NULL;
	if ((new = line_lstnew(NULL, 0)))
	{
		i = 0;
		while (av && av[i])
		{
			i++;
			line_lstaddb(new, line_lstnew(ft_strdup(av[i]), ft_strlen(av[i])));
		}
	}
	return (new);
}

int				line_listcount(t_line_lst *elem)
{
	int			nb;
	t_line_lst	*tmp;

	nb = 0;
	if ((tmp = elem))
	{
		while ((tmp = tmp->next))
		{
			nb++;
			//tmp-> = nb;
		}
	}
	return (nb);
}

t_line_lst	*line_lstnew(char *var, int i)
{
	t_line_lst		*new;
	struct winsize	ws;

	new = NULL;
	ioctl(ttyslot(), TIOCGWINSZ, &ws);
	if ((new = (t_line_lst *)malloc(sizeof(t_line_lst))))
	{
		new->prev = NULL;
		new->next = NULL;
		new->str = var;
		new->len = i;
		new->nb_lines = i / ws.ws_col + (i % ws.ws_col > 0 ? 1 : 0);
	}
	return (new);
}

void			line_lstaddb(t_line_lst *start, t_line_lst *new)
{
	t_line_lst	*tmp;

	tmp = NULL;
	if ((tmp = start) && new)
	{
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}

void			line_lstdelone(t_line_lst **lst)
{
	if (lst && *lst)
	{
		if ((*lst)->prev)
			(*lst)->prev->next = (*lst)->next;
		if ((*lst)->next)
			(*lst)->next->prev = (*lst)->prev;
		ft_strdel(&(*lst)->str);
		ft_memdel((void **)lst);
	}
}
