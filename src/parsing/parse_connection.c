/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_connection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void			check_valid_name(t_room **rooms, char *id)
{
	t_room			*tmp;

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
	t_connection	*new_connection;

	new_connection = (t_connection*)ft_memalloc(sizeof(t_connection));
	new_connection->room = room;
	new_connection->next = NULL;
	return (new_connection);
}

void			add_connection(t_room **rooms, char *home, char *room2)
{
	t_room			*tmp_home;
	t_room			*tmp2;
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

void			parse_connection(char *line, t_room **rooms)
{
	char			**ids;

	if (!(*rooms))
		throw_error(NO_ROOMS);
	 if (count_char(line, '-') != 1 || count_words(line, '-', 0, 0) != 2)
	 	throw_error(GENERAL);
	ids = ft_strsplit(line, '-');
	check_valid_name(rooms ,ids[0]);
	check_valid_name(rooms ,ids[1]);
	add_connection(rooms, ids[0], ids[1]);
	add_connection(rooms, ids[1], ids[0]);
	free(ids[0]);
	free(ids[1]);
}
