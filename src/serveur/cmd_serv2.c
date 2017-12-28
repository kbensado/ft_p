/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_serv2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 02:28:16 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/02 16:40:24 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/serveur/serveur.h"

void		quit_serv(t_serv *s, t_char *cmd)
{
	MEMDEL(s->sock.login);
	MEMDEL(s->sock.passwd);
	(void)cmd;
	ft_del_tab(s->sock.env, 2);
	send_msg(s, "SUCCESS, kthxbye\n", 17, "");
	close(s->cs);
}

t_char		set_exec_ls(char **src, size_t count,
			t_serv *s)
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
			res.array[i] = add_home(src[j], s);
			if (res.array[i] == NULL)
				res.array[i] = ft_strdup(s->sock.env[1]);
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

void		ls_serv(t_serv *s, t_char *cmd)
{
	t_char	av;

	if (cmd->size == 1)
	{
		av.array = ft_strtabnew(3, "/bin/ls", s->sock.env[1],
		NULL);
		av.size = 3;
		execv_it(s->cs, true, av);
		send(s->cs, "SUCCESS\n", 7, 0);
		return ;
	}
	av = set_exec_ls(cmd->array, cmd->size, s);
	execv_it(s->cs, true, av);
	send(s->cs, "SUCCESS\n", 7, 0);
}

void		pwd_serv(t_serv *s, t_char *cmd)
{
	char	*msg;
	char	*tmp;

	msg = NULL;
	tmp = NULL;
	if (cmd->size > 1)
	{
		send(s->cs, "FAILURE : pwd do not works with arg\n", 36, 0);
		return ;
	}
	tmp = ft_strless(s->sock.env[0], s->sock.env[1], false);
	if (tmp == NULL)
		tmp = ft_strdup("/");
	msg = ft_strultimatecat(3, "SUCCESS\n", tmp, "\n");
	create_send_msg(msg, s, false, 0);
	ft_memdel((void *)&tmp);
}
