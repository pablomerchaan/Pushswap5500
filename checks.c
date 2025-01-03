/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:51:30 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/28 16:52:11 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

struct s_rots	check_rrarrb(int *list, int length, int partition, int idx)
{
	struct s_rots	rot;
	int				steps_a;
	int				steps_b;
	int				next;

	next = get_next(list, length, partition, list[idx]);
	steps_a = idx + 1;
	steps_b = length - next;
	rot.type = 1;
	if (steps_a < steps_b)
		rot.cost = steps_b;
	else
		rot.cost = steps_a;
	rot.steps_a = rot.cost - steps_b;
	rot.steps_b = rot.cost - steps_a;
	return (rot);
}

struct s_rots	check_rarb(int *list, int length, int partition, int idx)
{
	struct s_rots	rot;
	int				steps_a;
	int				steps_b;
	int				next;

	next = get_next(list, length, partition, list[idx]);
	steps_a = partition - idx - 1;
	steps_b = next - partition;
	if (steps_b < 0)
		steps_b = 0;
	rot.type = 0;
	if (steps_a < steps_b)
		rot.cost = steps_b;
	else
		rot.cost = steps_a;
	rot.steps_a = rot.cost - steps_b;
	rot.steps_b = rot.cost - steps_a;
	return (rot);
}

struct s_rots	check_rrarb(int *list, int length, int partition, int idx)
{
	struct s_rots	rot;
	int				steps_a;
	int				steps_b;
	int				next;

	next = get_next(list, length, partition, list[idx]);
	steps_a = idx + 1;
	steps_b = next - partition;
	rot.type = 3;
	rot.cost = steps_a + steps_b;
	rot.steps_a = steps_a;
	rot.steps_b = steps_b;
	return (rot);
}

struct s_rots	check_rarrb(int *list, int length, int partition, int idx)
{
	struct s_rots	rot;
	int				steps_a;
	int				steps_b;
	int				next;

	next = get_next(list, length, partition, list[idx]);
	steps_a = partition - idx - 1;
	steps_b = length - next;
	rot.type = 2;
	rot.cost = steps_a + steps_b;
	rot.steps_a = steps_a;
	rot.steps_b = steps_b;
	return (rot);
}

struct s_rots	check(int *list, int length, int partition, int idx)
{
	struct s_rots	current_min;
	struct s_rots	candidate;

	current_min = check_rarb(list, length, partition, idx);
	candidate = check_rrarrb(list, length, partition, idx);
	if (candidate.cost < current_min.cost)
		current_min = candidate;
	candidate = check_rarrb(list, length, partition, idx);
	if (candidate.cost < current_min.cost)
		current_min = candidate;
	candidate = check_rrarb(list, length, partition, idx);
	if (candidate.cost < current_min.cost)
		current_min = candidate;
	return (current_min);
}
