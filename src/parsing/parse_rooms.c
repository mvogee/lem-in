/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		check_name_exists(char *id, t_room **rooms)
{
	t_room		*tmp;

	tmp = *rooms;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (ft_strequ(id, tmp->id))
			throw_error(DUPLICATE_NAME);
		tmp = tmp->next;
	}
}

t_room		*make_room(char *id, int x_coord, int y_coord, int start_end)
{
	t_room		*new_room;

	new_room = (t_room*)ft_memalloc(sizeof(t_room));
	new_room->id = id;
	new_room->x_coord = x_coord;
	new_room->y_coord = y_coord;
	if (start_end > 0)
		new_room->is_start = 1;
	else if (start_end < 0)
		new_room->is_end = 1;
	new_room->num_ants = 0;
	new_room->next = NULL;
	new_room->connections = NULL;
	new_room->to_end = INT_MAX;
	return (new_room);
}

t_room		*start_end_room(char *line, t_room **rooms)
{
	char		**input;
	t_room		*new_room;
	int 		start_end;

	start_end = (ft_strequ(line, "##start") ? 1 : -1);
	free(line);
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (line[0] == '#')
		{
			free(line);
			continue ;
		}
		else if (count_words(line, ' ', 0, 0) == 3)
			break ;
		else if (count_char(line, '-'))
			throw_error(GENERAL);
	}
	input = ft_strsplit(line, ' ');
	check_name_exists(input[0], rooms);
	new_room = make_room(input[0], ft_atoi(input[1]),
		ft_atoi(input[2]), start_end);
	free_inputs(input, 1, 2);
	return (new_room);
}

void		add_room(t_room *new_room, t_room **rooms)
{
	t_room		*tmp;

	tmp = *rooms;
	if (!(*rooms))
		*rooms = new_room;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_room;
	}
}

void		parse_rooms(char *line, t_room **rooms, int *info_type)
{
	char		**input;
	t_room		*new_room;
	int 		start_end;

	start_end = 0;
	if (count_words(line, ' ', 0, 0) == 3 ||
		ft_strequ(line, "##start") || ft_strequ(line, "##end"))
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			new_room = start_end_room(line, rooms);
		else
		{
			input = ft_strsplit(line, ' ');
			check_name_exists(input[0], rooms);
			new_room = make_room(input[0], ft_atoi(input[1]),
				ft_atoi(input[2]), start_end);
			free_inputs(input, 1, 2);
		}
		add_room(new_room, rooms);
	}
	else if (count_char(line, '-') == 1)
		*info_type += 1;
	else
		throw_error(GENERAL);
}
