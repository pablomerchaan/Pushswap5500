/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookahead.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:17:02 by paperez-          #+#    #+#             */
/*   Updated: 2024/12/10 13:17:24 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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

struct s_intslk	lkaux2(double c_m, int d, struct s_intslk ints, struct s_l tmpl)
{
	struct s_rots	candidate;
	struct s_rots	goodrot;

	goodrot.type = -1;
	while (ints.i >= 0)
	{
		if (tmpl.list[ints.i] >= c_m)
		{
			candidate = check(tmpl.list, tmpl.length, tmpl.partition, ints.i);
			ints.current_cost = candidate.cost;
			if (g_reclook == 1 && d > 1)
			{
				ints.current_cost += lookahead(tmpl, candidate, c_m, d - 1);
			}
			if (goodrot.type == -1 || ints.current_cost < ints.good_cost)
			{
				goodrot = candidate;
				ints.good_cost = ints.current_cost;
			}
		}
		ints.i--;
	}
	return (ints);
}

struct s_rots	lkaux1(double c_m, int d, struct s_intslk ints, struct s_l tmpl)
{
	struct s_rots	candidate;
	struct s_rots	goodrot;

	goodrot.type = -1;
	while (ints.i >= 0)
	{
		if (tmpl.list[ints.i] >= c_m)
		{
			candidate = check(tmpl.list, tmpl.length, tmpl.partition, ints.i);
			ints.current_cost = candidate.cost;
			if (g_reclook == 1 && d > 1)
			{
				ints.current_cost += lookahead(tmpl, candidate, c_m, d - 1);
			}
			if (goodrot.type == -1 || ints.current_cost < ints.good_cost)
			{
				goodrot = candidate;
				ints.good_cost = ints.current_cost;
			}
		}
		ints.i--;
	}
	return (goodrot);
}
