/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:19:53 by aflores-          #+#    #+#             */
/*   Updated: 2025/04/27 23:00:23 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	skip_whitespace_and_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

static double	parse_integer_part(const char *str, int *i)
{
	double	n;

	n = 0.0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		n = n * 10.0 + (str[*i] - '0');
		*i = *i + 1;
	}
	return (n);
}

static double	parse_decimal_part(const char *str, int *i)
{
	double	n;
	double	decimal;

	n = 0.0;
	decimal = 0.1;
	if (str[*i] == '.')
	{
		*i = *i + 1;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			n += (str[*i] - '0') * decimal;
			decimal *= 0.1;
			*i = *i + 1;
		}
	}
	return (n);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;
	int		i;

	sign = 1;
	i = skip_whitespace_and_sign(str, &sign);
	result = parse_integer_part(str, &i);
	result += parse_decimal_part(str, &i);

	if (result > DBL_MAX)
	{
		if (sign > 0)
			return DBL_MAX;
		else
			return -DBL_MAX;
	}
	if (result != 0.0 && result < DBL_MIN)
	{
		if (sign > 0)
			return DBL_MIN;
		else
			return -DBL_MIN;
	}
	return (result * sign);
}


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

int handle_zoom(int button, t_data *data)
{
    if (!data)
        return (1);

    if (button == 4)
        data->zoom *= 1.05;
    else if (button == 5)
        data->zoom /= 1.05;

    if (data->zoom > 1e10) data->zoom = 1e10;
    if (data->zoom < 1e-10) data->zoom = 1e-10;

    if (data->fractal_type == 1)
        render_mandelbrot(data);
    else if (data->fractal_type == 2)
        render_julia(data);

    return (0);
}

int handle_mouse(int button, int x, int y, void *param)
{
    t_data *data;
	
	data = (t_data *)param;
    (void)x;
    (void)y;
    if (!data || (button != 4 && button != 5))
        return (0);
    handle_zoom(button, data);
    if (data->fractal_type == 1)
        render_mandelbrot(data);
    else if (data->fractal_type == 2)
        render_julia(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return (0);
}

void initialize_data(t_data *data)
{
    if (!data)
		return ;
	ft_memset(data, 0, sizeof(t_data));
    data->zoom = 1.0;
    data->cx = -0.7;
    data->cy = 0.27015;
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

void	check_errors(int argc, char **argv, t_data *data)
{
	if (argc < 2 || argc > 4)
		return (write(2, "Invalid parameters\n", 19), exit(ERROR));
	if (ft_strncmp(argv[1], "julia", 6) != 0 && ft_strncmp(argv[1], "mandelbrot", 10) != 0)
		return (write(2, "Invalid parameters\n", 19), exit(ERROR));
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0 && argc != 2)
		return (write(2, "Invalid parameters\n", 19), exit(ERROR));
	if (ft_strncmp(argv[1], "julia", 6) == 0 && (argc != 4 && argc != 2))
		return (write(2, "Invalid parameters\n", 19), exit(ERROR));
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		data->fractal_type = 1;
	if (ft_strncmp(argv[1], "julia", 6) == 0)
		data->fractal_type = 2;	
}

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

void	parse_data(t_data *data, char **argv)
{
	int		i;
	int		dot_seen;
	double	real_val;
	double	imag_val;


	i = 0;
	dot_seen = 0;
	real_val = 0.0;
	imag_val = 0.0;
	if (argv[2][i] == '-' || argv[2][i] == '+')
		i++;
	while (argv[2][i])
	{
		if (argv[2][i] == '.')
		{
			if (dot_seen)
				exit(ERROR); 
			dot_seen = 1;
		}
		else if (!ft_isdigit(argv[2][i]))
			exit(ERROR);
		i++;
	}
	real_val = ft_atof(argv[2]);
	if (real_val > 1.7976931348623157e+308 || real_val < -1.7976931348623157e+308)
    {
        write(2, "Error: Real value is out of bounds.\n", 36);
        exit(ERROR);
    }
	data->z.real = real_val;
	i = 0;
	dot_seen = 0;
	if (argv[3][i] == '-' || argv[3][i] == '+')
		i++;
	while (argv[3][i])
	{
		if (argv[3][i] == '.')
		{
			if (dot_seen)
				exit(ERROR);
			dot_seen = 1;
		}
		else if (!ft_isdigit(argv[3][i]))
			exit(ERROR);
		i++;
	}
	imag_val = ft_atof(argv[3]);
	if (imag_val > 1.7976931348623157e+308 || imag_val < -1.7976931348623157e+308)
	{
		write(2, "Error: Imaginary value is out of bounds.\n", 42);
		exit(ERROR);
	}
	data->z.imag = imag_val;
}


int main(int argc, char **argv)
{
    t_data *data;
	
	data = malloc(sizeof(t_data));
    if (!data)
        exit(ERROR);
    initialize_data(data);
    init_mlx(data);
    check_errors(argc, argv, data);
    if (data->fractal_type == 1)
        render_mandelbrot(data);
    else if (data->fractal_type == 2)
    {
        parse_data(data, argv);
        render_julia(data);
    }
    else {
        free(data);
        exit(ERROR);
    }
    mlx_hook(data->win, 4, 0, handle_mouse, data);
    mlx_hook(data->win, 5, 0, handle_mouse, data);
    mlx_key_hook(data->win, handle_keypress, data);
    mlx_hook(data->win, 17, 0, handle_exit, data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    mlx_loop(data->mlx);
    return (0);
}
