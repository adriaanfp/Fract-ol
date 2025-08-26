/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:05:37 by aflores-          #+#    #+#             */
/*   Updated: 2025/05/11 20:46:36 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	handle_zoom(int button, t_data *data)
{
	if (!data)
		return (1);
	if (button == 4)
		data->zoom *= 1.1;
	else if (button == 5)
		data->zoom *= 0.9;
	if (data->zoom > 1e10)
		data->zoom = 1e10;
	if (data->zoom < 0.1)
		data->zoom = 0.1;
	return (0);
}

t_complex	get_coords(int x, int y, t_data *data)
{
	t_complex	c;

	if (data->fractal_type == 1)
	{
		c.real = (x - WIDTH / 2.0) * 4.0 / WIDTH / data->zoom + data->move_x;
		c.imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT / data->zoom + data->move_y;
	}
	else
	{
		calculate_julia_coordinates(x, y, data, &c);
	}
	return (c);
}

void	adjust_viewport(t_data *data, t_complex before, t_complex after)
{
	data->move_x += before.real - after.real;
	data->move_y += before.imag - after.imag;
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_data		*data;
	t_complex	before;
	t_complex	after;

	data = (t_data *)param;
	if (!data || (button != 4 && button != 5))
		return (0);
	before = get_coords(x, y, data);
	handle_zoom(button, data);
	after = get_coords(x, y, data);
	adjust_viewport(data, before, after);
	render_fractal(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0)
	{
		if (*str1 != *str2)
		{
			return ((unsigned char)*str1 - (unsigned char)*str2);
		}
		if (*str1 == '\0' || *str2 == '\0')
			return (0);
		str1++;
		str2++;
		n--;
	}
	return (0);
}
