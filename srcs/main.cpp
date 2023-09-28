/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:59:32 by astucky           #+#    #+#             */
/*   Updated: 2022/10/28 18:32:26 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>
#include <Server.hpp>

int	main(int ac, char **av)
{
	if (ac != 3)
		std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
	else
	{
		try
		{
			Server::checkport(av[1]);
			irc(std::atoi(av[1]), av[2]);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	return (0);
}
