/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:36:20 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 19:44:58 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	checkenv_check(int i, int *ret, char **params, int builtin)
{
	char	*oc;

	if (params[i][0] == '"')
	{
		oc = params[i];
		params[i] = ft_strimoc(params[i], '"');
		ft_strdel(&oc);
	}
	oc = ft_strchr(params[i], '=');
	if (oc)
		*oc = '\0';
	if (params[i][0] != '"' && params[i][0] != '.' && params[i][0]
	!= '/' && (!params[i][0] || ft_isdigit(params[i][0])
	|| !ft_isalnum(params[i][0]) || !ft_strcheck(params[i], "!@#$%^&*-,.")
	|| params[i][0] == '='))
	{
		if (oc)
			*oc = '=';
		ft_putstr_fd((builtin == 1 ? "setenv: '" : "env: '"), 2);
		ft_putstr_fd(params[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*ret = 0;
	}
	if (oc)
		*oc = '=';
}

int		checkenv_params(char **params, int builtin)
{
	int		i;
	int		ret;

	ret = 1;
	i = 1;
	while (params[i] && params[i][0] == '-')
		i++;
	while (params[i])
	{
		checkenv_check(i, &ret, params, builtin);
		i++;
	}
	return (ret);
}

int		setenv_builtin(char **params, t_env_list *env)
{
	if (params && env && checkenv_params(params, 1))
	{
		env = modify_env(params, env, 1);
		return (1);
	}
	return (0);
}

void	unset_errors(char *param)
{
	if (param)
	{
		ft_putstr_fd("unsetenv: '", 2);
		ft_putstr_fd(param, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
}

int		unsetenv_builtin(char **params, t_env_list *env)
{
	int			i;
	t_env_list	*tmp;

	if (params && env && (i = 1))
	{
		while (params[i] && (tmp = env))
		{
			if (ft_isdigit(params[i][0]) || ft_strchr(params[i], '='))
			{
				unset_errors(params[i]);
				break ;
			}
			while ((tmp = tmp->next))
			{
				if (ft_strcmp(params[i], tmp->var) == 0)
				{
					env_lstdelone(&tmp);
					break ;
				}
			}
			i++;
		}
		return (1);
	}
	return (0);
}
