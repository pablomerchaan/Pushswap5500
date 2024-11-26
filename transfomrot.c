/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfomrot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:22:41 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/26 18:13:18 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int * do_rotations(struct l list, struct rots rot, int type_1, int type_2, int comp_1, int comp_2)
{
	int	c;
	struct	change rotation;

	rotation.type = type_1;
	rotation.idx = list.partition;
	c = 0;
	while (c < comp_1)
	{
		transform(list.list, rotation, list.length);
		c++;
	}
	rotation.type = type_2;
	rotation.idx = list.partition;
	c = 0;
	while (c < comp_2)
	{
		transform(list.list, rotation, list.length);
		c++;
	}
	return (list.list);
}

int *transformrot(struct l list, struct rots rot)
{
	int	c;
	struct	change rotation;

	if (rot.type == 0)
	{
		if (rot.stepsA == 0)
			do_rotations(list, rot, 7, 6, rot.cost - rot.stepsB, rot.stepsB);
		else
			do_rotations(list, rot, 7, 5, rot.cost - rot.stepsA, rot.stepsA);
	}
	if (rot.type == 1)
	{
		if (rot.stepsA == 0)
			do_rotations(list, rot, 10, 9, rot.cost - rot.stepsB, rot.stepsB);
		else
			do_rotations(list, rot, 10, 8, rot.cost - rot.stepsA, rot.stepsA);
	}
	if (rot.type == 2)
		do_rotations(list, rot, 5, 9,	rot.stepsA, rot.stepsB);
	if (rot.type == 3)
		do_rotations(list, rot, 8, 6,	rot.stepsA, rot.stepsB);
	return (list.list);
}
