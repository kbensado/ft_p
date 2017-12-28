/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 19:45:16 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/02 16:48:39 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/serveur/serveur.h"

#include <stdio.h>

void			less_n(t_char *cmd)
{
	if (cmd->array[cmd->size - 1][ft_strlen(cmd->array[cmd->size - 1]) - 1]
		== '\n')
	{
		cmd->array[cmd->size - 1][ft_strlen(cmd->array[cmd->size - 1]) - 1] = 0;
	}
}

char			*path_for_client(char *path, t_serv *s)
{
	size_t			i;
	size_t			j;
	size_t			len;
	char			*res;

	i = 0;
	j = 0;
	len = 0;
	res = NULL;
	while (s->sock.env[1][i] && path[i] == s->sock.env[1][i])
		i++;
	ft_printf("%d | %d\n", i, ft_strlen(path));
	ft_printf("%s | %s\n", s->sock.env[1][i], path);
	if (i == ft_strlen(path))
	{
		res = ft_strdup("/");
		return (res);
	}
	res = ft_strsub(path, i, ft_strlen(path) - 1);
	return (res);
}

void			create_send_msg(char *mgs, t_serv *s, bool file, size_t size)
{
	size_t		n;

	n = 0;
	if (file == true)
	{
		while (n < size)
			n += send(s->cs, mgs, 4096, 0);
		ft_memdel((void *)&mgs);
		return ;
	}
	send(s->cs, mgs, ft_strlen(mgs), 0);
}

void			send_msg(t_serv *s, void *msg, size_t len, char *error)
{
	if (send(s->cs, msg, len, 0) < 0)
	{
		perror(error);
		exit(-1);
	}
}

void			cd_no_right(t_serv *s)
{
	char		*buff;

	buff = CAT(2, s->sock.env[0], "*");
	ft_printf("mn env = %s |||| buff = %s\n", s->sock.env[1], buff);
	if (match(s->sock.env[1], buff) == 0)
	{
		WS("ALLO");
		s->sock.env[1] = s->sock.env[0];
	}
}
