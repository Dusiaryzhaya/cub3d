/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:23:10 by stefan            #+#    #+#             */
/*   Updated: 2025/02/24 14:05:47 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// Initializes the player structure with starting position, orientation,
// and default values.
// - start_x, start_y: Starting coordinates of the player.
// - orientation: The angle at which the player initially faces.
// Sets default movement flags to false, player HP, direction vector,
// and camera plane for rendering.

void	init_player(t_ctrl *ctrl)
{
	int	index;

	index = get_table_index(ctrl->game->player.angle);
	ctrl->game->player.x = ctrl->map.player_position.x;
	ctrl->game->player.y = ctrl->map.player_position.y;
	ctrl->game->player.angle = ctrl->map.player_position.orientation;
	ctrl->game->player.key_up = false;
	ctrl->game->player.key_down = false;
	ctrl->game->player.key_right = false;
	ctrl->game->player.key_left = false;
	ctrl->game->player.left_rotate = false;
	ctrl->game->player.right_rotate = false;
	ctrl->game->player.hp = PLAYER_HP;
	ctrl->game->player.dir_x = ctrl->trig_tables->cos_table[index];
	ctrl->game->player.dir_y = ctrl->trig_tables->sin_table[index];
	ctrl->game->player.plane_x = -ctrl->game->player.dir_y * 0.66;
	ctrl->game->player.plane_y = ctrl->game->player.dir_x * 0.66;
}

// Initializes the texture structure and allocates memory for frame data.
// - texture: Pointer to the texture structure to initialize.
// - max_frames: The maximum number of frames the texture can hold.
// Allocates memory for frames, paths, and frame addresses.
// Exits on allocation failure.

void	init_texture(t_texture *texture, int max_frames)
{
	int	i;

	i = 0;
	ft_memset(texture, 0, sizeof(t_texture));
	texture->path = NULL;
	texture->frames = malloc(max_frames * sizeof(void *));
	texture->paths = malloc(max_frames * sizeof(void *));
	texture->frames_addr = malloc(max_frames * sizeof(void *));
	if (!texture->frames || !texture->paths || !texture->frames_addr)
	{
		printf("Error: Failed to allocate memory for texture frames\n");
		exit(EXIT_FAILURE);
	}
	while (i < max_frames)
	{
		texture->frames[i] = NULL;
		texture->paths[i] = NULL;
		texture->frames_addr[i] = NULL;
		i++;
	}
}

// Initializes the main game structure with default values and textures.
// Sets default colors for floor and ceiling, initializes
// shooting and fight parameters,
// and prepares directional textures with a predefined frame count

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	init_texture(&game->north_texture, 4);
	init_texture(&game->south_texture, 4);
	init_texture(&game->east_texture, 4);
	init_texture(&game->west_texture, 4);
	game->floor_color = 0xFFFFFFFF;
	game->ceiling_color = 0xFFFFFFFF;
	game->is_shooting = 0;
	game->shoot_ac = 0;
	game->fight.fight_started = 0;
	game->fight.enemy_shoot = 0;
	game->fight.player_shoot = 0;
	game->fight.shoot_delay = 80;
	game->fight.lose_flag = 0;
	game->fight.win_flag = 0;
}

// Initializes the map structure with default values.
// Resets map properties like size, player positions,
// enemy/door counters, and sets pointers to NULL.

void	init_map(t_map *map)
{
	map->full_map = NULL;
	map->map_tmp = NULL;
	map->player_position.x = 0;
	map->player_position.y = 0;
	map->player_index.x = 0;
	map->player_index.y = 0;
	map->rows = 0;
	map->columns = 0;
	map->players_count = 0;
	map->has_free_way = 0;
	map->textures_defined = 0;
	map->colors_defined = 0;
	map->map_started = 0;
	map->doors_counter = 0;
	map->enemies_counter = 0;
	map->doors = NULL;
	map->enemies = NULL;
}

// Initializes the main control structure (t_ctrl).
// - Sets up the map, game, and trigonometric tables.
// - Allocates memory for the game structure and handles
// allocation failures gracefully.
// - Returns 0 on success, 1 on failure.

int	init_ctrl(t_ctrl *ctrl)
{
	init_map(&ctrl->map);
	ctrl->show_controls = 0;
	ctrl->anim.fc = 0;
	ctrl->anim.ac = 0;
	ctrl->gnl.save = NULL;
	ctrl->gnl.line = NULL;
	ctrl->game = malloc(sizeof(t_game));
	if (!ctrl->game)
		return (1);
	init_game(ctrl->game);
	ctrl->trig_tables = init_trig_tables();
	if (!ctrl->trig_tables)
	{
		printf("Error: Failed to initialize trigonometric tables.\n");
		free(ctrl->game);
		return (1);
	}
	return (0);
}
