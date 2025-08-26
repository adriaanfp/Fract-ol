/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:39:22 by aflores-          #+#    #+#             */
/*   Updated: 2025/05/11 20:45:45 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	calculate_julia_iterations(double real, double imag, double cx, double cy)
{
	int		iter;
	double	tmp_real;

	iter = 0;
	while (real * real + imag * imag <= 4 && iter < MAX_ITER)
	{
		tmp_real = real * real - imag * imag + cx;
		imag = 2 * real * imag + cy;
		real = tmp_real;
		iter++;
	}
	return (iter);
}

void	calculate_julia_coordinates(int x, int y, t_data *data, t_complex *c)
{
	c->real = (x - WIDTH / 2.0) * 4.0 / WIDTH / data->zoom + data->move_x;
	c->imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT / data->zoom + data->move_y;
}

void	render_julia(t_data *data)
{
	int			x;
	int			y;
	int			iter;
	t_complex	c;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			calculate_julia_coordinates(x, y, data, &c);
			iter = calculate_julia_iterations(c.real, c.imag, data->z.real,
					data->z.imag);
			my_mlx_pixel_put(data, x, y, map_color(iter));
			y++;
		}
		x++;
	}
}
