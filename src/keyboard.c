/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 05:33:43 by pbondoer          #+#    #+#             */
/*   Updated: 2016/11/23 03:09:13 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys.h"
#include <stdlib.h>

int		draw_hooks(int key, t_mlx *mlx)
{
	int		doot;

	doot = 0;
	if (key >= K_DIGIT_1 && key <= K_DIGIT_1 + 3)
		mlx->palette = &get_palettes()[key - K_DIGIT_1];
	else if (key == K_NUM_ENTER)
		mlx->smooth = 1 - mlx->smooth;
	else
		doot = 1;
	if (!doot)
		draw(mlx);
	return (doot);
}

void	move(int key, t_mlx *mlx)
{
	double w;
	double h;

	w = (mlx->viewport.xmax - mlx->viewport.xmin) * mlx->viewport.zoom;
	h = (mlx->viewport.ymax - mlx->viewport.ymin) * mlx->viewport.zoom;
	if (key == K_UP)
		mlx->viewport.offy -= h * 0.05f;
	if (key == K_DOWN)
		mlx->viewport.offy += h * 0.05f;
	if (key == K_LEFT)
		mlx->viewport.offx -= w * 0.05f;
	if (key == K_RIGHT)
		mlx->viewport.offx += w * 0.05f;
	if (key == K_L)
		mlx->mouselock = 1 - mlx->mouselock;
}

int		hook_keydown(int key, t_mlx *mlx)
{
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	if (key == K_NUM_0)
		reset_viewport(mlx);
	if (key == K_NUM_MULT)
		mlx->viewport.max *= 2;
	if (key == K_NUM_DIV)
		if (mlx->viewport.max / 2 >= 2)
			mlx->viewport.max /= 2;
	if (key == K_NUM_PLUS)
		zoom(WIN_WIDTH / 2, WIN_HEIGHT / 2, &mlx->viewport, 1 / ZOOM);
	if (key == K_NUM_MINUS)
		zoom(WIN_WIDTH / 2, WIN_HEIGHT / 2, &mlx->viewport, ZOOM);
	move(key, mlx);
	if (draw_hooks(key, mlx))
		render(mlx);
	return (0);
}
