/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Returns 1 if character is any standard whitespace, else 0.
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

// Converts a numeric string to double (handles optional sign and decimal part)
double	ft_atof(const char *str)
{
	double	res;
	double	frac;
	int		neg;
	int		len;

	while (ft_isspace(*str))
		str++;
	neg = (*str == '-');
	res = (double)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
		str++;
	frac = (double)ft_atoi(str);
	len = 0;
	while (str[len] && ft_isdigit(str[len]))
		len++;
	while (len--)
		frac /= 10;
	if (neg)
		return (res - frac);
	return (res + frac);
}

// Count the number of elements in a string array
int	nb_of_elements(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// Check if the string matches the identifier
int	is_identifier(char *str, char *identifier)
{
	int	i;

	i = 0;
	while (identifier[i])
	{
		if (str[i] != identifier[i])
			return (0);
		i++;
	}
	if (str[i] != '\0' && str[i] != '\n' && !ft_isspace(str[i]))
		return (0);
	return (1);
}

// Check if the string is a valid double (-12.3, +0.56, 42, etc.)
int	is_double(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (str[i + 1] == '\0' || str[i + 1] == '\n')
				return (0);
		}
		else if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (dot_count > 1)
		return (0);
	return (1);
}
