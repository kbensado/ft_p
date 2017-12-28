/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 18:51:16 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/04 06:21:33 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define MAX_SOCK 42

# include "../../libft/inc/libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdio.h>

typedef struct protoent			t_proto;
typedef struct hostent			t_hostent;
typedef struct sockaddr_in		t_sockaddr;
typedef struct sockaddr_in6		t_sockaddrv6;

typedef struct					s_client
{
	int				cs;
	int				port;
	int				sock[MAX_SOCK];
	int				master_sock;
	int				sd;
	char			**cmd;
	t_arg			opt;
	t_proto			*proto;
	t_sockaddr		sockaddr;
	t_sockaddrv6	sockaddr6;
	t_sockaddr		csockaddr;
	size_t			clen;
	t_char			env;
	char			*addr;
	char			*login;
	char			**my_env;

}								t_client;

typedef void					(*t_cmd)(char *cmd, t_client *s);

/*
**			main.c
*/

int								main(int ac, char **av, char **env);

/*
**			serv.c
*/

bool							create_client(t_client *s);

/*
**			cmd.c
*/

void							get_cmd(t_client *s, int i, char *buff);

t_char							set_exec_lls(char **src, size_t count,
								t_client *s);

t_char							opt_ls(t_char cmd, bool opt, t_client *s,
								size_t i);

void							ls_client(char *cmd, t_client *s);
void							cd_client(char *cmd, t_client *s);
void							get_client(char *cmd, t_client *s);
void							put_client(char *cmd, t_client *s);
void							pwd_client(char *cmd, t_client *s);
void							quit_client(char *cmd, t_client *s);
void							lcd_client(char *cmd, t_client *s);
void							lpwd_client(char *cmd, t_client *s);
void							lls_client(char *cmd, t_client *s);

/*
**			macro.c
*/

void							set_login(char *str, t_client *s);
bool							rec_msg(t_client *s, char *target);
bool							rec_file(t_client *s, ssize_t len, int fd);
void							send_msg(t_client *s, void *msg,
								size_t len, char *error);
bool							send_zero(t_client *s);
void							client_get_norme(t_client *s, int fd,
								t_char *buff);
void							client_put_norme(t_client *s, t_file *file);

static const					t_cmd g_signed[] =
{
	[0] = ls_client,
	[1] = cd_client,
	[2] = get_client,
	[3] = put_client,
	[4] = pwd_client,
	[5] = quit_client,
	[6] = lcd_client,
	[7] = lpwd_client,
	[8] = lls_client,
};

#endif
