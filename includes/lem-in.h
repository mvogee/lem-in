/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft.h"
#include "ft_printf.h"
#include <limits.h>

typedef enum 		e_error
{
	GENERAL,
	NO_ANTS,
	NO_START,
	NO_END,
	NO_ROOMS,
	NO_VALID_PATH,
	DUPLICATE_NAME
}					t_error;

typedef enum		e_infotype
{
	NUM_ANTS = 0,
	ROOMS = 1,
	CONNECTIONS = 2
}					t_infotype;

typedef struct		s_connection
{
	struct s_connection	*next;
	struct s_room 		*room;
}					t_connection;

typedef struct 		s_visited
{
	struct s_visited	*next;
	struct s_room		*room;
}					t_visited;

typedef struct 		s_ants
{
	struct s_ants	*next;
	int 			moved;
	int				id;
	struct s_room	*room;
	t_visited		*visited;
}					t_ants;

typedef struct		s_room
{
	struct s_room	*next;
	char			*id;
	int				x_coord;
	int				y_coord;
	int				is_start;
	int				is_end;
	int				num_ants;
	t_connection	*connections;
	int				visited;
	int				path_checked;
	int				pathable;
	int				to_end;
}					t_room;


typedef struct 		s_all
{
	int				num_ants;
	t_room			*rooms;
	t_room			*start;
	t_room			*end;
	int				num_paths;
	t_ants			*ants;
}					t_all;

/*
** prototypes
*/

/*
** main.c
*/

void	throw_error(int reason);
t_room	*find_start(t_room *rooms);
t_room	*find_end(t_room *rooms);
int		check_reachable(t_room **start, char *end_id);
void	reset_visited(t_room **rooms);

/*
** output.c
*/

void	print_ants(t_ants *ants);
void	print_distances(t_all **all);
void	print_connections(t_connection *connections);
void	print_rooms(t_room	*start);

/*
** parse_information
*/

int				count_char(char *str, char c);
int				ft_isnum(char *str);

void			check_name_exists(char *id, t_room **rooms);
t_room			*make_room(char *id, int x_coord, int y_coord, int start_end);
t_room			*start_end_room(char *line, t_room **rooms);
void			add_room(t_room *new_room, t_room **rooms);
void			parse_rooms(char *line, t_room **rooms, int *info_type);

void			check_valid_name(t_room **rooms, char *id);
t_connection	*make_connection(t_room *room);
void			add_connection(t_room **rooms, char *home, char *room2);
void			parse_connection(char *line, t_room **rooms);

t_room			*parse_information(int *num_ants);

/*
** find_paths.c
*/

int		get_potential_paths(t_all **all, char *end_id);
void	reset_path_checked(t_room **start);
void	set_node_distance(t_room **room, int distance);
int		get_max_start_dist(t_room *start);

void	reset_moved(t_ants **ants);
void	add_visited_room(t_visited **visited, t_room **room);
t_ants	*create_new_ant(int id, t_room **start);
void	add_new_ant(t_ants **ants, t_ants *new_ant);
void	create_ants(t_all **all);

int		not_visited(t_visited *visited_rooms, t_room *room_to_check);
void	move_ant(t_ants **ant, t_room **moveto);
void	find_move(t_ants **ant);
t_ants	*get_closest_ant(t_ants **ants);
t_ants	*remove_ant(t_ants **ants, t_ants *done_ant);
void	start_movement(t_all **all);

void	find_paths(t_all **all);


/*
** freeing.c
*/

void	free_visited(t_visited **visited);
void	free_connections(t_connection **connections);
void	free_rooms(t_room **rooms);
void	free_all(t_all **all);

#endif
