/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Checks whether a line begins with the given identifier token.
static int	line_starts_with_identifier(char *line, char identifier)
{
	if (!line)
		return (0);
	while (*line && ft_isspace(*line))
		line++;
	if (*line != identifier)
		return (0);
	line++;
	if (*line == '\0' || *line == '\n' || ft_isspace(*line))
		return (1);
	return (0);
}

// Simply count the numbers of 'A', 'C', and 'L' characters in *file.
// Return 1 if there is exactly one of each, else return 0.
int	count_mandatory_identifiers(char **file)
{
	int	i;
	int	a_count;
	int	c_count;
	int	l_count;

	i = 0;
	a_count = 0;
	c_count = 0;
	l_count = 0;
	while (file[i])
	{
		if (line_starts_with_identifier(file[i], 'A'))
			a_count++;
		else if (line_starts_with_identifier(file[i], 'C'))
			c_count++;
		else if (line_starts_with_identifier(file[i], 'L'))
			l_count++;
		i++;
	}
	return (a_count == 1 && c_count == 1 && l_count == 1);
}

// Legal characters are : A, C, L, sp, pl, cy
// " ", "\n", "0"-"9", ".", ",", "-", "+"
int	is_legal(char c)
{
	if ((c >= '0' && c <= '9') || ft_isspace(c) || c == '.' || c == ','
		|| c == '-' || c == 'A' || c == 'C' || c == 'L' || c == 's' || c == 'p'
		|| c == 'l' || c == 'c' || c == 'y' || c == '+')
		return (1);
	return (0);
}

// Returns 1 if all characters in file are legal for the .rt format, else 0.
int	detect_illegal_characters(char **file)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (file[i])
	{
		while (file[i][y])
		{
			if (!is_legal(file[i][y]))
				return (0);
			y++;
		}
		y = 0;
		i++;
	}
	return (1);
}

// Return the line number where the first occurrence of the identifier is found.
// (useful for A, C, L since they should only appear once but not for objects)
int	where_is(char **file, char identifier)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (line_starts_with_identifier(file[i], identifier))
			return (i);
		i++;
	}
	return (-1);
}
