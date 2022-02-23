/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_ph_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:03:21 by abambi            #+#    #+#             */
/*   Updated: 2021/09/27 15:33:53 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_args(int ac, char **av, t_args **args)
{
	if (ac == 5 || ac == 6)
		;
	else
		return (ft_free_exit(NULL, NULL, NULL, "Error\n-> wrong num of args\n"));
	*args = malloc(sizeof(t_args));
	if (*args == NULL)
		return (ft_free_exit(NULL, NULL, NULL, \
			"Error\n-> in malloc() of args\n"));
	(*args)->ph_sum = ft_atoi_ph(av[1]);
	(*args)->life_time = ft_atoi_ph(av[2]);
	(*args)->eat_time = ft_atoi_ph(av[3]);
	(*args)->sleep_time = ft_atoi_ph(av[4]);
	if (ac == 6)
		(*args)->eat_min = ft_atoi_ph(av[5]);
	else
		(*args)->eat_min = -1;
	if ((*args)->ph_sum == -1 || (*args)->life_time == -1 || \
		(*args)->eat_time == -1 || (*args)->sleep_time == -1 || \
		(ac == 6 && (*args)->eat_min == -1))
		return (ft_free_exit(*args, NULL, NULL, \
			"Error\n-> in syntacs of args\n"));
	if (check_arg_logic(ac, args) == -1)
		return (ft_free_exit(*args, NULL, NULL, "Error\n-> no logic in args\n"));
	return (0);
}

int	check_arg_logic(int ac, t_args **args)
{
	if ((*args)->ph_sum == 0 || (*args)->ph_sum > 200 || \
	(*args)->life_time < 60 || \
	(*args)->eat_time < 60 || \
	(*args)->sleep_time < 60 || \
	(ac == 6 && (*args)->eat_min == 0))
		return (-1);
}

unsigned long long	count_time_period(struct timeval current_time, \
	struct timeval start_point)
{
	unsigned long long	period;

	period = \
	(current_time.tv_sec - start_point.tv_sec) * 1000 + \
	(current_time.tv_usec - start_point.tv_usec) / 1000;
	return (period);
}

int	ft_free_exit(t_args *args, t_philosopher *man, \
				pthread_mutex_t *forks, char *err_msg)
{
	int	i;
	int	total_all;

	total_all = 0;
	if (args != NULL)
	{
		total_all = args->ph_sum;
		free(args);
		args = NULL;
	}
	if (man != NULL)
	{
		pthread_mutex_destroy(&man->add->printing);
		pthread_mutex_destroy(&man->add->eat_counter);
		if (man->add != NULL)
		{
			free(man->add);
			man->add = NULL;
		}
		free(man);
		man = NULL;
	}
	ft_free_exit_part2(forks, err_msg, total_all);
	return (-1);
}

void	ft_free_exit_part2(pthread_mutex_t *forks, char *err_msg, int total_all)
{
	int	i;

	i = -1;
	if (forks != NULL)
	{
		while (++i < total_all)
			pthread_mutex_destroy(forks + i);
		free(forks);
		forks = NULL;
	}
	write(2, err_msg, ft_strlen(err_msg));
}
