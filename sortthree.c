/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortthree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:22:37 by paperez-          #+#    #+#             */
/*   Updated: 2024/12/10 14:49:23 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	sortaux(int *list, int length, int c)
{
	if (list[c] < list[c + 1])
	{
		if (list[c + 1] < list[c + 2])
			return (0);
		else
		{
			transform_rra(list, length);
			if (list[c] < list[c + 1])
				transform_sa (list, length);
		}
		c++;
	}
	return (c);
}

int	sortthree(int *list, int length)
{
	int	c;

	c = 0;
	c = sortaux(list, length, c);
	if (c == 0)
	{
		if (list[2] < list[1])
		{
			transform_sa (list, length);
			transform_ra (list, length);
		}
		else if (list[2] < list[0])
		{
			transform_ra(list, length);
			transform_ra(list, length);
		}
		else
			transform_sa(list, length);
	}
	return (2);
}
