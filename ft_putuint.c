/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:48:45 by paperez-          #+#    #+#             */
/*   Updated: 2024/04/28 17:51:53 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	numlen(unsigned int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_putuint(unsigned int nb)
{
	unsigned int	c;
	char			d[1];
	int				count;

	count = numlen(nb);
	c = nb;
	if (nb > 9)
	{
		c %= 10;
		ft_putuint(nb / 10);
	}
	d[0] = c + '0';
	write (1, d, 1);
	return (count);
}
