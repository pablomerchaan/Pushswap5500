/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:25:49 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/28 16:49:16 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/*
int prerun(int *list, int length){
  struct change swap;
  int i;
  int type;
  int steps;

  i = 0;
  type = 1;
  steps = 0;
  while (i <= length) {
    swap.idx = 0;
    if (i > 0 && list[i - 1] > list[i])
      type *= 2;
    if (i < length - 1 && list[i + 1] > list[i + 2])
      type *= 3;

    if (type == 2)
      swap.type = 2;
    if (type == 3)
      swap.type = 3;
    if (type == 6)
      swap.type = 4;

    if (type != 1) {
      transform(list, swap, length);
      steps += 1;
    }
    steps += 1;
    i++;
  }
  return(steps);
}
*/
struct s_l	maketmpl(struct s_l list, struct s_rots rot, int sw)
{
	struct s_l	tmpl;
	int			i;

	i = 0;
	tmpl.list = malloc(sizeof(int) * (list.length));
	while (i < list.length)
	{
		tmpl.list[i] = list.list[i];
		i++;
	}
	tmpl.length = list.length;
	tmpl.partition = list.partition;
	if (sw == 0)
		transformrot(tmpl, rot);
	return (tmpl);
}
/*
int	checktype(struct s_l list, struct s_l tmpl, struct s_rots goodrot, int cost)
{
	if (goodrot.type != -1)
	{
		tmpl.length = list.length;
		tmpl.partition = list.partition;
		transformrot(tmpl, goodrot);
		cost += goodrot.cost;
		list.partition -= 1;
	}
	return (cost);
	//TODO averiguar por qué esta función hace que el coste aumente.
}
*/

struct s_l	completetmpl(struct s_l tmpl, struct s_l list)
{
	tmpl.length = list.length;
	tmpl.partition = list.partition;
	return (tmpl);
}
/*
int	lookahead(struct s_l list, struct s_rots rot, double current_min, int depth)
{
	struct s_intslk	intslk;
	struct s_rots	goodrot;
	struct s_rots	candidate;
	struct s_l		tmpl;

	if (depth == 0)
		return (0);
	intslk.cost = 0;
	tmpl = maketmpl(list, rot);
	intslk.current_depth = 1;
	while (intslk.current_depth <= depth && list.partition > 0)
	{
		intslk.i = list.partition - 1;
		goodrot.type = -1;
		intslk.good_cost = INT_MAX;
		while (intslk.i >= 0)
		{
			if (tmpl.list[intslk.i] >= current_min)
			{
				candidate = check(tmpl.list, list.length, list.partition, intslk.i);
				intslk.current_cost = candidate.cost;
				if (g_reclook == 1 && depth > 1)
				{
					tmpl = completetmpl (tmpl, list);
					intslk.current_cost += lookahead(tmpl, candidate, current_min, depth - 1);
				}
				if (goodrot.type == -1 || intslk.current_cost < intslk.good_cost)
				{
					goodrot = candidate;
					intslk.good_cost = intslk.current_cost;
				}
			}
			intslk.i--;
		}
		if (goodrot.type != -1)
		{
			tmpl = completetmpl(tmpl, list);
			transformrot(tmpl, goodrot);
			intslk.cost += goodrot.cost;
			list.partition -= 1;
		}
		intslk.current_depth += 1;
	}
	free (tmpl.list);
	return (intslk.cost);
}*/
int	lookahead(struct s_l list, struct s_rots rot, double current_min, int depth)
{
	struct s_intslk	intslk;
	struct s_rots	goodrot;
	struct s_l		tmpl;

	intslk.cost = 0;
	tmpl = maketmpl(list, rot, 0);
	intslk.current_depth = 1;
	while (intslk.current_depth <= depth && list.partition > 0)
	{
		intslk.i = list.partition - 1;
		intslk.good_cost = INT_MAX;
		tmpl = completetmpl (tmpl, list);
		goodrot = lkaux1(current_min, depth, intslk, tmpl);
		intslk = lkaux2(current_min, depth, intslk, tmpl);
		if (goodrot.type != -1)
		{
			tmpl = completetmpl(tmpl, list);
			transformrot(tmpl, goodrot);
			intslk.cost += goodrot.cost;
			list.partition -= 1;
		}
		intslk.current_depth += 1;
	}
	free (tmpl.list);
	return (intslk.cost);
}

struct s_intslk	lkaux2( double current_min, int depth, struct s_intslk intslk, struct s_l tmpl)
{
	struct s_rots candidate;
	struct s_rots goodrot;

	goodrot.type = -1;
	while (intslk.i >= 0)
	{
		if (tmpl.list[intslk.i] >= current_min)
		{
			candidate = check(tmpl.list, tmpl.length, tmpl.partition, intslk.i);
			intslk.current_cost = candidate.cost;
			if (g_reclook == 1 && depth > 1)
			{
				intslk.current_cost += lookahead(tmpl, candidate, current_min, depth - 1);
			}
			if (goodrot.type == -1 || intslk.current_cost < intslk.good_cost)
			{
				goodrot = candidate;
				intslk.good_cost = intslk.current_cost;
			}
		}
		intslk.i--;
	}
	return (intslk);
}

struct s_rots	lkaux1( double current_min, int depth, struct s_intslk intslk, struct s_l tmpl)
{
	struct s_rots candidate;
	struct s_rots goodrot;

	goodrot.type = -1;
	while (intslk.i >= 0)
	{
		if (tmpl.list[intslk.i] >= current_min)
		{
			candidate = check(tmpl.list, tmpl.length, tmpl.partition, intslk.i);
			intslk.current_cost = candidate.cost;
			if (g_reclook == 1 && depth > 1)
			{
				intslk.current_cost += lookahead(tmpl, candidate, current_min, depth - 1);
			}
			if (goodrot.type == -1 || intslk.current_cost < intslk.good_cost)
			{
				goodrot = candidate;
				intslk.good_cost = intslk.current_cost;
			}
		}
		intslk.i--;
	}
	return (goodrot);
}

int	rotaux(struct s_l list, int round, int size_segment, int current_cost)
{
	struct s_rots	goodrot;
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

struct s_rots	auxaux(struct s_intsaux ints, struct s_l list, struct s_rots goodrot, int current_cost)
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

int rotations(int *lst, int min, int max, int length)
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
	intsr.steps += rotaux(list, intsr.round, size_segment, intsr.current_cost);
	intsr.i = get_next(list.list, list.length, 0, INT_MIN);
	rotation.type = 9;
	rotation.idx = 0;
	intsr.j = 0;
	while (intsr.j < list.length - intsr.i)
	{
		transform(list.list, rotation, list.length);
		emit_step(rotation.type);
		intsr.j++;
	}
	intsr.steps += (list.length - intsr.i);
	if (intsr.i == 0)
		intsr.i = list.length;
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
		printf("mensaje de error");
	list.list = malloc(sizeof(int) * (argc - 1));
	list.length = 0;
	max = INT_MIN;
	min = INT_MAX;
	while (list.length < argc - 1)
	{
		list.list[list.length] = ft_atoi(argv[list.length + 1]);
		if (list.list[list.length] > max)
			max = list.list[list.length];
		if (list.list[list.length] < min)
			min = list.list[list.length];
		list.length++;
	}
	cum += rotations (list.list, min, max, list.length);
	free (list.list);
	return (0);
}
