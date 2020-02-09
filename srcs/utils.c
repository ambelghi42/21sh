/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:18:24 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 20:27:39 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <dirent.h>

int			env_listcount(t_env_list *elem)
{
	int			nb;
	t_env_list	*tmp;

	nb = 0;
	if ((tmp = elem))
	{
		while ((tmp = tmp->next))
			nb++;
	}
	return (nb);
}

t_env_list	*env_tolist(char **env)
{
	int			i;
	char		*var;
	char		*value;
	t_env_list	*new;

	new = NULL;
	if ((new = env_lstnew(NULL, NULL)))
	{
		i = 0;
		while (env && env[i])
		{
			var = ft_strchr(env[i], '=');
			*var = '\0';
			value = ft_strdup(env[i]);
			*var = '=';
			var = ft_strdup(&var[1]);
			env_lstaddb(new, env_lstnew(value, var));
			i++;
		}
	}
	return (new);
}

char		**env_totab(t_env_list **list)
{
	int			i;
	char		**new;
	t_env_list	*tmp;

	new = NULL;
	if (list && (tmp = *list) && tmp->next)
	{
		i = env_listcount(*list);
		if (!(new = (char**)malloc(sizeof(char *) * (i + 1))))
			return (new);
		new[i] = NULL;
		i = 0;
		while ((tmp = tmp->next))
		{
			new[i] = ft_strnew(ft_strlen(tmp->var) + ft_strlen(tmp->value) + 1);
			new[i] = ft_strcat(new[i], tmp->var);
			new[i] = ft_strcat(new[i], "=");
			new[i] = ft_strcat(new[i], tmp->value);
			i++;
		}
	}
	return (new);
}

char		*exec_path(t_env_list *env, char *line)
{
	if (line && env)
	{
		if (line[0] == '.' || line[0] == '/')
			return (ft_strdup(line));
		else
			return (ft_which(get_env(env, "PATH"), line));
	}
	return (NULL);
}
