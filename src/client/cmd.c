/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:21:00 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/04 06:26:53 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/client/client.h"

void		cd_client(char *cmd, t_client *s)
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
	if ((n = recv(s->master_sock, mgs, 4096, 0)) < 0)
	{
		perror("recv()");
		exit(-1);
	}
	WS(mgs);
}

void		get_client(char *cmd, t_client *s)
{
	t_char		buff;
	int			fd;
	size_t		len;

	len = 0;
	ft_strsplit_char(cmd, ' ', &buff, 0);
	if (buff.size == 1)
	{
		WS("get: expected at least 1 args, have none");
		ft_del_tab(buff.array, buff.size);
		return ;
	}
	if ((fd = create_file(CAT(3, s->my_env[1], "/",
		buff.array[1]), true)) == -1)
	{
		WS("ERROR get");
		ft_memdel((void *)&cmd);
		return ;
	}
	send_msg(s, cmd, ft_strlen(cmd), "send()");
	client_get_norme(s, fd, &buff);
	ft_memdel((void *)&cmd);
}

void		put_client(char *cmd, t_client *s)
{
	t_file	file;
	t_char	buff;
	char	*path;

	ft_strsplit_char(cmd, ' ', &buff, 0);
	if (buff.size == 2)
	{
		path = ft_strultimatecat(3, s->my_env[1], "/", buff.array[1]);
		file = get_file(path, 0);
		if (file.fd > 0)
		{
			send_msg(s, cmd, ft_strlen(cmd) + 1, "send(put1)");
			if (rec_msg(s, "envoie le") == false)
			{
				ft_printf("ERROR PUT : %s\n", buff.array[1]);
				ft_del_tab(buff.array, buff.size);
				return ;
			}
			client_put_norme(s, &file);
		}
		else
			ft_printf("%s dosn't exist\n", buff.array[1]);
	}
	ft_del_tab(buff.array, buff.size);
}

t_char		set_exec_lls(char **src, size_t count,
			t_client *s)
{
	t_char	res;
	size_t	i;
	size_t	j;

	i = 1;
	j = 1;
	res.array = ft_memalloc(sizeof(char *) * (count + 1));
	res.array[0] = ft_strdup("/bin/ls");
	while (j < count)
	{
		if (src[j][0] != '-')
		{
			res.array[i] = ft_strultimatecat(3, s->my_env[1], "/", src[j]);
			if (res.array[i] == NULL)
				res.array[i] = ft_strdup(s->my_env[1]);
		}
		else
			res.array[i] = ft_strdup(src[j]);
		i++;
		j++;
	}
	res.array[i] = NULL;
	res.size = i + 1;
	res = opt_ls(res, false, s, 1);
	return (res);
}

void		lls_client(char *cmd, t_client *s)
{
	t_char	av;
	t_char	buff;

	ft_strsplit_char(cmd, ' ', &buff, 0);
	if (buff.size == 1)
	{
		av.array = ft_strtabnew(3, "/bin/ls", s->my_env[1],
		NULL);
		av.size = 3;
		execv_it(1, true, av);
		ft_del_tab(buff.array, buff.size);
		return ;
	}
	av = set_exec_lls(buff.array, buff.size, s);
	execv_it(1, true, av);
	ft_del_tab(buff.array, buff.size);
}
