/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:10:09 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/17 13:31:35 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"
#include <fcntl.h>
#include <unistd.h>

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
}

int	check_file_exists(char *filename)
{
	int		fd;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd != -1)
	{
		read(fd, buffer, 1);
		close(fd);
		return (1);
	}
	return (0);
}

int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

int	parse_arguments(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 4) != 0)
		return (0);
	if (ft_strlen(av[1]) < 4)
		return (0);
	if (!check_file_exists(av[1]))
		return (0);
	return (1);
}

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

void	skip_whitespaces(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

int	is_valid_id(char *line)
{
	if ((line[0] == 'A' || line[0] == 'C' || line[0] == 'L') 
		&& (line[1] == ' ' || line[1] == '\t' || line[1] == '\0'))
		return (1);
	if ((ft_strncmp(line, "sp", 2) == 0 || 
		 ft_strncmp(line, "pl", 2) == 0 || 
		 ft_strncmp(line, "cy", 2) == 0)
		&& (line[2] == ' ' || line[2] == '\t' || line[2] == '\0'))
		return (1);
	return (0);
}

// Returns 0 if it finds identifiers that are not : A, C, L, sp, pl, cy regardless of count
// accepts \n
int	check_invalid_identifiers(char **file)
{
	int	i;

	i = 0;
	char *line;

	while (file[i])
	{
		line = file[i];
		skip_whitespaces(&line);
		if (*line != '\0' && *line != '\n')
		{
			if (!is_valid_id(line))
			{
				printf("Error\nInvalid identifier found: %s\n", line);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

// there MUST be exactly one A and C, at least one L
int	check_identifier_counts(char **file)
{
	int i = 0;
	int count_A = 0;
	int count_C = 0;
	int count_L = 0;
	char *line;

	while (file[i])
	{
		line = file[i];
		skip_whitespaces(&line);
		if (*line == 'A' && (line[1] == ' ' || line[1] == '\t' || line[1] == '\0'))
			count_A++;
		else if (*line == 'C' && (line[1] == ' ' || line[1] == '\t' || line[1] == '\0'))
			count_C++;
		else if (*line == 'L' && (line[1] == ' ' || line[1] == '\t' || line[1] == '\0'))
			count_L++;
		i++;
	}
	if (count_A != 1)
		return (0);
	if (count_C != 1)
		return (0);
	if (count_L != 1)
		return (0);
	return (1);
}

int	count_letter(char *line, char letter, int expected_count)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == letter)
			count++;
		i++;
	}
	if (count != expected_count)
		return (0);
	return (1);
}


int	parse_file(char *filename)
{
	char    **file;

	file = copy_file_to_array(filename);
	if (!file)
		return (0);
	if (!check_invalid_identifiers(file))
		return (0);
	if (!check_identifier_counts(file))
		return (0);
	// if (check_each_acl_identifiers(file) == 0)
	// 	return (0);
	return (1);
}

int	parse(int ac, char **av)
{
	if(!parse_arguments(ac, av))
		return (0);
	if (!parse_file(av[1]))
		return (0);
	printf("Parsing successful.\n");
	return (1);
}
