/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:23:27 by aflores-          #+#    #+#             */
/*   Updated: 2025/04/25 16:56:52 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mandelbrot(double cx, double cy)
{
	double	x;
	double	y;
	double	xtemp;
	int		iter;

	x = 0.0;
	y = 0.0;
	iter = 0;
	while (x * x + y * y <= 4.0 && iter < MAX_ITER)
	{
		xtemp = x * x - y * y + cx;
		y = 2 * x * y + cy;
		x = xtemp;
		iter++;
	}
	return (iter);
}

void	render_mandelbrot(t_data *data)
{
	int		x;
	int		y;
	int		iter;
	double	cx;
	double	cy;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			cx = (x - WIDTH / 2.0) * 4.0 / WIDTH / data->zoom + data->move_x;
			cy = (y - HEIGHT / 2.0) * 4.0 / HEIGHT / data->zoom + data->move_y;
			iter = mandelbrot(cx, cy);
			my_mlx_pixel_put(data, x, y, map_color(iter));
			y++;
		}
		x++;
	}
}
