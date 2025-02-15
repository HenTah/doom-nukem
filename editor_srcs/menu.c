/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:50:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/06 15:35:24 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief The main help menu texts, shown when no specific edit mode is on.
 * 
 * @param app
 * @param start_y
*/
static void	main_menu(t_app *app, int start_y)
{
	render_text(app, (t_rect){20, start_y, 260, 100}, "DIVIDE GRID ( Z / X ) \n\
MOVE ( WASD ) \nZOOM ( SCROLL ) \nRETURN TO ORIGIN ( 1 )");
	render_text(app, (t_rect){20, start_y + 55, 270, 100}, "LEFT CLICK MOUSE TO\
 SELECT SECTOR / POINT / OBJECT / PLAYER. POINT / OBJECT / MEMBER SECTOR\
 REQUIRE AN ACTIVE SECTOR SELECTION FIRST.");
	render_text(app, (t_rect){20, start_y + 125, 270, 15}, "RIGHT CLICK MOUSE\
 TO UNSELECT.");
	render_point(app, screen_to_world(app, (t_point){25, start_y + 149}),
		3, PLAYER);
	render_text(app, (t_rect){35, start_y + 144, 270, 15}, "PLAYER");
	render_text(app, (t_rect){20, start_y + 160, 270, 30}, "PLAYER MUST BE\
 PLACED INSIDE AN ACTIVE SECTOR (NOT IN MEMBER).");
	render_text(app, (t_rect){20, start_y + 200, 270, 15}, "SECTORS");
	render_text(app, (t_rect){205, start_y + 200, 270, 15}, "/");
	render_amount_info(app, (t_rect){180, 240, 90, 15}, app->sector_count);
	render_amount_info(app, (t_rect){220, 240, 90, 15}, MAX_SECTOR_COUNT);
	render_text(app, (t_rect){20, start_y + 215, 270, 15}, "OBJECTS");
	render_text(app, (t_rect){205, start_y + 215, 270, 15}, "/");
	render_amount_info(app, (t_rect){180, 255, 90, 15}, app->object_count);
	render_amount_info(app, (t_rect){220, 255, 90, 15}, MAX_OBJECTS);
	render_text(app, (t_rect){18, start_y + 230, 270, 15}, "INTERACTIONS");
	render_text(app, (t_rect){205, start_y + 230, 270, 15}, "/");
	render_amount_info(app, (t_rect){180, 270, 90, 15}, app->interaction_count);
	render_amount_info(app, (t_rect){220, 270, 90, 15}, MAX_INTERACTIONS);
}

/**
 * @brief Renders the texts for the buttons on the upper right corner.
 * 
 * @param app
*/
static void	render_button_menu_texts(t_app *app)
{
	if (app->active_sector)
	{
		if (get_member_sector_count(app->active_sector) >= MAX_MEMBER_SECTORS
			|| app->active_sector->parent_sector)
			toggle_active_color(app, TRUE, "CANNOT ADD NEW (MEMBER) SECTOR",
				(t_rect){WIN_W - 145, 10, 180, 40});
		else
			toggle_active_color(app, app->list_creation, "CREATE MEMBER",
				(t_rect){WIN_W - 135, 17, 150, 15});
		if (app->object_count < MAX_OBJECTS)
			toggle_active_color(app, app->object_new, "ADD OBJECT",
				(t_rect){WIN_W - 120, 77, 150, 15});
		else
			toggle_active_color(app, TRUE, "CANNOT ADD MORE OBJECTS",
				(t_rect){WIN_W - 145, 70, 150, 40});
	}
	else
		toggle_active_color(app, app->list_creation, "CREATE SECTOR",
			(t_rect){WIN_W - 135, 17, 150, 15});
	toggle_active_color(app, app->linking_mode, "AUTO PORTALS",
		(t_rect){WIN_W - 130, 47, 150, 15});
	toggle_active_color(app, FALSE, "SAVE",
		(t_rect){WIN_W - 100, 107, 150, 15});
	toggle_active_color(app, FALSE, "SAVE WITH ASSETS",
		(t_rect){WIN_W - 144, 137, 150, 15});
}

/**
 * @brief Renders the buttons on the upper right corner.
 * 
 * @param app
 * @param mouse
*/
static void	render_button_menu(t_app *app, t_point mouse)
{
	int		index;
	int		y;

	index = -1;
	y = 10;
	while (++index < 5)
	{
		if ((get_member_sector_count(app->active_sector) >= MAX_MEMBER_SECTORS
				&& y == 10) || (y == 10 && app->active_sector
				&& app->active_sector->parent_sector)
			|| (y == 70 && !app->active_sector)
			|| (y == 70 && app->object_count >= MAX_OBJECTS))
		{
			y += 30;
			continue ;
		}
		if (check_mouse(mouse, (t_rect){WIN_W - 160, y, 150, 20}))
			color_surface(app->assets.ui_frame, ACTIVE_TEXT);
		render_ui_frame(app, (t_rect){WIN_W - 160, y, 150, 25}, 1, BG_MENU);
		color_surface(app->assets.ui_frame, TEXT);
		y += 30;
	}
	render_button_menu_texts(app);
}

/**
 * @brief Renders the correct menu texts on the help menu sidebar depending what
 * editing mode is on.
 * 
 * @param app
*/
static void	help_menu_texts(t_app *app)
{
	t_point	mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	change_font(app, 20, TEXT);
	render_text(app, (t_rect){10, 10, 260, 20}, "LEVEL EDITOR");
	change_font(app, 11, TEXT);
	if (app->active_sector && !app->active && !app->object_menu
		&& !app->interaction_menu)
		sector_edit_menu(app, mouse, 40);
	else if (app->active && !app->interaction_menu && !app->object_menu
		&& !app->list_creation)
		wall_edit_menu(app, mouse);
	else if (app->interaction_menu)
		interaction_edit_menu(app, 40, mouse);
	else if (app->player_menu)
		player_edit_menu(app);
	else if (app->object_menu)
		object_edit_menu(app);
	else
	{
		main_menu(app, 40);
		gravity_menu(app);
	}
	color_surface(app->assets.ui_frame, TEXT);
	render_button_menu(app, mouse);
}

/**
 * @brief Renders the help menu sidebar to the left of the screen.
 * 
 * @param app
*/
void	render_help_menu(t_app *app)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < HELP_MENU_W)
		{
			if (x > (HELP_MENU_W - 3) || x < 2 || y < 2 || y > (WIN_H - 3))
				put_pixel_to_surface(app->surface, x, y, TEXT);
			else
				put_pixel_to_surface(app->surface, x, y, BG_MENU);
			x++;
		}
		y++;
	}
	color_surface(app->assets.ui_frame, ACTIVE_TEXT);
	help_menu_texts(app);
	color_surface(app->assets.ui_frame, TEXT);
}
