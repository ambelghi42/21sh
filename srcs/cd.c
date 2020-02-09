/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:29:31 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/16 19:54:41 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	cd_oldpwd(t_env_list *env, char *params, char **path)
{
	if (params && path && ft_strcmp(params, "-") == 0)
	{
		if (!((*path = get_env(env, "OLDPWD")) && *path))
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		else
			ft_putendl(*path);
	}
	else if ((!params || !*params) && !(get_env(env, "HOME")))
		ft_putstr_fd("cd: HOME not set\n", 2);
}

int		cd_builtin(char **params, t_env_list *env)
{
	char	*path;
	char	*old_pwd;
	int		i;

	if (params && env)
	{
		i = 1;
		path = NULL;
		while (params[i] && params[i][0] == '-'
				&& !ft_strstr(params[i], "---")
				&& ft_strcmp(params[i], "-") != 0)
			i++;
		path = (!params[i] || !*params[i] ? get_env(env, "HOME") : params[i]);
		cd_oldpwd(env, params[i], &path);
		old_pwd = getcwd(NULL, 0);
		if (path && *path && chdir(path) < 0)
			cd_errors(path);
		if (path && *path)
			set_cdpwd(env, old_pwd);
		if (!path)
			ft_strdel(&old_pwd);
	}
	return (0);
}

void	cd_errors(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (access(path, R_OK) == -1)
	{
		ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
}

void	set_cdpwd(t_env_list *env, char *old_pwd)
{
	char	*pwd;
	char	*pwd2;

	if ((pwd = getcwd(NULL, 0)))
	{
		pwd2 = get_env(env, "PWD");
		if (pwd2)
			ft_strdel(&old_pwd);
		if (get_env(env, "OLDPWD"))
			set_env(env, "OLDPWD", pwd2 ? ft_strdup(pwd2) : old_pwd);
		else
			env_lstaddb(env, env_lstnew(ft_strdup("OLDPWD"),
						pwd2 ? ft_strdup(pwd2) : old_pwd));
		if (get_env(env, "PWD"))
			set_env(env, "PWD", pwd);
		else
			env_lstaddb(env, env_lstnew(ft_strdup("PWD"), pwd));
	}
}
