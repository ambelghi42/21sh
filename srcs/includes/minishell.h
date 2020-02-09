/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:04:48 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 20:00:24 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>

typedef struct	s_env_list
{
	char				*var;
	char				*value;
	struct s_env_list	*prev;
	struct s_env_list	*next;
}				t_env_list;

int				env_listcount(t_env_list *elem);
t_env_list		*env_lstnew(char *var, char *value);
void			env_lstaddb(t_env_list *start, t_env_list *new);
t_env_list		*env_tolist(char **env);
char			**env_totab(t_env_list **list);
char			*get_env(t_env_list *env, char *var);
char			*which_path(char **path, char *exec, int i);
char			*ft_which(char const *paths, char *exec);
void			free_tab(char **tab);
void			get_expansion(char **params, t_env_list *env);
char			*get_tilde(char *line, t_env_list *env);
char			*get_dollar(char *line, t_env_list *env);
char			**get_params(char *line, t_env_list *env);
char			*exec_path(t_env_list *env, char *line);
int				ft_checkopt(char c, char *options, char *name);
int				env_getopt(char **av);
t_env_list		*modify_env(char **params, t_env_list *env, int skip_opt);
t_env_list		*new_env(char **params, t_env_list *new);
int				env_builtin(char **params, t_env_list *env);
void			print_env(t_env_list *env);
void			set_env(t_env_list *env, char *var, char *value);
int				minishell_launch(t_env_list **env, char **params);
int				is_builtin(char *exec);
int				launch_builtin(t_env_list *env, char **params);
void			handle_sigint(int sig);
t_env_list		*env_dup(t_env_list *list);
void			env_lstfree(t_env_list **lst);
int				check_envprms(char **av);
void			envbuiltin_exec(char **param, t_env_list *env,
				t_env_list *env_lst);
int				setenv_builtin(char **params, t_env_list *env);
void			env_lstdelone(t_env_list **lst);
int				unsetenv_builtin(char **params, t_env_list *env);
int				echo_builtin(char **params);
int				exit_builtin(char **params);
int				cd_builtin(char **params, t_env_list *env);
void			cd_errors(char *path);
int				checkenv_params(char **params, int builtin);
int				exec_error(char *exec, char *program, int error);
int				minishell_fork(t_env_list **env, char **params, char *exec_p);
void			set_cdpwd(t_env_list *env, char *old_pwd);
int				msh_child(int init, int is_child);
int				get_interrupt(int init, int is_interrupt);
void			modify_envset(t_env_list *env, char *param, char *oc);

#endif
