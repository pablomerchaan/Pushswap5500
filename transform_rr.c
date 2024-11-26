/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_rr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:07:38 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/26 19:29:26 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	*transform_rra(int *list, int idx)
{
	int	tmp;
	int	c;

	c = 0;
	tmp = list[0];
	while (c < idx - 1)
	{
		list[c] = list[c + 1];
		c++;
	}
	list[c] = tmp;
	return (list);
}

int	*transform_rrb(int *list, int idx, int length)
{
	int	tmp;
	int	c;

	tmp = list[length - 1];
	c = length - 1;
	while (c > idx)
	{
		list[c] = list[c - 1];
		c--;
	}
	list[idx] = tmp;
	return (list);
}

int	*transform_rrr(int *list, int idx, int length)
{
	int	*r;

	r = transform_rra(list, idx);
	r = transform_rrb(list, idx, length);
	return (r);
}
