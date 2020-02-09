/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:31:14 by ambelghi          #+#    #+#             */
/*   Updated: 2020/02/06 13:05:23 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_select.h"
#include "libft.h"

int		my_putchar(int c)
{
	ft_putchar_fd((char)c, ttyslot());
	return (1);
}

static char	**split_pos(const char *s)
{
	int		i;
	char	**ret;
	i = 0;
	while (*(s + i) && (*(s + i) == 27 || *(s + i) == '['))
		i++;
	ret = ft_strsplit((s + i), ";");
	return (ret);
}

void		get_cs_line_position(int *col, int *row)
{
	char	buf[16];
	char	**n;

	ft_bzero(&buf, 16);
	t_cs_line *cs = cs_master(NULL, 0);
	int fd = cs->tty;
	write(fd, "\033[6n", ft_strlen("\033[6n"));
	read(fd, &buf, 16);
	if (!(n = split_pos(buf)))
	{
		*col = 0;
		*row = 0;
		return ;
	}
//	read(ttyslot(), &buf, 0);
	*row = ft_atoi(n[0]) - 1;
	*col = ft_atoi(n[1]) - 1;
	ft_strdel(&n[0]);
	ft_strdel(&n[1]);
	free(n);

}

/*
void	get_cs_line_position(int *col, int *rows)
{
	char	buf[5];
	int		i;
	int		a;
	int		fd;
	int		len;

	a = 0;
	i = 0;
	fd = ttyslot();
	len = 0;
	write(fd, "\033[6n", 4);
	read(fd, buf, 4);
	buf[4] = '\0';
	while (buf[i])
	{
		if (buf[i] >= 48 && buf[i] <= 57)
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
				*col = ft_atoi(&buf[i]) - 1;
			a++;
		}
		i++;
	}
	read(fd, buf, 4);
}
*/
int		get_maxlen(t_line_lst *list)
{
	t_line_lst	*tmp;
	int				max_len;
	int				ncol;

	max_len = 0;
	ncol = 0;
	if ((tmp = list))
	{
		while ((tmp = tmp->next))
		{
	//		if ((ncol = ft_strlen(tmp->name)) > max_len)
	//			max_len = ncol;
		}
	}
	return (max_len);
}

void	putchar_n(char c, int n)
{
	t_cs_line	*cs;

	cs = cs_master(NULL, 0);
	while (n-- > 0)
		write(cs->tty, &c, 1);
}

int		get_nbmax(t_cs_line *cs)
{
	int	nb_max;

	nb_max = 1;
	if (cs)
	{
	//	nb_max = cs->scroll
	//		* (cs->max_col / (cs->max_len + 1) + 1)
	//		+ (cs->lines_col * (cs->max_col / (cs->max_len + 1) + 1)
	//				- cs->max_scroll - 1);
	//	nb_max = (nb_max > cs->nb_elem ? cs->nb_elem : nb_max);
	}
	return (nb_max);
}
