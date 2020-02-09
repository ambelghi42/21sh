/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:04:24 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 20:26:29 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_env_list	*env_lstnew(char *var, char *value)
{
	t_env_list	*new;

	new = NULL;
	if ((new = (t_env_list *)malloc(sizeof(t_env_list))))
	{
		new->prev = NULL;
		new->next = NULL;
		new->var = var;
		new->value = value;
	}
	return (new);
}

void		env_lstaddb(t_env_list *start, t_env_list *new)
{
	t_env_list	*tmp;

	tmp = NULL;
	if ((tmp = start) && new)
	{
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}

void		env_lstdelone(t_env_list **lst)
{
	if (lst && *lst)
	{
		if ((*lst)->prev)
			(*lst)->prev->next = (*lst)->next;
		if ((*lst)->next)
			(*lst)->next->prev = (*lst)->prev;
		ft_strdel(&(*lst)->var);
		ft_strdel(&(*lst)->value);
		ft_memdel((void **)lst);
	}
}

void		env_lstfree(t_env_list **lst)
{
	t_env_list	*tmp;
	t_env_list	*next;

	if (lst && (tmp = *lst))
	{
		while (tmp)
		{
			next = tmp->next;
			if (tmp->var)
				ft_strdel(&tmp->var);
			if (tmp->value)
				ft_strdel(&tmp->value);
			ft_memdel((void **)&tmp);
			tmp = next;
		}
	}
}

t_env_list	*env_dup(t_env_list *list)
{
	t_env_list	*new;
	t_env_list	*tmp;

	new = NULL;
	tmp = list;
	if ((new = env_lstnew(NULL, NULL)))
	{
		while ((tmp = tmp->next))
		{
			env_lstaddb(new, env_lstnew(ft_strdup(tmp->var),
						ft_strdup(tmp->value)));
		}
	}
	return (new);
}
