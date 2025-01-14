/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_wall_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:32:25 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/23 16:26:18 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief When a decor is selected on the wall, displays interaction options
 * for it and placement offset options.
 * 
 * @param app
 * @param mouse
*/
static void	render_wall_decor_options(t_app *app, t_point mouse)
{
	int		id;
	char	*offset;

	if (!app->current_interaction)
		id = find_decor_interaction(app, 0, 1);
	else
		id = find_interaction(app);
	render_current_interaction_status(app, mouse, 220, id);
	toggle_active_color(app, app->decor_edit, "DECOR OFFSET ( G )",
		(t_rect){25, 290, 200, 20});
	render_text(app, (t_rect){25, 305, 260, 100}, "ACTIVATE DECOR OFFSET \
WITH 'G' AND USE ARROW KEYS TO CHANGE. \n \n  X\n  Y");
	offset = ft_ftoa(app->active->decor_offset.x, 4);
	if (!offset)
		return ;
	render_text(app, (t_rect){60, 342, 50, 15}, offset);
	free(offset);
	offset = ft_ftoa(app->active->decor_offset.y, 4);
	if (!offset)
		return ;
	render_text(app, (t_rect){60, 357, 50, 15}, offset);
	free(offset);
}

/**
 * @brief Renders the wall's portal related information. 
 * 
 * @param app
*/
static void	render_portal_status(t_app *app)
{
	if (app->active->type != -1)
	{
		toggle_active_color(app, 1, "- PORTAL -", (t_rect){50, 380, 200, 20});
		toggle_active_color(app, 0, "NO PORTAL", (t_rect){155, 380, 200, 20});
	}
	else
	{
		toggle_active_color(app, 0, "PORTAL", (t_rect){60, 380, 200, 20});
		toggle_active_color(app, 1, "- NO PORTAL -",
			(t_rect){145, 380, 200, 20});
	}
	toggle_active_color(app, app->portal_selection, "CREATE PORTAL ( L )",
		(t_rect){25, 410, 260, 15});
	render_text(app, (t_rect){25, 430, 265, 150}, "SELECT WALL TO CREATE PORTAL\
, PRESS 'L', SELECT SECTOR TO LINK PORTAL TO, PRESS 'L' AGAIN. DOUBLE PRESS 'L'\
 TO REMOVE PORTAL.");
}

/**
 * @brief If wall doesn't have a decor (-1), renders add button, else 
 * showcases the decor icons.
 * 
 * @param app
 * @param mouse
*/
static void	handle_wall_decor(t_app *app, t_point mouse)
{
	if (app->active->decor == -1)
	{
		render_ui_frame(app, (t_rect){90, 160, 100, 21}, 1, 0);
		render_interaction_button(app, (t_rect){108, 166, 100, 20}, mouse,
			"ADD DECOR");
	}
	else
	{
		render_up_and_down_arrows(app, (t_point){263, 160},
			(t_point){10, 165}, 8);
		render_icons(app, (t_point){25, 150}, app->active->decor,
			app->assets.objects);
		render_ui_frame(app, (t_rect){185, 120, 80, 21}, 1, 0);
		render_interaction_button(app, (t_rect){200, 125, 120, 20}, mouse,
			"REMOVE");
		render_wall_decor_options(app, mouse);
	}
}

/**
 * @brief Renders wall specific information on the help menu sidebar when active
 * wall is selected.
 * 
 * @param app
 * @param mouse
*/
void	wall_edit_menu(t_app *app, t_point mouse)
{
	toggle_active_color(app, 1, "WALL", (t_rect){125, 32, 200, 15});
	render_arrows(app, (t_point){12, 70}, (t_point){265, 70});
	render_icons(app, (t_point){25, 60}, app->active->tex, app->assets.sprite);
	toggle_active_color(app, 1, "DECOR", (t_rect){122, 122, 200, 15});
	handle_wall_decor(app, mouse);
	render_portal_status(app);
	render_text(app, (t_rect){25, 505, 260, 15}, "CREATE / CHANGE FLOOR SLOPE\
 ( H )");
	render_text(app, (t_rect){25, 520, 260, 15}, "CREATE / CHANGE CEILING SLOPE\
 ( Y )");
	if (app->active_sector->floor_slope_wall == app->active)
		toggle_active_color(app, TRUE, "FLOOR SLOPE STARTS FROM THIS WALL.",
			(t_rect){25, 540, 260, 30});
	if (app->active_sector->ceil_slope_wall == app->active)
		toggle_active_color(app, TRUE, "CEILING SLOPE STARTS FROM THIS WALL.",
			(t_rect){25, 570, 260, 30});
}

/**
 * @brief Deletes all existing decor interactions for a specific wall decor.
 * 
 * @param app
*/
void	del_all_decor_interactions(t_app *app)
{
	int		id;

	id = 0;
	while (id < MAX_INTERACTIONS)
	{
		if (app->interactions[id].activation_wall == app->active
			&& app->interactions[id].activation_sector == app->active_sector)
			delete_interaction(app, id);
		id++;
	}
	app->current_interaction = NULL;
}
