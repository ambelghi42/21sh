/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 19:25:38 by ambelghi          #+#    #+#             */
/*   Updated: 2020/02/04 14:00:53 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "ft_select.h"

void	handle_sigint(int sig)
{
	t_cs_line	*cs;

	if (sig == SIGINT && (cs = cs_master(NULL, 0)))
	{
		ft_clear(0);
        term_init(0, NULL);
        if (cs->input)
			ft_strdel(&cs->input);
		if (msh_child(0, 0) == 0)
		{
			ft_putstr_fd("\nminishell-1.0$ ", ttyslot());
		}
		else
			get_interrupt(1, 1);
	}
}

int		msh_child(int init, int is_child)
{
	static int ew = 0;

	if (init == 1)
		ew = is_child;
	return (ew);
}

int		get_interrupt(int init, int is_interrupt)
{
	static int ew = 0;

	if (init == 1)
		ew = is_interrupt;
	return (ew);
}
