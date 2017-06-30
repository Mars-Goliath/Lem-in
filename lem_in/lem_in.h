/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlambert <mlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 01:10:38 by mlambert          #+#    #+#             */
/*   Updated: 2017/06/27 22:23:19 by mlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEM_IN_H
# define LEM_IN_H

 #include <stdlib.h>
 #include "ft_printf.h"
 #include "get_next_line.h"

typedef struct	s_link
{
	struct	s_room	*room;
	struct	s_link	*next;
}				t_link;

typedef struct	s_room
{
	char	*name;
	int		path_locked;
	int		ants_nb;
	int		coord_y;
	int		coord_x;
	int		weight;
	t_link 	*link;
	t_link	*first_link;
	struct 	s_room *next;
	struct	s_room *father;
}				t_room;

typedef struct	s_lem
{
	int		colony;
	int		nb_rooms;
	int		phase;
	int		match;
	t_room	*otherside_of_link;
	t_room	*room;
	t_room	*start;
	t_room	*end;
	char	*buffer;
}				t_lem;

void	init_room(t_lem	*lem);
void	init_lem(t_lem	*lem);
void	errors(int	error_type);
int		fill_buffer(t_lem *lem, char *line);
int		room_specs(char *line, t_lem *lem, int start_1end_2);
int		links(t_lem *lem, char *line);
int		solve(t_lem *lem);
void	path_carving(t_lem *lem);
int		the_march(t_lem *lem);

void	display(t_lem *lem);


#endif
