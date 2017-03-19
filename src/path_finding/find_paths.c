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

int		get_potential_paths(t_all **all, char *end_id)
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
	t_room	*cur_room;
	t_room	*best;
	t_room	*check;
	t_connection *tmp_con;

	cur_room = (*ant)->room;
	best = cur_room;
	tmp_con = cur_room->connections;
	while (tmp_con)
	{
		check = tmp_con->room;
		if ((check->num_ants == 0 && check->to_end <= best->to_end &&
			not_visited((*ant)->visited, check)) || check->is_end)
		{
			if ((cur_room->is_start && check->pathable) ||
				!cur_room->is_start || check->is_end)
				best = check;
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

void	start_movement(t_all **all)
{
	t_ants	*tmp_ants;
	ft_printf("\e[32m________Ant Moves__________\n\e[00m");
	while ((*all)->end->num_ants < (*all)->num_ants && (*all)->ants)
	{
		tmp_ants = (*all)->ants;
		while (tmp_ants)
		{
			tmp_ants = get_closest_ant(&(*all)->ants);
			if (!tmp_ants)
				break ;
			find_move(&tmp_ants);
			if (tmp_ants->room->is_end)
			{
				free_visited(&tmp_ants->visited);
				(*all)->ants = remove_ant(&(*all)->ants, tmp_ants);
			}
			else
				tmp_ants->moved = 1;
		}
		reset_moved(&(*all)->ants);
		ft_printf("\n");
	}
	ft_printf("\e[32m___________________________\n");
}

// __________movement ^^ _______________

void	find_paths(t_all **all)
{
	(*all)->num_paths = get_potential_paths(all, (*all)->end->id);
	reset_visited(&(*all)->rooms);
	reset_path_checked(&(*all)->start);
	set_node_distance(&(*all)->end, 0);
	(*all)->start->to_end += (*all)->num_ants;
	create_ants(all);
	start_movement(all);
}
