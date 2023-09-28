/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:37:28 by astucky           #+#    #+#             */
/*   Updated: 2022/10/29 17:10:07 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	irc(unsigned short port, std::string password)
{
	Server *server;
	try
	{
		server = new Server(port, password);
	}
	catch (std::exception &e)
	{
		if (server)
			delete server;
		std::cerr << e.what() << std::endl;
		return ;
	}

	try
	{
		server->run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}	
	delete server;
}
