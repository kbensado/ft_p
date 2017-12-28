/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:17:20 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/01 19:32:04 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/client/client.h"

bool			rec_msg(t_client *s, char *target)
{
	char		msg[4096];
	ssize_t		n;

	n = 0;
	while (1)
	{
		ft_bzero(msg, 4096);
		n = recv(s->master_sock, msg, 4096, 0);
		if (n > 0)
		{
			if (target != NULL)
			{
				if (match(msg, target) == 1)
					return (true);
				else
					return (false);
			}
			WS(msg);
			break ;
		}
	}
	return (true);
}

void			send_msg(t_client *s, void *msg, size_t len, char *error)
{
	if (send(s->master_sock, msg, len, 0) < 0)
	{
		perror(error);
		exit(-1);
	}
}

bool			rec_file(t_client *s, ssize_t len, int fd)
{
	char		msg[4096];
	ssize_t		n;

	n = 0;
	ft_bzero(msg, 4096);
	if (fd < 0 || len == 0)
		return (false);
	while (len > 0)
	{
		if ((n = recv(s->master_sock, msg, 4096, 0)) < 0)
		{
			perror("recv:file_rec :");
			exit(-1);
		}
		if (match(msg, "ERROR ") == 1)
			break ;
		len = len - n;
		write(fd, msg, n);
		ft_bzero(msg, 4096);
	}
	close(fd);
	return (true);
}

void			ft_error(char *error)
{
	perror(error);
	exit(-1);
}

void			set_login(char *str, t_client *s)
{
	t_char			log;

	ft_strsplit_char(str, ' ', &log, 0);
	s->login = ft_strdup(log.array[0]);
	ft_del_tab(log.array, log.size);
}
