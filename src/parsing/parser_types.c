/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Parses a segment and ensures it is 0-255 without signs.
// Increments the string pointer forward.
static int	parse_segment_rgb(char **str)
{
	long	val;
	int		len;

	val = 0;
	len = 0;
	if (!ft_isdigit(**str))
		return (-1);
	while (ft_isdigit(**str))
	{
		val = val * 10 + (**str - '0');
		(*str)++;
		len++;
	}
	if (len > 3 || val > 255)
		return (-1);
	return (0);
}

// Validates the RGB string: int,int,int
// - No signs allowed (+ or -)
// - Range 0-255
// - Exactly 2 commas
int	is_rgb(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (count < 3)
	{
		if (parse_segment_rgb(&str) == -1)
			return (0);
		if (count < 2)
		{
			if (*str != ',')
				return (0);
			str++;
		}
		count++;
	}
	if (*str != '\0' && *str != '\n')
		return (0);
	return (1);
}

// Parses one vec3 segment (x, y, or z) and advances the pointer.
static int	parse_segment_vec3(char **str)
{
	int	dot_count;

	if (!str || !*str)
		return (-1);
	dot_count = 0;
	if (**str == '-' || **str == '+')
		(*str)++;
	if (!ft_isdigit(**str))
		return (-1);
	while (**str && **str != ',' && **str != '\n')
	{
		if (**str == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (-1);
			if (!ft_isdigit(*(*str + 1)))
				return (-1);
		}
		else if (!ft_isdigit(**str))
			return (-1);
		(*str)++;
	}
	return (0);
}

// Validates the VEC3 string: double,double,double
// - Signs allowed (+ or -)
// - Decimal points allowed
// - Exactly 2 commas
int	is_vec3(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (count < 3)
	{
		if (parse_segment_vec3(&str) == -1)
			return (0);
		if (count < 2)
		{
			if (*str != ',')
				return (0);
			str++;
		}
		count++;
	}
	if (*str != '\0' && *str != '\n')
		return (0);
	return (1);
}

// Checks if the string is a valid integer representation.
int	is_int(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
