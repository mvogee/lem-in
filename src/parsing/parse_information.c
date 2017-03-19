/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_information.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 16:43:16 by mvogee            #+#    #+#             */
/*   Updated: 2017/03/09 16:43:16 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int				count_char(char *str, char c)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	else if (str[0] == '#')
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int		ft_isnum(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	count_words(char const *s, char c, int flag, int wrdstrt)
{
	int word_count;
	int index;

	word_count = 0;
	index = 0;
	if (!*s)
		return (0);
	if (s[0] != c)
	{
		word_count++;
		if (flag == 1 && wrdstrt == 1)
			return (index);
	}
	while (s[index])
	{
		if (s[index] == c && s[index + 1] != c && s[index + 1] != '\0')
			word_count++;
		index++;
		if (flag == 1 && word_count == wrdstrt)
			return (index);
	}
	return (word_count);
}

void		get_num_ants(char *line, int *num_ants, int *info_type)
{
	if (!ft_isnum(line))
		throw_error(NO_ANTS);
	*num_ants = ft_atoi(line);
	*info_type += 1;
}

t_room		*parse_information(int *num_ants)
{
	int		info_type;
	char	*line;
	t_room	*rooms;

	info_type = NUM_ANTS;
	line = NULL;
	rooms = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0 && line)
	{
		if ((line[0] == '#' && !ft_strequ(line, "##start")
			&& !ft_strequ(line, "##end")) || line[0] == '\0')
		{
			(line[0] == '\0' ? throw_error(GENERAL) : ft_printf("%s\n", line));
			continue ;
		}
		(line[0] == '#' ? ft_printf("%s\n", line) : 0);
		if (info_type == ROOMS)
			parse_rooms(line, &rooms, &info_type);
		if (info_type == CONNECTIONS)
			parse_connection(line, &rooms);
		if (info_type == NUM_ANTS)
			get_num_ants(line, num_ants, &info_type);
		free(line);
	}
	return (rooms);
}
