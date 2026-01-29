/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevisout <kevisout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 18:26:32 by kevisout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Counts the number of lines in a file.
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

// Fills a preallocated array with all lines from a file (NULL-terminated).
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

// Reads an entire file into a NULL-terminated array of lines.
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
