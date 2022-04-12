/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CODAM C FILE                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire     ########   codam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
THIS FILE IS LICENSED UNDER THE GNU GPLv3
Copyright (C) 2022  Will Maguire

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>

The definition of Free Software is as follows:
				- The freedom to run the program, for any purpose.
				- The freedom to study how the program works, and adapt it to your needs.
				- The freedom to redistribute copies so you can help your neighbor.
				- The freedom to improve the program, and release
				your improvements to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

/* No matter where you go, every process is connected... */

#include "../include/pipex.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int 	fd[2];
	int		pid;
	char	c;

	if (argc != ARG_LIMIT)
	{
		ft_printf("Invalid number of arguments!\n");
		return (EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		err_exit("PLUMBING ERROR (main)");
	pid = fork();
	if (pid == -1)
		err_exit("fork() failed (main):");
	if (!pid)
	{
		dup2(fd[READ], STDIN_FILENO);
		close(fd[WRITE]);
		while (read(STDIN_FILENO, &c, 1) != EOF)
		{
			ft_putchar(c);
		}
		ft_putchar('\n');
	}
	if (pid)
	{
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[READ]);
		ft_printf("Hello from parent process! %s", argv[1]);
		close(fd[WRITE]);
	}
	return (EXIT_SUCCESS);
}
