/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:07:57 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/26 19:31:33 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	*transform_ra(int *list, int idx)
{
	int	tmp;
	int	c;

	tmp = list[idx - 1];
	c = idx - 1;
	while (c > 0)
	{
		list[c] = list[c - 1];
		c--;
	}
	list[0] = tmp;
	return (list);
}

int	*transform_rb(int *list, int idx, int length)
{
	int	tmp;
	int	c;

	tmp = list[idx];
	c = idx;
	while (c + 1 < length)
	{
		list[c] = list[c + 1];
		c++;
	}
	list[c] = tmp;
	return (list);
}

int	*transform_rr(int *list, int idx, int length)
{
	transform_ra (list, idx);
	transform_rb (list, idx, length);
	return (list);
}
