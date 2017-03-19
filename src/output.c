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
	t_ants			*tmp;

	tmp = ants;
	ft_printf("_______ants_______\n");
	while (tmp)
	{
		ft_printf("ant id: %d in room: %s\n", tmp->id, tmp->room->id);
		tmp = tmp->next;
	}
	ft_printf("__________________\n");
}

void	print_distances(t_all **all)
{
	t_room			*tmp;

	tmp = (*all)->rooms;
	while (tmp)
	{
		ft_printf("score room %s: %d\n", tmp->id, tmp->to_end);
		tmp = tmp->next;
	}
}

void	print_connections(t_connection *connections)
{
	t_connection	*tmp;

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
	t_room			*tmp;

	tmp = rooms;
	if (!rooms)
		return ;
	ft_printf("\e[32m_______rooms_______\n\e[00m");
	while (tmp)
	{
		if (tmp->is_start)
			ft_printf("\e[32mv start node v\n\e[00m");
		else if (tmp->is_end)
			ft_printf("\e[32mv end node v\n\e[00m");
		ft_printf("id: %s\n", tmp->id);
		print_connections(tmp->connections);
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("\e[32m___________________\e[00m\n\n");
}
