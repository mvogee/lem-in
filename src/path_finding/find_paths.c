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


void	set_node_distance(t_room **room, int distance)
{
	t_connection	*tmp_con;
	t_room			*tmp_room;

	tmp_con = (*room)->connections;
	if (distance < (*room)->to_end)
		(*room)->to_end = distance;
	while (tmp_con)
	{
		tmp_room = tmp_con->room;
		if (tmp_room->to_end > distance + 1)
			set_node_distance(&tmp_room, distance + 1);
		tmp_con = tmp_con->next;
	}
	return ;
}

// void	get_paths(t_all **all, int longest_dist, int shortest_dist)
// {
// 	t_room			*tmp_room;
// 	t_connection	*tmp_con;
// 	t_path			*new_path;

// 	tmp_con = (*all)->start->connections;
// 	while (tmp_con)
// 	{
// 		tmp_room = tmp_con->room;
// 		if (!tmp_room->pathable || tmp_room->to_end > shortest_dist)
// 		{
// 			tmp_con = tmp_con->next;
// 			continue ;
// 		}
// 	}
// }

int		get_max_start_dist(t_room *start)
{
	t_connection	*tmp_con;
	t_room			*tmp_room;
	int				largest;

	largest = 0;
	tmp_con = start->connections;
	while (tmp_con)
	{
		tmp_room = tmp_con->room;
		if (tmp_room->to_end > largest)
			largest = tmp_room->to_end;
		tmp_con = tmp_con->next;
	}
	return (largest);
}


//_________________ants vv __________________

t_ants	*create_new_ant(int id, t_room **start)
{
	t_ants	*new_ant;

	new_ant = (t_ants*)ft_memalloc(sizeof(t_ants));
	if (!new_ant)
		throw_error(GENERAL);
	new_ant->id = id;
	new_ant->next = NULL;
	new_ant->room = *start;
	new_ant->moved = 0;
	return (new_ant);
}

void	add_new_ant(t_ants **ants, t_ants *new_ant)
{
	t_ants	*tmp;

	tmp = *ants;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_ant;
}

void	create_ants(t_all **all)
{
	int		count;
	t_ants	*new_ant;

	count = 1;
	while (count <= (*all)->num_ants)
	{
		new_ant = create_new_ant(count, &(*all)->start);
		if (!((*all)->ants))
			(*all)->ants = new_ant;
		else
			add_new_ant(&(*all)->ants, new_ant);
		count++;
	}
}

//____________ants ^^___________________

void	find_paths(t_all **all)
{
	//how ever many connections come out of start and connect to end is how many paths we can have
	// in order for a path to be valid it needs to at the point of end or joining a main path have less moves to end than it did at start;
	// first find how many of the start children can reach end;
	// get the best path.
	// rate paths. only save a path if by the time it joins best path it is shorter distance to end than start

	// instead of predefining paths we have distances. alwasy every turn move ants close to the end
	// start from the end. move though nodes looking for occupied node keeping track of the previous node for printing
	// once an ant is found check if it can move forward
	(*all)->num_paths = get_potential_paths(all, (*all)->end->id); // make this funtion
	reset_visited(&(*all)->rooms);
	reset_path_checked(&(*all)->start);
	ft_printf("num paths: %d\n", (*all)->num_paths);
	set_node_distance(&(*all)->end, 0); //from end assing each node a distance
	print_distances(all);
	create_ants(all);
	print_ants((*all)->ants);
//	get_paths(all);// make this. finds paths to use.
//	move_ants(all,  get_max_start_dist((*all)->start), (*all)->start->to_end - 1); // make this. moves ants
}

// t_all_paths		*find_all_paths(t_all **all)
// {
// 	t_connection	*tmp_con;
// 	t_room			*tmp_room;
// 	t_all_paths		*all_paths;
// 	t_path			*new_path;

// 	paths = (t_all_paths*)ft_memalloc(sizeof(t_all_paths));
// 	tmp_con = (*all)->start->connections;
// 	new_path = find_best_path(all); // make this. needs to check every possible path and pick the best one

// 	while (tmp_con)
// 	{
// 		tmp_room = tmp_con->room;
// 		if (tmp_room->pathable == 1)
// 		{
// 			new_path = create_new_path(paths, tmp_room); // make this. will recursively build 
// 			mark_path(new_path); // mark the path nodes as visited and assign to_end value based on total_len - count
// 		// depth search every single path possible from tmp_room and only keep the shortest path.
// 		// do depth search for each child of start
// 		// take the best shortest path and mark the nodes perma visited as well as distance to end
// 			add_to_all_paths(&all_paths, &new_path);
// 			// add the new path to the 
// 		}
// 		tmp_con = tmp_con->next;
// 	}
// }
