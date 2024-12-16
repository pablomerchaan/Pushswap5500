/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:03:32 by paperez-          #+#    #+#             */
/*   Updated: 2024/12/16 15:20:47 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	*onearglist(char **argv)
{
	int	c;
	int	c2;
	int	*list;

	c = 0;
	c2 = 0;
	list = malloc (sizeof(int) * howmany(argv));
	while (argv[1][c] != '\0')
	{
		if(argv[1][c] == ' ')
			c++;
		list[c2] = ft_atoi(&argv[1][c]);
		while (argv[1][c] != ' ' && argv[1][c != '\0'])
			c++;
		c2++;
	}
	return (list);
}

struct s_minmax	oneargmin(char **argv, int *list, int length)
{
	int	c;
	struct s_minmax	m;

	c = 0;
	m.max = INT_MIN;
	m.min = INT_MAX;
	while (c < length)
	{
		if (ft_atoi(&argv[1][c]) == '\0')
		{
			printf("Error");
			m.max = 0;
			m.min = 0;
			c = 10000;
		}
		if (list[c] > m.max)
			m.max = list[c];
		if (list[c] < m.min)
			m.min = list[c];
		c++;
	}
	return (m);
}

int	howmany(char **argv)
{
	int	c;
	int	r;

	r = 0;
	c = 0;
	while (argv[1][c] != '\0')
	{
		if (argv[1][c] == ' ')
			r++;
		c++;
	}
	r++;
	return (r);
}
