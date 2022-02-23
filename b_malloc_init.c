/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_malloc_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:03:21 by abambi            #+#    #+#             */
/*   Updated: 2021/09/27 04:52:30 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	malloc_init_forks(pthread_mutex_t **forks, t_philosopher *man, \
			t_args *args)
{
	*forks = malloc(sizeof(pthread_mutex_t) * args->ph_sum);
	if (*forks == NULL)
		return (ft_free_exit(args, man, NULL, "Error\n-> in forks' malloc"));
	if (init_forks(man, *forks, args) == -1)
		return (-1);
	return (0);
}

int	init_forks(t_philosopher *man, pthread_mutex_t *forks, \
				t_args *args)
{
	int	i;

	i = 0;
	while (i < args->ph_sum)
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
			return (ft_free_exit(args, man, forks, "Error\n-> in init forks"));
		i++;
	}
	return (0);
}

int	malloc_init_add(t_add **add, t_philosopher *man, \
			pthread_mutex_t *forks, t_args *args)
{
	struct timeval	t_actual;

	*add = malloc(sizeof(t_add) * 1);
	if (*add == NULL)
		return (ft_free_exit(args, NULL, forks, "Error\n-> in add's malloc"));
	if (pthread_mutex_init(&(*add)->printing, NULL) != 0)
		return (ft_free_exit(args, NULL, forks, "Error\n-> (1) in init add"));
	if (pthread_mutex_init(&(*add)->eat_counter, NULL) != 0)
		return (ft_free_exit(args, NULL, forks, "Error\n-> (2) in init add"));
	gettimeofday(&t_actual, NULL);
	(*add)->t_start = t_actual;
	(*add)->ate_all = 0;
	return (0);
}

int	malloc_init_philosophers(t_philosopher **man, t_add **add, \
			pthread_mutex_t *forks, t_args *args)
{
	*man = malloc(sizeof(t_philosopher) * args->ph_sum);
	if (*man == NULL)
	{
		free(*add);
		return (ft_free_exit(args, NULL, forks, "Error\n-> in man's malloc"));
	}
	init_philosophers(*man, add, forks, args);
	return (0);
}

void	init_philosophers(t_philosopher *man, t_add **add, \
			pthread_mutex_t *forks, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->ph_sum)
	{
		man[i].id = i + 1;
		man[i].l_fork = forks + i;
		man[i].r_fork_from_neighbour = forks + (i + 1) % args->ph_sum;
		man[i].start_last_meal = (*add)->t_start;
		man[i].add = *add;
		man[i].args = args;
		man[i].finish = 0;
		i++;
	}
}
