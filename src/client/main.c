/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 18:50:24 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/01 19:26:14 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/client/client.h"

void			handle_error(char *str)
{
	WS(str);
	exit(-1);
}

char			**pwd_home(char **env)
{
	char		**res;
	size_t		i;

	i = 0;
	res = ft_memalloc(sizeof(char *) * 2);
	while (env[i])
	{
		if (match(env[i], "HOME=*"))
			res[0] = ft_strless("HOME=", env[i], false);
		if (match(env[i], "PWD=*"))
			res[1] = ft_strless("PWD=", env[i], false);
		i++;
	}
	return (res);
}

int				main(int ac, char **av, char **env)
{
	t_client	s;

	ft_bzero(&s, sizeof(s));
	s.addr = av[1];
	s.env = ft_getenv(env);
	s.my_env = pwd_home(env);
	s.cmd = ft_strtabnew(9, "ls", "cd", "get", "put", "pwd",
						"quit", "lcd", "lpwd", "lls");
	s.opt = ft_get_arg(av, ac, ft_set_arg(1, "ipv6"), 0);
	if (ac < 3 || s.opt.inc != s.opt.nb_opt)
		handle_error("Feed me with an arg pls or do not fucked up\
		with the option pls !!!");
	if ((s.port = ft_atoi(av[ac - 1])) < 1025)
		handle_error("port 2 low");
	if (create_client(&s) == false)
		handle_error("Error creation");
	return (0);
}
