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

// I didn't ask for this...

#include "../include/pipex.h"
#include "../include/defs.h"

char	*get_path_env(char *env[])
{
	const char	*p_str;
	int			iterator;

	iterator = 0;
	while (ft_strncmp(p_str, env[iterator], ft_strlen(p_str)))
	{
		iterator++;
		if (!env[iterator + 1])
			return (NULL);
	}
	return (env[iterator]);
}

char	*get_path(char *prog_n, char *env[])
{
	static char	*path_env;
	char		*abs_path;
	char		**exec_direcs;
	int			iter;

	if (!path_env)
		path_env = get_path_env(env);
	exec_direcs = ft_split(path_env, ':');
	while(exec_direcs[iter] != NULL)
	{
		abs_path = ft_strjoin(prog_n, exec_direcs[iter]);
		if (!access(abs_path, F_OK))
		{
			free(exec_direcs);
			return (abs_path);
		}
		free(abs_path);
		iter++;
	}
	free
	return ();
}
