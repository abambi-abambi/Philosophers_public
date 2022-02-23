/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:03:21 by abambi            #+#    #+#             */
/*   Updated: 2021/09/25 19:34:55 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_args			*args;
	t_philosopher	*man;
	pthread_mutex_t	*forks;
	t_add			*add;

	args = NULL;
	man = NULL;
	forks = NULL;
	add = NULL;
	if (parse_args(ac, av, &args) == -1)
		return (-1);
	if (prepare_to_play(&man, &forks, &add, args) == -1)
		return (-1);
	if (begin_the_game(man, forks, args) == -1)
		return (-1);
	end_the_game(man);
	ft_free_exit(args, man, forks, "");
	return (1);
}

int	prepare_to_play(t_philosopher **man, pthread_mutex_t **forks, \
	t_add **add, t_args *args)
{
	if (malloc_init_forks(forks, *man, args) == -1)
		return (-1);
	if (malloc_init_add(add, *man, *forks, args) == -1)
		return (-1);
	if (malloc_init_philosophers(man, add, *forks, args) == -1)
		return (-1);
	return (0);
}
