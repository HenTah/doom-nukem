/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_render_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:54:45 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 21:05:58 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

int	object_tex_size(t_app *app, int id)
{
	if (app->objects[id].type <= MAX_SMALL_OBJECTS)
	{
		return (TEX_PICKUP);
	}
	return (TEX_OBJECT);
}

/**
 * Returns radial direction of a vector.
 */
double	get_radial_direction(t_vector2 *vector)
{
	double	rad;

	rad = atan2(vector->x, vector->y);
	if (rad < 0)
		rad = rad + 2 * M_PI;
	return (rad);
}

void	object_frame(t_app *app, t_vector2 dir, t_render_object *object)
{
	double	rad;

	object->frame = 0;
	if (app->objects[object->id].type <= MAX_UNIQUE_OBJECTS)
	{
		rad = get_radial_direction(&dir);
			object->frame = ((int)((rad + app->objects[object->id].rot)
					/ PI_PI * SPRITE_ANGLES) % SPRITE_ANGLES);
	}
}

void	init_draw_area(t_render_object *object)
{
	object->draw_start = object->start;
	if (object->draw_start.x < 0)
		object->draw_start.x = 0;
	if (object->draw_start.y < 0)
		object->draw_start.y = 0;
	if (object->end.x >= WIN_W)
		object->end.x = WIN_W - 1;
	if (object->end.y >= WIN_H)
		object->end.y = WIN_H - 1;
}

void	draw_object_pixel(t_app *app, t_render_object *object,
		t_point window, int color)
{
	if ((color & 0xFF000000) > 0)
	{
		put_pixel_to_surface_check(app, window, shade_depth(
				shade_color(color, object->light), object->dist), object->dist);
	}
}