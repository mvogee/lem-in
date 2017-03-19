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
		if (tmp_room->path_checked == 1)
		{
			tmp_con = tmp_con->next;
			continue ;
		}
		if (check_reachable(&tmp_room, end_id))
		{
			reset_visited(&(*all)->rooms);
			tmp_room->pathable = 1;
			total_paths++;
		}
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
		if (tmp_room->to_end > largest && tmp_room->pathable)
			largest = tmp_room->to_end;
		tmp_con = tmp_con->next;
	}
	return (largest);
}


//_________________ants vv __________________
void	reset_moved(t_ants **ants)
{
	t_ants	*tmp;

	tmp = *ants;
	while (tmp)
	{
		tmp->moved = 0;
		tmp = tmp->next;
	}
}

void	add_visited_room(t_visited **visited, t_room **room)
{
	t_visited 	*tmp_visited;
	t_visited	*new_visited;

	new_visited = (t_visited*)ft_memalloc(sizeof(t_visited));
	new_visited->next = NULL;
	new_visited->room = *room;
	if (!(*visited))
		*visited = new_visited;
	else
	{
		tmp_visited = *visited;
		while (tmp_visited->next)
			tmp_visited = tmp_visited->next;
		tmp_visited->next = new_visited;
	}
}

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
	add_visited_room(&new_ant->visited, start);
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

//__________movement vv________________

int		not_visited(t_visited *visited_rooms, t_room *room_to_check)
{
	t_visited	*tmp_visited;

	tmp_visited = visited_rooms;
	while (tmp_visited)
	{
		if (ft_strequ(tmp_visited->room->id, room_to_check->id))
			return (0);
		tmp_visited = tmp_visited->next;
	}
	return (1);
}

void	move_ant(t_ants **ant, t_room **moveto)
{
	(*ant)->room->num_ants -= 1;
	(*moveto)->num_ants += 1;
	ft_printf("L%d-%s ", (*ant)->id, (*moveto)->id);
	(*ant)->room = *moveto;
}

void	find_move(t_ants **ant)
{
	t_room	*cur_room; // the room the ant is currently in
	t_room	*best; // current best room to move to
	t_room	*check; // the room the ant might move to
	t_connection *tmp_con; // the connections to the room the ant is in

	cur_room = (*ant)->room;
	best = cur_room;
	tmp_con = cur_room->connections;
	while (tmp_con) // look for the best unocupied room
	{
		check = tmp_con->room;
		if (check->num_ants == 0 && check->to_end <= best->to_end && not_visited((*ant)->visited, check))
		{
			if ((cur_room->is_start && check->pathable) || !cur_room->is_start)
				best = check;
		}
		if (check->is_end)
		{
			best = check;
			break ;
		}
		tmp_con = tmp_con->next;
	}
	if (!ft_strequ(best->id, cur_room->id))
	{
		add_visited_room(&(*ant)->visited, &cur_room);
		move_ant(ant, &best);
	}
}

t_ants	*get_closest_ant(t_ants **ants)
{
	t_ants		*closest;
	t_ants		*tmp_ants;

	tmp_ants = *ants;
	closest = NULL;
	while (tmp_ants)
	{
		if (!tmp_ants->moved)
		{
			if (closest == NULL)
				closest = tmp_ants;
			else if(tmp_ants->room->to_end < closest->room->to_end)
				closest = tmp_ants;
		}
		tmp_ants = tmp_ants->next;
	}
	return (closest);
}

t_ants	*remove_ant(t_ants **ants, t_ants *done_ant)
{
	t_ants	*head;
	t_ants	*tmp_ants;
	t_ants	*prev;

	head = *ants;
	if (head->id == done_ant->id)
	{
		head = head->next;
		free(done_ant);
		return (head);
	}
	tmp_ants = head->next;
	prev = head;
	while (tmp_ants)
	{
		if (tmp_ants->id == done_ant->id)
		{
			prev->next = done_ant->next;
			free(done_ant);
			return (head);
		}
		prev = tmp_ants;
		tmp_ants = tmp_ants->next;
	}
	return (head);
}

void	start_movement(t_all **all)
{
	t_ants	*tmp_ants;

	while ((*all)->end->num_ants < (*all)->num_ants && (*all)->ants)
	{
		tmp_ants = (*all)->ants; // sets ants back to the head ant node
		while (tmp_ants)
		{
			tmp_ants = get_closest_ant(&(*all)->ants); //returns null if all have been moved
			if (!tmp_ants)
				break ;
			find_move(&tmp_ants); // make this
			if (tmp_ants->room->is_end)
			{
				free_visited(&tmp_ants->visited);
				(*all)->ants = remove_ant(&(*all)->ants, tmp_ants);
			}
			else
				tmp_ants->moved = 1;
		}
		reset_moved(&(*all)->ants);
		ft_printf("%d\n", (*all)->end->num_ants);
	}
}

// __________movement ^^ _______________

void	find_paths(t_all **all)
{
	(*all)->num_paths = get_potential_paths(all, (*all)->end->id); // make this funtion
	reset_visited(&(*all)->rooms);
	reset_path_checked(&(*all)->start);
	ft_printf("num paths: %d\n", (*all)->num_paths);
	set_node_distance(&(*all)->end, 0); //from end assing each node a distance
	(*all)->start->to_end += (*all)->num_ants;
	print_distances(all);
	create_ants(all);
	print_ants((*all)->ants);
	start_movement(all); // make this. moves ants
}
