/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 13:44:07 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 19:54:36 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <signal.h>

t_env_list	*modify_env(char **params, t_env_list *env, int skip_opt)
{
	int		i;
	char	*oc;

	if (params && env)
	{
		i = 1;
		while (skip_opt && params[i] && params[i][0] == '-')
			i++;
		while (params[i])
		{
			if (params[i][0] != '=' && (oc = ft_strchr(params[i], '=')))
				modify_envset(env, params[i], oc);
			i++;
		}
	}
	return (env);
}

t_env_list	*new_env(char **params, t_env_list *new)
{
	int		i;
	char	*var;
	char	*value;
	char	*oc;

	if (params && new)
	{
		i = 1;
		while (params[i] && params[i][0] == '-')
			i++;
		while ((oc = ft_strchr(params[i], '=')))
		{
			*oc = '\0';
			var = ft_strdup(params[i]);
			value = ft_strdup(&oc[1]);
			env_lstaddb(new, env_lstnew(var, value));
			*oc = '=';
			i++;
		}
	}
	return (new);
}

void		envbuiltin_exec(char **param, t_env_list *env, t_env_list *env_lst)
{
	int		process;
	char	**env_tab;
	char	*exec_p;

	if (param && *param && env)
	{
		process = fork();
		if (process > 0)
			wait(0);
		else if (process == 0)
		{
			env_tab = env_totab(&env_lst);
			exec_p = (*param[0] == '.' || *param[0] == '/' ? param[0]
					: exec_path(env, *param));
			if (execve((exec_p ? exec_p : param[0]), param, env_tab) == -1)
				exec_error((exec_p ? exec_p : param[0]), "env", -1);
			ft_strdel(&exec_p);
			free_tab(env_tab);
			exit(0);
		}
	}
}

int			env_builtin(char **params, t_env_list *env)
{
	int			i;
	t_env_list	*env_lst;

	if (params && env && checkenv_params(params, 0)
			&& (i = env_getopt(params)) >= 0)
	{
		env_lst = (modify_env(params, (i == 1 ? env_lstnew(NULL, NULL)
						: env_dup(env)), 1));
		i = 1;
		while (params[i] && (params[i][0] == '-' || ft_strchr(params[i], '=')))
			i++;
		if (params[i] && !is_builtin(params[i]))
			envbuiltin_exec(&params[i], env, env_lst);
		else
			print_env(env_lst);
		env_lstfree(&env_lst);
		return (1);
	}
	return (0);
}

void		print_env(t_env_list *env)
{
	t_env_list	*tmp;
	int			tty;

	if ((tmp = env))
	{
		tty = ttyslot();
		while ((tmp = tmp->next))
		{
			ft_putstr_fd(tmp->var, tty);
			ft_putchar_fd('=', tty);
			ft_putstr_fd(tmp->value, tty);
			ft_putchar_fd('\n', tty);
		}
	}
}
