/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strselect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmerieux <hmerieux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:52:42 by hmerieux          #+#    #+#             */
/*   Updated: 2020/01/12 18:52:50 by hmerieux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_lenselect(char *str, char c)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str != c)
			i++;
		str++;
	}
	return (i);
}

static void		ft_cpyselect(char *src, char *dst, char c)
{
	while (*src)
	{
		if (*src == c)
			src++;
		else
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
}

char			*ft_strselect(char *str, char c)
{
	char	*dst;
	int		len;

	len = ft_lenselect(str, c);
	dst = ft_strnew(len);
	if (!dst)
		return (NULL);
	ft_cpyselect(str, dst, c);
	return (dst);
}