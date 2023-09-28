/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODEcommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:20:53 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 17:46:07 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

std::string	Server::get_modes(Channel *chan)
{
	std::string modes;

	if(chan->is_invite_only())
		modes.push_back('i');
	
	if(int total = chan->get_op_nbr())
	{
		modes += "o ";
		int i = 0;
		std::vector<std::pair<Client *, bool> > member_list = chan->get_all_members();
		for(std::vector<std::pair<Client *, bool> >::iterator it = member_list.begin(); it < member_list.end(); it++)
		{
			if ((*it).second)
			{
				modes += (*it).first->get_nickname();
				i++;
			}
			if (i < total)
				modes.push_back(',');
		}
	}
	return (modes);
}

void	Server::oper_mode_minus(std::vector<std::string> args_split, Channel *chan, Client *c, Client *target)
{
	std::vector< std::pair<Client *, bool> > member_list = chan->get_all_members();
		if (args_split[2] != c->get_nickname())
			return;
		else if (member_list.size() > 1)
			chan->set_op(target, false);
		if (!chan->get_op_nbr() && (member_list.size() > 1))
		{
			if(member_list.begin()->first->get_nickname() != c->get_nickname())
				chan->set_op(member_list.begin()->first, true);
			else
				chan->set_op((++member_list.begin())->first, true);
		}
}

void	Server::oper_mode(std::vector<std::string> args_split, Channel *chan, Client *c)
{
	Client *target;

	if ((target = chan->get_member(args_split[2])) == NULL)
		send_message(c, ERR_NOSUCHNICK(args_split[2]));
	else if (args_split[1].find('+') != std::string::npos)
			chan->set_op(target, true);
	else if (args_split[1].find('-') != std::string::npos)
		oper_mode_minus(args_split, chan, c, target);
}

void	Server::invite_mode(std::vector<std::string> args_split, Channel *chan)
{
	if (args_split[1].find('+') != std::string::npos)
		chan->set_invite_only(true);
	else if (args_split[1].find('-') != std::string::npos)
		chan->set_invite_only(false);
}

bool	Server::parse_mode(std::vector<std::string> message_split, std::vector<std::string> args_split, Client *c, Channel **chan)
{
	if (message_split[1].empty())
		send_message(c, ERR_NEEDMOREPARAMS(message_split[0]));
	else if ((*chan = get_chan(args_split[0])))
	{
		if ((*chan)->get_member(c->get_nickname()) == NULL)
			send_message(c, ERR_NOTONCHANNEL((*chan)->get_name()));
		else if (args_split.size() <= 1)
			send_message(c, RPL_CHANNELMODEIS((*chan)->get_name(), get_modes(*chan)));
		else if ((args_split[1].find('o') != std::string::npos && args_split.size() != 3) || \
		(args_split[1].find('i') != std::string::npos && args_split.size() != 2))
			send_message(c, ERR_NEEDMOREPARAMS(message_split[0]));
		else if ((args_split.size() == 2 && (args_split[1].compare("+i") != 0 && args_split[1].compare("-i") != 0)) || \
		(args_split.size() == 3 && (args_split[1].find("+o") != 0 && args_split[1].find("-o") != 0)))
			send_message(c, ERR_UNKNOWNMODE(args_split[1]));
		else if (!(*chan)->is_operator(c))
			send_message(c, ERR_CHANOPRIVSNEEDED((*chan)->get_name()));
		else
			return (1);
	}
	else
		send_message(c, ERR_NOSUCHCHANNEL(args_split[0]));
	return (0);
}

void	Server::mode(std::vector<std::string> message_split, Client *c)
{
	Channel *chan = NULL;
	std::vector<std::string> args_split = split_args(message_split[1]);
	if (!parse_mode(message_split, args_split, c, &chan))
		return;
	
	if (args_split[1].find('i') != std::string::npos && args_split.size() == 2)
		invite_mode(args_split, chan);
	else if (args_split[1].find('o') != std::string::npos && args_split.size() == 3)
		oper_mode(args_split, chan, c);
	else
		send_message(c, ERR_UNKNOWNMODE(args_split[1]));
}
