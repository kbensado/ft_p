/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 19:26:12 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/02 16:22:00 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/serveur/serveur.h"

void				set_new_sock(t_serv *s)
{
	char			message[37];
	char			msg[1024];
	ssize_t			n;

	n = 0;
	ft_bzero(message, 37);
	ft_strcpy(message, "Connected\n[Login] [Password] please\n");
	if (send(s->cs, message, ft_strlen(message), 0)
	!= (ssize_t)ft_strlen(message))
		WS("send connection permitted : error\n");
	while (1)
	{
		ft_bzero(msg, 1024);
		n = recv(s->cs, msg, 1024, 0);
		if (n > 0)
		{
			WS(msg);
			check_cmd(s, msg);
		}
	}
}

static void			read_sock(t_serv *s)
{
	int				r;
	char			buff[1024];
	int				ret;
	int				max;
	int				i;

	ret = 0;
	max = s->master_sock;
	i = -1;
	ft_bzero(&buff, 1024);
	r = 0;
	while (1)
	{
		s->cs = accept(s->master_sock,
		(struct sockaddr *)&s->csockaddr, (void *)&s->clen);
		if (s->cs != -1)
			fork_it(s);
	}
}

static void			create_ipv4(t_serv *s, size_t opt)
{
	s->master_sock = socket(AF_INET, SOCK_STREAM, s->proto->p_proto);
	s->sockaddr.sin_family = ip_vers(&s->opt);
	s->sockaddr.sin_port = htons(s->port);
	s->sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (setsockopt(s->master_sock, SOL_SOCKET, SO_REUSEADDR,
	(char *)&opt, sizeof(opt)) < 0)
	{
		perror("1 :");
		exit(-1);
	}
	if (bind(s->master_sock, (const struct sockaddr *)&s->sockaddr,
		sizeof(struct sockaddr_in)) == -1)
	{
		perror("2 :");
		exit(-1);
	}
	if (listen(s->master_sock, MAX_SOCK) < 0)
	{
		perror("3 :");
		exit(-1);
	}
	read_sock(s);
	close(s->cs);
	close(s->master_sock);
}

/*
**	address family problem
*/

static void			create_ipv6(t_serv *s)
{
	s->proto->p_proto = AF_INET6;
	s->master_sock = socket(PF_INET6, SOCK_STREAM, s->proto->p_proto);
	if (s->master_sock > 0)
	{
		s->sockaddr.sin_family = 30;
		s->sockaddr.sin_port = htonl(s->port);
		s->sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(s->master_sock, (const struct sockaddr *)&s->sockaddr6,
			sizeof(struct sockaddr_in6)) == -1)
		{
			perror("");
			exit(-1);
		}
		listen(s->master_sock, 42);
		s->cs = accept(s->master_sock, (struct sockaddr *)&s->csockaddr6,
		(void *)&s->clen);
		read_sock(s);
		close(s->cs);
		close(s->master_sock);
	}
}

bool				create_serv(t_serv *s)
{
	s->proto = getprotobyname("tcp");
	if (s->proto == 0)
		return (false);
	if (ip_vers(&s->opt) == 2)
		create_ipv4(s, 1);
	else
		create_ipv6(s);
	return (true);
}
