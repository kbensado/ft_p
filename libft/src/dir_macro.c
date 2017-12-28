/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_macro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbensado <kbensado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 20:46:18 by kbensado          #+#    #+#             */
/*   Updated: 2017/08/27 18:26:06 by kbensado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/libft_malloc.h"

t_file				get_file(char *path, size_t len)
{
	t_file			res;
	size_t			size;
	size_t			tmp;

	ft_bzero(&res, sizeof(t_file));
	res.fd = open(path, O_RDONLY);
	tmp = 0;
	size = 0;
	if (res.fd == -1)
		return (res);
	fstat(res.fd, &res.file);
	size = res.file.st_size;
	(void)len;
	if (size > 0)
	{
		res.ptr = FILE_MAP(size, res.fd);
		return (res);
	}
	ft_memdel((void *)&res.ptr);
	return (res);
}

int					create_file(char *path, bool del)
{
	int				fd;

	fd = -1;
	if ((fd = open(path, O_RDWR)) > 0)
		return (-1);
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd < 0)
	{
		if (del == true)
			MEMDEL(path);
		return (-1);
	}
	if (del == true)
		MEMDEL(path);
	return (fd);
}

bool				create_dir(char *path)
{
	if (mkdir(path, 0700) == 0)
		return (true);
	return (false);
}

bool				dir_exist(char *path, DIR *buff)
{
	buff = opendir(path);
	if (buff != NULL)
	{
		closedir(buff);
		return (true);
	}
	return (false);
}

void				rm_file(char *path)
{
	pid_t	daddy;
	int		i;

	daddy = fork();
	if (daddy > 0)
		waitpid(daddy, &i, 0);
	else if (daddy == 0)
		execl("/bin/rm", "/bin/rm", path, NULL);
	else
		wait(&daddy);
}
