/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 08:35:18 by pbondoer          #+#    #+#             */
/*   Updated: 2016/12/16 00:44:09 by pbondoer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdint.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

typedef struct		s_rgba
{
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;
	uint8_t		a;
}					t_rgba;

typedef union		u_color
{
	int			value;
	t_rgba		rgba;
}					t_color;

typedef struct		s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
	int			width;
	int			height;
}					t_image;

typedef struct		s_map
{
	int			width;
	int			height;
	int			**values;
}					t_map;

typedef struct		s_player
{
	float		x;
	float		y;
	float		direction;
}					t_player;

typedef struct		s_mlx
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_map		*map;
}					t_mlx;

t_mlx				*init();
t_mlx				*del_mlx(t_mlx *mlx);
void				render(t_mlx *mlx);
int					hook_mousedown(int button, int x, int y, t_mlx *mlx);
int					hook_mouseup(int button, int x, int y, t_mlx *mlx);
int					hook_mousemove(int x, int y, t_mlx *mlx);
int					hook_keydown(int key, t_mlx *mlx);
int					hook_expose(t_mlx *mlx);
t_image				*del_image(t_mlx *mlx, t_image *img);
t_image				*new_image(t_mlx *mlx, int w, int h);
void				clear_image(t_image *img);
void				image_set_pixel(t_image *image, int x, int y, int color);
t_color				clerp(t_color c1, t_color c2, double p);
t_map				*read_map(char * fd);

#endif
