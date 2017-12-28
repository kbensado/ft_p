/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 06:19:49 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/04 06:21:55 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/client/client.h"

bool			send_zero(t_client *s)
{
	size_t		t;

	t = 0;
	if (send(s->master_sock, &t, sizeof(size_t), 0) < 0)
	{
		perror("");
		exit(-1);
	}
	return (false);
}

static void		client_norme(t_client *s, t_char *buff)
{
	size_t		len;
	char		*path;

	len = 0;
	path = CAT(3, s->my_env[1], "/",
	buff->array[1]);
	if (recv(s->master_sock, &len, sizeof(size_t), 0) < 0)
	{
		perror("recv()");
		exit(-1);
	}
	ft_printf("ERROR : %s doesnt exist\n", buff->array[1]);
	rm_file(path);
	if (recv(s->master_sock, &len, 1024, 0) < 0)
	{
		perror("recv()");
		exit(-1);
	}
	ft_memdel((void *)&path);
}

void			client_get_norme(t_client *s, int fd, t_char *buff)
{
	size_t		len;

	len = 0;
	if (recv(s->master_sock, &len, sizeof(size_t), 0) < 0)
	{
		perror("recv()");
		exit(-1);
	}
	if (len > 0)
	{
		if (rec_file(s, len, fd) == true)
		{
			send_msg(s, "good", 4, "LE GOOD");
			rec_msg(s, NULL);
		}
	}
	else
		client_norme(s, buff);
}

void			client_put_norme(t_client *s, t_file *file)
{
	if (send(s->master_sock, &file->file.st_size, sizeof(size_t), 0) < 0)
	{
		perror("send(put2)");
		exit(-1);
	}
	send_msg(s, file->ptr, file->file.st_size, "send(put3)");
	rec_msg(s, NULL);
	close(file->fd);
	munmap(file->ptr, file->file.st_size);
}
