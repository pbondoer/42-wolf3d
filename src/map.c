/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 03:11:00 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 16:05:50 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		get_tile(t_map *m, int x, int y)
{
	if (x < 0 || y < 0 || x > m->width - 1 || y > m->height - 1)
		return (0);
	return (m->values[y][x]);
}

int		is_full_map(t_map *m)
{
	int x;
	int y;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (get_tile(m, x, y) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int		is_enclosed_map(t_map *m)
{
	int x;
	int y;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if ((x == 0 || y == 0 || x == m->width - 1 || y == m->height) && 
					get_tile(m, x, y) == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
