/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/02/02 14:06:47 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Returns the first non-whitespace character of a line (or '\0').
static char	get_first_char(char *line)
{
	int	j;

	j = 0;
	while (line[j] && ft_isspace(line[j]))
		j++;
	return (line[j]);
}

// Returns 1 if the character can start an object line, else 0.
static int	is_obj_line(char c)
{
	return (c == 's' || c == 'p' || c == 'c');
}

// Creates and appends a new object node (split content) to parser->obj.
static int	add_obj_node(char *line, t_parser *parser)
{
	char		**split_content;
	t_object	*node;

	split_content = split_line(line);
	if (!split_content)
		return (0);
	node = obj_new(split_content);
	if (!node)
	{
		free_tab(split_content);
		return (0);
	}
	add_obj_back(&parser->lst, node);
	return (1);
}

// Fill the linked list parser->obj with all objects found in the file
int	fill_obj(char **file, t_parser *parser)
{
	int		i;
	char	first_char;

	i = 0;
	parser->lst = NULL;
	while (file[i])
	{
		first_char = get_first_char(file[i]);
		if (first_char == '\0' || first_char == 'A' || first_char == 'C'
			|| first_char == 'L')
		{
			i++;
			continue ;
		}
		if (is_obj_line(first_char) && !add_obj_node(file[i], parser))
			return (0);
		i++;
	}
	return (1);
}
