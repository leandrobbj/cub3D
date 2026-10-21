/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbraga <lbraga@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 15:51:04 by vascopinto        #+#    #+#             */
/*   Updated: 2026/10/21 19:46:24 by lbraga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_error	err;
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		return (print_error(ERR_ARGS));
	err = parse_file(argv[1], &game.setup);
	if (err != OK)
		return (print_error(err));
	start_cub3d(&game);
	free_config(&game.setup);
	return (0); // acho que devemos retornar 1 porque se chegou aqui foi erro
}
