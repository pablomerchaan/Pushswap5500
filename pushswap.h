/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:58:52 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/26 20:12:39 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>

static const int	g_segments = 9;
static const int	g_lookahead = 60;
static const int	g_reclook = 0;

enum e_type_of_change
{
	PA,
	PB,
	SA,
	SB,
	SS,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
};

struct s_change
{
	enum e_type_of_change	type;
	int			idx;
};

struct s_rots
{
	int	type;
	int	cost;
	int	idx;
	int	steps_a;
	int	steps_b;
};

struct s_l
{
	int	*list;
	int	length;
	int	partition;
};

int	*transformrot(struct s_l list, struct s_rots rot);
struct	s_rots check(int *list, int length, int partition, int idx);
int	get_next(int *list, int length, int partition, int num);
int	ft_atoi(const char *str);
int	sq(int c);
int	*convert(struct s_change prev, struct s_change actual);
int	*transform(int *list, struct s_change actual, int length);
int	*transform_sa(int *list, int idx);
int	*transform_sb(int *list, int idx);
int	*transform_ss(int *list, int idx);
int	*transform_ra(int *list, int idx);
int	*transform_rb(int *list, int idx, int length);
int	*transform_rr(int *list, int idx, int length);
int	*transform_rra(int *list, int idx);
int	*transform_rrb(int *list, int idx, int length);
int	*transform_rrr(int *list, int idx, int length);
int	rotations(int *list, int min, int max, int length);
struct	s_rots  minrot(struct s_rots rot1, struct s_rots rot2);
