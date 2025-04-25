/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:19:53 by aflores-          #+#    #+#             */
/*   Updated: 2025/04/25 17:07:01 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	handle_zoom(int button, int x, int y, t_data *data)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	zoom_factor = 1.05;
	mouse_re = (x - WIDTH / 2.0) * 4.0 / WIDTH / data->zoom + data->move_x;
	mouse_im = (y - HEIGHT / 2.0) * 4.0 / HEIGHT / data->zoom + data->move_y;
	if (button == 4)
		data->zoom *= zoom_factor;
	if (button == 5)
		data->zoom /= zoom_factor;
	data->move_x = mouse_re - (x - WIDTH / 2.0) * 4.0 / WIDTH / data->zoom;
	data->move_y = mouse_im - (y - HEIGHT / 2.0) * 4.0 / HEIGHT / data->zoom;
	return (0);
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	t_complex	z;

	handle_zoom(button, x, y, data);
	z.real = (x - WIDTH / 2.0) * 4.0 / WIDTH / data->zoom + data->move_x;
	z.imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT / data->zoom + data->move_y;
	if (data->fractal_type == 0)
		render_mandelbrot(data);
	else
		render_julia(data, z);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data		data;
	t_complex	z;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Fract-ol");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp,
			&data.line_len, &data.endian);
	data.zoom = 1.0;
	data.move_x = 0.0;
	data.move_y = 0.0;
	data.fractal_type = 0;
	mlx_mouse_hook(data.win, handle_mouse, &data);
	mlx_key_hook(data.win, handle_keypress, &data);
	mlx_hook(data.win, 17, 0, handle_exit, &data);
	z.real = 0.0;
	z.imag = 0.0;
	if (data.fractal_type == 0)
		render_mandelbrot(&data);
	else
		render_julia(&data, z);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
