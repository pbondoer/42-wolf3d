/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 05:33:43 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/16 00:46:05 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "keys.h"
#include <stdlib.h>

int		hook_keydown(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == K_ESC)
		exit(EXIT_SUCCESS);
	// TODO: render
	return (0);
}
