/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:16:31 by astucky           #+#    #+#             */
/*   Updated: 2022/10/28 19:30:22 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Client.hpp>

Client::Client(int sd, Server *serv, sockaddr_in address) : _sd(sd), _password(false), _address(address)
{
	_serv = serv;
	_nickname = "";
	_user.username = "";
	_user.hostname = "";
	_user.servername = "";
	_user.realname = "";
	_buffer = "";
	_channels_joined = 0;
}

Client::~Client()
{
	close(_sd);
}

user Client::get_username() const
{
	return (_user);
}

std::string Client::get_username_only() const
{
	return (_user.username);
}

std::string Client::get_nickname() const
{
	return (_nickname);
}

int	Client::get_sd() const
{
	return (_sd);
}

bool	Client::get_pass(void) const
{
	return (_password);
}

std::string	Client::get_ip() const
{
	std::string ip = inet_ntoa(_address.sin_addr);
	return ip;
}

std::vector<Channel *>	Client::get_channels(void) const
{
	return (_channels);
}

bool	Client::is_registered() const
{
	if (!_password || _nickname.empty() || \
			_user.username.empty() || _user.hostname.empty() || \
			_user.servername.empty() || _user.realname.empty())
		return (false);
	return (true);
}

bool	Client::can_still_join() const
{
    if (_channels_joined < 11)
		return (true);
    else
		return (false);
}

void	Client::set_username(std::string const &usr, std::string const &host, std::string const &server, std::string const &real)
{
	_user.username = usr;
	_user.hostname = host;
	_user.servername = server;
	_user.realname = real;
}

void	Client::set_nickname(std::string const &str)
{
	_nickname = str;
}

void	Client::set_sd(int const &descriptor)
{
	_sd = descriptor;
}

void	Client::set_pass(bool pass)
{
	_password = pass;
}

void	Client::join_channel(Channel *c)
{
	_channels.push_back(c);
	_channels_joined++;
}

void	Client::leave_channel(Channel *c)
{
	c->remove_member(this);

	std::vector<Channel *>::iterator it = std::find(_channels.begin(), _channels.end(), c);
	if (it != _channels.end())
	{
		_channels.erase(it);
		_channels_joined--;
	}
}

void	Client::add_to_buffer(const std::string &input)
{
	_buffer += input;
}

const std::string	Client::get_request(void)
{
	size_t len = _buffer.find("\r\n");
	if (len != std::string::npos)
	{
		std::string ret = _buffer.substr(0, len);
		_buffer = _buffer.substr(len + 2);
		return (ret);
	}
	return ("");
}

void	Client::invite(Channel *c)
{
	if (std::find(_invited.begin(), _invited.end(), c) == _invited.end())
		_invited.push_back(c);
}

bool	Client::is_invited(Channel *c)
{
	return (std::find(_invited.begin(), _invited.end(), c) != _invited.end());
}

void	Client::remove_invite(Channel *c)
{
	std::vector<Channel *>::iterator it = std::find(_invited.begin(), _invited.end(), c);
	if (it != _invited.end())
		_invited.erase(it);
}
