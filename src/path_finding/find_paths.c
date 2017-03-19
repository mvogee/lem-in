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
