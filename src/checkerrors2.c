/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:41:21 by aflores-          #+#    #+#             */
/*   Updated: 2025/05/11 20:45:23 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	print_error_and_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	check_fractal_type(char **argv, t_data *data)
{
	if (ft_strncmp(argv[1], "julia", 6) == 0)
		data->fractal_type = 2;
	else if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		data->fractal_type = 1;
	else
		print_error_and_exit("Invalid parameters\n");
}

void	check_mandelbrot_params(int argc)
{
	if (argc != 2)
		print_error_and_exit("Invalid parameters for Mandelbrot\n");
}

void	check_julia_params(int argc)
{
	if (argc > 4)
		print_error_and_exit("Invalid parameters for Julia\n");
}
