/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:07:51 by paperez-          #+#    #+#             */
/*   Updated: 2024/11/26 19:32:07 by paperez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	*transform_sa(int *list, int idx)
{
	int	tmp;

	tmp = list[idx - 1];
	list[idx - 1] = list[idx - 2];
	list[idx - 2] = tmp;
	return (list);
}

int	*transform_sb(int *list, int idx)
{
	int	tmp;

	tmp = list[idx];
	list[idx] = list[idx + 1];
	list[idx + 1] = tmp;
	return (list);
}

int	*transform_ss(int *list, int idx)
{
	int	tmp;

	tmp = list[idx - 1];
	list[idx - 1] = list[idx - 2];
	list[idx - 2] = tmp;
	tmp = list[idx];
	list[idx] = list[idx + 1];
	list[idx + 1] = tmp;
	return (list);
}
