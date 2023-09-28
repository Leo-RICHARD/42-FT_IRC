/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:23:19 by lrichard          #+#    #+#             */
/*   Updated: 2022/10/28 19:34:12 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_irc.hpp>

Channel::Channel(std::string const &name) : _members(), _invite_only(false), _topic("")
{
	if (checkname(name))
		_name = name;
	else
		throw(std::exception());
	_capacity = 1000;
}

Channel::~Channel()
{
}

bool	Channel::checkname(std::string const &name) const
{
	std::string s(1, 7);

	if (name[0] != '#' || \
			name.size() > 200 || \
			name.find_first_of(" ," + s) != std::string::npos)
		return (false);
	return (true);
}

// Getters
std::string	Channel::get_name() const
{
	return (_name); 
}

std::vector<std::pair <Client *, bool> >	Channel::get_all_members() const
{
	return (_members);
}

Client	*Channel::get_member(std::string const &name)
{
	if (_members.size() == 0)
		return (0);
	for (std::vector< std::pair<Client *, bool> >::iterator it = _members.begin(); it != _members.end(); it++)
			if (lowercase((*it).first->get_nickname()) == lowercase(name))
				return ((*it).first);
	return (0); 
}

bool	Channel::has_room() const
{
	if (_capacity)
		return (true);
	else
		return (false);
}

int		Channel::get_op_nbr()
{
	int ret = 0;
	for (std::vector< std::pair<Client*, bool> >::iterator it = _members.begin(); it < _members.end(); it++)
	{
		if ((*it).second)
			ret++;
	}
	return (ret);
}

bool	Channel::is_invite_only() const
{
	if (_invite_only)
		return (true);
	else
		return (false);
}

std::string	Channel::get_topic() const
{
	return _topic;
}

bool	Channel::is_operator(Client *c) const
{
	return (std::find(_members.begin(), _members.end(), std::make_pair(c, true)) != _members.end());
}

// Setters
void	Channel::add_member(Client *newMember, bool op)
{
	_members.push_back(std::make_pair(newMember, op));
	_capacity--;
}

void	Channel::set_topic(std::string const &new_topic)
{
	_topic = new_topic;
}

void	Channel::remove_member(Client *member)
{
	for (std::vector<std::pair <Client *, bool > >::iterator it = _members.begin(); it != _members.end(); it++)
		if (lowercase((*it).first->get_nickname()) == lowercase(member->get_nickname()))
		{
			_members.erase(it);
			break;
		}
	_capacity++;

	if (!get_op_nbr() && _members.size())
		(_members.begin())->second = 1;
}

void	Channel::set_invite_only(bool val)
{
	_invite_only = val;
}

void	Channel::set_op(Client *op, bool val)
{
	bool old_val = !val;

	if (val)
		old_val = false;
	std::vector<std::pair<Client *, bool> >::iterator it = find(_members.begin(), _members.end(), std::make_pair(op, old_val));
	if (it == _members.end())
		return;
	(*it).second = val;
}

// Other
void	Channel::msg_everyone(std::string message, std::string sender_nick)
{	
	for (std::vector< std::pair<Client*, bool> >::iterator it = _members.begin(); it != _members.end(); it++)
		if (sender_nick != (*it).first->get_nickname())
			Server::send_message((*it).first, message);
}
