/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_carving.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 18:41:42 by mlambert          #+#    #+#             */
/*   Updated: 2017/07/03 05:54:21 by mlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			flush(t_lem *lem, t_room *room)
{
	if (room->path_locked == 0)
		room->weight = 0;
	if (check_sons(lem, room, &room->link) == 0)
	{
		if (room != lem->end)
			flush(lem, room->father);
		else
			return (0);
	}
	if (room->link->room->weight == 0)
	{
		room->link->room->father = room;
		flush(lem, room->link->room);
	}
	return (0);
}

t_room		*check_weight(t_room *room, t_room *room_link, t_room *tmp)
{
	if (room->weight > room_link->weight)
	{
		if (tmp != NULL)
		{
			if (tmp->weight > room_link->weight && room_link->path_locked == 0)
				tmp = room_link;
		}
		else
			tmp = room_link;
	}
	return (tmp);
}

t_room		*which_way(t_lem *lem, t_room *room)
{
	t_room *tmp;

	tmp = NULL;
	room->link = room->first_link;
	while (room->link->next != NULL)
	{
		tmp = check_weight(room, room->link->room, tmp);
		room->link = room->link->next;
	}
	tmp = check_weight(room, room->link->room, tmp);
	return (tmp);
}

void		path_carving(t_lem *lem)
{
	int	n;
	t_room	*path_tmp;

	n = 1;
	path_tmp = lem->start;

//	while (lem->paths != 0)
//	{
		while (path_tmp != lem->end)
		{
			path_tmp = which_way(lem, path_tmp);
			path_tmp->path_locked = n;
		}
//		flush(lem, lem->end);
//		n++;
//	}
}
