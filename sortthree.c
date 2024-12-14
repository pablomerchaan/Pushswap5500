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
			emit_step(8);
			if (list[c] < list[c + 1])
			{
				transform_sa (list, length);
				emit_step(2);
			}
		}
		c++;
	}
	return (c);
}
void	sortaux2(int *list, int length)
{
	if (list[2] < list[1])
	{
		transform_sa (list, length);
		emit_step(2);
		transform_ra (list, length);
		emit_step(5);
	}
	else if (list[2] < list[0])
	{
		transform_ra(list, length);
		emit_step(5);
		transform_ra(list, length);
		emit_step(5);
	}
}

int	sortthree(int *list, int length)
{
	int	c;

	c = 0;
	c = sortaux(list, length, c);
	if (c == 0)
	{
		if (list[2] < list[1] || list[1] < list[2])
			sortaux2(list, length);
		else
		{
			transform_sa(list, length);
			emit_step(2);
		}
	}
	return (2);
}
