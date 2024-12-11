/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:25:49 by paperez-          #+#    #+#             */
/*   Updated: 2024/12/11 13:51:01 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	rotaux(struct s_l list, int round, int size_segment, int current_cost)
{
	struct s_rots		goodrot;
	struct s_intsaux	ints;

	ints.steps = 0;
	while (round >= 0)
	{
		ints.current_min = round * size_segment;
		ints.i = -1;
		while (ints.i != list.partition)
		{
			goodrot = auxaux(ints, list, goodrot, current_cost);
			transformrot(list, goodrot);
			emit_from_rots(goodrot);
			list.partition -= 1;
			printf("PB\n");
			ints.steps += goodrot.cost + 1;
			ints.i = 0;
			while (ints.i < list.partition)
			{
				if (list.list[ints.i] > ints.current_min)
					break ;
				ints.i++;
			}
		}
		round--;
	}
	return (ints.steps);
}

struct s_rots	auxaux(struct s_intsaux ints,
			struct s_l list, struct s_rots goodrot, int current_cost)
{
	struct s_rots	candidate;

	ints.i = list.partition - 1;
	goodrot.type = -1;
	ints.good_cost = INT_MAX;
	while (ints.i >= 0)
	{
		if (list.list[ints.i] >= ints.current_min)
		{
			candidate = check(list.list, list.length, list.partition, ints.i);
			current_cost = candidate.cost;
			current_cost += lookahead(list, candidate, ints.current_min, 60);
			if (goodrot.type == -1 || current_cost < ints.good_cost)
			{
				goodrot = candidate;
				ints.good_cost = current_cost;
			}
		}
		ints.i--;
	}
	return (goodrot);
}

int	emitlaststeps(struct s_intsrot intsr, int length, struct s_l list)
{
	struct s_change		rotation;
	
	rotation.type = 9;
	rotation.idx = 0;
	intsr.j = 0;
	if (intsr.i == 0)
		intsr.i = list.length;
	while (intsr.j < list.length - intsr.i)
	{
		transform(list.list, rotation, list.length);
		emit_step(rotation.type);
		intsr.j++;
	}
	intsr.steps += (list.length - intsr.i);
	intsr.steps += list.length;
	intsr.i = 0;
	while (intsr.i < length)
	{
		emit_step(0);
		intsr.i++;
	}
	return (intsr.steps);
}
	
int	rotations(int *lst, int min, int max, int length)
{
	struct s_intsrot	intsr;
	struct s_l			list;
	double				size_segment;

	intsr.steps = 0;
	size_segment = (max - min) / 9;
	list.partition = length;
	list.length = length;
	list.list = lst;
	intsr.round = 8;
	intsr.current_cost = 0;
	if (length < 4)
	{
		intsr.steps += sortthree(lst, length);
		return (intsr.steps);
	}
	else if (length < 15)
		intsr.steps += rotaux(list, 1, length, intsr.current_cost);
	else
		intsr.steps += rotaux(list, intsr.round, size_segment, intsr.current_cost);
	intsr.i = get_next(list.list, list.length, 0, INT_MIN);
	intsr.steps += emitlaststeps(intsr, length, list);
	return (intsr.steps);
}

int	main(int argc, char **argv)
{
	struct s_l	list;
	int			cum;
	int			max;
	int			min;

	cum = 0;
	list.list = NULL;
	if (argc < 2)
		printf ("mensaje de error");
	list.list = malloc (sizeof(int) * (argc - 1));
	list.length = 0;
	max = INT_MIN;
	min = INT_MAX;
	while (list.length < argc - 1)
	{
		if (ft_atoi(argv[list.length + 1]) == '\0')
		{
			printf("Error");
			return ('\0');
		}
		list.list[list.length] = ft_atoi(argv[list.length + 1]);
		if (list.list[list.length] > max)
			max = list.list[list.length];
		if (list.list[list.length] < min)
			min = list.list[list.length];
		list.length++;
	}
	if (sorted(list.list, list.length) == 0)
		return (0);
	cum += rotations (list.list, min, max, list.length);
	free (list.list);
	return (0);
}
