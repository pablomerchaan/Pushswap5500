/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfomrot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:22:41 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/28 17:14:40 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	*do_rotations(struct s_l list, struct s_rots rot, int type_1, int type_2, int comp_1, int comp_2)
{
	struct s_change	rotation;
	int				c;

	rotation.type = type_1;
	rotation.idx = list.partition;
	c = 0;
	while (c < comp_1)
	{
		transform (list.list, rotation, list.length);
		c++;
	}
	rotation.type = type_2;
	rotation.idx = list.partition;
	c = 0;
	while (c < comp_2)
	{
		transform (list.list, rotation, list.length);
		c++;
	}
	return (list.list);
}

int	*transformrot(struct s_l list, struct s_rots rot)
{
	if (rot.type == 0)
	{
		if (rot.steps_a == 0)
			do_rotations (list, rot, 7, 6, rot.cost - rot.steps_b, rot.steps_b);
		else
			do_rotations (list, rot, 7, 5, rot.cost - rot.steps_a, rot.steps_a);
	}
	if (rot.type == 1)
	{
		if (rot.steps_a == 0)
			do_rotations (list, rot, 10, 9, rot.cost - rot.steps_b, rot.steps_b);
		else
			do_rotations (list, rot, 10, 8, rot.cost - rot.steps_a, rot.steps_a);
	}
	if (rot.type == 2)
		do_rotations (list, rot, 5, 9, rot.steps_a, rot.steps_b);
	if (rot.type == 3)
		do_rotations (list, rot, 8, 6, rot.steps_a, rot.steps_b);
	return (list.list);
}
