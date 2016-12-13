/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 08:28:17 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/13 18:17:14 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "wolf.h"

int		die(char *reason)
{
	ft_putendl(reason);
	return (1);
}

int		main(int argc, char **argv)
{
	t_mlx		*mlx;

	if (argc < 2)
		return (die("error: not enough arguments"));
	if ((mlx->map = load_map(argv[1])) == NULL)
		return (die("error: invalid map file"));
	if ((mlx = init()) == NULL)
		return (die("error: mlx couldn't initialize properly"));
	render(mlx);
	mlx_expose_hook(mlx->window, hook_expose, mlx);
	mlx_hook(mlx->window, 6, 1L << 6, hook_mousemove, mlx); // key hook!!
	mlx_loop(mlx->mlx);
	return (0);
}
