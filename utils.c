/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:10:52 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/28 14:38:57 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ft_atoi(const char *str)
{
	int		result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	gnaux(int c, int partition, int *list, int next)
{
	while (c != partition)
	{
		if (list[c] < list[next])
			next = c;
		c--;
	}
	return (next);
}

int	get_next(int *list, int length, int partition, int num)
{
	int	c;
	int	next;
	int	current_next;

	if (partition == length)
		return (length - 1);
	c = partition;
	next = partition;
	current_next = INT_MAX;
	while (c < length)
	{
		if (list[c] - num < current_next && list[c] - num > 0)
		{
			current_next = list[c] - num;
			next = c;
		}
		c++;
	}
	c--;
	if (current_next == INT_MAX)
		next = gnaux(c, partition, list, next);
	return (next);
}

int	getmin(int A, int B)
{
	if (A < B)
		return (A);
	else
		return (B);
}

struct	s_rots	minrot(struct s_rots rot1, struct s_rots rot2)
{
	if (rot1.cost < rot2.cost)
		return (rot1);
	return (rot2);
}

char *get_step_name(int type)
{
  if (type == 0)
    return("PA");
  else if (type == 1)
    return("PB");
  else if (type == 5)
    return("RA");
  else if (type == 6)
    return("RB");
  else if (type == 7)
    return("RR");
  else if (type == 8)
    return("RRA");
  else if (type == 9)
    return("RRB");
  else if (type == 10)
    return("RRR");
  return("WRONG TYPE");
}

void emit_step(int type)
{
  char *name;

  name = malloc(sizeof(char) * 3);
  name = get_step_name(type);
  printf("%s\n", name);
}

void	do_print(int type_1, int type_2, int comp_1, int comp_2)
{
	int				c;

	c = 0;
	while (c < comp_1)
	{
		emit_step(type_1);
		c++;
	}
	c = 0;
	while (c < comp_2)
	{
		emit_step(type_2);
		c++;
	}
}

void emit_from_rots(struct s_rots rot)
{
	if (rot.type == 0)
	{
		if (rot.steps_a == 0)
			do_print (7, 6, rot.cost - rot.steps_b, rot.steps_b);
		else
			do_print (7, 5, rot.cost - rot.steps_a, rot.steps_a);
	}
	if (rot.type == 1)
	{
		if (rot.steps_a == 0)
			do_print (10, 9, rot.cost - rot.steps_b, rot.steps_b);
		else
			do_print (10, 8, rot.cost - rot.steps_a, rot.steps_a);
	}
	if (rot.type == 2)
		do_print (5, 9, rot.steps_a, rot.steps_b);
	if (rot.type == 3)
		do_print (8, 6, rot.steps_a, rot.steps_b);
}
