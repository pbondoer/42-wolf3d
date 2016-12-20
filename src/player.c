/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:08:58 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 03:17:44 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

void		init_player(t_player *p)
{
	p->x = 3.5f;
	p->y = 3.5f;
	p->d.x = -1.0f;
	p->d.y = 0.0f;
	p->p.x = 0.0f;
	p->p.y = 2.0 / 3.0f;
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
