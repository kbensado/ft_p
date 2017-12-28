/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:04:07 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/01 19:26:15 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/client/client.h"

void		pwd_client(char *cmd, t_client *s)
{
	char	msg[4096];
	int		n;

	ft_bzero(&msg, 4096);
	if (send(s->master_sock, cmd, ft_strlen(cmd), 0) < 0)
	{
		perror("send()");
		exit(-1);
	}
	ft_memdel((void *)&cmd);
	if ((n = recv(s->master_sock, msg, 4096, 0)) < 0)
	{
		perror("recv()");
		exit(-1);
	}
	WS(msg);
}

void		quit_client(char *cmd, t_client *s)
{
	t_char	buff;
	char	msg[4096];
	int		n;

	ft_bzero(msg, 4096);
	ft_strsplit_char(cmd, ' ', &buff, 0);
	if (buff.size != 1)
	{
		ft_del_tab(buff.array, buff.size);
		ft_printf("quit: expected 0 args, got %d\n", buff.size);
		return ;
	}
	if (send(s->master_sock, cmd, ft_strlen(cmd), 0) < 0)
	{
		perror("send()");
		exit(-1);
	}
	if ((n = recv(s->master_sock, msg, 4096, 0)) < 0)
	{
		perror("recv()");
		exit(-1);
	}
	WS(msg);
	exit(0);
}

void		lcd_client(char *cmd, t_client *s)
{
	char	*str;
	t_char	buff;

	ft_strsplit_char(cmd, ' ', &buff, 0);
	if (buff.size > 2)
	{
		ft_del_tab(buff.array, buff.size);
		ft_printf("lcd: expected 2 args max, got %d\n", buff.size);
		return ;
	}
	if (buff.size == 1)
	{
		ft_memdel((void *)&s->my_env[1]);
		s->my_env[1] = ft_strdup(s->my_env[0]);
		return ;
	}
	str = ft_strultimatecat(3, s->my_env[1], "/", buff.array[1]);
	if (dir_exist(str, NULL) == true)
		s->my_env[1] = real_pwd_file(str, NULL, NULL);
	else
	{
		ft_printf("lcd : %s is not a directory\n", str);
		ft_memdel((void *)&str);
	}
	ft_del_tab(buff.array, buff.size);
}

void		lpwd_client(char *cmd, t_client *s)
{
	char	*str;
	t_char	buff;

	ft_strsplit_char(cmd, ' ', &buff, 0);
	if (buff.size != 1)
	{
		ft_del_tab(buff.array, buff.size);
		ft_printf("lpwd: expected 0 args, got %d\n", buff.size);
		return ;
	}
	str = ft_strultimatecat(2, "Local pwd is : ", s->my_env[1]);
	WS(str);
	ft_del_tab(buff.array, buff.size);
	ft_memdel((void *)&str);
}

t_char		opt_ls(t_char cmd, bool opt, t_client *s,
				size_t i)
{
	t_char		tmp;

	ft_bzero(&tmp, sizeof(t_char));
	while (i < cmd.size - 1)
	{
		if (cmd.array[i][0] != '-')
			opt = true;
		i++;
	}
	i = 0;
	if (opt == false)
	{
		tmp.array = ft_memalloc(sizeof(char **) * (cmd.size + 1));
		while (i < cmd.size - 1)
		{
			tmp.array[i] = ft_strdup(cmd.array[i]);
			i++;
		}
		tmp.array[i] = ft_strdup(s->my_env[1]);
		tmp.array[++i] = NULL;
		tmp.size = i + 1;
		ft_del_tab(cmd.array, cmd.size);
	}
	return (opt == false ? tmp : cmd);
}
