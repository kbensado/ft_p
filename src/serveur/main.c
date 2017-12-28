/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 18:19:01 by kbensado          #+#    #+#             */
/*   Updated: 2017/12/02 16:47:29 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/serveur/serveur.h"

void		handle_error(char *str)
{
	WS(str);
	free_everything();
	exit(-1);
}

int			main(int ac, char **av, char **env)
{
	t_serv	s;

	ft_bzero(&s, sizeof(s));
	s.env = ft_getenv(env);
	s.pwd = ft_strnew(MAXPATHLEN);
	s.pwd = getcwd(s.pwd, MAXPATHLEN);
	s.opt = ft_get_arg(av, ac, ft_set_arg(1, "ipv6"), 0);
	s.cmd = ft_strtabnew(9, "ls", "cd", "get", "put", "pwd",
						"quit", "lcd", "lpwd", "lls");
	if (ac < 2 || s.opt.inc != s.opt.nb_opt)
		handle_error(ER);
	if ((s.port = ft_atoi(av[ac - 1])) < 1025)
		handle_error("port 2 low");
	if (create_serv(&s) == false)
		handle_error("Error creation");
	return (0);
}
