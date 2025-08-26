/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:11:20 by aflores-          #+#    #+#             */
/*   Updated: 2025/05/11 19:45:33 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit (ERROR);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!data->win)
	{
		write(2, "Error creating window.\n", 23);
		mlx_destroy_display(data->mlx);
		exit (ERROR);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		write(2, "Error creating image.\n", 22);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		exit (ERROR);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	data->zoom = 1.0;
	data->move_x = 0.0;
	data->move_y = 0.0;
}

void	initialize_data(t_data *data)
{
	if (!data)
		return ;
	ft_memset(data, 0, sizeof(t_data));
	data->zoom = 1.0;
	data->cx = -0.7;
	data->cy = 0.27015;
}
