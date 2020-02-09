/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:27:55 by ambelghi          #+#    #+#             */
/*   Updated: 2020/02/09 19:15:15 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "ft_select.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	size_handler(int sig)
{
	t_cs_line			*cs;
	//t_point				ew;
	//struct winsize	ws;

	if (sig == SIGWINCH && (cs = cs_master(NULL, 0)))
	{
		//	get_cs_line_position(&ew.x, &ew.y);
		cs->min_row = 0;
		cs->min_col = 0;
		ft_clear(1);
		cs_set(NULL, 0);
		int cr = get_line(cs);
	//	if (cr - cs->scroll + cs->min_row >= cs->screen.y)
	//		cs->scroll = cr - (cs->screen.y - cs->min_row - 1);
		//get_cs_line_position(&cs->min_col, &cs->min_row);
		if (cs->screen.x < 17)
			cs->min_col = (cs->scroll > 0 ? 0 : 1);
		else
			cs->min_col = 15;
		//int row_prompt = 1;
//		row_prompt = (PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) / (cs->screen.x - 1)	
//			+ (((PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) % (cs->screen.x - 1)) >= 0
//			? 1 : 0);
		cs->min_row = 0;// (cs->screen.x > 1 ? 0 : 1);//(PROMPT_SIZE + (cs->scroll > 0 ? 5 : 0)) / cs->screen.x;
		//	if (cs->cr - cs->scroll + cs->min_row >= cs->screen.y)
		cr = get_line(cs);
		cs->cr = cr;
		cs->scroll = cs->cr - (cs->screen.y - cs->min_row - 1);
		if (cs->scroll < 0)
			cs->scroll = 0;
		//cs->min_row = 0;
		//	cs->min_row += row_prompt;//PROMPT_SIZE / cs->screen.x;
	//	move_cs(&cs);
		print_cmdline(cs);
/*		cs->min_row = row_prompt - 1;
		move_cs(&cs);
		cs->min_row = 0;
*/	}
}

void	pause_handler(int sig)
{
	t_cs_line	*cs;

	//	if (sig == SIGCONT && (cs = cs_master(NULL, 0)))
	//		term_init(2, cs->av);
	if ((sig == SIGTSTP || sig == SIGTTIN || sig == SIGTTOU || sig == SIGSTOP)
			&& (cs = cs_master(NULL, 0)))
	{
		//		term_init(0, cs->av);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGSTOP, SIG_DFL);
		ioctl(cs->tty, TIOCSTI, "\x1A");
	}
}

void	sig_handler(int sig)
{
	t_cs_line *cs;

	if (sig >= 0 && (cs = cs_master(NULL, 0)))
	{
		ft_clear(0);
		term_init(0, NULL);
		if (cs->input)
			ft_strdel(&cs->input);
		cs->sig_int = 1;
		//		read_me(env_master(NULL, 0));
		//		ft_putstr_fd("\nminishell-1.0$ ", ttyslot());
		//exit(1);
	}
}
