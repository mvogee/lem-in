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

int		main(void)
{
	t_all	*all;

	all = (t_all*)ft_memalloc(sizeof(t_all));
	all->rooms = parse_information(&all->num_ants); // done
	print_rooms(all->rooms);
	// all->start = find_start(all->rooms); // make this
	// all->end = find_end(all->rooms); // make this
	if (all->num_ants <= 0)
		throw_error(NO_ANTS);
	// all->start->num_ants = all->num_ants; // adds ants to start
	// check_reachable(all->start, all->end); // make this
	// find_paths(); // find paths to start and do algorithms stuff
}