/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 04:19:00 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/20 05:07:07 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf.h"
#include <stddef.h>
#include <stdio.h>

void	free_textures(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < TEX_MAP_SIZE)
		del_image(mlx, mlx->tex[i++]);
}

int		load_textures(t_mlx *mlx)
{
	static char	*map[TEX_MAP_SIZE] = { "textures/brick.xpm",
		"textures/wood.xpm", "textures/metal.xpm", "textures/stone.xpm", NULL };
	t_image		*img;
	int			i;

	i = 1;
	while (i < TEX_MAP_SIZE && map[i - 1])
	{
		if ((img = xpm_image(map[i - 1], mlx)) == NULL)
		{
			free_textures(mlx);
			return (1);
		}
		mlx->tex[i] = img;
		i++;
	}
	mlx->tex[0] = NULL;
	return (0);
}
