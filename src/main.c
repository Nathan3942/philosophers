/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:33:34 by nathan            #+#    #+#             */
/*   Updated: 2024/02/12 11:58:00 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_rules	rules;
	int		error;
	
	if (argc != 5 && argc != 6)
		return (writeError("Number of argument"));
	if ((error = initAll(&rules, argv)))
		return (errorManager(error));
	if (launcher(&rules))
		return (writeError("Creating thread"));
	return (0);
}