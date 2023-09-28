/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASScommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:45:15 by astucky           #+#    #+#             */
/*   Updated: 2022/10/28 17:54:47 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

void	Server::pass(std::vector<std::string> message_split, Client *c)
{
	if (message_split.size() == 1)
		send_message(c, ERR_NEEDMOREPARAMS("PASS"));
	else if (!_password.compare(message_split[1]))
		c->set_pass(1);
	else
		send_message(c, ERR_PASSWDMISMATCH);
}
