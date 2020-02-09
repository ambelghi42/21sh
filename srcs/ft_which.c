/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:20:59 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 20:21:09 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "dirent.h"
#include "minishell.h"

char	*which_path(char **path, char *exec, int i)
{
	char	*dst;

	dst = ft_strnew(ft_strlen(path[i]) + ft_strlen(exec) + 1);
	ft_strcat(dst, path[i]);
	ft_strcat(dst, "/");
	ft_strcat(dst, exec);
	free_tab(path);
	return (dst);
}

char	*get_env(t_env_list *env, char *var)
{
	t_env_list	*tmp;

	tmp = NULL;
	if ((tmp = env) && var)
	{
		while ((tmp = tmp->next))
			if (ft_strcmp(tmp->var, var) == 0)
				return ((tmp->value ? tmp->value : "\0"));
	}
	return (NULL);
}

void	set_env(t_env_list *env, char *var, char *value)
{
	t_env_list	*tmp;

	tmp = NULL;
	if ((tmp = env) && var)
	{
		while ((tmp = tmp->next))
		{
			if (ft_strcmp(tmp->var, var) == 0)
			{
				ft_strdel(&(tmp->value));
				tmp->value = value;
			}
		}
	}
}

char	*ft_which(char const *paths, char *exec)
{
	struct dirent	*file;
	char			**tab;
	DIR				*dir;
	int				i;

	i = -1;
	if (!(paths && exec && (tab = ft_strsplit(paths, ":"))))
		return (NULL);
	while (tab[++i])
	{
		if (!(dir = opendir(tab[i])))
			continue;
		while ((file = readdir(dir)))
			if (ft_strcmp(file->d_name, exec) == 0)
				break ;
		closedir(dir);
		if (file)
			return (which_path(tab, exec, i));
	}
	free_tab(tab);
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
			ft_strdel(&tab[i++]);
		free(tab);
		tab = NULL;
	}
}
