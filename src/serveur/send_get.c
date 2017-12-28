/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 16:48:15 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/02 16:46:17 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/serveur/serveur.h"

static bool		send_zero(t_serv *s)
{
	size_t		t;

	t = 0;
	if (send(s->cs, &t, sizeof(size_t), 0) < 0)
	{
		perror("");
		exit(-1);
	}
	return (false);
}

void			close_file(t_serv *s, t_file *buff)
{
	rec_msg(s, NULL);
	send(s->cs, "SUCCESS get", 11, 0);
	munmap(buff->ptr, buff->file.st_size);
	close(buff->fd);
}

bool			send_file(char *file, t_serv *s)
{
	char	*tmp;
	t_file	buff;

	tmp = CAT(3, USER_PWD, "/", file);
	buff = get_file(tmp, 0);
	if (buff.ptr != NULL && buff.fd != -1)
	{
		if (send(s->cs, &buff.file.st_size, sizeof(size_t), 0) < 0)
		{
			perror("send():file_len :");
			exit(-1);
		}
		if (send(s->cs, buff.ptr, buff.file.st_size, 0) < 0)
		{
			perror("");
			exit(-1);
		}
	}
	else
		return (send_zero(s));
	close_file(s, &buff);
	return (true);
}

bool			get_file_from_client(t_serv *s, int fd, size_t len)
{
	int		n;
	char	msg[4096];

	n = 0;
	ft_bzero(msg, 4096);
	if (fd < 0)
		return (false);
	while (len > 0)
	{
		n = recv(s->cs, msg, 4096, 0);
		len -= n;
		write(fd, msg, n);
		ft_bzero(msg, 4096);
	}
	close(fd);
	return (true);
}
