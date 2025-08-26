/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:09:49 by aflores-          #+#    #+#             */
/*   Updated: 2025/05/11 20:44:54 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	parse_value(const char *str, const char *err_msg)
{
	double	val;

	if (!is_valid_number(str))
		exit(ERROR);
	val = ft_atof(str);
	if (val > 1.7976931348623157e+308 || val < -1.7976931348623157e+308)
	{
		write(2, err_msg, ft_strlen(err_msg));
		exit(ERROR);
	}
	return (val);
}

void	check_errors(int argc, char **argv, t_data *data)
{
	if (argc < 2 || argc > 4)
		print_error_and_exit("Invalid parameters\n");
	check_fractal_type(argv, data);
	if (data->fractal_type == 1)
		check_mandelbrot_params(argc);
	if (data->fractal_type == 2)
		check_julia_params(argc);
	if (data->fractal_type == 2 && argc == 2)
	{
		data->z.real = -0.7;
		data->z.imag = 0.27015;
	}
	else if (argc == 4)
	{
		data->z.real = parse_value(argv[2],
				"Error: Real value is out of bounds.\n");
		data->z.imag = parse_value(argv[3],
				"Error: Imaginary value is out of bounds.\n");
	}
}
