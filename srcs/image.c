/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:30 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/06 19:27:09 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Changes color of a specific pixel in surface.
 * 
 * @param surface 
 * @param x 
 * @param y 
 * @param color 
 */
void	put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (y * surface->pitch) + (x * IMAGE_PIXEL_BYTES);
	if (x < 0 || y < 0 || pixel_pos < 0 || x >= surface->w || y >= surface->h)
		return ;
	pixel = surface->pixels + pixel_pos;
	*(int *)pixel = color;
}

/**
 * @brief Changes color of a specific pixel in surface.
 * 
 * @param surface 
 * @param x 
 * @param y 
 * @param color 
 */
void	put_pixel_to_surface_check(t_app *app, t_point point,
	int color, float distance)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (point.y * app->surface->pitch) + (point.x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || point.x < 0 || point.y < 0
		|| point.x >= app->surface->w || point.y >= app->surface->h)
		return ;
	if (app->depthmap[point.y / 2][point.x] >= distance)
	{
		pixel = app->surface->pixels + pixel_pos;
		if (point.y % 2)
			app->depthmap[point.y / 2][point.x] = distance;
		*(int *)pixel = color;
	}
}
