/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 13:45:38 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/22 14:53:21 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_file_error(t_error err)
{
	if (err == ERR_ARGS)
		ft_putstr_fd("Usage: ./cub3D <map.cub>", 2);
	else if (err == ERR_EXT)
		ft_putstr_fd("File must have a .cub extension", 2);
	else if (err == ERR_OPEN)
		ft_putstr_fd(strerror(errno), 2);
	else if (err == ERR_READ)
		ft_putstr_fd("Could not read the file", 2);
	else if (err == ERR_EMPTY)
		ft_putstr_fd("Empty file", 2);
	else if (err == ERR_MALLOC)
		ft_putstr_fd("Memory allocation failed", 2);
}

static void	put_element_error(t_error err)
{
	if (err == ERR_ELEMENT)
		ft_putstr_fd("Invalid line (unknown or badly formatted element)", 2);
	else if (err == ERR_MISSING_ELEMENT)
		ft_putstr_fd("Not all elements were defined", 2);
	else if (err == ERR_DUP_ELEMENT)
		ft_putstr_fd("Element defined more than once", 2);
	else if (err == ERR_TEXTURE)
		ft_putstr_fd("Invalid texture (format, extension or file)", 2);
	else if (err == ERR_COLOR)
		ft_putstr_fd("Invalid color (expected R,G,B with values 0-255)", 2);
}

static void	put_map_error(t_error err)
{
	if (err == ERR_NO_MAP)
		ft_putstr_fd("No map found in file", 2);
	else if (err == ERR_MAP_CHAR)
		ft_putstr_fd("Invalid character in the map", 2);
	else if (err == ERR_MULTIPLE_OR_NO_PLAYER)
		ft_putstr_fd("Exactly one player position is required", 2);
	else if (err == ERR_MAP_OPEN)
		ft_putstr_fd("Map is not surrounded by walls", 2);
	else if (err == ERR_MAP_NOT_LAST)
		ft_putstr_fd("Map is not the last element in the file", 2);
}

int	print_error(t_error err)
{
	ft_putstr_fd("Error\n", 2);
	put_file_error(err);
	put_element_error(err);
	put_map_error(err);
	ft_putstr_fd("\n", 2);
	return (1);
}
