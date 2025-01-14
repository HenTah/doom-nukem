/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:38:26 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/06 13:36:37 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Mouse click events in the player menu.
 * 
 * @param app
 * @param mouse
*/
void	player_menu_events(t_app *app, t_point	mouse)
{
	select_inventory(app, mouse);
	select_weapons(app, mouse);
}

/**
 * @brief Changes interaction's event id to 0 (no interaction). If wall/sector/
 * object had an interaction before, deletes the existing interaction.
 * 
 * @param app
*/
static void	no_interaction_check(t_app *app)
{
	int		id;
	int		interaction;

	if (!app->current_interaction)
		return ;
	if (app->current_interaction->event_id)
	{
		interaction = find_interaction(app);
		id = interaction;
		while (id < MAX_INTERACTIONS
			&& app->interactions[interaction].event_id != 0)
		{
			if (&(app->interactions[id]) == app->current_interaction)
				delete_interaction(app, id);
			id++;
		}
		app->current_interaction = NULL;
		app->interaction_menu = FALSE;
	}
	else
		app->current_interaction->event_id = 0;
}

/**
 * @brief Updates the target sector for the current interaction based on mouse
 * click.
 * 
 * @param app
 * @param mouse
*/
static void	update_target_sector(t_app *app, t_point mouse)
{
	if (app->current_interaction && mouse.x > HELP_MENU_W)
	{
		app->current_interaction->target_sector = find_child_target_sector(app,
				app->current_interaction->target_sector);
		if (!app->current_interaction->target_sector)
			app->current_interaction->target_sector = find_child_sector(app);
		if (!app->current_interaction->target_sector)
			app->current_interaction->target_sector = click_sector(app);
		if (!app->current_interaction->target_sector)
			app->current_interaction->target_sector = app->active_sector;
	}
}

/**
 * @brief Updates the interaction's event id for the one clicked on the menu.
 * 
 * @param app
 * @param start_y
 * @param mouse
*/
static void	update_event_id(t_app *app, int start_y, t_point mouse)
{
	if (!app->current_interaction)
		return ;
	if (check_mouse(mouse, (t_rect){90, start_y + 25, 113, 15}))
		no_interaction_check(app);
	if (check_mouse(mouse, (t_rect){100, start_y + 40, 93, 15}))
		app->current_interaction->event_id = 1;
	if (check_mouse(mouse, (t_rect){90, start_y + 55, 110, 15}))
		app->current_interaction->event_id = 2;
	if (check_mouse(mouse, (t_rect){50, start_y + 70, 183, 15}))
		app->current_interaction->event_id = 3;
	if (check_mouse(mouse, (t_rect){125, start_y + 85, 40, 15}))
		app->current_interaction->event_id = 4;
	if (check_mouse(mouse, (t_rect){110, start_y + 100, 70, 15}))
		app->current_interaction->event_id = 5;
	if (check_mouse(mouse, (t_rect){125, start_y + 115, 40, 15}))
		app->current_interaction->event_id = 6;
	if (check_mouse(mouse, (t_rect){102, start_y + 130, 82, 15}))
		app->current_interaction->event_id = 7;
}

/**
 * @brief Mouse click events in the interaction menu. If click is outside menu,
 * changes interaction's targer sector to the one clicked (if click's outside
 * sector, targer sector is active sector). Clicking interaction menu changes
 * the event id accordingly.
 * 
 * @param app
 * @param start_y
 * @param mouse
*/
void	interaction_menu_events(t_app *app, int start_y, t_point mouse)
{
	if (!app->current_interaction)
		return ;
	update_target_sector(app, mouse);
	update_event_id(app, start_y, mouse);
	if (check_mouse(mouse, (t_rect){158, start_y + 300, 40, 20}))
		app->current_interaction->requires_key = FALSE;
	if (check_mouse(mouse, (t_rect){213, start_y + 300, 40, 20}))
		app->current_interaction->requires_key = TRUE;
	if (check_mouse(mouse, (t_rect){204, start_y + 255, 60, 15})
		&& app->current_interaction->interaction_link == -1)
			app->current_interaction->interaction_link = 0;
	if (check_mouse(mouse, (t_rect){187, start_y + 273, 73, 16})
		&& app->current_interaction->interaction_link > -1)
		app->current_interaction->interaction_link = -1;
	if (check_mouse(mouse, (t_rect){85, start_y + 330, 150, 15}))
		link_interaction(app);
}
