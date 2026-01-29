/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:50:50 by kevisout          #+#    #+#             */
/*   Updated: 2026/01/29 15:40:04 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

/*
- Checks if there is exactly 1 argument (the file name)
- Checks if the file has a .rt extension
- Checks if the file exists and is readable
*/
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
