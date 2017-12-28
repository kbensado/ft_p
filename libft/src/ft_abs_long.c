/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_long.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 16:23:00 by kbensado          #+#    #+#             */
/*   Updated: 2016/03/04 16:23:09 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

long long		ft_abs_long(long long value)
{
	printf("entrer dans abslong avec %lld\n", value);
	if (value < -9223372036854775807)
		value = value + 1;
	if (value < 0)
		value = (value * -1);
	printf("sortie abslong avec %lld\n", value);
	return (value);
}
