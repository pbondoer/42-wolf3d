/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:08:58 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 14:14:37 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <math.h>

static void	place_player(t_player *p, t_map *m)
{
	int	x;
	int	y;
	int	f;

	y = 0;
	f = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (!(f = get_tile(m, x, y)))
				break ;
			x++;
		}
		if (!f)
			break ;
		y++;
	}
	if (y == m->height && x == m->width)
		ft_putendl("warning: map contains no empty space");
	p->x = x + 0.5f;
	p->y = y + 0.5f;
}

void		init_player(t_player *p, t_map *m)
{
	place_player(p, m);
	p->d.x = 1.0f;
	p->d.y = 0.0f;
	p->p.x = 0.0f;
	p->p.y = 2.0f / 3.0f;
}

static void	rotate(t_vector *v, float angle)
{
	float x;
	float c;
	float s;

	x = v->x;
	c = cos(angle);
	s = sin(angle);
	v->x = v->x * c - v->y * s;
	v->y = x * s + v->y * c;
}

void		rotate_player(t_player *p, float angle)
{
	rotate(&p->d, angle);
	rotate(&p->p, angle);
}

void		move_player(t_player *p, t_map *m, float distance)
{
	if (!get_tile(m, p->x + distance * p->d.x, p->y))
		p->x += distance * p->d.x;
	if (!get_tile(m, p->x, p->y + distance * p->d.y))
		p->y += distance * p->d.y;
}
