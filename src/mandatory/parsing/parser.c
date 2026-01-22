/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:09 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/22 20:07:25 by kevisout         ###   ########.fr       */
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

// Fill the linked list parser->obj with all objects found in the file
int	fill_obj(char **file, t_parser *parser)
{
	int		i;
	int		j;
	char	**split_content;
	t_list	*node;
	char	first_char;

	i = 0;
	parser->obj = NULL;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ')
			j++;
		first_char = file[i][j];
		if (first_char == 'A' || first_char == 'C' || first_char == 'L')
		{
			i++;
			continue ;
		}
		if (first_char == 's' || first_char == 'p' || first_char == 'c')
		{
			split_content = ft_split(file[i], ' ');
			if (!split_content)
				return (0);
			node = ft_lstnew(split_content);
			if (!node)
				return (0);
			ft_lstadd_back(&parser->obj, node);
		}
		i++;
	}
	return (1);
}

// Fill the parser struct with all its content
int	fill_parser_struct(char **file, t_parser *parser)
{
	if (!fill_ambient_content(file, parser))
		return (0);
	if (!fill_camera_content(file, parser))
		return (0);
	if (!fill_light_content(file, parser))
		return (0);
	if (!fill_obj(file, parser))
		return (0);
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
	if (str[i] != '\0')
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
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (i == 0 || str[i + 1] == '\0' || str[i + 1] == '\n')
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

static int	parse_segment_vec3(char **str)
{
	if (!str || !*str)
		return (-1);
	while (ft_isdigit(**str) || **str == '-' || **str == '+')
		(*str)++;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
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

// Must have 3 elements :
// 1. Identifier 'A'
// 2. Ambient lighting ratio [0.0 - 1.0] (double)
// 3. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_ambient_content(char **ambient)
{
	if (nb_of_elements(ambient) != 3)
		return (ft_putstr_fd("Error\nA: invalid number of elements\n", 2), 0);
	if (!is_identifier(ambient[0], "A"))
		return (ft_putstr_fd("Error\nA: invalid identifier\n", 2), 0);
	if (!is_double(ambient[1]))
		return (ft_putstr_fd("Error\nA: invalid lightning ratio\n", 2), 0);
	if (!is_rgb(ambient[2]))
		return (ft_putstr_fd("Error\nA: invalid RGB\n", 2), 0);
	return (1);
}

// Must have 4 elements :
// 1. Identifier 'C'
// 2. Viewpoint coordinates x,y,z (doubles)
// 3. Orientation vector x,y,z (doubles) [-1.0 - 1.0]
// 4. FOV (integer) [0 - 180]
int	parse_camera_content(char **camera)
{
	if (nb_of_elements(camera) != 4)
		return (ft_putstr_fd("Error\nC: invalid number of elements\n", 2), 0);
	if (!is_identifier(camera[0], "C"))
		return (ft_putstr_fd("Error\nC: invalid identifier\n", 2), 0);
	if (!is_vec3(camera[1]))
		return (ft_putstr_fd("Error\nC: invalid coordinates\n", 2), 0);
	if (!is_vec3(camera[2]))
		return (ft_putstr_fd("Error\nC: invalid orientation vector\n", 2), 0);
	if (!is_double(camera[3]))
		return (ft_putstr_fd("Error\nC: invalid FOV\n", 2), 0);
	return (1);
}

// Must have 3 or 4 elements :
// 1. Identifier 'L'
// 2. Light position x,y,z (doubles)
// 3. Brightness ratio [0.0 - 1.0] (double)
// 4. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_light_content(char **light)
{
	if (nb_of_elements(light) != 3 && nb_of_elements(light) != 4)
		return (ft_putstr_fd("Error\nL: invalid number of elements\n", 2), 0);
	if (!is_identifier(light[0], "L"))
		return (ft_putstr_fd("Error\nL: invalid identifier\n", 2), 0);
	if (!is_vec3(light[1]))
		return (ft_putstr_fd("Error\nL: invalid light position\n", 2), 0);
	if (!is_double(light[2]))
		return (ft_putstr_fd("Error\nL: invalid brightness ratio\n", 2), 0);
	if (nb_of_elements(light) == 4 && !is_rgb(light[3]))
		return (ft_putstr_fd("Error\nL: invalid RGB\n", 2), 0);
	return (1);
}

// Must have 4 elements :
// 1. Identifier 'sp'
// 2. Sphere center x,y,z (doubles)
// 3. Sphere diameter (double)
// 4. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_sphere_content(char **content)
{
	if (nb_of_elements(content) != 4)
		return (ft_putstr_fd("Error\nsp: invalid number of elements\n", 2), 0);
	if (!is_identifier(content[0], "sp"))
		return (ft_putstr_fd("Error\nsp: invalid identifier\n", 2), 0);
	if (!is_vec3(content[1]))
		return (ft_putstr_fd("Error\nsp: invalid center\n", 2), 0);
	if (!is_double(content[2]))
		return (ft_putstr_fd("Error\nsp: invalid diameter\n", 2), 0);
	if (!is_rgb(content[3]))
		return (ft_putstr_fd("Error\nsp: invalid RGB\n", 2), 0);
	return (1);
}

// Must have 4 elements :
// 1. Identifier 'pl'
// 2. Plane point x,y,z (doubles)
// 3. Plane normal vector x,y,z (doubles) [-1.0 - 1.0]
// 4. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_plane_content(char **content)
{
	if (nb_of_elements(content) != 4)
		return (ft_putstr_fd("Error\npl: invalid number of elements\n", 2), 0);
	if (!is_identifier(content[0], "pl"))
		return (ft_putstr_fd("Error\npl: invalid identifier\n", 2), 0);
	if (!is_vec3(content[1]))
		return (ft_putstr_fd("Error\npl: invalid point\n", 2), 0);
	if (!is_vec3(content[2]))
		return (ft_putstr_fd("Error\npl: invalid orientation vector\n", 2), 0);
	if (!is_rgb(content[3]))
		return (ft_putstr_fd("Error\npl: invalid RGB\n", 2), 0);
	return (1);
}

// Must have 5 elements :
// 1. Identifier 'cy'
// 2. Cylinder base point x,y,z (doubles)
// 3. Cylinder orientation vector x,y,z (doubles) [-1.0 - 1.0]
// 4. Cylinder diameter (double)
// 5. Cylinder height (double)
// 6. RGB color [0-255],[0-255],[0-255] (integers)
int	parse_cylinder_content(char **content)
{
	if (nb_of_elements(content) != 6)
		return (ft_putstr_fd("Error\ncy: invalid number of elements\n", 2), 0);
	if (!is_identifier(content[0], "cy"))
		return (ft_putstr_fd("Error\ncy: invalid identifier\n", 2), 0);
	if (!is_vec3(content[1]))
		return (ft_putstr_fd("Error\ncy: invalid base point\n", 2), 0);
	if (!is_vec3(content[2]))
		return (ft_putstr_fd("Error\ncy: invalid orientation vector\n", 2), 0);
	if (!is_double(content[3]))
		return (ft_putstr_fd("Error\ncy: invalid diameter\n", 2), 0);
	if (!is_double(content[4]))
		return (ft_putstr_fd("Error\ncy: invalid height\n", 2), 0);
	if (!is_rgb(content[5]))
		return (ft_putstr_fd("Error\ncy: invalid RGB\n", 2), 0);
	return (1);
}

int	parse_object_content(t_parser *parser)
{
	t_list	*current;

	current = parser->obj;
	while (current)
	{
		if (current->content == NULL)
			return (0);
		if (is_identifier(((char **)current->content)[0], "sp"))
		{
			if (!parse_sphere_content((char **)current->content))
				return (0);
		}
		else if (is_identifier(((char **)current->content)[0], "pl"))
		{
			if (!parse_plane_content((char **)current->content))
				return (0);
		}
		else if (is_identifier(((char **)current->content)[0], "cy"))
		{
			if (!parse_cylinder_content((char **)current->content))
				return (0);
		}
		else
			return (0);
		current = current->next;
	}
	return (1);
}

// Parse each content of the parser struct
int	parse_struct_content(t_parser *parser)
{
	if (!parse_ambient_content(parser->ambient))
		return (0);
	if (!parse_camera_content(parser->camera))
		return (0);
	if (!parse_light_content(parser->light))
		return (0);
	if (!parse_object_content(parser))
		return (0);
	return (1);
}

int	parse_file(char **file, t_parser *parser)
{
	if (!count_mandatory_identifiers(file))
		return (0);
	if (!detect_illegal_characters(file))
		return (0);
	if (!one_identifier_per_line(file))
		return (0);
	if (!detect_illegal_object(file))
		return (0);
	if (!fill_parser_struct(file, parser))
		return (0);
	if (!parse_struct_content(parser))
		return (0);
	return (1);
}

int	parse(int ac, char **av, t_data *data)
{
	char		**file;
	t_parser	parser;

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
