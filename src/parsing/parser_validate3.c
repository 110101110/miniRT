/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:30:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/30 02:04:27 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Checks if the second letter of identifier is correct
static int	check_obj_char(char c, char next)
{
	if (c == 's' && next != 'p')
		return (0);
	if (c == 'p' && next != 'l')
		return (0);
	if (c == 'c' && next != 'y')
		return (0);
	return (1);
}

// Checks if 'line' starts with a valid object identifier
static int	check_line_objects(char *line)
{
	int	y;

	y = 0;
	while (line[y])
	{
		if (!check_obj_char(line[y], line[y + 1]))
			return (0);
		if (line[y] == 's' || line[y] == 'p' || line[y] == 'c')
			y++;
		y++;
	}
	return (1);
}

// If 's' is found , it should be followed by 'p'. (sp)
// If 'p' is found , it should be followed by 'l'. (pl)
// If 'c' is found , it should be followed by 'y'. (cy)
int	detect_illegal_object(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (!check_line_objects(file[i]))
			return (0);
		i++;
	}
	return (1);
}
