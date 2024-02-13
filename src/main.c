/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:33:34 by nathan            #+#    #+#             */
/*   Updated: 2024/02/13 15:20:13 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		error;

	if (argc != 5 && argc != 6)
		return (write_error("Number of argument"));
	error = init_all(&rules, argv);
	if (error)
		return (error_manager(error));
	if (launcher(&rules))
		return (write_error("Creating thread"));
	return (0);
}
