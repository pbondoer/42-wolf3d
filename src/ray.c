/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:21:04 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 05:14:46 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf.h"
#include <stdio.h>

typedef struct	s_cast
{
	int		mx;
	int		my;
	float	sx;
	float	sy;
	float	dx;
	float	dy;
	int		stepx;
	int		stepy;
}				t_cast;

void			cast(t_ray *r, t_map *m, t_player *p)
{
	t_cast	t;
	int		hit;
	int		blockdist;

	t.mx = (int)p->x;
	t.my = (int)p->y;
	t.dx = sqrt((r->diry * r->diry) / (r->dirx * r->dirx) + 1);
	t.dy = sqrt((r->dirx * r->dirx) / (r->diry * r->diry) + 1);
	t.stepx = (r->dirx < 0 ? -1 : 1);
	t.stepy = (r->diry < 0 ? -1 : 1);
	t.sx = (r->dirx < 0 ? p->x - t.mx : t.mx - p->x + 1) * t.dx;
	t.sy = (r->diry < 0 ? p->y - t.my : t.my - p->y + 1) * t.dy;
	blockdist = 0;
	hit = 0;
	while (!hit && blockdist < VIEW_DIST)
	{
		if (t.sx < t.sy)
		{
			t.sx += t.dx;
			t.mx += t.stepx;
			r->side = 0;
		}
		else
		{
			t.sy += t.dy;
			t.my += t.stepy;
			r->side = 1;
		}
		if (t.mx < 0 || t.my < 0 || t.mx > m->width - 1 || t.my > m->height - 1)
			break ;
		hit = get_tile(m, t.mx, t.my);
		blockdist++;
	}
	r->height = 0;
	if (hit)
	{
		r->distance = (r->side ? (t.my - p->y + (1 - t.stepy) / 2) / r->diry :
			(t.mx - p->x + (1 - t.stepx) / 2) / r->dirx);
		r->height = (int)round(WIN_HEIGHT / r->distance);
		r->light = 1.0f * (1.0f - r->distance / VIEW_DIST) * (r->side ? 0.9 : 1.0f);
	}
}
