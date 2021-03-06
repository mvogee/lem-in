/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:09:46 by mvogee            #+#    #+#             */
/*   Updated: 2017/01/16 23:34:00 by mvogee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		pf_isalnum(int c)
{
	if (c && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')))
		return (1);
	return (0);
}
