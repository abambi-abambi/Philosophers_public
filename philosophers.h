/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abambi <abambi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 21:03:21 by abambi            #+#    #+#             */
/*   Updated: 2021/09/27 15:34:03 by abambi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define HAS_TAKEN_A_FORK1 "\033[32mhas taken a fork\033[0m"
# define HAS_TAKEN_A_FORK2 "\033[35mhas taken a fork\033[0m"
# define YES	1
# define NO		0
# define FALSE	-2

typedef struct s_args
{
	int			ph_sum;
	int			life_time;
	int			eat_time;
	int			sleep_time;
	int			eat_min;
}	t_args;

typedef struct s_atoi_ph
{
	long int	num;
	long		digits;
}	t_atoi_ph;

typedef struct s_add
{
	struct timeval	t_start;
	pthread_mutex_t	printing;
	pthread_mutex_t	eat_counter;
	int				ate_all;
}	t_add;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	struct timeval	start_last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork_from_neighbour;
	t_args			*args;
	t_add			*add;
	int				finish;
}	t_philosopher;

int					ask_garson_permission(t_philosopher *man);

int					begin_the_game(t_philosopher *man, pthread_mutex_t *forks, \
		t_args *args);

int					check_arg_logic(int ac, t_args **args);
void				check_meals_count(t_philosopher *man, int sum_of_meals);
int					count_dishes(t_philosopher *man);
int					count_sheep(t_philosopher *man);
int					count_spaghetti(t_philosopher *man, int *sum_of_meals);
unsigned long long	count_time_period(struct timeval current_time, \
		struct timeval start_point);

void				duo_end(t_philosopher *man, struct timeval t_now, int i);

int					end_the_game(t_philosopher *man);

int					ft_atoi_ph(const char *str);
int					ft_free_exit(t_args *args, t_philosopher *man, \
		pthread_mutex_t *forks, char *err_msg);
void				ft_free_exit_part2(pthread_mutex_t *forks, \
		char *err_msg, int total_all);
size_t				ft_strlen(const char *str);

void				garson_decision(t_philosopher *man);

int					init_forks(t_philosopher *philosopher, \
		pthread_mutex_t *forks, t_args *args);
void				init_philosophers(t_philosopher *philosopher, t_add **add, \
		pthread_mutex_t *forks, t_args *args);

void				*life_cycle(t_philosopher *man);

int					malloc_init_add(t_add **add, t_philosopher *man, \
		pthread_mutex_t *forks, t_args *args);
int					malloc_init_forks(pthread_mutex_t **forks, \
		t_philosopher *man, t_args *args);
int					malloc_init_philosophers(t_philosopher **man, t_add **add, \
		pthread_mutex_t *forks, t_args *args);
int					msg(t_philosopher *philosopher, char *msg);

void				*one_fork_exception(t_philosopher *man);

int					parse_args(int ac, char **av, t_args **args);
int					prepare_to_play(t_philosopher **man, \
		pthread_mutex_t **forks, t_add **add, t_args *args);

void				wait_for_finish_all(t_philosopher *man);

#endif
