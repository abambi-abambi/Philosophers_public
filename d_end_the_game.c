/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_end_the_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:03:21 by abambi            #+#    #+#             */
/*   Updated: 2021/09/27 15:33:51 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	end_the_game(t_philosopher *man)
{
	int				i;
	struct timeval	t_now;

	while (1)
	{
		i = -1;
		while (++i < man->args->ph_sum)
		{
			gettimeofday(&t_now, NULL);
			if (count_time_period(t_now, man[i].start_last_meal) \
				> man->args->life_time)
			{
				duo_end(man, t_now, i);
				wait_for_finish_all(man);
				return (1);
			}
		}
		usleep(500);
	}
	return (0);
}

void	duo_end(t_philosopher *man, struct timeval t_now, int i)
{
	if (man->add->ate_all != man->args->ph_sum)
	{
		pthread_mutex_lock(&man->add->eat_counter);
		man->args->eat_min = FALSE;
		pthread_mutex_unlock(&man->add->eat_counter);
		pthread_mutex_lock(&man->add->printing);
		printf("%5llu %3d %s\n", \
		count_time_period(t_now, man->add->t_start), \
			man[i].id, "died\n");
		pthread_mutex_unlock(&man->add->printing);
	}
	else if (man->add->ate_all == man->args->ph_sum)
	{
		pthread_mutex_lock(&man->add->printing);
		printf("\n\033[32mGAME_OVER\033[0m\n");
		pthread_mutex_unlock(&man->add->printing);
	}	
}

void	wait_for_finish_all(t_philosopher *man)
{
	int	i;

	while (1)
	{
		usleep(500);
		i = 0;
		while (i < man->args->ph_sum && man[i].finish == 1)
		{
			i++;
		}
		if (i == man->args->ph_sum)
			return ;
	}
}
