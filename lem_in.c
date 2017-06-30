/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 20:42:33 by mlambert          #+#    #+#             */
/*   Updated: 2017/06/30 18:24:09 by mlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <fcntl.h>

void		final_step(int break_loop, t_lem *lem)
{
	if (break_loop == 0)
		break_loop = solve(&lem);
	if (break_loop != 0)
		errors(break_loop);
}

int			where_is_my_colony(t_lem *lem, char *line)
{
	int		n;
	int		i;

	i = -1;
	n = 0;
	while(line[++i])
		if (ft_isdigit(line[i]) != 1)
		{
			ft_memdel((void**)&line);
			return(-1);
		}
	n = ft_atoi(line);
	lem->colony = n;
	fill_buffer(lem, line);
	ft_memdel((void**)&line);
	return (0);
}

int			fill_buffer(t_lem *lem, char *line)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	tmp = NULL;
	if (lem->buffer == NULL)
	{
		tmp = ft_strjoin(line, "\n");
		lem->buffer = ft_strdup(tmp);
		ft_memdel((void**)&tmp);
	}
	else
	{
		tmp = ft_strjoin(line, "\n");
		tmp2 = lem->buffer;
		lem->buffer = ft_strjoin(lem->buffer, tmp);
		ft_memdel((void**)&tmp2);
		ft_memdel((void**)&tmp);
	}
	return (0);
}

int			comment_start_end(t_lem *lem, char *line, int break_loop, int fd)
{
	int		start_end;

	start_end = 0;
	if (line[1] != '#')
		fill_buffer(lem, line);
	if (lem->colony == -1 && line[1] == '#' && line[2] != '#' && \
	(ft_strcmp(line, "##start") || ft_strcmp(line, "##end")))
		return(-1);
	else if (line[1] == '#' && line[2] != '#' && \
	(ft_strcmp(line, "##start") == 0 || ft_strcmp(line, "##end") == 0))
	{
		start_end = (line[2] == 's') ? 1 : 2;
		fill_buffer(lem, line);
		ft_memdel((void**)&line);
		get_next_line(fd, &line);
		fill_buffer(lem, line);
		room_specs(line, lem, start_end);
	}
	ft_memdel((void**)&line);
	return (0);
}
// INITIALIZING EACH ROOM IS CAPITAL. YOU WILL SEGFAULT YOU SON OF A BITCH. DO YOU HEAR ME ? YOU WILL. SEGFAULT.
// CAN YOU REDEFINE START OR END WITHOUT HAVING TO CREATE ANOTHER ROOM ?
int			main(int argc, char **argv)
{
	t_lem	lem;
	char	*line;
	int		break_loop;
	int		fd;

	line = NULL;
	init_lem(&lem);
	break_loop = 0;
	fd = open(argv[1], O_RDONLY);
	while(break_loop == 0 && get_next_line(fd, &line))
	{
		if (line[0] == '#')
			break_loop = comment_start_end(&lem, line, break_loop, fd);
		else if (lem.colony == -1)
			break_loop = where_is_my_colony(&lem, line);
		else if (!(ft_strchr(line, '-') && line[0] > 32))			// WARNING, WE DO NOT ACCEPT MORE THAN ONE SPACE BETWEEN "NAME X Y" I MUST THINK ABOUT A WAY TO
			break_loop = room_specs(line, &lem, 0);
		else if ((ft_strchr(line, '-')) && line[0] > 32)
		{
			lem.phase = (lem.phase == 0) ? 1 : lem.phase;
			break_loop = links(&lem, line);
			lem.match = 0;
		}
	}
	final_step(break_loop, lem);
	return (0);
}
