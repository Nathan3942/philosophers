/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:29:39 by nathan            #+#    #+#             */
/*   Updated: 2024/05/22 16:49:20 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eat_philo(t_philo *philo, t_rules *rules)
{
	if (philo->id % 2 == 0)
	{
		usleep(rules->time_eat);
		pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
		action_print(rules, philo->id, "has taken a fork");
		pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
		action_print(rules, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
		action_print(rules, philo->id, "has taken a fork");
		pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
		action_print(rules, philo->id, "has taken a fork");
	}
	pthread_mutex_lock(&(rules->meal_check));
	action_print(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	smart_sleep(rules->time_eat, rules);
	(philo->x_ate)++;
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}

static void	*pthread(void *void_philo)
{
	t_philo	*phi;
	t_rules	*rules;

	phi = (void *)void_philo;
	rules = phi->rules;
	if (rules->nb_philo == 1)
		return (NULL);
	if (phi->id % 2 == 0)
		usleep(rules->time_eat);
	while (!(rules->dieded))
	{
		eat_philo(phi, rules);
		if ((phi->x_ate >= rules->nb_eat && rules->nb_eat != -1)
			|| rules->all_ate)
			break ;
		action_print(rules, phi->id, "is sleeping");
		smart_sleep(rules->time_sleep, rules);
		action_print(rules, phi->id, "is thinking");
	}
	return (NULL);
}

static void	death_check(t_rules *r, t_philo *p)
{
	int	i;

	while (!(r->all_ate) && !(r->dieded))
	{
		i = -1;
		while (++i < r->nb_philo)
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(timestamp(), p[i].t_last_meal) > r->time_death)
			{
				action_print(r, i, "died");
				r->dieded = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
		}
		if (r->dieded)
			break ;
		i = 0;
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}

static void	exit_launcher(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nb_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->meal_check));
	pthread_mutex_destroy(&(rules->writing));
}

int	launcher(t_rules *rules)
{
	t_philo	*phi;
	int		i;

	i = 0;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, pthread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_check(rules, phi);
	exit_launcher(rules, phi);
	return (0);
}
