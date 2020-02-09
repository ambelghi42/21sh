/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:39:42 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/27 18:24:41 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft.h"

t_line_lst	*line_dup(t_line_lst *list)
{
	t_line_lst	*new;
	t_line_lst	*tmp;

	new = NULL;
	tmp = list;
	if ((new = line_lstnew(NULL, 0)))
	{
		while ((tmp = tmp->next))
		{
			line_lstaddb(new, line_lstnew(ft_strdup(tmp->str), tmp->len));
		}
	}
	return (new);
}

t_line_lst	*line_getlst(t_line_lst *list, int n)
{
	t_line_lst	*tmp;
	int				i;

	if ((tmp = list))
	{
		i = 1;
		while (tmp && tmp->prev)
			tmp = tmp->prev;
		while (tmp->next && (tmp = tmp->next) && i++ < n)
			;
	}
	return (tmp);
}

void			line_lstfree(t_line_lst **lst)
{
	t_line_lst	*tmp;
	t_line_lst	*next;

	if (lst && (tmp = *lst))
	{
		while (tmp)
		{
			next = tmp->next;
			if (tmp->str)
				ft_strdel(&tmp->str);
			ft_memdel((void **)&tmp);
			tmp = next;
		}
	}
}

void	line_lstinsert(t_line_lst *lst, t_line_lst *insert)
{
	t_line_lst	*tmp;

	if(lst && insert)
	{
		if ((tmp = lst->next))
		{
			insert->prev = lst;
			insert->next = lst->next;
			lst->next->prev = insert;
			lst->next = insert;
		}
		else
		{
			lst->next = insert;
			insert->prev = lst;
		}
	}
}
