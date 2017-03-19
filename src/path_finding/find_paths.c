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
