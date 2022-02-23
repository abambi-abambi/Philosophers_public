/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_ph_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:03:21 by abambi            #+#    #+#             */
/*   Updated: 2021/09/27 15:33:55 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	count_dishes(t_philosopher *man)
{
	struct timeval	t_0;
	struct timeval	t_now;
	int				think_time;
	int				count_dishes;

	gettimeofday(&t_0, NULL);
	think_time = man->args->eat_time - 50;
	count_dishes = 0;
	while (1)
	{
		gettimeofday(&t_now, NULL);
		if (count_time_period(t_now, t_0) >= think_time)
			return (count_dishes);
		count_dishes += 1;
		usleep(100);
	}
	return (count_dishes);
}

int	count_spaghetti(t_philosopher *man, int *sum_of_meals)
{
	struct timeval	t_now;
	int				count_spaghetti;

	gettimeofday(&man->start_last_meal, NULL);
	count_spaghetti = 0;
	*sum_of_meals += 1;
	while (1)
	{
		gettimeofday(&t_now, NULL);
		if (count_time_period(t_now, man->start_last_meal) \
			>= man->args->eat_time)
			return (count_spaghetti);
		count_spaghetti += 1;
		usleep(100);
	}
	return (count_spaghetti);
}

int	count_sheep(t_philosopher *man)
{
	struct timeval	t_0;
	struct timeval	t_now;
	int				count_sheep;

	gettimeofday(&t_0, NULL);
	count_sheep = 0;
	while (1)
	{
		gettimeofday(&t_now, NULL);
		if (count_time_period(t_now, t_0) >= man->args->sleep_time)
			return (count_sheep);
		count_sheep += 1;
		usleep(100);
	}
	return (count_sheep);
}

int	ask_garson_permission(t_philosopher *man)
{
	if (man->args->eat_min != FALSE)
		return (YES);
	else
		return (NO);
}

int	msg(t_philosopher *man, char *msg)
{
	struct timeval		t_0;
	struct timeval		t_now;
	unsigned long long	period;
	int					move;

	pthread_mutex_lock(&man->add->eat_counter);
	move = ask_garson_permission(man);
	pthread_mutex_unlock(&man->add->eat_counter);
	if (move == YES)
	{
		t_0 = man->add->t_start;
		pthread_mutex_lock(&man->add->printing);
		gettimeofday(&t_now, NULL);
		printf("%5llu %3d %s\n", count_time_period(t_now, t_0), man->id, msg);
		pthread_mutex_unlock(&man->add->printing);
	}
	return (1);
}
