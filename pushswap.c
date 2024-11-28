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
struct s_l	maketmpl(struct s_l list, struct s_rots rot)
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
}

int	rotaux(struct s_l list, int round, int size_segment, int current_cost)
{
	struct s_rots	goodrot;
	struct s_rots	candidate;
	int				current_min;
	int				good_cost;
	int				steps;
	int				i;

	steps = 0;
	while (round >= 0)
	{
		current_min = round * size_segment;
		i = -1;
		while (i != list.partition)
		{
			i = list.partition - 1;
			goodrot.type = -1;
			good_cost = INT_MAX;
			while (i >= 0)
			{
				if (list.list[i] >= current_min)
				{
					candidate = check(list.list, list.length, list.partition, i);
					current_cost = candidate.cost;
					current_cost += lookahead(list, candidate, current_min, g_lookahead);
					if (goodrot.type == -1 || current_cost < good_cost)
					{
						goodrot = candidate;
						good_cost = current_cost;
					}
		/*j = 0;
		while (j < list.length) {
			printf("%i ", list[j]);
			j++;
		}
		printf("\n\n");
		printf("Rots cost: %i, type: %i, A: %i, B: %i", goodrot.cost, goodrot.type, goodrot.steps_a, goodrot.stepsB);
		printf("\n\n");
		printf("Steps: %i", steps);
		printf("\n\n");*/
				}
				i--;
			}
			transformrot(list, goodrot);
			list.partition -= 1;
			steps += goodrot.cost + 1;
			i = 0;
			while (i < list.partition)
			{
				if (list.list[i] > current_min)
					break ;
				i++;
			}
		}
		round--;
	}
	return (steps);
}

int rotations(int *lst, int min, int max, int length)
{
	struct s_intsrot	intsr;
	struct s_change		rotation;
	struct s_l			list;
	double				size_segment;

	intsr.steps = 0;
	size_segment = (max - min) / g_segments;
	rotation.type = 0;
	rotation.idx = length;
	list.partition = length;
	list.length = length;
	list.list = lst;
	//intsr.steps += prerun(list.list, list.length);
	intsr.round = g_segments - 1;
	intsr.steps += rotaux(list, intsr.round, size_segment, intsr.current_cost);
	intsr.i = get_next(list.list, list.length, 0, INT_MIN);
	rotation.type = 9;
	rotation.idx = 0;
	intsr.j = 0;
	while (intsr.j < list.length - intsr.i)
	{
		transform(list.list, rotation, list.length);
		intsr.j++;
	}
	if (intsr.i == 0)
		intsr.i = list.length;
	intsr.steps += (list.length - intsr.i);
	intsr.steps += list.length;
	intsr.j = 0;
	while (intsr.j < list.length)
	{
		printf("%i ", list.list[intsr.j]);
		intsr.j++;
	}
	printf("\n\n");
	printf("Steps: %i", intsr.steps);
	printf("\n\n");
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
