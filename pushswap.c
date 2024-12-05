/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:25:49 by paperez-          #+#    #+#             */
/*   Updated: 2024/12/05 19:36:13 by paperez-         ###   ########.fr       */
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
			ints.i = list.partition - 1;
			goodrot.type = -1;
			ints.good_cost = INT_MAX;
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

	while (ints.i >= 0)
	{
		if (list.list[ints.i] >= ints.current_min)
		{
			candidate = check(list.list, list.length, list.partition, ints.i);
			current_cost = candidate.cost;
			current_cost += lookahead(list, candidate, ints.current_min, g_lookahead);
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

int	rotations(int *lst, int min, int max, int length)
{
	struct s_intsrot	intsr;
	struct s_change		rotation;
	struct s_l			list;
	double				size_segment;

	intsr.steps = 0;
	size_segment = (max - min) / g_segments;
	list.partition = length;
	list.length = length;
	list.list = lst;
	intsr.round = g_segments - 1;
	intsr.current_cost = 0;
	intsr.steps += rotaux(list, intsr.round, size_segment, intsr.current_cost);
	intsr.i = get_next(list.list, list.length, 0, INT_MIN);
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
  /* remove vvv
	intsr.j = 0;
	while (intsr.j < list.length)
	{
		printf("%i ", list.list[intsr.j]);
		intsr.j++;
	}
	printf("\n\n");
	printf("Steps: %i", intsr.steps);
	printf("\n\n");
  // remove ^^^*/
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
			printf("ERROR");
			return ('\0');
		}
		list.list[list.length] = ft_atoi(argv[list.length + 1]);
		if (list.list[list.length] > max)
			max = list.list[list.length];
		if (list.list[list.length] < min)
			min = list.list[list.length];
		list.length++;
	}
	/*
	if (list.length < 6)
		cum += sortfive();//TODO funcion que ordene 3 y 5 numeros.
	else*/
	cum += rotations (list.list, min, max, list.length);
	free (list.list);
	return (0);
}
