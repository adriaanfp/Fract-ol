/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:57:26 by aflores-          #+#    #+#             */
/*   Updated: 2025/05/11 21:12:30 by aflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 50
# define ERROR 1

typedef struct s_complex
{
	double		real;
	double		imag;
}				t_complex;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	double		zoom;
	double		move_x;
	double		move_y;
	int			fractal_type;
	double		cx;
	double		cy;
	t_complex	z;
}				t_data;

int				mandelbrot(double cx, double cy);
int				map_color(int iter);
void			calculate_julia_coordinates(int x, int y, t_data *data,
					t_complex *c);
int				calculate_julia_iterations(double real, double imag, double cx,
					double cy);

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			render_mandelbrot(t_data *data);
void			render_julia(t_data *data);
void			switch_fractal(t_data *data);

int				handle_keypress(int key, t_data *data);
int				handle_exit(t_data *data);
int				handle_mouse(int button, int x, int y, void *param);
int				handle_zoom(int button, t_data *data);
void			*ft_memset(void *s, int c, size_t n);
void			initialize_data(t_data *data);
void			init_mlx(t_data *data);
void			check_errors(int argc, char **argv, t_data *data);
void			check_julia_params(int argc);
void			check_mandelbrot_params(int argc);
void			check_fractal_type(char **argv, t_data *data);
void			print_error_and_exit(char *msg);
double			parse_value(const char *str, const char *err_msg);
int				ft_strncmp(const char *str1, const char *str2, size_t n);
double			ft_atof(const char *str);
int				ft_isdigit(int c);
int				is_valid_number(const char *str);
void			render_fractal(t_data *data);
void			initialize_and_check(int argc, char **argv, t_data *data);
t_complex		get_coords(int x, int y, t_data *data);

#endif