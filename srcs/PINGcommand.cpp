/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PINGcommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:22:01 by lrichard          #+#    #+#             */
/*   Updated: 2022/09/26 13:34:14 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	Server::ping(std::vector<std::string> message_split, Client *c)
{
    send_message(c, "PONG\r\n");
    (void) message_split;
}