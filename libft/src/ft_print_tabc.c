/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tabc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 19:38:57 by kbensado          #+#    #+#             */
/*   Updated: 2017/01/24 00:10:06 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void		ft_print_tabc(char **str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		WS(str[i]);
		i++;
	}
}
