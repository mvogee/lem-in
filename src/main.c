/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	throw_error(int reason)
{
	if (reason == GENERAL)
		write(2 ,"\e[31mERROR\n", 12);
	else if (reason == NO_ANTS)
		write(2, "\e[31mERROR\nNO ANTS\n", 20);
	else if (reason == NO_END)
		write(2, "\e[31mERROR\nNO END ROOM FOUND\n", 30);
	else if (reason == NO_START)
		write(2, "\e[31mERROR\nNO START ROOM FOUND\n", 32);
	else if (reason == NO_ROOMS)
		write(2, "\e[31mERROR\nNO ROOMS\n", 21);
	else if (reason == NO_VALID_PATH)
		write(2, "\e[31mERROR\nNO PATH POSSIBLE\n", 29);
	else if (reason == DUPLICATE_NAME)
		write(2, "\e[31mERROR\nDUPLICATE NAME\n", 27);
	exit(EXIT_FAILURE);
}

t_room	*find_start(t_room *rooms)
{
	t_room	*start;

	start = rooms;
	while (start)
	{
		if (start->is_start == 1)
			return (start);
		start = start->next;
	}
	throw_error(NO_START);
	return (NULL);
}

t_room	*find_end(t_room *rooms)
{
	t_room *end;

	end = rooms;
	while (end)
	{
		if (end->is_end == 1)
			return (end);
		end = end->next;
	}
	throw_error(NO_END);
	return (NULL);
}

int		check_reachable(t_room **start, char *end_id)
{
	t_room			*tmp;
	t_connection	*con;

	tmp = *start;
	con = (*start)->connections;
	if (ft_strequ(tmp->id, end_id))
		return (1);
	(*start)->visited = 1;
	while (tmp->visited && con)
	{
		tmp = con->room;
		con = con->next;
		if (tmp->visited == 0)
		{
			if (check_reachable(&tmp, end_id))
				return (1);
		}
	}
	return (0);
}	

void	reset_visited(t_room **rooms)
{
	t_room *tmp;

	tmp = *rooms;
	while (tmp)
	{
		if (tmp->visited == 1)
			tmp->visited = 0;
		tmp = tmp->next;
	}
}

int		main(void)
{
	t_all	*all;

	all = (t_all*)ft_memalloc(sizeof(t_all));
	all->rooms = parse_information(&all->num_ants);
	print_rooms(all->rooms); // remove this.
	all->start = find_start(all->rooms);
	//ft_printf("start id: %s\n", all->start->id);
	all->end = find_end(all->rooms);
	//ft_printf("end id: %s\n", all->end->id); // remove this
	if (all->num_ants <= 0)
		throw_error(NO_ANTS);
	all->start->num_ants = all->num_ants;
	ft_printf("number of ants: \e[31m%d\n\n\e[00m", all->start->num_ants);
	if (!(check_reachable(&all->start, all->end->id)))
		throw_error(NO_VALID_PATH);
	reset_visited(&all->rooms);
	find_paths(&all);
	free_all(&all);
}
