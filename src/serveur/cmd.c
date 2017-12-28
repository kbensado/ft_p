/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:31:57 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/02 18:00:11 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/serveur/serveur.h"

void			set_log(char *log, char *pwd, char *path, t_serv *s)
{
	static bool	key = false;

	s->sock.login = log;
	s->sock.passwd = pwd;
	s->sock.env = (char **)ft_memalloc(sizeof(char *) * 2);
	s->sock.env[0] = ft_strdup(path);
	s->sock.env[1] = ft_strdup(path);
	if (key == false)
		send(s->cs, "Login Success\n", 14, 0);
	key = true;
}

bool			create_login(char *path, t_serv *s, t_char cmd)
{
	char	*buff;
	int		fd;

	buff = NULL;
	if (create_dir(path) == true)
	{
		buff = ft_strultimatecat(2, path, "/.pwd");
		s->sock.sock = s->cs;
		set_log(cmd.array[0], cmd.array[1], path, s);
		fd = open(buff, O_CREAT | O_RDWR, 0400);
		if (fd == -1)
		{
			ft_memdel((void *)&path);
			perror("");
			return (false);
		}
		write(fd, s->sock.passwd, ft_strlen(s->sock.passwd));
		close(fd);
		ft_memdel((void *)&buff);
		return (true);
	}
	return (false);
}

bool			read_pwd(char *pwd, char *path)
{
	t_file		buff;
	char		*tmp;

	tmp = ft_strcatdup(path, "/.pwd");
	buff = get_file(tmp, 0);
	if (ft_strequ(buff.ptr, pwd) == 1)
	{
		ft_memdel((void *)&tmp);
		munmap(buff.ptr, buff.file.st_size);
		return (true);
	}
	ft_memdel((void *)&tmp);
	return (false);
}

static void		is_cmd(t_serv *s, t_char *cmd)
{
	int			i;
	char		*tmp;

	if (cmd->array[cmd->size - 1][ft_strlen(cmd->array[cmd->size - 1]) - 1]
	== '\n')
	{
		tmp = ft_strsub(cmd->array[cmd->size - 1], 0,
		ft_strlen(cmd->array[cmd->size - 1]) - 1);
		ft_memdel((void *)&cmd->array[cmd->size - 1]);
		cmd->array[cmd->size - 1] = tmp;
	}
	i = ft_contains_str_at(s->cmd, cmd->array[0], 9);
	if ((i != -1) && (i < 6))
	{
		ft_printf("command spotted a %d in %s\n", i, cmd->array[1]);
		g_signed[i](s, cmd);
	}
	ft_del_tab(cmd->array, cmd->size);
}

void			check_cmd(t_serv *s, char *buff)
{
	t_char		tmp;

	ft_bzero(&tmp, sizeof(t_char));
	buff = ft_str_replace(buff, '\n', 0);
	ft_strsplit_char(buff, ' ', &tmp, 0);
	if (s->sock.login == NULL)
	{
		if (tmp.size == 2 && ft_str_is_alphanum(tmp.array[0], true) == true
		&& ft_str_is_alphanum(tmp.array[1], true) == true)
		{
			if (check_dir_serv(s, &tmp) == false)
				return ;
		}
		else
			send(s->cs, "[Login] [Password], alphanum only\n", 35, 0);
	}
	else
		is_cmd(s, &tmp);
}
