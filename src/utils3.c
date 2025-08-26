/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:05:55 by aflores-          #+#    #+#             */
/*   Updated: 2025/05/11 21:11:41 by aflores-         ###   ########.fr       */
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

int	is_valid_number(const char *str)
{
	int	i;
	int	dot_seen;

	i = 0;
	dot_seen = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (dot_seen)
				return (0);
			dot_seen = 1;
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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
	if (result > 1.7976931348623157e+308)
	{
		if (sign > 0)
			return (1.7976931348623157e+308);
		else
			return (-1.7976931348623157e+308);
	}
	if (result != 0.0 && result < 2.2250738585072014e-308)
	{
		if (sign > 0)
			return (2.2250738585072014e-308);
		else
			return (-2.2250738585072014e-308);
	}
	return (result * sign);
}
