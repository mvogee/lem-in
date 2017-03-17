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

typedef struct		s_room
{
	// all the stuff each individual room needs
	struct s_room	*next;
	char			*id;
	int				x_coord;
	int				y_coord;
	int				is_start;
	int				is_end;
	int				num_ants;
	t_connection	*connections;
}					t_room;

typedef struct 		s_all
{
	//general info such as start of linked lists number of total ants etc
	int 			num_ants;
	t_room			*rooms;
	t_room 			*start;
	t_room 			*end;
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

/*
** output.c
*/

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


#endif
