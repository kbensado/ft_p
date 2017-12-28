/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 18:50:24 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/01 23:11:17 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/client/client.h"

static uint8_t		ip_vers(t_arg *s)
{
	size_t			i;

	i = 0;
	while (i < s->nb_opt)
	{
		if (ft_strequ(s->opt.array[i], "ipv6") == 1)
			return (AF_INET6);
		i++;
	}
	return (AF_INET);
}

static void			treat_data(t_client *s, char *buff, int n)
{
	char			msg[1024];

	ft_bzero(msg, 1024);
	rec_msg(s, NULL);
	ft_memdel((void *)&buff);
	while (get_next_line(0, &buff) > 0)
	{
		send_msg(s, buff, ft_strlen(buff), "send()");
		if ((n = recv(s->master_sock, msg, 1024, 0)) < 0)
		{
			perror("recv()");
			exit(-1);
		}
		if (match(msg, "Login Su*") == 1)
		{
			WS("Login Success");
			break ;
		}
		else
			WS(msg);
	}
	ft_bzero(msg, 1024);
	set_login(buff, s);
	ft_memdel((void *)&buff);
	get_cmd(s, 0, NULL);
}

static void			create_ipv4(t_client *s)
{
	t_hostent		*hostinfo;
	t_sockaddr		sin;
	const char		*hostname;

	hostinfo = NULL;
	s->master_sock = socket(AF_INET, SOCK_STREAM, 0);
	hostname = ft_strdup(s->addr);
	hostinfo = gethostbyname(hostname);
	if (hostinfo == NULL)
	{
		ft_printf("Unknown host %s.\n", hostname);
		exit(-1);
	}
	sin.sin_addr = *(struct in_addr *)hostinfo->h_addr;
	sin.sin_port = htons(s->port);
	sin.sin_family = AF_INET;
	s->sockaddr.sin_addr.s_addr = inet_addr(s->addr);
	if (connect(s->master_sock, (const struct sockaddr *)&sin,
	sizeof(t_sockaddr)) == -1)
	{
		perror("");
		exit(-1);
	}
	treat_data(s, NULL, 0);
}

/*
**	address family problem
*/

static void			create_ipv6(t_client *s)
{
	t_sockaddrv6		sin;

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
		if (connect(s->master_sock, (const struct sockaddr *)&sin,
		sizeof(t_sockaddrv6)) == -1)
			exit(-1);
		treat_data(s, NULL, 0);
		close(s->cs);
		close(s->master_sock);
	}
}

bool				create_client(t_client *s)
{
	s->proto = getprotobyname("tcp");
	if (s->proto == 0)
		return (false);
	if (ip_vers(&s->opt) == 2)
		create_ipv4(s);
	else
		create_ipv6(s);
	return (true);
}
