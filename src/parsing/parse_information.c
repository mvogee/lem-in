/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_information.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int				count_char(char *str, char c) // this can go in extras
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	else if (str[0] == '#')
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int		ft_isnum(char *str) // extras
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void		get_num_ants(char *line, int *num_ants, int *info_type)
{
	if (!ft_isnum(line))
		throw_error(NO_ANTS);
	*num_ants = ft_atoi(line);
	*info_type += 1;
}



//_______________ parse_rooms _________________ vv
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
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			throw_error(GENERAL);
		else if (line[0] == '#')
		{
			free(line);
			continue ;
		}
		else if (count_char(line, ' ') == 2)
			break ;
		else if (count_char(line, '-'))
			throw_error(GENERAL);
	}
	input = ft_strsplit(line, ' ');
	check_name_exists(input[0], rooms);
	new_room = make_room(input[0], ft_atoi(input[1]), ft_atoi(input[2]), start_end);
	return (new_room);
}

void		add_room(t_room *new_room, t_room **rooms)
{
	t_room	*tmp;

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
	if (count_char(line, ' ') == 2 || ft_strequ(line, "##start") || ft_strequ(line, "##end"))
	{
		if (ft_strequ(line, "##start") || ft_strequ(line, "##end"))
			new_room = start_end_room(line, rooms);
		else
		{
			input = ft_strsplit(line, ' ');
			check_name_exists(input[0], rooms);
			new_room = make_room(input[0], ft_atoi(input[1]), ft_atoi(input[2]), start_end);
		}
			add_room(new_room, rooms);
	}
	else if (count_char(line, '-') == 1)
		*info_type += 1;
	else
		throw_error(GENERAL);
}
//_____________________ parse_rooms _________________ ^^

void		check_valid_name(t_room **rooms, char *id)
{
	t_room		*tmp;

	tmp = *rooms;
	while (tmp)
	{
		if (ft_strequ(tmp->id, id))
			return ;
		tmp = tmp->next;
	}
	throw_error(GENERAL);
}

t_connection	*make_connection(t_room *room)
{
	t_connection *new_connection;

	new_connection = (t_connection*)ft_memalloc(sizeof(t_connection));
	new_connection->room = room;
	new_connection->next = NULL;
	return (new_connection);
}

void		add_connection(t_room **rooms, char *home, char *room2)
{
	t_room	*tmp_home;
	t_room	*tmp2;
	t_connection	*new_connection;
	t_connection	**connections;
	t_connection	*tmp_con;

	tmp_home = *rooms;
	tmp2 = *rooms;
	while (!ft_strequ(tmp_home->id, home))
		tmp_home = tmp_home->next;
	while (!ft_strequ(tmp2->id, room2))
		tmp2 = tmp2->next;
	connections = &tmp_home->connections;
	tmp_con = *connections;
	new_connection = make_connection(tmp2);
	if (!(*connections))
		*connections = new_connection;
	else
	{
		while (tmp_con->next)
			tmp_con = tmp_con->next;
		tmp_con->next = new_connection;
	}
}

void		parse_connection(char *line, t_room **rooms)
{
	char	**ids;

	if (count_char(line, '-') != 1)
		throw_error(GENERAL);
	ids = ft_strsplit(line, '-');
	check_valid_name(rooms ,ids[0]);
	check_valid_name(rooms ,ids[1]);
	add_connection(rooms, ids[0], ids[1]);
	add_connection(rooms, ids[1], ids[0]);
}

//___________________parse_connection________________ ^^

t_room		*parse_information(int *num_ants)
{
	int		info_type;
	char	*line;
	t_room	*rooms; // this is linked list of all rooms

	info_type = NUM_ANTS;
	line = NULL;
	rooms = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0 && line)
	{
		if ((line[0] == '#' && !ft_strequ(line, "##start") && !ft_strequ(line, "##end")) || line[0] == '\0')
		{
			(line[0] == '\0' ? throw_error(GENERAL) : ft_printf("%s\n", line)); // nessesary?
			continue ;
		}
		if (info_type == ROOMS)
			parse_rooms(line, &rooms, &info_type);
		if (info_type == CONNECTIONS)
			parse_connection(line, &rooms);
		if (info_type == NUM_ANTS)
			get_num_ants(line, num_ants, &info_type);
		free(line);
	}
	if (!rooms)
		throw_error(NO_ROOMS);
	return (rooms);
}
