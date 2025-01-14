/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:33:06 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 18:31:09 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Changes all wall types of the selected sector to it's parent,
 * linking them together.
 * 
 * @param app
 * @param sector
 */
void	change_walls_type(t_app *app, t_sector_list *sector)
{
	t_wall_list	*head;

	if (!sector)
		return ;
	head = sector->wall_list;
	while (head)
	{
		head->type = get_sector_id(app, sector->parent_sector);
		head = head->next;
		if (head == sector->wall_list)
			break ;
	}
}

/**
 * @brief Changes all walls in the given list to wall_tex param.
 * 
 * @param walls 
 * @param wall_tex 
 */
void	change_walls_tex(t_wall_list *walls, int wall_tex)
{
	t_wall_list	*tmp;

	tmp = walls;
	while (tmp)
	{
		tmp->tex = wall_tex;
		tmp = tmp->next;
		if (tmp == walls)
			break ;
	}
}
