/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:26:50 by aflores-          #+#    #+#             */
/*   Updated: 2025/04/25 17:06:00 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	switch_fractal(t_data *data)
{
	t_complex	z;

	data->fractal_type = 1 - data->fractal_type;
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->line_len, &data->endian);
	if (data->fractal_type == 0)
		render_mandelbrot(data);
	else
	{
		z.real = -0.7;
		z.imag = 0.27015;
		render_julia(data, z);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	handle_keypress(int key, t_data *data)
{
	t_complex	z;

	if (key == 65307)
		handle_exit(data);
	if (key == 106)
		switch_fractal(data);
	if (key == 65361)
		data->move_x -= 0.1 / data->zoom;
	if (key == 65362)
		data->move_y -= 0.1 / data->zoom;
	if (key == 65363)
		data->move_x += 0.1 / data->zoom;
	if (key == 65364)
		data->move_y += 0.1 / data->zoom;
	if (data->fractal_type == 0)
		render_mandelbrot(data);
	else
	{
		z.real = -0.7;
		z.imag = 0.27015;
		render_julia(data, z);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	handle_exit(t_data *data)
{
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		if (data->mlx)
			mlx_loop_end(data->mlx);
		free(data->mlx);
	exit(0);
}
