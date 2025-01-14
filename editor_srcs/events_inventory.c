/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_inventory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:59:10 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/07 14:29:57 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Decreases the item amount of the inventory if the item is selected.
 * 
 * @param app
*/
static void	decrease_item_amount(t_app *app)
{
	if (app->selected[0] && app->player.inventory.armor_pack > 0)
		app->player.inventory.armor_pack--;
	if (app->selected[1] && app->player.inventory.key > 0)
		app->player.inventory.key--;
	if (app->selected[2] && app->player.inventory.ammo > 0)
		app->player.inventory.ammo--;
	if (app->selected[3] && app->player.inventory.potion > 0)
		app->player.inventory.potion--;
	if (app->selected[4] && app->player.inventory.jetpack == TRUE)
		app->player.inventory.jetpack = FALSE;
}

/**
 * @brief Increases the item amount of the inventory if the item is selected.
 * 
 * @param app
*/
static void	increase_item_amount(t_app *app)
{
	if (app->selected[0]
		&& app->player.inventory.armor_pack < MAX_ITEM_CAPACITY)
		app->player.inventory.armor_pack++;
	if (app->selected[1] && app->player.inventory.key < MAX_ITEM_CAPACITY)
		app->player.inventory.key++;
	if (app->selected[2] && app->player.inventory.ammo < MAX_AMMO)
		app->player.inventory.ammo++;
	if (app->selected[3] && app->player.inventory.potion < MAX_ITEM_CAPACITY)
		app->player.inventory.potion++;
	if (app->selected[4] && app->player.inventory.jetpack == FALSE)
		app->player.inventory.jetpack = TRUE;
}

/**
 * @brief Event function to change item amount in inventory using the left and
 * right arrowkeys.
 * 
 * @param app
 * @param keycode
*/
void	change_item_amount(t_app *app, SDL_Keycode keycode)
{
	if (keycode == SDLK_LEFT)
		decrease_item_amount(app);
	if (keycode == SDLK_RIGHT)
		increase_item_amount(app);
}
