/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:57:26 by aflores-          #+#    #+#             */
/*   Updated: 2025/04/27 23:06:26 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <float.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 50
# define ERROR 1

typedef struct s_complex
{
	double	real;
	double	imag;
}			t_complex;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	double	zoom;
	double	move_x;
	double	move_y;
	int		fractal_type;
	double	cx;
	double	cy;
	t_complex z;
}			t_data;

int			mandelbrot(double cx, double cy);
int			map_color(int iter);
void	calculate_julia_coordinates(int x, int y, t_data *data);
int			calculate_julia_iterations(double zx, double zy, double cx,
				double cy);
int			julia(double cx, double cy, double zx, double zy);

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		render_mandelbrot(t_data *data);
void	render_julia(t_data *data);
void	switch_fractal(t_data *data);

int 	handle_keypress(int key, t_data *data);
int			handle_exit(t_data *data);

#endif
