/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:19:26 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/08 16:23:23 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>

void	get_expansion(char **params, t_env_list *env)
{
	int	i;

	if (params && env)
	{
		i = 0;
		while (params[i])
		{
			params[i] = get_tilde(params[i], env);
			params[i] = get_dollar(params[i], env);
			i++;
		}
	}
}

char	*get_tilde(char *line, t_env_list *env)
{
	char	*new;
	char	*oc;

	new = NULL;
	if (line && line[0] == '~')
	{
		oc = get_env(env, "HOME");
		if (!(new = ft_strnew(ft_strlen(oc) + ft_strlen(line) - 1)))
			return (NULL);
		new = ft_strcat(new, oc);
		new = ft_strcat(new, &line[1]);
		ft_strdel(&line);
		line = new;
	}
	return (line);
}

char	*get_dollarset(t_env_list *env, char *line, int i, int j)
{
	char	*oc;
	char	*expand;

	oc = NULL;
	if (env && line)
	{
		oc = ft_strsub(line, i + 1, j - i - 1);
		expand = get_env(env, oc);
		ft_strdel(&oc);
		if (!(oc = ft_strnew(i + ft_strlen(&line[j]) + ft_strlen(expand))))
			return (NULL);
		oc = ft_strncat(oc, line, i);
		oc = ft_strcat(oc, expand);
		oc = ft_strcat(oc, &line[j]);
	}
	return (oc);
}

char	*get_dollar(char *line, t_env_list *env)
{
	char	*oc;
	char	*expand;
	int		i;
	int		j;

	i = 0;
	oc = NULL;
	while (line && env && line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
		{
			expand = NULL;
			j = i + 1;
			while (line[j] && (ft_isalnum(line[j]) > 0 || line[j] == '_'))
				j++;
			if (!(expand = get_dollarset(env, line, i, j)))
				return (NULL);
			ft_strdel(&line);
			line = expand;
			i = -1;
		}
		i++;
	}
	return (line);
}

char	**get_params(char *line, t_env_list *env)
{
	char		**tab;
	struct stat	stats;
	int			ret;

	tab = NULL;
	if (line && (tab = ft_strsplit(line, " \t")) && *tab)
	{
		if ((tab[0][0] == '/' || tab[0][0] == '.'))
		{
			if ((ret = stat(tab[0], &stats)) != 0 || S_ISDIR(stats.st_mode))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(tab[0], 2);
				if (ret != 0)
					ft_putstr_fd(": No such file or directory\n", 2);
				else
					ft_putstr_fd(": Is a directory\n", 2);
				free_tab(tab);
				return (NULL);
			}
		}
		get_expansion(tab, env);
	}
	return (tab);
}
