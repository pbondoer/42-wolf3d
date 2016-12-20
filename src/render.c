/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 10:44:47 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 08:47:05 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>

static void	draw_floor(t_mlx *mlx, t_ray *r, int x, int y)
{
	float	curDist;
	float	weight;
	int		fx;
	int		fy;

	while (y < WIN_HEIGHT)
	{
		curDist = WIN_HEIGHT / (2.0f * y - WIN_HEIGHT);
		weight = curDist / r->distance;
		fx = (int)((weight * r->fx + (1.0f - weight) * mlx->player.x) *
			mlx->floor->width) % mlx->floor->width;
		fy = (int)((weight * r->fy + (1.0f - weight) * mlx->player.y) *
			mlx->floor->height) % mlx->floor->height;
		image_set_pixel(mlx->image, x, y, clerp((t_color)0x0, get_pixel(mlx->floor, fx, fy), 1.0f - curDist / VIEW_DIST).value);
		fx = (int)((weight * r->fx + (1.0f - weight) * mlx->player.x) *
			mlx->ceiling->width) % mlx->ceiling->width;
		fy = (int)((weight * r->fy + (1.0f - weight) * mlx->player.y) *
			mlx->ceiling->height) % mlx->ceiling->height;
		image_set_pixel(mlx->image, x, WIN_HEIGHT - y, clerp((t_color)0x0, get_pixel(mlx->ceiling, fx, fy), 1.0f - curDist / VIEW_DIST).value);
		y++;
	}
}

static void	draw_column(t_mlx *mlx, t_ray *r, int x)
{
	int		y;
	int		start;
	int		end;
	int		texY;

	if (r->texture == NULL)
		return ;
	start = (WIN_HEIGHT - r->height) / 2;
	end = start + r->height;
	if (start < 0)
		start = 0;
	if (end > WIN_HEIGHT - 1)
		end = WIN_HEIGHT - 1;
	y = start;
	while (y < end)
	{
		texY = ((y - WIN_HEIGHT * 0.5f + r->height * 0.5f) * r->texture->height) / r->height;
		//image_set_pixel(mlx->image, x, y++, get_pixel(r->texture, r->texpos, texy).value);
		image_set_pixel(mlx->image, x, y++, clerp((t_color)0x0, get_pixel(r->texture, r->texX, texY), r->light).value);
	}
	draw_floor(mlx, r, x, y);
}

void		render(t_mlx *mlx)
{
	int		x;
	t_ray	ray;
	float	camera;

	clear_image(mlx->image);
	x = 0;
	while (x < WIN_WIDTH)
	{
		camera = 2.0f * x / WIN_WIDTH - 1.0f;
		ray.x = mlx->player.d.x + mlx->player.p.x * camera;
		ray.y = mlx->player.d.y + mlx->player.p.y * camera;
		cast(&ray, mlx->map, &mlx->player, mlx->tex);
		// DRAW THE THING
		draw_column(mlx, &ray, x);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
}

