/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:58:22 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/03 11:00:51 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Checks that the wall you're trying to make a portal from, isn't
 * linking to the same sector the wall is in.
*/
static t_bool	check_if_valid_link(t_app *app)
{
	t_vec2_lst	*temp;
	t_vec2_lst	*next;

	temp = app->active_sector->wall_list;
	while (temp)
	{
		if (temp == app->active_last)
			return (FALSE);
		if (temp->next == app->active_sector->wall_list)
			break ;
		next = temp->next;
		temp = next;
	}
	return (TRUE);
}

/**
 * Handles the manual linking event using active wall and active sector
 * activate on a selected wall, navigate to link target sector, activate again
 */
void	link_wall_to_sector(t_app *app)
{
	if (app->list_ongoing || app->list_creation)
	{
		app->portal_selection = FALSE;
		app->active_last = NULL;
	}
	if (app->portal_selection && app->active && app->active->type != -1)
	{
		app->active_last->type = -1;
		app->portal_selection = FALSE;
		app->active_last = NULL;
	}
	else if (app->portal_selection && app->active_sector && app->active_last)
	{
		app->active_last->type = get_sector_id(app, app->active_sector);
		if (!check_if_valid_link(app))
			app->active_last->type = -1;
		app->portal_selection = FALSE;
		app->active_last = NULL;
	}
	else if (!app->portal_selection && app->active)
	{
		app->portal_selection = TRUE;
		app->active_last = app->active;
	}
}