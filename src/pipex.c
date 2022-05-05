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

/* Executes a program with input and output fds as specified in arguments. */
static void	exec_pipe(int i_fd, int o_fd, char *prog_n, char *env[])
{
	char	**args;
	char	*path;

	args = ft_split(prog_n, ' ');
	if (ft_strnstr(args[0], "/", ft_strlen(args[0])))
		path = args[0];
	else
		path = get_path(args[0], env);
	if (!path)
	{
		ft_printf("%s: Unable to find path to executable\n", args[0]);
		free_ptr_array(args);
		exit(EXIT_FAILURE);
	}
	dup2(i_fd, STDIN_FILENO);
	dup2(o_fd, STDOUT_FILENO);
	if (execve(path, args, env) == -1)
		err_exit(path, EXIT_FAILURE);
}

/* Main function handling pipes and forking, as well as input/output files.  */
static void	fork_and_pipe(char *argv[], char *env[], int i_file, int o_file)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		err_exit("PLUMBING ERROR IN (fork_and_pipe)", EXIT_FAILURE);
	pid = fork();
	if (pid == FORK_FAILURE)
		err_exit("SPOON AT (fork_and_pipe)", EXIT_FAILURE);
	if (pid == FORK_CHILD)
	{
		close(fd[WRITE]);
		exec_pipe(fd[READ], o_file, argv[3], env);
	}
	close(fd[READ]);
	exec_pipe(i_file, fd[WRITE], argv[2], env);
}

/* Handles the opening of the input/output file descriptors */
/* before executing the piping. */
int	main(int argc, char *argv[], char *env[])
{
	int	i_file;
	int	o_file;

	if (argc != ARG_LIMIT)
	{
		ft_putstr_fd("INSUFFICIENT ARGUMENTS\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	i_file = open(argv[1], O_RDONLY);
	if (i_file == -1)
		err_exit(argv[1], EXIT_FAILURE);
	o_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (o_file == -1)
		err_exit(argv[4], EXIT_FAILURE);
	fork_and_pipe(argv, env, i_file, o_file);
}
