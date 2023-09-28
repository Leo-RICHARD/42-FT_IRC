/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USERcommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:22:13 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 19:51:29 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	Server::user(std::vector<std::string> message_split, Client *c)
{    
    std::vector<std::string> args_split = split_args(message_split[1]);
    if (args_split.size() < 4 || args_split[3][0] != ':')
    {
	    send_message(c, ERR_NEEDMOREPARAMS(message_split[0]));
	    return ;
    }
    c->set_username(args_split[0], args_split[1], args_split[2], args_split[3]);
}
