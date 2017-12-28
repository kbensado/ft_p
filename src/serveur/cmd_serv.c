/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_serv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 02:28:16 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/04 06:27:34 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/serveur/serveur.h"

char			*add_home(char *src, t_serv *s)
{
	char	*res;
	char	*buff;
	char	*tmp;
	char	*check;

	buff = NULL;
	check = NULL;
	res = ft_strultimatecat(3, s->sock.env[0], "/",
	src);
	tmp = ft_strultimatecat(2, s->sock.env[0], "*");
	check = real_pwd_file(res, NULL, NULL);
	if (check == NULL || match(check, tmp) == 0)
	{
		ft_memdel((void *)&res);
		return (NULL);
	}
	ft_memdel((void *)&buff);
	ft_memdel((void *)&check);
	ft_memdel((void *)&tmp);
	return (res);
}

t_char			opt_ls(t_char cmd, bool opt, t_serv *s,
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
		tmp.array[i] = ft_strdup(s->sock.env[1]);
		tmp.array[++i] = NULL;
		tmp.size = i + 1;
		ft_del_tab(cmd.array, cmd.size);
	}
	return (opt == false ? tmp : cmd);
}

void			cd_serv(t_serv *s, t_char *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (cmd->size > 2)
	{
		send(s->cs, "cd [dir], only 1 arg\n", 21, 0);
		return ;
	}
	if (cmd->size == 1)
	{
		s->sock.env[1] = s->sock.env[0];
		create_send_msg(ft_strultimatecat(3, ND, "/", "\n"), s, false, 0);
		return ;
	}
	tmp = ft_strultimatecat(3, s->sock.env[1], "/", cmd->array[1]);
	if (dir_exist(tmp, NULL) == true)
		s->sock.env[1] = real_pwd_file(tmp, NULL, NULL);
	cd_no_right(s);
	if (ft_strequ(s->sock.env[1], s->sock.env[0]) == 1)
	{
		S_MSG(CAT(3, "SUCCESS, new dir is : ", "/", "\n"), false);
		return ;
	}
	S_MSG(ft_strultimatecat(3, "SUCCESS, new dir is : ",
	ft_strless(s->sock.env[0], s->sock.env[1], false), "\n"), false);
}

void			get_serv(t_serv *s, t_char *cmd)
{
	char		*msg;
	size_t		i;

	msg = NULL;
	i = 1;
	if (cmd->size < 2)
	{
		send(s->cs, "ERROR : arg needed\n", 19, 0);
		return ;
	}
	while (i < cmd->size)
	{
		if (send_file(cmd->array[i], s) == false)
			create_send_msg(CAT(3, "ERROR GET : ",
			cmd->array[i], "\n"),
		s, false, 0);
		i++;
	}
}

void			put_serv(t_serv *s, t_char *cmd)
{
	int			fd;

	if (cmd->size == 1)
	{
		S_MSG("put: expected at least 1 args, has none", false);
		ft_del_tab(cmd->array, cmd->size);
		return ;
	}
	fd = create_file(ft_strultimatecat(3, s->sock.env[1],
	"/", cmd->array[1]), true);
	if (fd > 0)
		put_norme(s, fd, cmd);
	else
	{
		S_MSG("NON", false);
	}
}
