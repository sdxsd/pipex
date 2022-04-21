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
#include "../include/defs.h"

static int	file_to_pipe(char *file, int write_end)
{
	int		fd;
	int		c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FAILURE);
	while (read(fd, &c, 1) != 0)
		write(write_end, &c, write_end);
	close(fd);
	close(write_end);
	return (SUCCESS);
}

/* Executes a program with input and output fds as specified in arguments.  */
static void	exec_pipe(int i_fd, int o_fd, char *prog_n, char *env[])
{
	char	**args;
	char	*path;

	dup2(i_fd, STDIN_FILENO);
	dup2(o_fd, STDOUT_FILENO);
	args = ft_split(prog_n, ' ');
	path = get_path(args[0], env);
	if (!path)
		err_exit(prog_n);
	execve(path, args, env);
}

static int	fork_and_pipe(char *argv[], char *env[])
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		err_exit("PLUMBING ERROR IN (fork_and_pipe)");
	pid = fork();
	if (pid == FORK_FAILURE)
		err_exit("SPOON AT (fork_and_pipe)");
	if (pid == FORK_CHILD)
	{
		close(fd[WRITE]);
		exec_pipe(fd[READ], STDOUT_FILENO, argv[2], env);
	}
	if (!file_to_pipe(argv[1], fd[WRITE]))
		err_exit(argv[1]);
	close(fd[WRITE]);
	return (SUCCESS);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc != ARG_LIMIT)
		print_return("INSUFFICIENT ARGUMENTS\n", EXIT_FAILURE);
	fork_and_pipe(argv, env);
	waitpid(-1, NULL, WNOHANG);
	return (EXIT_SUCCESS);
}
