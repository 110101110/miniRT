/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qizhang <qizhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:09:43 by qizhang           #+#    #+#             */
/*   Updated: 2026/01/29 16:00:11 by qizhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	clean_exit(t_data *data)
{
	if (data->obj)
		free_obj(data->obj);
	data->obj = NULL;
	return (0);
}
