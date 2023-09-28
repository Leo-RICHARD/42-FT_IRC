/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:37:21 by astucky           #+#    #+#             */
/*   Updated: 2022/10/29 15:57:02 by pmillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>
#include <cerrno>

Server::Server(unsigned short prt, std::string const pswd) : _port(prt), _password(pswd)
{
	_nbClients = 0;

	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw (SocketErrorException());
	int option = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	if (fcntl(_socket, F_SETFL, O_NONBLOCK) == -1)
		throw (FctnlErrorException());

	_info.sin_family = AF_INET;
	_info.sin_addr.s_addr = INADDR_ANY;
	_info.sin_port = htons(_port);

	if (bind(_socket, (struct sockaddr *)&_info, sizeof(_info)))
		throw (BindingErrorException());
	if (listen(_socket, 3))
		throw (ListeningErrorException());

	_nfd = _socket + 1;
	the_filling_tab_function();
}

Server::Server(void)
{
	_nbClients = 0;
	the_filling_tab_function();
}

void Server::the_filling_tab_function()
{
	_cmds_list[0] = "pass";
	_commands[0] = &Server::pass;
	_cmds_list[1] = "nick";
	_commands[1] = &Server::nick;
	_cmds_list[2] = "user";
	_commands[2] = &Server::user;
	_cmds_list[3] = "quit";
	_commands[3] = &Server::quit;
	_cmds_list[4] = "join";
	_commands[4] = &Server::join;
	_cmds_list[5] = "part";
	_commands[5] = &Server::part;
	_cmds_list[6] = "mode";
	_commands[6] = &Server::mode;
	_cmds_list[7] = "invite";
	_commands[7] = &Server::invite;
	_cmds_list[8] = "kick";
	_commands[8] = &Server::kick;
	_cmds_list[9] = "privmsg";
	_commands[9] = &Server::privmsg;
	_cmds_list[10] = "ping";
	_commands[10] = &Server::ping;
	_cmds_list[11] = "notice";
	_commands[11] = &Server::notice;
	_cmds_list[12] = "topic";
	_commands[12] = &Server::topic;
}

Server::~Server()
{
	for (std::vector<Client *>::iterator it = _clientList.begin(); it < _clientList.end(); it++)
		delete *it;
	_clientList.clear();

	for (std::vector<Channel *>::iterator it = _channels.begin(); it < _channels.end(); it++)
		delete *it;
	_channels.clear();
	close(_socket);
}

const std::string &Server::get_pass(void) const
{
	return _password;
}

Client *Server::get_client(std::string const &name)
{
	Client *c;
	for (std::vector<Client *>::iterator it = _clientList.begin(); it < _clientList.end(); it++)
	{
		c = *it;
		if (lowercase(c->get_nickname()) == lowercase(name))
			return (c);
	}
	return (0);
}

Channel	*Server::get_chan(std::string const &name)
{
	if (_channels.size() == 0)
		return (0);
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		if (lowercase((*it)->get_name()) == lowercase(name))
			return (*it);
	return (0);
}

void	Server::checkport(const char *port)
{
	for (int i = 0; port[i]; i++)
		if (!isdigit(port[i]))
			throw(InvalidPortException());
	if (!port[0] || std::atoi(port) > 65535 || std::string(port).length() > 6)
		throw(InvalidPortException());
}

bool	Server::add_client(void)
{
	int info_len = sizeof(_info);
	int newfd = 0;

	newfd = accept(_socket, (struct sockaddr *)&_info, (socklen_t *)&info_len);

	if (newfd < 0)
	{
		std::cerr << "Error: could not accept new client" << std::endl;
		return 0;
	}

	_clientList.push_back(new Client(newfd, this, _info));
	_nbClients++;
	FD_SET(newfd, &_readfds);
	if (newfd >= _nfd)
		_nfd = newfd + 1;
	return 1;
}

void	Server::remove_client(std::vector<Client *>::iterator cursor)
{
	FD_CLR((*cursor)->get_sd(), &_readfds);
	delete *cursor;

	_clientList.erase(cursor);
	_nbClients--;
}

void	Server::send_message(Client *c, const std::string &message)
{
	send(c->get_sd(), message.c_str(), message.length(), 0);
}

void	Server::safe_quit(Client * c)
{
	std::vector<std::string> message_split;

	message_split.push_back("QUIT");
	message_split.push_back(":Client has been disconnected.");
	(this->*(_commands[3]))(message_split, c);
}

void	Server::run(void)
{
	Client *c;
	std::cout << "port = " << _port << std::endl;
	std::cout << "password = " << _password << std::endl;

	FD_ZERO(&_readfds);
	FD_SET(_socket, &_readfds);
	fd_set	cpy;
	FD_ZERO(&cpy);
	char r[500];
	int len;

	while (1)
	{		
		cpy = _readfds;

		if ((select(_nfd, &cpy, 0, 0, 0)) < 0)
		{
			if (errno==EINTR)
				std::cerr << "Select syscall encountered an error" << std::endl;
			else
				std::cerr << "timeout select" << std::endl;
			return ;
		}
		if (FD_ISSET(_socket, &cpy) && !add_client())
			return ;
		for (std::vector<Client *>::iterator it = _clientList.begin(); it < _clientList.end(); it++)
		{
			c = *it;

			if (FD_ISSET(c->get_sd(), &cpy))
			{
				len = read(c->get_sd(), r, 49);
				if (!len)
					safe_quit((*it));
				else
				{
					r[len] = 0;
					parse(r, it);
				}
			}
		}
	}
}

void	Server::remove_channel(Channel *channel)
{
	std::vector<Channel *>::iterator it;
	for (it = this->_channels.begin(); it < this->_channels.end(); it++)
	{
		if (channel == (*it))
		{
			delete (*it);
			_channels.erase(it);
		}
	}
}
