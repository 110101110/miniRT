/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/30 02:15:56 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Returns index of the first non-whitespace character in the line.
static size_t	skip_leading_ws(const char *line)
{
	size_t	src;

	src = 0;
	while (line[src] && ft_isspace(line[src]))
		src++;
	return (src);
}

// Copies line into norm, collapsing whitespace runs into single spaces.
static size_t	collapse_ws(const char *line, char *norm, size_t src)
{
	size_t	dst;
	int		in_space;

	dst = 0;
	in_space = 0;
	while (line[src])
	{
		if (ft_isspace(line[src]))
			in_space = 1;
		else
		{
			if (in_space && dst > 0)
				norm[dst++] = ' ';
			in_space = 0;
			norm[dst++] = line[src];
		}
		src++;
	}
	if (dst > 0 && norm[dst - 1] == ' ')
		dst--;
	norm[dst] = '\0';
	return (dst);
}

// Creates a clean copy of 'line', trimming and collapsing whitespace
static char	*dup_trim_collapse_ws(const char *line)
{
	char	*normalized;

	if (!line)
		return (NULL);
	normalized = (char *)malloc(ft_strlen(line) + 1);
	if (!normalized)
		return (NULL);
	collapse_ws(line, normalized, skip_leading_ws(line));
	return (normalized);
}

// Splits 'line' at spaces after normalizing whitespace.
char	**split_rt_fields(const char *line)
{
	char	*normalized;
	char	**split;

	normalized = dup_trim_collapse_ws(line);
	if (!normalized)
		return (NULL);
	split = ft_split(normalized, ' ');
	free(normalized);
	return (split);
}
