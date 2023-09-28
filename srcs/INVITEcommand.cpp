/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITEcommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:20:14 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 16:19:44 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

bool	check_channel(Client *c, Client *dest, Channel *subject, std::vector<std::string> args_split)
{
	if (!subject)
	{
		std::string msg = ":" + c->get_nickname() + " INVITE " + dest->get_nickname() + " " + args_split[1] + "\r\n";
		Server::send_message(dest, msg);
		Server::send_message(c, RPL_INVITING(c->get_nickname(), args_split[0], args_split[1]));
	}
	else if (!subject->get_member(c->get_nickname()))
		Server::send_message(c, ERR_NOTONCHANNEL(args_split[1]));
	else if (subject->get_member(args_split[0]) == dest)
		Server::send_message(c, ERR_USERONCHANNEL(args_split[0], args_split[1]));
	else if (subject->is_invite_only() && !subject->is_operator(c))
		Server::send_message(c, ERR_CHANOPRIVSNEEDED(args_split[1]));
	else
		return (1);
	return (0);
}

void	Server::invite(std::vector<std::string> message_split, Client *c)
{
	std::vector<std::string> args_split = split_args(message_split[1]);
	if (args_split.size() != 2)
	{
		send_message(c, ERR_NEEDMOREPARAMS("INVITE"));
		return;
	}
	Client *dest = get_client(args_split[0]);
	Channel *subject = get_chan(args_split[1]);
	if (!dest)
		send_message(c, ERR_NOSUCHNICK(args_split[0]));
	else if (check_channel(c, dest, subject, args_split))
	{
		dest->invite(subject);
		std::string msg = ":" + c->get_nickname() + " INVITE " + dest->get_nickname() + " " + subject->get_name() + "\r\n";
		send_message(dest, msg);
		send_message(c, RPL_INVITING(c->get_nickname(), args_split[0], args_split[1]));
	}
}
