/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:00:00 by kevisout          #+#    #+#             */
/*   Updated: 2026/02/07 15:33:53 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
	// parser->lst = NULL;
}
