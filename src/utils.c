/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:26:50 by aflores-          #+#    #+#             */
/*   Updated: 2025/04/28 20:05:22 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}


int handle_keypress(int key, t_data *data)
{
	if (!data)
		return (0);
    if (key == 65307)
		handle_exit(data);
    else if (key == 65361)
		data->move_x -= 0.1 / data->zoom;
    else if (key == 65362)
		data->move_y -= 0.1 / data->zoom;
    else if (key == 65363)
		data->move_x += 0.1 / data->zoom;
    else if (key == 65364)
		data->move_y += 0.1 / data->zoom;
    else
		return (0);
    if (data->fractal_type == 1)
        render_mandelbrot(data);
    else if (data->fractal_type == 2)
        render_julia(data);
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
		{
			mlx_loop_end(data->mlx);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
	exit(0);
}
