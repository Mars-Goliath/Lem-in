/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_march.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 17:08:35 by mlambert          #+#    #+#             */
/*   Updated: 2017/06/30 18:10:33 by mlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ants_n_rooms(t_lem *lem, t_room *path)
{
	path->ants_nb = lem->colony - lem->start->ants_nb - 1; 		//need to think about end-start link;
	if (path == lem->end)
	{
		path->ants_nb += 1;
		path->link->room->ants_nb = 0;
		ft_printf("L%d %s", path->ants_nb, lem->end->name);
		if (lem->colony - path->ants_nb >= 1)
			ft_printf("%c", ' ');
	}
	else
	{
		path->ants_nb = path->link->room->ants_nb;
		path->link->room->ants_nb = 0;
		ft_printf("L%d %s", path->ants_nb, path->name);
	}
}

t_link	*on_the_way(t_lem *lem, t_room *path)
{
	path->link = path->first_link;
	while ((path->link != NULL))
	{
		if (path->link->room == lem->start)
			return (path->link);
		if (path->link->room != lem->end && path->link->room->path_locked != 0)
		{
			if (path->weight < path->link->room->weight)
				return (path->link);
		}
		path->link = path->link->next;
	}
	return (path->link);
}

void	move(t_room *path, t_lem *lem)
{
	while (path != lem->start)
	{
		path->link = on_the_way(lem, path);
		if (path->link->room == lem->start && lem->start->ants_nb != 0)
		{
			path->ants_nb = lem->colony - lem->start->ants_nb + 1; 		//need to think about end-start link;
			lem->start->ants_nb -= 1;
			ft_printf("L%d %s", path->ants_nb, path->name);
		}
		else if (path->link->room->ants_nb != 0)
			ants_n_rooms(lem, path);
		path = path->link->room;
	}
	ft_printf("%c", '\n');
}

int		the_march(t_lem *lem)
{
	int		n;
	t_room	*path;

	n = lem->colony;
	while (lem->end->ants_nb != lem->colony)
	{
		path = lem->end;
		move(path, lem);
	}
	return (0);
}
