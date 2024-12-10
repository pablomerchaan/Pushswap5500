/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:40:36 by paperez-          #+#    #+#             */
/*   Updated: 2024/12/10 14:16:53 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static char	maphexa(unsigned int h, char c)
{
	char	res;

	if (h > 9 && c == 'x')
		res = (h - 10 + 'a');
	else if (h > 9 && c == 'X')
		res = (h - 10 + 'A');
	else
		res = h + '0';
	return (res);
}

int	ft_puthexaux(unsigned long long h, const char c, int count)
{
	unsigned long long	h2;
	char				s;

	if (h < 16)
	{
		s = maphexa(h, c);
		write (1, &s, 1);
		count++;
		return (count);
	}
	if (h >= 16)
	{
		h2 = h / 16;
		count = ft_puthexaux(h2, c, count);
		s = maphexa(h % 16, c);
		write (1, &s, 1);
		count++;
	}
	return (count);
}
