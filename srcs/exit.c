/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:02:23 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/29 16:36:47 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	exit_builtin(char **params)
{
	int	i;
	int	ret;

	ret = 1;
	if (params)
	{
		ft_putendl("exit");
		i = 0;
		if (params[1] && !is_strdigit(params[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(params[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
		else if (params[1] && !params[2] && is_strdigit(params[1]))
			ret = ft_atoi(params[1]);
		else if (params[1] && params[2])
			ft_putstr_fd("exit: too many argument\n", 2);
	}
	exit(ret);
}
