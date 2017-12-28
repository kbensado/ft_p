/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 13:59:55 by kbensado          #+#    #+#             */
/*   Updated: 2017/08/19 05:11:00 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char			*ft_strcat(char *s1, char *s2)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (s2 == NULL)
		return (s1);
	while (s1[i])
		i++;
	while (s2[k])
	{
		s1[i] = s2[k];
		i++;
		k++;
	}
	s1[i] = '\0';
	return (s1);
}

char			*ft_strultimatecat(size_t count, ...)
{
	int			i;
	size_t		len;
	va_list		ap;
	char		**tmp;
	char		*res;

	i = 0;
	res = NULL;
	len = 0;
	va_start(ap, count);
	tmp = ft_memalloc(sizeof(char *) * count);
	while (i < (int)count)
	{
		res = va_arg(ap, char *);
		tmp[i] = ft_strdup(res);
		len += ft_strlen(res);
		i++;
	}
	i = -1;
	res = ft_memalloc(len + 1);
	while (++i < (int)count)
		res = ft_strcat(res, tmp[i]);
	ft_del_tab(tmp, count);
	return (res);
}

char			*ft_strcatpath(char *s1, char *s2)
{
	size_t		i;
	size_t		k;
	char		*res;

	i = 0;
	k = 0;
	while (s1[i])
		i++;
	while (s2[k])
	{
		k++;
		i++;
	}
	res = ft_strnew(i + 1);
	res = ft_strcat(res, s1);
	res = ft_strcat(res, "/");
	res = ft_strcat(res, s2);
	return (res);
}

char			*ft_strcatdup(char *s1, char *s2)
{
	size_t		i;
	size_t		k;
	char		*res;

	i = 0;
	k = 0;
	res = NULL;
	while (s1[i])
		i++;
	while (s2[k])
	{
		k++;
		i++;
	}
	res = ft_strnew(i + 1);
	res = ft_strcat(res, s1);
	res = ft_strcat(res, s2);
	return (res);
}
