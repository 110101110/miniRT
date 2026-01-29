/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_range.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Check if 'value' (as a double) is within the range [min, max]
int	check_range_double(double value, double min, double max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

// Check if 'value' (as an int) is within the range [min, max]
int	check_range_int(int value, int min, int max)
{
	if (value < min || value > max)
		return (0);
	return (1);
}

// Check if the float value overflows
int	check_float_overflows(char *str)
{
	double	val;

	val = ft_atof(str);
	if (val > DBL_MAX || val < -DBL_MAX)
		return (0);
	return (1);
}

// Check if the int value overflows
int	check_int_overflows(char *str)
{
	long	val;
	int		i;
	int		sign;

	val = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		val = val * 10 + (str[i] - '0');
		i++;
	}
	val *= sign;
	if (val > INT_MAX || val < INT_MIN)
		return (0);
	return (1);
}
