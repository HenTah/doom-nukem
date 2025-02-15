/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_assets_wav.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:00:47 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 21:44:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Exports wav audio data.
 * 
 * @param info 
 * @param index 
 * @param fd 
 * @param path 
 */
void	export_wav(t_import_info *info, int index, int fd, const char *path)
{
	unsigned char	*buffer;
	int				length;
	int				write_length;
	int				i;

	buffer = NULL;
	length = 0;
	buffer = read_source(path, &length);
	if (!buffer)
		exit_error(MSG_ERROR_FILE_READ);
	info->header.asset_info[index].size = length;
	i = 0;
	while (i < length)
	{
		if (i + MAX_UNCOMPRESS_BATCH < length)
			write_length = MAX_UNCOMPRESS_BATCH;
		else
			write_length = length - i;
		if (write(fd, buffer + i, write_length) == -1)
			exit_error(MSG_ERROR_FILE_WRITE);
		calculate_progress_assets(info, index, i);
		i += MAX_UNCOMPRESS_BATCH;
	}
	free(buffer);
}

/**
 * @brief Exports all game audio data.
 * 
 * @param info 
 * @param fd 
 */
void	export_wavs(t_import_info *info, int fd)
{
	export_wav(info, EXPORT_MUSIC, fd, MUSIC_PATH);
	export_wav(info, EXPORT_SOUND_LASER, fd, SOUND_LASER_PATH);
	export_wav(info, EXPORT_SOUND_SHOT, fd, SOUND_SHOT_PATH);
	export_wav(info, EXPORT_SOUND_RELOAD, fd, SOUND_RELOAD_PATH);
	export_wav(info, EXPORT_SOUND_BUMP, fd, SOUND_BUMP_PATH);
	export_update_progress(info);
}
