/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:08:03 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/26 19:27:06 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	*transform(int *list, struct s_change actual, int length)
{
	if (actual.type == 2)
		list = transform_sa(list, actual.idx);
	else if (actual.type == 3)
		list = transform_sb(list, actual.idx);
	else if (actual.type == 4)
		list = transform_ss(list, actual.idx);
	else if (actual.type == 5)
		list = transform_ra(list, actual.idx);
	else if (actual.type == 6)
		list = transform_rb(list, actual.idx, length);
	else if (actual.type == 7)
		list = transform_rr(list, actual.idx, length);
	else if (actual.type == 8)
		list = transform_rra(list, actual.idx);
	else if (actual.type == 9)
		list = transform_rrb(list, actual.idx, length);
	else if (actual.type == 10)
		list = transform_rrr(list, actual.idx, length);
	return (list);
}
