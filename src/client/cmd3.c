/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:06:50 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/01 19:51:49 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/client/client.h"

void			ls_client(char *cmd, t_client *s)
{
	char		mgs[4096];
	int			n;

	ft_bzero(&mgs, 4096);
	if (send(s->master_sock, cmd, ft_strlen(cmd), 0) < 0)
	{
		perror("send()");
		exit(-1);
	}
	ft_memdel((void *)&cmd);
	while (1)
	{
		ft_bzero(&mgs, 4096);
		n = recv(s->master_sock, mgs, 4096, 0);
		if (n > 0)
		{
			WS(mgs);
			if (match(mgs, "*SUCCESS*") == 1)
				break ;
		}
	}
}

void			get_cmd(t_client *s, int i, char *buff)
{
	char		mgs[4096];
	t_char		tmp;

	ft_bzero(&tmp, sizeof(t_char));
	ft_bzero(&mgs, 4096);
	while (1)
	{
		write(1, ":> ", 3);
		get_next_line(0, &buff);
		ft_strsplit_char(buff, ' ', &tmp, 0);
		if (tmp.size > 0)
		{
			i = ft_contains_str_at(s->cmd, tmp.array[0], 9);
			if (i > -1)
				g_signed[i](buff, s);
			if (ft_strequ(tmp.array[0], "quit") == 1)
			{
				ft_del_tab(tmp.array, tmp.size);
				break ;
			}
			ft_del_tab(tmp.array, tmp.size);
		}
		buff = NULL;
	}
}
