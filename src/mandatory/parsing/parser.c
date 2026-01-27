/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:09 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/27 23:06:56 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

void	free_tab(char **tab);
int	nb_of_elements(char **tab);
int	is_identifier(char *str, char *identifier);
int	check_range_double(double value, double min, double max);
int	check_float_overflows(char *str);

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

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

static size_t	skip_leading_ws(const char *line)
{
	size_t	src;

	src = 0;
	while (line[src] && ft_isspace(line[src]))
		src++;
	return (src);
}

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

static char	**split_rt_fields(const char *line)
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

static int	count_file_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	fill_file_array(char *filename, char **file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		file[i++] = line;
		line = get_next_line(fd);
	}
	file[i] = NULL;
	close(fd);
	return (1);
}

char	**copy_file_to_array(char *filename)
{
	int		line_count;
	char	**file;

	line_count = count_file_lines(filename);
	if (line_count < 0)
		return (NULL);
	file = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!file)
		return (NULL);
	if (!fill_file_array(filename, file))
	{
		free(file);
		return (NULL);
	}
	return (file);
}

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
	if ((c >= '0' && c <= '9') || ft_isspace(c) || c == '.'
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

static int	count_alpha_chars(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] >= 'A' && line[i] <= 'Z')
			|| (line[i] >= 'a' && line[i] <= 'z'))
			count++;
		i++;
	}
	return (count);
}

static char	get_first_non_space(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	return (*line);
}

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
		if (first != '\0'
			&& !validate_alpha_count(first, count_alpha_chars(file[i])))
			return (0);
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

// Go to the line where 'A' is located and split its content in parser->ambient
int	fill_ambient_content(char **file, t_parser *parser)
{
	int	line;

	line = where_is(file, 'A');
	if (line == -1)
		return (0);
	parser->ambient = split_rt_fields(file[line]);
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
	parser->camera = split_rt_fields(file[line]);
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
	parser->light = split_rt_fields(file[line]);
	if (!parser->light)
		return (0);
	return (1);
}

static char	get_first_char(char *line)
{
	int	j;

	j = 0;
	while (line[j] && ft_isspace(line[j]))
		j++;
	return (line[j]);
}

static int	is_obj_line(char c)
{
	return (c == 's' || c == 'p' || c == 'c');
}

static int	add_obj_node(char *line, t_parser *parser)
{
	char	**split_content;
	t_list	*node;

	split_content = split_rt_fields(line);
	if (!split_content)
		return (0);
	node = ft_lstnew(split_content);
	if (!node)
	{
		free_tab(split_content);
		return (0);
	}
	ft_lstadd_back(&parser->obj, node);
	return (1);
}

// Fill the linked list parser->obj with all objects found in the file
int	fill_obj(char **file, t_parser *parser)
{
	int		i;
	char	first_char;

	i = 0;
	parser->obj = NULL;
	while (file[i])
	{
		first_char = get_first_char(file[i]);
		if (first_char == '\0' || first_char == 'A'
			|| first_char == 'C' || first_char == 'L')
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

static int	is_int(char *str)
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

static int	check_vec3_values(char *vec, double min, double max)
{
	char	**parts;
	int		idx;

	parts = ft_split(vec, ',');
	if (!parts)
		return (0);
	if (nb_of_elements(parts) != 3)
	{
		free_tab(parts);
		return (0);
	}
	idx = 0;
	while (idx < 3)
	{
		if (!is_double(parts[idx]) || !check_float_overflows(parts[idx])
			|| !check_range_double(ft_atof(parts[idx]), min, max))
		{
			free_tab(parts);
			return (0);
		}
		idx++;
	}
	free_tab(parts);
	return (1);
}

static int	vec3_is_not_zero(char *vec)
{
	char	**parts;
	double	x;
	double	y;
	double	z;

	parts = ft_split(vec, ',');
	if (!parts)
		return (0);
	if (nb_of_elements(parts) != 3)
	{
		free_tab(parts);
		return (0);
	}
	x = ft_atof(parts[0]);
	y = ft_atof(parts[1]);
	z = ft_atof(parts[2]);
	free_tab(parts);
	if (x == 0.0 && y == 0.0 && z == 0.0)
		return (0);
	return (1);
}

static int	check_sphere_values(char **content)
{
	double	val;

	val = ft_atof(content[2]);
	if (!check_float_overflows(content[2]) || val <= 0.0)
		return (ft_putstr_fd("Error\nsp: invalid diameter\n", 2), 0);
	return (1);
}

static int	check_plane_values(char **content)
{
	if (!check_vec3_values(content[2], -1.0, 1.0))
		return (ft_putstr_fd("Error\npl: invalid normal vector value\n", 2), 0);
	if (!vec3_is_not_zero(content[2]))
		return (ft_putstr_fd("Error\npl: invalid normal vector value\n", 2), 0);
	return (1);
}

static int	check_cylinder_values(char **content)
{
	double	val;

	if (!check_vec3_values(content[2], -1.0, 1.0))
		return (ft_putstr_fd("Error\ncy: invalid axis vector value\n", 2), 0);
	if (!vec3_is_not_zero(content[2]))
		return (ft_putstr_fd("Error\ncy: invalid axis vector value\n", 2), 0);
	val = ft_atof(content[3]);
	if (!check_float_overflows(content[3]) || val <= 0.0)
		return (ft_putstr_fd("Error\ncy: invalid diameter\n", 2), 0);
	val = ft_atof(content[4]);
	if (!check_float_overflows(content[4]) || val <= 0.0)
		return (ft_putstr_fd("Error\ncy: invalid height\n", 2), 0);
	return (1);
}

static int	check_object_values(t_parser *parser)
{
	t_list	*current;
	char	**content;

	current = parser->obj;
	while (current)
	{
		content = (char **)current->content;
		if (!content)
			return (0);
		if (is_identifier(content[0], "sp")
			&& !check_sphere_values(content))
			return (0);
		else if (is_identifier(content[0], "pl")
			&& !check_plane_values(content))
			return (0);
		else if (is_identifier(content[0], "cy")
			&& !check_cylinder_values(content))
			return (0);
		current = current->next;
	}
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
	if (!is_int(camera[3]))
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

static int	parse_single_object(char **content)
{
	if (is_identifier(content[0], "sp"))
		return (parse_sphere_content(content));
	if (is_identifier(content[0], "pl"))
		return (parse_plane_content(content));
	if (is_identifier(content[0], "cy"))
		return (parse_cylinder_content(content));
	return (0);
}

int	parse_object_content(t_parser *parser)
{
	t_list	*current;

	current = parser->obj;
	while (current)
	{
		if (!current->content || !parse_single_object(current->content))
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

// Check ambient lighting ratio [0.0 - 1.0]
int	check_ambient_light_values(t_parser *parser)
{
	if (!check_float_overflows(parser->ambient[1])
		|| !check_range_double(ft_atof(parser->ambient[1]), 0.0, 1.0))
		return (ft_putstr_fd("Error\n\
A: ambient lighting ratio out of range\n", 2), 0);
	return (1);
}

// Check camera vector [-1.0 - 1.0]
// Check FOV [0 - 180]
int	check_camera_values(t_parser *parser)
{
	if (!check_vec3_values(parser->camera[2], -1.0, 1.0))
		return (ft_putstr_fd("Error\n\
C: camera orientation vector out of range\n", 2), 0);
	if (!vec3_is_not_zero(parser->camera[2]))
		return (ft_putstr_fd("Error\nC: orientation vector is null\n", 2), 0);
	if (!check_int_overflows(parser->camera[3])
		|| !check_range_int(ft_atoi(parser->camera[3]), 0, 180))
		return (ft_putstr_fd("Error\nC: FOV out of range\n", 2), 0);
	return (1);
}

// Check light brightness ratio [0.0 - 1.0]
int	check_light_values(t_parser *parser)
{
	if (!check_float_overflows(parser->light[2])
		|| !check_range_double(ft_atof(parser->light[2]), 0.0, 1.0))
		return (ft_putstr_fd("Error\n\
L: light brightness ratio out of range\n", 2), 0);
	return (1);
}

// Check if the values are within their specified ranges
int	check_values_ranges(t_parser *parser)
{
	if (!check_ambient_light_values(parser))
		return (0);
	if (!check_camera_values(parser))
		return (0);
	if (!check_light_values(parser))
		return (0);
	if (!check_object_values(parser))
		return (0);
	return (1);
}

int	parse_file(char **file, t_parser *parser)
{
	if (!count_mandatory_identifiers(file))
		return (ft_putstr_fd("Error\nproblem with identifier count\n", 2), 0);
	if (!detect_illegal_characters(file))
		return (ft_putstr_fd("Error\nillegal character detected\n", 2), 0);
	if (!one_identifier_per_line(file))
		return (ft_putstr_fd("Error\nproblem with identifiers format\n", 2), 0);
	if (!detect_illegal_object(file))
		return (ft_putstr_fd("Error\nillegal identifier detected\n", 2), 0);
	if (!fill_parser_struct(file, parser))
		return (ft_putstr_fd("Error\nfailed to fill parser struct\n", 2), 0);
	if (!parse_struct_content(parser))
		return (0);
	if (!check_values_ranges(parser))
		return (0);
	return (1);
}

// Free a string array
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// Free t_parser struct content
void	free_parser(t_parser *parser)
{
	free_tab(parser->ambient);
	free_tab(parser->camera);
	free_tab(parser->light);
	ft_lstclear(&parser->obj, (void *)free_tab);
}

t_color	store_rgb(char *str)
{
	t_color	color;
	char	**rgb_values;

	rgb_values = ft_split(str, ',');
	if (!rgb_values)
		return ((t_color){0, 0, 0});
	color.x = (unsigned char)ft_atoi(rgb_values[0]);
	color.y = (unsigned char)ft_atoi(rgb_values[1]);
	color.z = (unsigned char)ft_atoi(rgb_values[2]);
	free_tab(rgb_values);
	return (color);
}

int	store_ambient_lightning_data(char **ambient, t_ambient *data)
{
	data->ratio = ft_atof(ambient[1]);
	data->color = store_rgb(ambient[2]);
	return (1);
}

t_vec3	store_vec3(char *str)
{
	t_vec3	vec;
	char	**vec_values;

	vec_values = ft_split(str, ',');
	if (!vec_values)
		return ((t_vec3){0.0, 0.0, 0.0});
	vec.x = ft_atof(vec_values[0]);
	vec.y = ft_atof(vec_values[1]);
	vec.z = ft_atof(vec_values[2]);
	free_tab(vec_values);
	return (vec);
}

int	store_camera_data(char **camera, t_camera *data)
{
	data->origin = store_vec3(camera[1]);
	data->dir = store_vec3(camera[2]);
	data->fov = ft_atoi(camera[3]);
	return (1);
}

// Add this for bonus :
// if (nb_of_elements(light) == 4)
// 	data->color = store_rgb(light[3]);
int	store_light_data(char **light, t_light *data)
{
	data->origin = store_vec3(light[1]);
	data->ratio = ft_atof(light[2]);
	return (1);
}

int	store_sphere_data(char **content, t_data *data)
{
	t_sphere	*sphere;
	t_object	*obj_node;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->center = store_vec3(content[1]);
	sphere->diameter = ft_atof(content[2]);
	sphere->color = store_rgb(content[3]);
	obj_node = (t_object *)malloc(sizeof(t_object));
	if (!obj_node)
	{
		free(sphere);
		return (0);
	}
	obj_node->type = SPHERE;
	obj_node->data = sphere;
	obj_node->next = data->obj;
	data->obj = obj_node;
	return (1);
}

int	store_plane_data(char **content, t_data *data)
{
	t_plane		*plane;
	t_object	*obj_node;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->point = store_vec3(content[1]);
	plane->normal = store_vec3(content[2]);
	plane->color = store_rgb(content[3]);
	obj_node = (t_object *)malloc(sizeof(t_object));
	if (!obj_node)
	{
		free(plane);
		return (0);
	}
	obj_node->type = PLANE;
	obj_node->data = plane;
	obj_node->next = data->obj;
	data->obj = obj_node;
	return (1);
}

int	store_cylinder_data(char **content, t_data *data)
{
	t_cylinder	*cylinder;
	t_object	*obj_node;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->center = store_vec3(content[1]);
	cylinder->axis = store_vec3(content[2]);
	cylinder->diameter = ft_atof(content[3]);
	cylinder->height = ft_atof(content[4]);
	cylinder->color = store_rgb(content[5]);
	obj_node = (t_object *)malloc(sizeof(t_object));
	if (!obj_node)
	{
		free(cylinder);
		return (0);
	}
	obj_node->type = CYLINDER;
	obj_node->data = cylinder;
	obj_node->next = data->obj;
	data->obj = obj_node;
	return (1);
}

// goofy helper function
void	init_objects_data(t_list *obj_list, t_data *data, t_list **current)
{
	*current = obj_list;
	data->obj = NULL;
}

int	store_objects_data(t_list *obj_list, t_data *data)
{
	t_list	*current;
	char	**content;

	init_objects_data(obj_list, data, &current);
	while (current)
	{
		content = (char **)current->content;
		if (is_identifier(content[0], "sp"))
		{
			if (!store_sphere_data(content, data))
				return (0);
		}
		else if (is_identifier(content[0], "pl"))
		{
			if (!store_plane_data(content, data))
				return (0);
		}
		else if (is_identifier(content[0], "cy"))
		{
			if (!store_cylinder_data(content, data))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

int	store_data(t_parser *parser, t_data *data)
{
	if (!store_ambient_lightning_data(parser->ambient, &data->ambient))
		return (0);
	if (!store_camera_data(parser->camera, &data->cam))
		return (0);
	if (!store_light_data(parser->light, &data->light))
		return (0);
	if (!store_objects_data(parser->obj, data))
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
	ft_bzero(&parser, sizeof(t_parser));
	if (!parse_file(file, &parser))
	{
		free_parser(&parser);
		free_tab(file);
		return (0);
	}
	if (!store_data(&parser, data))
	{
		free_parser(&parser);
		free_tab(file);
		return (0);
	}
	free_parser(&parser);
	free_tab(file);
	return (1);
}
