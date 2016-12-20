/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 10:44:47 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 05:24:08 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>

void		render(t_mlx *mlx)
{
	int		x;
	int		y;
	int		start;
	int		end;
	t_ray	ray;
	float	camera;

	clear_image(mlx->image);
	x = 0;
	while (x < WIN_WIDTH)
	{
		camera = 2.0f * x / WIN_WIDTH - 1.0f;
		ray.dirx = mlx->player.d.x + mlx->player.p.x * camera;
		ray.diry = mlx->player.d.y + mlx->player.p.y * camera;
		cast(&ray, mlx->map, &mlx->player);
		// DRAW THE THING
		start = (WIN_HEIGHT - ray.height) / 2;
		end = start + ray.height;
		if (start < 0)
			start = 0;
		if (end > WIN_HEIGHT - 1)
			end = WIN_HEIGHT - 1;
		y = start;
		while (y < end)
			image_set_pixel(mlx->image, x, y++, clerp((t_color)0x0, (t_color)0xFFFFFF, ray.light).value);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	printf("render ok\n");
}
