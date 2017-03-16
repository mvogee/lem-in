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

void	print_connections(t_connections *connections)
{
	t_connections *tmp;

	tmp = connections;
	ft_printf("connections: ")
	while (tmp)
	{
		ft_printf("%s, ", tmp->room->id);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	print_rooms(t_room	*start)
{
	t_room		*tmp

	tmp = start;
	while (tmp)
	{
		ft_printf("id: %s\n", tmp->id);
		ft_printf("is_start: %d\nis_end: %d\n", tmp->is_start, tmp->is_end);
		print_connections(tmp->connections);
		ft_printf("\n\n");
		tmp = tmp->next;
	}
}