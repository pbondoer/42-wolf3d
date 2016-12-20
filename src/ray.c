/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:21:04 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 08:31:19 by pbondoer         ###   ########.fr       */
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
	float	wall;
}				t_cast;

void			castfloor(t_ray *r, t_cast *t)
{
	r->fx = (float)t->mx + (r->side ? t->wall : 0) + (!r->side && r->x < 0 ? 1.0f : 0);
	r->fy = (float)t->my + (r->side ? 0 : t->wall) + (r->side && r->y < 0 ? 1.0f : 0);
}

void			cast(t_ray *r, t_map *m, t_player *p, t_image *tex[])
{
	t_cast	t;
	int		hit;
	int		blockdist;

	t.mx = (int)p->x;
	t.my = (int)p->y;
	t.dx = sqrt((r->y * r->y) / (r->x * r->x) + 1);
	t.dy = sqrt((r->x * r->x) / (r->y * r->y) + 1);
	t.stepx = (r->x < 0 ? -1 : 1);
	t.stepy = (r->y < 0 ? -1 : 1);
	t.sx = (r->x < 0 ? p->x - t.mx : t.mx - p->x + 1) * t.dx;
	t.sy = (r->y < 0 ? p->y - t.my : t.my - p->y + 1) * t.dy;
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
		r->distance = (r->side ? (t.my - p->y + (1 - t.stepy) / 2) / r->y :
			(t.mx - p->x + (1 - t.stepx) / 2) / r->x);
		r->height = (int)floor(WIN_HEIGHT / r->distance);
		r->light = 1.0f * (1.0f - r->distance / VIEW_DIST) * (r->side ? 0.9 : 1.0f);
		r->texture = tex[hit];
		t.wall = (r->side ? p->x + r->distance * r->x :
			p->y + r->distance * r->y);
		t.wall -= floor(t.wall);
		r->texX = (int)(t.wall * r->texture->width);
		castfloor(r, &t);
	}
}
