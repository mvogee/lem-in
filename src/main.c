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
		write(2 ,"ERROR\n", 7);
	else if (reason == NO_ANTS)
		write(2, "ERROR\nNO ANTS\n", 15);
	else if (reason == NO_END)
		write(2, "ERROR\nNO END ROOM FOUND\n", 25);
	else if (reason == NO_START)
		write(2, "ERROR\nNO START ROOM FOUND\n", 27);
	else if (reason == NO_ROOMS)
		write(2, "ERROR\nNO ROOMS\n", 16);
	else if (reason == NO_VALID_PATH)
		write(2, "ERROR\nNO PATH POSSIBLE\n", 24);
	else if (reason == DUPLICATE_NAME)
		write(2, "ERROR\nDUPLICATE NAME\n", 22);
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

int		main(void)
{
	t_all	*all;

	all = (t_all*)ft_memalloc(sizeof(t_all));
	all->rooms = parse_information(&all->num_ants); // done
	print_rooms(all->rooms);
	all->start = find_start(all->rooms); // make this
	ft_printf("start id: %s\n", all->start->id);
	all->end = find_end(all->rooms); // make this
	ft_printf("end id: %s\n", all->end->id);
	if (all->num_ants <= 0)
		throw_error(NO_ANTS);
	// all->start->num_ants = all->num_ants; // adds ants to start
	// check_reachable(all->start, all->end); // make this
	// find_paths(); // find paths to start and do algorithms stuff
}