/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 00:13:29 by napark            #+#    #+#             */
/*   Updated: 2021/12/29 23:54:23 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_exit_arg(char *args[])
{
	int	i;
	int	j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (ft_issign(args[i][j]))
				j++;
			if (!ft_isdigit(args[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	exit_inbuilt(char *args[])
{
	long	exit_code;
	int		i;

	i = 0;
	if (ft_strncmp(args[i], "exit", ft_strlen(args[i])) != 0)
		return (EXIT_FAILURE);
	i++;
	if (args[i])
		exit_code = ft_atol(args[i]);
	else
		exit_code = get_err_code();
	if (!is_valid_exit_arg(args + i) || ft_strlen(args[i]) > 19)
	{
		ft_fprintf(STDERR_FILENO, "exit: not a valid argument\n");
		exit_code = 255;
	}
	else if (args[i] && args[++i])
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		ft_fprintf(STDERR_FILENO, "exit\n");
		return (EXIT_FAILURE);
	}
	ft_fprintf(STDERR_FILENO, "exit\n");
	exit(exit_code);
	return (exit_code);
}
