/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:55:07 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 20:17:59 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int			ft_checkopt(char c, char *options, char *name)
{
	if (!ft_strchr(options, c))
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	else
		return (1);
}

int			env_getopt(char **av)
{
	int				i;
	int				z;
	int				ret;

	ret = 0;
	if (av)
	{
		i = 1;
		while (av[i] && av[i][0] == '-' && ft_strcmp(av[i], "--") != 0)
		{
			z = 1;
			while (av[i][z] != '\0')
			{
				if (ft_checkopt(av[i][z], "i", "env") != 1)
					return (-1);
				else
					ret = 1;
				z++;
			}
			i++;
		}
	}
	return (ret);
}

void		modify_envset(t_env_list *env, char *param, char *oc)
{
	if (param && oc)
	{
		*oc = '\0';
		if (get_env(env, param))
			set_env(env, param, ft_strdup(oc + 1));
		else
			env_lstaddb(env, env_lstnew(ft_strdup(param), ft_strdup(oc + 1)));
		*oc = '=';
	}
}
