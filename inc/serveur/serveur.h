/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 18:11:42 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/02 18:07:44 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include "../../libft/inc/libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdio.h>

# define MAX_SOCK 42
# define USER_PWD s->sock.env[1]
# define S_MSG(x, y) (create_send_msg(x, s, y, 0))
# define ND "SUCCESS, new dir is : "
# define ER "Feed me with an arg pls or do not fucked up with the option pls !"

typedef struct protoent			t_proto;
typedef struct sockaddr_in		t_sockaddr;
typedef struct sockaddr_in6		t_sockaddrv6;

typedef void		(*t_func)(size_t key);

/*
**	env[0] = HOME env[1] = PWD
*/

typedef	struct		s_sock
{
	int				sock;
	char			*login;
	char			*passwd;
	char			**env;

}					t_sock;

typedef struct		s_serv
{
	int				cs;
	int				port;
	t_sock			sock;
	int				master_sock;
	int				sd;
	t_arg			opt;
	t_proto			*proto;
	t_sockaddr		sockaddr;
	t_sockaddrv6	sockaddr6;
	t_sockaddr		csockaddr;
	t_sockaddrv6	csockaddr6;
	size_t			clen;
	t_char			env;
	char			*pwd;
	char			*buff;
	char			**cmd;

}					t_serv;

typedef void		(*t_cmd)(t_serv *s, t_char *cmd);

static const char	*g_cmd[] =
{
	"ls",
	"cd",
	"get",
	"put",
	"pwd",
	"quit",
};

/*
**			main.c
*/

int					main(int ac, char **av, char **env);

/*
**			macro.c
*/

void				less_n(t_char *cmd);
void				send_msg(t_serv *s, void *msg, size_t len, char *error);
uint8_t				ip_vers(t_arg *s);
void				fork_it(t_serv *s);
t_char				opt_ls(t_char cmd, bool opt, t_serv *s,
					size_t i);
char				*add_home(char *src, t_serv *s);
void				set_log(char *log, char *pwd, char *path, t_serv *s);
bool				create_login(char *path, t_serv *s, t_char cmd);
bool				check_dir_serv(t_serv *s, t_char *tmp);
bool				read_pwd(char *pwd, char *path);
bool				rec_msg(t_serv *s, char *target);
void				put_norme(t_serv *s, int fd, t_char *cmd);

/*
**			serv.c
*/

bool				create_serv(t_serv *s);

/*
**			cmd.c
*/

void				check_cmd(t_serv *s, char *buff);

/*
**			send_get.c
*/

bool				send_file(char *file, t_serv *s);
bool				get_file_from_client(t_serv *s, int fd, size_t len);
void				set_new_sock(t_serv *s);
void				cd_no_right(t_serv *s);

void				create_send_msg(char *mgs, t_serv *s, bool file,
					size_t size);
char				*path_for_client(char *path, t_serv *serv);

void				ls_serv(t_serv *s, t_char *cmd);
void				cd_serv(t_serv *s, t_char *cmd);
void				get_serv(t_serv *s, t_char *cmd);
void				put_serv(t_serv *s, t_char *cmd);
void				pwd_serv(t_serv *s, t_char *cmd);
void				quit_serv(t_serv *s, t_char *cmd);

static const		t_cmd g_signed[] =
{
	[0] = ls_serv,
	[1] = cd_serv,
	[2] = get_serv,
	[3] = put_serv,
	[4] = pwd_serv,
	[5] = quit_serv,

};

#endif
