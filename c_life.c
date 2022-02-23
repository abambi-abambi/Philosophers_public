/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_life.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:03:21 by abambi            #+#    #+#             */
/*   Updated: 2021/09/27 15:34:02 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	begin_the_game(t_philosopher *man, pthread_mutex_t *forks, \
			t_args *args)
{
	int	i;

	i = 0;
	while (i < args->ph_sum)
	{
		if (pthread_create(&man[i].thread, NULL, (void *)life_cycle, man + i))
			return (ft_free_exit(args, man, forks, \
				"Error\n-> in pthread create()"));
		if (pthread_detach(man[i].thread))
			return (ft_free_exit(args, man, forks, \
				"Error\n-> in pthread detach()"));
		usleep(400);
		i++;
	}
	return (0);
}

void	*life_cycle(t_philosopher *man)
{
	int	sum_of_meals;

	if (man->id % 2 == 0)
		msg(man, "\033[36mis thinking\033[0m") + count_dishes(man);
	sum_of_meals = 0;
	if (man->l_fork == man->r_fork_from_neighbour)
		return (one_fork_exception(man));
	while (man->args->eat_min == -1 || sum_of_meals < man->args->eat_min)
	{
		pthread_mutex_lock(man->l_fork) + msg(man, HAS_TAKEN_A_FORK1);
		pthread_mutex_lock(man->r_fork_from_neighbour) + \
				msg(man, HAS_TAKEN_A_FORK2);
		msg(man, "is eating") + count_spaghetti(man, &sum_of_meals);
		pthread_mutex_unlock(man->r_fork_from_neighbour);
		pthread_mutex_unlock(man->l_fork);
		msg(man, "\033[34mis sleeping\033[0m") + count_sheep(man);
		msg(man, "\033[31mis thinking\033[0m");
	}
	check_meals_count(man, sum_of_meals);
	garson_decision(man);
	return (NULL);
}

void	check_meals_count(t_philosopher *man, int sum_of_meals)
{
	if (man->args->eat_min != -1)
	{
		pthread_mutex_lock(&man->add->eat_counter);
		if (sum_of_meals == man->args->eat_min)
		{
			man->add->ate_all += 1;
		}
		pthread_mutex_unlock(&man->add->eat_counter);
	}
}

void	garson_decision(t_philosopher *man)
{
	man->finish = 1;
}

void	*one_fork_exception(t_philosopher *man)
{
	pthread_mutex_lock(man->l_fork) + msg(man, HAS_TAKEN_A_FORK1);
	pthread_mutex_unlock(man->l_fork);
	garson_decision(man);
	return (NULL);
}
