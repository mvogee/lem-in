/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	add_visited_room(t_visited **visited, t_room **room)
{
	t_visited	*tmp_visited;
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
