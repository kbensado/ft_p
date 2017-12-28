/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:17:56 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/02 18:00:39 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/serveur/serveur.h"

uint8_t				ip_vers(t_arg *s)
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

void				fork_it(t_serv *s)
{
	pid_t	daddy;

	daddy = fork();
	if (daddy > 0)
		set_new_sock(s);
	else
		wait(&daddy);
}

bool				check_dir_serv(t_serv *s, t_char *tmp)
{
	s->buff = ft_strultimatecat(3, s->pwd, "/user/", tmp->array[0]);
	if ((dir_exist(s->buff, NULL) == true) &&
	(read_pwd(tmp->array[1], s->buff) == false))
	{
		send(s->cs, "Login already exist/Wrong Password\n", 35, 0);
		return (false);
	}
	else if (dir_exist(s->buff, NULL) == false)
	{
		if (create_login(s->buff, s, *tmp) == false)
		{
			send(s->cs, "Problem to create user_env\n", 27, 0);
			return (false);
		}
	}
	set_log(ft_strdup(tmp->array[0]), ft_strdup(tmp->array[1]), s->buff, s);
	ft_memdel((void *)&s->buff);
	ft_del_tab(tmp->array, tmp->size);
	return (true);
}

bool				rec_msg(t_serv *s, char *target)
{
	char			msg[4096];
	ssize_t			n;

	n = 0;
	while (1)
	{
		ft_bzero(msg, 4096);
		n = recv(s->cs, msg, 4096, 0);
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

void				put_norme(t_serv *s, int fd, t_char *cmd)
{
	size_t			len;
	int				n;

	len = 0;
	n = 0;
	S_MSG("envoie le", false);
	if ((n = recv(s->cs, &len, sizeof(size_t), 0)) < 0)
	{
		perror("recv(len)");
		exit(-1);
	}
	get_file_from_client(s, fd, len);
	S_MSG(CAT(3, "SUCCESS ", cmd->array[1], " transfered\n"), false);
}
