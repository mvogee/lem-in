/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_ants(t_ants *ants)
{
	t_ants	*tmp;

	tmp = ants;
	while (tmp)
	{
		ft_printf("ant id: %d in room: %s\n", tmp->id, tmp->room->id);
		tmp = tmp->next;
	}
}

void	print_distances(t_all **all)
{
	t_room		*tmp;

	tmp = (*all)->rooms;
	while (tmp)
	{
		ft_printf("score room %s: %d\n", tmp->id, tmp->to_end);
		tmp = tmp->next;
	}
}

void	print_connections(t_connection *connections)
{
	t_connection *tmp;

	tmp = connections;
	ft_printf("connections: ");
	while (tmp)
	{
		ft_printf("%s, ", tmp->room->id);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	print_rooms(t_room	*rooms)
{
	t_room		*tmp;

	tmp = rooms;
	if (!rooms)
		return ;
	while (tmp)
	{
		ft_printf("id: %s\n", tmp->id);
		ft_printf("is_start: %d\nis_end: %d\n", tmp->is_start, tmp->is_end);
		print_connections(tmp->connections);
		ft_printf("visited: %d\n", tmp->visited);
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("\n\n");
}