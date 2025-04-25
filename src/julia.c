/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:39:22 by aflores-          #+#    #+#             */
/*   Updated: 2025/04/25 16:56:46 by aflores-         ###   ########.fr       */
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

int	calculate_julia_iterations(double zx, double zy, double cx, double cy)
{
	return (julia(cx, cy, zx, zy));
}

void	calculate_julia_coordinates(int x, int y, t_data *data, t_complex *z)
{
	z->real = (x - WIDTH / 2.0) * 4.0 / WIDTH / data->zoom + data->move_x;
	z->imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT / data->zoom + data->move_y;
}

void	render_julia(t_data *data, t_complex z)
{
	int			x;
	int			y;
	int			iter;
	double		cx;
	double		cy;

	cx = -0.7;
	cy = 0.27015;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			calculate_julia_coordinates(x, y, data, &z);
			iter = calculate_julia_iterations(z.real, z.imag, cx, cy);
			my_mlx_pixel_put(data, x, y, map_color(iter));
			y++;
		}
		x++;
	}
}
