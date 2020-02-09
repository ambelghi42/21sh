/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:49:19 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 19:43:48 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int	exec_error(char *exec, char *program, int error)
{
	if (error < 0)
	{
		ft_putstr_fd(program, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(exec, 2);
		if (access(exec, F_OK) == 0 && access(exec, X_OK) == -1)
			ft_putstr_fd(": permission denied\n", 2);
		else if (exec[0] == '.' || exec[0] == '/')
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
	}
	return (-1);
}

int	minishell_fork(t_env_list **env, char **params, char *exec_p)
{
	int		pid;
	int		ret;
	char	**envp;

	ret = 0;
	if (env && params && exec_p)
	{
		pid = fork();
		envp = NULL;
		if (pid == 0)
		{
			envp = env_totab(env);
			ret = execve(exec_p, params, envp);
			exec_error((exec_p ? exec_p : params[0]), "minishell", ret);
			exit(0);
		}
		else if (pid > 0)
			wait(0);
		free_tab(envp);
		ft_strdel(&exec_p);
	}
	return (ret);
}

int	minishell_launch(t_env_list **env, char **params)
{
	char	*exec_p;
	int		ret;

	ret = 0;
	if (env && params)
	{
		if (is_builtin(params[0]))
			return (launch_builtin(*env, params));
		exec_p = exec_path(*env, params[0]);
		if (!exec_p || !*exec_p)
		{
			exec_error(params[0], "minishell", -1);
			ft_strdel(&exec_p);
			return (-1);
		}
		msh_child(1, 1);
		ret = minishell_fork(env, params, exec_p);
		msh_child(1, 0);
	}
	return (ret);
}

int	is_builtin(char *exec)
{
	if (ft_strcmp(exec, "env") == 0)
		return (1);
	else if (ft_strcmp(exec, "setenv") == 0)
		return (1);
	else if (ft_strcmp(exec, "unsetenv") == 0)
		return (1);
	else if (ft_strcmp(exec, "echo") == 0)
		return (1);
	else if (ft_strcmp(exec, "exit") == 0)
		return (1);
	else if (ft_strcmp(exec, "cd") == 0)
		return (1);
	return (0);
}

int	launch_builtin(t_env_list *env, char **params)
{
	if (env && params)
	{
		if (ft_strcmp(params[0], "env") == 0)
			return (env_builtin(params, env));
		else if (ft_strcmp(params[0], "setenv") == 0)
			return (setenv_builtin(params, env));
		else if (ft_strcmp(params[0], "unsetenv") == 0)
			return (unsetenv_builtin(params, env));
		else if (ft_strcmp(params[0], "echo") == 0)
			return (echo_builtin(params));
		else if (ft_strcmp(params[0], "exit") == 0)
			return (exit_builtin(params));
		else if (ft_strcmp(params[0], "cd") == 0)
			return (cd_builtin(params, env));
	}
	return (0);
}
