/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:14:05 by paperez-          #+#    #+#             */
/*   Updated: 2024/05/29 12:19:06 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(void *p)
{
	unsigned long long	c;
	int					count;

	c = (unsigned long long) p;
	if (!p)
		return (ft_putstr("(nil)"));
	write (1, "0x", 2);
	count = ft_puthexaux(c, 'x', 2);
	return (count);
}
