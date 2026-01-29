/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:44:30 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Counts alphabetical characters in a line.
static int	count_alpha_chars(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a'
				&& line[i] <= 'z'))
			count++;
		i++;
	}
	return (count);
}

// Returns the first non-whitespace character of a line (or '\0').
static char	get_first_non_space(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	return (*line);
}

// Validates expected alpha count based on the first character case.
static int	validate_alpha_count(char first, int count)
{
	if (first >= 'A' && first <= 'Z')
		return (count == 1);
	if (first >= 'a' && first <= 'z')
		return (count == 2);
	return (1);
}

// If first letter is uppercase, should have only 1 alphabetical in the line
// If first letter is lowercase, should have 2 alphabeticals in the line
int	one_identifier_per_line(char **file)
{
	int		i;
	char	first;

	i = 0;
	while (file[i])
	{
		first = get_first_non_space(file[i]);
		if (first != '\0' && !validate_alpha_count(first,
				count_alpha_chars(file[i])))
			return (0);
		i++;
	}
	return (1);
}
