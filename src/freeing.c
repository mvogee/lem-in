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

void		free_inputs(char **input, int start, int len)
{
	while (start <= len)
	{
		free(input[start]);
		start++;
	}
	free(input);
}

void	free_visited(t_visited **visited)
{
	t_visited		*tmp;
	t_visited		*next;

	tmp = *visited;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	free_connections(t_connection **connections)
{
	t_connection	*tmp;
	t_connection	*next;

	tmp = *connections;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	free_rooms(t_room **rooms)
{
	t_room			*tmp;
	t_room			*next;

	tmp = *rooms;
	while (tmp)
	{
		next = tmp->next;
		free_connections(&tmp->connections);
		free(tmp->id);
		free(tmp);
		tmp = next;
	}
}

void	free_all(t_all **all)
{
	free_rooms(&(*all)->rooms);
	free(*all);
}
