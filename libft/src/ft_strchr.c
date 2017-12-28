/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/23 15:02:57 by kbensado          #+#    #+#             */
/*   Updated: 2017/03/23 13:57:54 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char			*ft_replace_nonprint(char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 1 && s[i] <= 31)
			s[i] = 0;
		i++;
	}
	return (s);
}

char			*ft_str_replace(char *s, char c, char t)
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			s[i] = t;
		i++;
	}
	return (s);
}

char			*ft_strchr(char *s, int c)
{
	while (*s != (char)c && *s != '\0')
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
