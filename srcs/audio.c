/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:35:37 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/04 10:59:23 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	play_music(t_app *app, char *file)
{
	if (SDL_GetQueuedAudioSize(app->audio.device_id) == 0)
	{
		SDL_LoadWAV(file,
			&app->audio.wav_spec, &app->audio.music, &app->audio.music_length);	
		SDL_QueueAudio(app->audio.device_id, app->audio.music, app->audio.music_length);
		SDL_PauseAudioDevice(app->audio.device_id, 0);
		SDL_FreeWAV(app->audio.music);
	}	
}

void	play_sound(t_app *app, char *file)
{
	Uint32	size;
	Uint8	*ptr;

	SDL_LoadWAV(file,
		&app->audio.wav_spec, &app->audio.sound, &app->audio.sound_length);
	if (!app->audio.sound)
		exit_error(MSG_ERROR);
	size = SDL_GetQueuedAudioSize(app->audio.device_id);
	ptr = app->audio.music + app->audio.music_length - size;
	SDL_ClearQueuedAudio(app->audio.device_id);
	SDL_MixAudioFormat(ptr, app->audio.sound, AUDIO_S16SYS, app->audio.sound_length, SDL_MIX_MAXVOLUME);
	SDL_QueueAudio(app->audio.device_id, ptr, size);
	SDL_PauseAudioDevice(app->audio.device_id, 0);
	SDL_FreeWAV(app->audio.sound);
}

void	pause_audio(t_app *app)
{
	SDL_PauseAudioDevice(app->audio.device_id, 1);
}

void	unpause_audio(t_app *app)
{
	SDL_PauseAudioDevice(app->audio.device_id, 0);
}

void	stop_audio(t_app *app)
{
	SDL_ClearQueuedAudio(app->audio.device_id);
}