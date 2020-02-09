/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:29:30 by ambelghi          #+#    #+#             */
/*   Updated: 2020/01/10 19:29:48 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int	echo_builtin(char **params)
{
	int	i;
	int	tty;

	if (params)
	{
		i = 1;
		tty = ttyslot();
		while (params[i])
		{
			ft_putstr_fd(params[i++], ttyslot());
			ft_putchar_fd(' ', ttyslot());
		}
		ft_putchar_fd('\n', ttyslot());
		return (1);
	}
	return (0);
}
