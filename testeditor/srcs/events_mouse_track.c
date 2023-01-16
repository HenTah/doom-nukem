/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse_track.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:08:29 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 19:08:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Tracks mouse position and saves the snapped location to t_app
 * 
 * @param app 
 * @return int 
 */
int	events_mouse_track(t_app *app)
{
	t_point	current_pos;

	SDL_GetMouseState(&current_pos.x, &current_pos.y);
	snap_to_nearest(app, &current_pos, &app->mouse_track, app->divider);
	if (app->mouse_down && app->player_menu
		&& check_mouse(current_pos, (t_rect){40, 185, 240, 20}))
			app->player.armor = current_pos.x - 40;
	if (app->mouse_down && app->player_menu
		&& check_mouse(current_pos, (t_rect){40, 245, 240, 20}))
			app->player.health = current_pos.x - 40;
	if (app->player_menu && check_mouse(current_pos, (t_rect){40, 60, 32, 32}))
		app->player.selected_weapon = 0;
	if (app->player_menu && check_mouse(current_pos, (t_rect){82, 60, 32, 32}))
		app->player.selected_weapon = 1;
	if (app->player_menu && check_mouse(current_pos, (t_rect){124, 60, 32, 32}))
		app->player.selected_weapon = 2;
	if (app->player_menu && check_mouse(current_pos, (t_rect){166, 60, 32, 32}))
		app->player.selected_weapon = 3;
	if (app->player_menu && check_mouse(current_pos, (t_rect){208, 60, 32, 32}))
		app->player.selected_weapon = 4;
	return (0);
}