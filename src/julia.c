/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:39:22 by aflores-          #+#    #+#             */
/*   Updated: 2025/04/27 21:32:20 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	julia(double cx, double cy, double zx, double zy)
{
	int		iter;
	double	xtemp;

	iter = 0;
	while (zx * zx + zy * zy <= 4.0 && iter < MAX_ITER)
	{
		xtemp = zx * zx - zy * zy + cx;
		zy = 2 * zx * zy + cy;
		zx = xtemp;
		iter++;
	}
	return (iter);
}

int	calculate_julia_iterations(double real, double imag, double cx, double cy)
{
	int		iter;
	double	tmp_real;
	double	tmp_imag;

	iter = 0;
	while (real * real + imag * imag <= 4 && iter < MAX_ITER)
	{
		tmp_real = real * real - imag * imag + cx;
		tmp_imag = 2 * real * imag + cy;
		real = tmp_real;
		imag = tmp_imag;
		iter++;
	}
	return (iter);
}

void	calculate_julia_coordinates(int x, int y, t_data *data)
{
	double	scale_x;
	double	scale_y;

	scale_x = (x - (WIDTH / 2.0)) / (0.5 * data->zoom * WIDTH) + data->move_x;
	scale_y = (y - (HEIGHT / 2.0)) / (0.5 * data->zoom * HEIGHT) + data->move_y;
	data->z.real = scale_x;
	data->z.imag = scale_y;
}

void	render_julia(t_data *data)
{
	int		x;
	int		y;
	int		iter;
	double	cx;
	double	cy;

	cx = data->z.real;
	cy = data->z.imag;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			calculate_julia_coordinates(x, y, data);
			iter = calculate_julia_iterations(data->z.real, data->z.imag, cx, cy);
			my_mlx_pixel_put(data, x, y, map_color(iter));
			y++;
		}
		x++;
	}
}
