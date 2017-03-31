/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_to_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewallner <ewallner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:16:11 by ewallner          #+#    #+#             */
/*   Updated: 2017/03/30 20:04:27 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_string_len(t_env *e, int i)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	int		fd;

	e->player[i].len = 0;
	if ((fd = open(e->files[e->player[i].file_pos], O_RDONLY)) == -1)
		ft_exit(e, 1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (ret != 0)
			e->player[i].len += ret;
	}
	if (close(fd) == -1)
		ft_exit(e, 2);
	if (ret == -1)
		ft_exit(e, 3);
	return (e->player[i].len);
}

void	ft_files_to_string(t_env *e)
{
	int i;
	int fd;
	int len;

	i = 0;
	while (i < e->player_amount)
	{
		len = ft_string_len(e, i);
		if ((fd = open(e->files[e->player[i].file_pos], O_RDONLY)) == -1)
			ft_exit(e, 1);
		if (read(fd, e->player[i].string, e->player[i].len) == -1)
			ft_exit(e, 3);
		e->player[i].string[len] = '\0';
		if (close(fd) == -1)
			ft_exit(e, 2);
		i++;
	}
}
