/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:43 by anilchen          #+#    #+#             */
/*   Updated: 2025/02/24 13:57:54 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Frees memory allocated for a 2D map array.
// Iterates through each row and frees it if allocated.
// Finally, frees the pointer to the array itself.
// If the map pointer is NULL, the function exits immediately.

void	free_map(char **map, size_t rows)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	while (i < rows)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

// Frees memory for a single frame of a texture.
// Destroys the image in the MLX context if it exists,
// and sets its pointer to NULL.
// Frees the corresponding file path string if it exists and sets it to NULL.

void	free_frames(t_game *game, t_texture *texture)
{
	int	i;

	i = 0;
	while (texture->frames[i] != NULL)
	{
		mlx_destroy_image(game->mlx, texture->frames[i]);
		texture->frames[i] = NULL;
		i++;
	}
	free(texture->frames);
	texture->frames = NULL;
}

void	free_paths(t_texture *texture)
{
	int	i;

	i = 0;
	while (texture->paths[i] != NULL)
	{
		free(texture->paths[i]);
		texture->paths[i] = NULL;
		i++;
	}
	free(texture->paths);
	texture->paths = NULL;
}

// Frees all resources associated with a framed texture.
// Iterates through each frame, freeing the image and its associated file path.
// Frees the arrays that store the frames, paths, and frame addresses.
// Sets all freed pointers to NULL to avoid dangling references.

void	free_framed_texture(t_game *game, t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->frames)
	{
		free_frames(game, texture);
	}
	if (texture->paths)
	{
		free_paths(texture);
	}
	if (texture->frames_addr)
	{
		free(texture->frames_addr);
		texture->frames_addr = NULL;
	}
}
