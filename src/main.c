/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:19:53 by aflores-          #+#    #+#             */
/*   Updated: 2025/05/11 19:45:05 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	initialize_and_check(int argc, char **argv, t_data *data)
{
	initialize_data(data);
	init_mlx(data);
	check_errors(argc, argv, data);
}

void	render_fractal(t_data *data)
{
	if (data->fractal_type == 1)
		render_mandelbrot(data);
	else if (data->fractal_type == 2)
		render_julia(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(ERROR);
	initialize_and_check(argc, argv, data);
	render_fractal(data);
	mlx_mouse_hook(data->win, handle_mouse, data);
	mlx_key_hook(data->win, handle_keypress, data);
	mlx_hook(data->win, 17, 0, handle_exit, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
