/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:13:43 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 15:46:59 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


t_object	*obj_new(char **content)
{
	t_object	*node;

	node = malloc(sizeof(t_object));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	fill_node(t_object *node, t_type type, void *data, t_vec3 color)
{
	node->type = type;
	node->data = data;
	node->color = color;
}

void	add_obj_back(t_object **lst, t_object *node)
{
	t_object	*last;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = node;
}

void	free_obj(t_object *lst)
{
	t_object	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			free_tab(lst->content);
		if (lst->data)
			free(lst->data);
		free(lst);
		lst = tmp;
	}
}
