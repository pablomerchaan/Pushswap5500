/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformrot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:22:41 by paperez-          #+#    #+#             */
/*   Updated: 2024/12/05 19:04:02 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	getcomp_1(struct s_rots rot)
{
	int	result;

	if (rot.type == 0 || rot.type == 1)
	{
		if (rot.steps_a == 0)
			result = rot.cost - rot.steps_b;
		else
			result = rot.cost - rot.steps_a;
	}
	if (rot.type == 2 || rot.type == 3)
		result = rot.steps_a;
	return (result);
}

int	getcomp_2(struct s_rots rot)
{
	int	result;

	if (rot.type == 0 || rot.type == 1)
	{
		if (rot.steps_a == 0)
			result = rot.steps_b;
		else
			result = rot.steps_a;
	}
	if (rot.type == 2 || rot.type == 3)
		result = rot.steps_b;
	return (result);
}

int	*do_rotations(struct s_l list, struct s_rots rot, int type_1, int type_2)
{
	struct s_change	rotation;
	int				c;
	int				comp_1;
	int				comp_2;

	comp_1 = getcomp_1(rot);
	comp_2 = getcomp_2(rot);
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
			do_rotations (list, rot, 7, 6);
		else
			do_rotations (list, rot, 7, 5);
	}
	if (rot.type == 1)
	{
		if (rot.steps_a == 0)
			do_rotations (list, rot, 10, 9);
		else
			do_rotations (list, rot, 10, 8);
	}
	if (rot.type == 2)
		do_rotations (list, rot, 5, 9);
	if (rot.type == 3)
		do_rotations (list, rot, 8, 6);
	return (list.list);
}
