/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:25:49 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/26 18:17:56 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

const int g_segments = 9;
const int g_lookahead = 60;
const int g_reclook = 0;
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
int lookahead(struct l list, struct rots rot, double current_min, int depth){
	struct	l tmpl;
	int	i;
	int	cost;
	int	current_depth;
	struct	rots goodrot;
	struct	rots candidate;
	int	current_cost;
	int	good_cost;

	if (depth == 0)
		return 0;

	cost = 0;
	current_depth = 0;
	tmpl.list = malloc(sizeof(int) * (list.length));
	i = 0;
	while (i < list.length) {
		tmpl.list[i] = list.list[i];
		i++;
	}
	tmpl.length = list.length;
	tmpl.partition = list.partition;
	transformrot(tmpl, rot);
	current_depth = 1;

	while (current_depth <= depth && list.partition > 0) {
		i = list.partition - 1;
		goodrot.type = -1;
		good_cost = INT_MAX;
		while (i >= 0) {
	if (tmpl.list[i] >= current_min) {
				candidate = check(tmpl.list, list.length, list.partition, i);
				current_cost = candidate.cost;
				if (g_reclook == 1 && depth > 1)
				{
					tmpl.length = list.length;
					tmpl.partition = list.partition;
					current_cost += lookahead(tmpl, candidate, current_min, depth - 1);
				}
					if (goodrot.type == -1 || current_cost < good_cost) {
					goodrot = candidate;
					good_cost = current_cost;
				}
			}
			i--;
		}
		if (goodrot.type != -1) {
			tmpl.length = list.length;
			tmpl.partition = list.partition;
			transformrot(tmpl, goodrot);
			cost += goodrot.cost;
			list.partition -= 1;
		}
		current_depth += 1;
	}
	free(tmpl.list);
	return cost;
}

int	rotaux(struct l list, int round, int size_segment, int current_cost, int steps)
{
	int		i;
	struct rots	goodrot;
	struct rots	candidate;
	int		current_min;
	int		good_cost;

	while (round >= 0) {
		current_min = round * size_segment;
		i = -1;
		while (i != list.partition) {
			i = list.partition - 1;
			goodrot.type = -1;
			good_cost = INT_MAX;
			while (i >= 0) {
				if (list.list[i] >= current_min) {
					candidate = check(list.list, list.length, list.partition, i);
					current_cost = candidate.cost;
					current_cost += lookahead(list, candidate, current_min, g_lookahead);
					if (goodrot.type == -1 || current_cost < good_cost) {
						goodrot = candidate;
						good_cost = current_cost;
					}
		 /*j = 0;
		 while (j < list.length) {
			 printf("%i ", list[j]);
			 j++;
		 }
		 printf("\n\n");
		 printf("Rots cost: %i, type: %i, A: %i, B: %i", goodrot.cost, goodrot.type, goodrot.stepsA, goodrot.stepsB);
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
			while (i < list.partition) {
				if (list.list[i] > current_min)
					break;
				i++;
			}
		}
		round--;
	}
	return (steps);
}

int rotations(int *lst, int min, int max, int length){
	double	size_segment;
	int	j;
	int	i;
	int	round;
	struct	l list;
	int	current_steps;
	int	steps;
	struct	change	rotation;
	int	current_cost;

	steps = 0;
	size_segment = (max - min) / g_segments;
	rotation.type = 0;
	rotation.idx = length;
	list.partition = length;
	list.length = length;
	list.list = lst;

	//steps += prerun(list.list, list.length);

	round = g_segments - 1;
	steps += rotaux(list, round, size_segment, current_cost, steps);
	i = get_next(list.list, list.length, 0, INT_MIN);
	rotation.type = 9;
	rotation.idx = 0;
	j = 0;
	while (j < list.length - i) {
		transform(list.list, rotation, list.length);
		j++;
	}
	if (i == 0)
		i = list.length;
	steps += (list.length - i);
	/*printf("\n\n");
	printf("Steps withoout list.length: %i", steps);
	printf("\n\n");
	printf("\n\n");
	printf("Length: %i", list.length);
	printf("\n\n");*/
	steps += list.length;
	j = 0;
	while (j < list.length) {
		printf("%i ", list.list[j]);
		j++;
	}
	printf("\n\n");
	printf("Steps: %i", steps);
	printf("\n\n");
	return (steps);
}

int main(int argc, char **argv) {
	
	struct	l list;
	int	cum;
	int	max;
	int	min;

	cum = 0;
	list.list = NULL;
	if (argc < 2)
		printf("mensaje de error");
	list.list = malloc(sizeof(int) * (argc - 1));
	list.length = 0;
	max = INT_MIN;
	min = INT_MAX;
	while (list.length < argc - 1) {
		list.list[list.length] = ft_atoi(argv[list.length + 1]);
		if (list.list[list.length] > max)
			max = list.list[list.length];
		if (list.list[list.length] < min)
			min = list.list[list.length];
		list.length++;
	}
	cum += rotations(list.list, min, max, list.length);
	free(list.list);
	return (0);
}
