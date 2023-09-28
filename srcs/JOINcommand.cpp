/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOINcommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:20:40 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 19:59:21 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

void	Server::parse_join_chan(Channel * chan, std::vector<std::string> args_split, Client *c, int i)
{
	if (!c->can_still_join())
		send_message(c, ERR_TOOMANYCHANNELS(chan->get_name()));
	else if (!chan->has_room())
		send_message(c, ERR_CHANNELISFULL(chan->get_name()));
	else if (chan->is_invite_only() && !c->is_invited(chan))
		send_message(c, ERR_INVITEONLYCHAN(chan->get_name()));
	else if (!chan->get_member(c->get_nickname()))
	{
		if (c->is_invited(chan))
			c->remove_invite(chan);
		chan->add_member(c, 0);
		c->join_channel(chan);
		std::string msg = ":" + c->get_nickname() + "!" + c->get_username_only() + "@" + c->get_ip() + " JOIN " + args_split[i] + "\r\n";
		chan->msg_everyone(msg, "");
		if (chan->get_topic() != "")
			send_message(c, RPL_TOPIC(c->get_nickname(), chan->get_name(), chan->get_topic()));
		else
			send_message(c, RPL_NOTOPIC(c->get_nickname(), chan->get_name()));
		std::string name_list;
		std::vector< std::pair<Client *, bool> > members;
		members = chan->get_all_members();
		for (std::vector< std::pair<Client *, bool> >::iterator it = members.begin(); it < members.end(); it++)
		{
			if ((*it).second)
				name_list += '@';
			name_list += (*it).first->get_nickname();
			if (it < chan->get_all_members().end() - 1)
				name_list += ' ';
		}
		send_message(c, RPL_NAMREPLY(c->get_nickname(), chan->get_name(), name_list));
	}
}

void	Server::join(std::vector<std::string> message_split, Client *c)
{
	Channel *chan;

	if (message_split[1].empty())
	{
		send_message(c, ERR_NEEDMOREPARAMS(message_split[0]));
		return ;
	}

	std::vector<std::string> args_split = split_by_comma(message_split[1]);
	int len = args_split.size();
	for (int i = 0; i < len; i++)
	{
		if (args_split[i].find(' ') != std::string::npos)
		{
			send_message(c, ERR_NOSUCHCHANNEL(args_split[i]));
			return;			
		}
		chan = get_chan(args_split[i]);
		if (chan)
		{
			if(chan->get_member(c->get_nickname()))
				return;
			parse_join_chan(chan, args_split, c, i);
		}
		else
		{
			if (!c->can_still_join())
				send_message(c, ERR_TOOMANYCHANNELS(args_split[i]));
			else try
			{				
				chan = new Channel(args_split[i]);

				_channels.push_back(chan);
				chan->add_member(c, 1);
				c->join_channel(chan);
				std::string msg = ":" + c->get_nickname() + "!" + c->get_username_only() + "@" + c->get_ip() + " JOIN " + args_split[i] + "\r\n";
				chan->msg_everyone(msg, "");
				send_message(c, RPL_NAMREPLY(c->get_nickname(), chan->get_name(), ("@" + c->get_nickname())));
				send_message(c, RPL_NOTOPIC(c->get_nickname(), chan->get_name()));
			}
			catch (std::exception &e)
			{
				send_message(c, ERR_NOSUCHCHANNEL(args_split[i]));
				return;
			}
		}
	}
}
