/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		get_potential_paths(t_all **all, char *end_id) // max paths is number of start children nodes
{
	t_connection	*tmp_con;
	t_room			*tmp_room;
	int				total_paths;

	total_paths = 0;
	tmp_con = (*all)->start->connections;
	while (tmp_con)
	{
		(*all)->start->visited = 1;
		tmp_room = tmp_con->room;
//		ft_printf("looking down room %s\n", tmp_room->id);
		if (tmp_room->path_checked == 1)
		{
			tmp_con = tmp_con->next;
			continue ;
		}
		if (check_reachable(&tmp_room, end_id))
		{
			reset_visited(&(*all)->rooms);
			tmp_room->pathable = 1;
//			ft_printf("path found for %s\n", tmp_room->id);
			total_paths++;
		}
//		ft_printf("%s pathable?: %d\n",tmp_room->id, tmp_room->pathable);
		tmp_con = tmp_con->next;
		tmp_room->path_checked = 1;
	}
	return (total_paths);
}

void	reset_path_checked(t_room **start)
{
	t_connection	*tmp_con;
	t_room			*tmp_room;

	tmp_con = (*start)->connections;
	while (tmp_con)
	{
		tmp_room = tmp_con->room;
		tmp_room->path_checked = 0;
		tmp_con = tmp_con->next;
	}
}

void	find_paths(t_all **all)
{
	//how ever many connections come out of start and connect to end is how many paths we can have
	// in order for a path to be valid it needs to at the point of end or joining a main path have less moves to end than it did at start;
	// first find how many of the start children can reach end;
	// get the best path.
	// rate paths. only save a path if by the time it joins best path it is shorter distance to end than start

	(*all)->num_paths = get_potential_paths(all, (*all)->end->id); // make this funtion
	reset_visited(&(*all)->rooms);
	reset_path_checked(&(*all)->start);
	ft_printf("num paths: %d\n", (*all)->num_paths);
//	(*all)->all_paths = get_unique_paths(all); // make this. finds all unique paths
}
