/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:09 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/22 12:24:12 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

char	**copy_file_to_array(char *filename)
{
	int		fd;
	char	*line;
	char	**file;
	int		line_count;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line_count = 0;
	while (get_next_line(fd))
		line_count++;
	close(fd);
	file = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!file)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		file[i++] = line;
	}
	file[i] = NULL;
	close(fd);
	return (file);
}

// Simply count the numbers of 'A', 'C', and 'L' characters in *file.
// Return 1 if there is exactly one of each, else return 0.
int	count_mandatory_identifiers(char **file)
{
	int	i;
	int	y;
	int	a_count;
	int	c_count;
	int	l_count;

	i = 0;
	y = 0;
	a_count = 0;
	c_count = 0;
	l_count = 0;
	while (file[i])
	{
		while (file[i][y])
		{
			if (file[i][y] == 'A')
				a_count++;
			else if (file[i][y] == 'C')
				c_count++;
			else if (file[i][y] == 'L')
				l_count++;
			y++;
		}
		y = 0;
		i++;
	}
	if (a_count != 1 || c_count != 1 || l_count != 1)
		return (0);
	return (1);
}

// Legal characters are : A, C, L, sp, pl, cy
// " ", "\n", "0"-"9", ".", ",", "-", "+"
int	is_legal(char c)
{
	if ((c >= '0' && c <= '9') || c == ' ' || c == '\n' || c == '.'
		|| c == ',' || c == '-' || c == 'A' || c == 'C' || c == 'L'
		|| c == 's' || c == 'p' || c == 'l' || c == 'c' || c == 'y' || c == '+')
		return (1);
	return (0);
}

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

// If first letter is uppercase, should have only 1 alphabetical in the line
// If first letter is lowercase, should have 2 alphabeticals in the line
int	one_identifier_per_line(char **file)
{
	int	i;
	int	y;
	int	count;

	i = 0;
	while (file[i])
	{
		y = 0;
		count = 0;
		while (file[i][y])
		{
			if ((file[i][y] >= 'A' && file[i][y] <= 'Z') ||
				(file[i][y] >= 'a' && file[i][y] <= 'z'))
				count++;
			y++;
		}
		if (file[i][0] >= 'A' && file[i][0] <= 'Z')
		{
			if (count != 1)
				return (0);
		}
		else if (file[i][0] >= 'a' && file[i][0] <= 'z')
		{
			if (count != 2)
				return (0);
		}
		i++;
	}
	return (1);
}

// Return the line number where the first occurrence of the identifier is found.
// (useful for A, C, L since they should only appear once but not for objects)
int	where_is(char **file, char identifier)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (file[i])
	{
		while (file[i][y])
		{
			if (file[i][y] == identifier)
				return (i);
			y++;
		}
		y = 0;
		i++;
	}
	return (-1);
}

// Go to the line where 'A' is located and split its content in parser->ambient
int	fill_ambient_content(char **file, t_parser *parser)
{
	int	line;

	line = where_is(file, 'A');
	if (line == -1)
		return (0);
	parser->ambient = ft_split(file[line], ' ');
	if (!parser->ambient)
		return (0);
	return (1);
}

// Same for 'C'
int	fill_camera_content(char **file, t_parser *parser)
{
	int	line;

	line = where_is(file, 'C');
	if (line == -1)
		return (0);
	parser->camera = ft_split(file[line], ' ');
	if (!parser->camera)
		return (0);
	return (1);
}

// Same for 'L'
int	fill_light_content(char **file, t_parser *parser)
{
	int	line;

	line = where_is(file, 'L');
	if (line == -1)
		return (0);
	parser->light = ft_split(file[line], ' ');
	if (!parser->light)
		return (0);
	return (1);
}

int	fill_parser_struct(char **file, t_parser *parser)
{
	if (!fill_ambient_content(file, parser))
		return (0);
	if (!fill_camera_content(file, parser))
		return (0);
	if (!fill_light_content(file, parser))
		return (0);
	// if (!fill_obj(file, parser))
	// 	return (0);
	return (1);
}

// If 's' is found , it should be followed by 'p'. (sp)
// If 'p' is found , it should be followed by 'l'. (pl)
// If 'c' is found , it should be followed by 'y'. (cy)
int	detect_illegal_object(char **file)
{
	int	i;
	int	y;

	i = 0;
	while (file[i])
	{
		y = 0;
		while (file[i][y])
		{
			if (file[i][y] == 's')
			{
				if (file[i][y + 1] != 'p')
					return (0);
				y++;
			}
			else if (file[i][y] == 'p')
			{
				if (file[i][y + 1] != 'l')
					return (0);
				y++;
			}
			else if (file[i][y] == 'c')
			{
				if (file[i][y + 1] != 'y')
					return (0);
				y++;
			}
			y++;
		}
		i++;
	}
	return (1);
}

int	parse_file(char **file, t_parser *parser)
{
	if (!count_mandatory_identifiers(file)) // check bon nombre de A C L
		return (0);
	if (!detect_illegal_characters(file)) // detecte les caracteres illegaux
		return (0);
	if (!one_identifier_per_line(file)) // detecte si ya plus d'1 identifiant sur une meme ligne
		return (0);
	if (!detect_illegal_object(file)) // detecte les objets illegaux
		return (0);
	if (!fill_parser_struct(file, parser))
		return (0);
	(void)file;
	(void)parser;
	return (1);
}

int	parse(int ac, char **av, t_data *data)
{
	char		**file; // free later
	t_parser	parser; // free later

	if (!parse_arguments(ac, av))
		return (0);
	file = copy_file_to_array(av[1]);
	if (!file)
		return (0);
	if (!parse_file(file, &parser))
		return (0);
	printf("Parsing successful\n");
	return (1);
	(void)data;
}
