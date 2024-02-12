/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:29:03 by nathan            #+#    #+#             */
/*   Updated: 2024/02/12 12:34:20 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

struct s_rules;

typedef struct s_philo
{
	int             id;
	int             x_ate;
	int             left_fork_id;
	int             right_fork_id;
	long long       t_last_meal;
	struct s_rules  *rules;
	pthread_t       thread_id;
	
}                   t_philo;

typedef struct  s_rules
{
	int             nb_philo;
	int             time_death;
	int             time_eat;
	int             time_sleep;
	int             nb_eat;
	int             dieded;
	int             all_ate;
	long long       first_timestamp;
	pthread_mutex_t meal_check;
	pthread_mutex_t forks[250];
	pthread_mutex_t writing;
	t_philo         philosophers[250];
}                   t_rules;

//laucher
int 		launcher(t_rules *rules);

//init
int 		initAll(t_rules *rules, char **argv);

//utils
int			ft_atoi(const char *str);
long long	timestamp(void);
long long	timeDiff(long long pres, long long past);
void		actionPrint(t_rules *rules, int id, char *str);
void		smartSleep(long long time, t_rules *rules);

//error
int			writeError(char *str);
int			errorManager(int error);

#endif