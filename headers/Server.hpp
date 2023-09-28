/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmillet <pmillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:37:24 by astucky           #+#    #+#             */
/*   Updated: 2022/10/28 18:23:37 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ft_irc.hpp>

class	Server
{
	private:

		unsigned short			_port;
		std::string				_password;
		int						_socket;
		std::vector<Client *>	_clientList;
		int						_nbClients;
		int						_nfd;
		struct sockaddr_in		_info;
		fd_set					_readfds;
		void (Server::*_commands[13])(std::vector<std::string>, Client *);
		std::string				_cmds_list[13];
		std::vector<Channel *>	_channels;
		
		void						send_message_to_chan(std::string arg_chan, std::string text, Client *c);
		void						safe_quit(Client * c);
		void						msg_quit(std::vector<std::string> message_split, Client *c, std::vector<Channel *>::iterator it_channel);
		std::vector<std::string>	part_parse(std::vector<std::string> message_split, Client *c);
		void						msg_part(std::vector<std::string> message_split, Client *c, Channel *chan);
		void						parse_kick(std::vector<std::string> args_split, std::vector<std::string> *chan_split, std::vector<std::string> *outcast_split, std::string *reason, Client *c);
		void						msg_kick(Channel *chan, std::string name, std::string reason, Client *c);
		bool						set_topic(Channel *chan, Client *c, std::string new_topic);
		void						invite_mode(std::vector<std::string> args_split, Channel *chan);
		void						oper_mode(std::vector<std::string> args_split, Channel *chan, Client *c);
		std::string					get_modes(Channel *chan);
		void						oper_mode_minus(std::vector<std::string> args_split, Channel *chan, Client *c, Client *target);
		bool						parse_mode(std::vector<std::string> message_split, std::vector<std::string> args_split, Client *c, Channel **chan);
		void						parse_join_chan(Channel * chan, std::vector<std::string> args_split, Client *c, int i);

	public :

		Server(unsigned short prt, std::string pswd);
		Server(void);
		~Server();
		void	the_filling_tab_function();

		const	std::string &get_pass(void) const;

		Client *					get_client(std::string const &name);
		Channel *					get_chan(std::string const &);
		static void					checkport(const char *port);
		bool						add_client(void);
		void						remove_client(std::vector<Client *>::iterator cursor);
		static void					send_message(Client *c, const std::string &message);
		void						run(void);
		void						parse(const std::string input, std::vector<Client *>::iterator c);
		void						remove_channel(Channel *channel);



		// list of commands

		void	pass(std::vector<std::string> message_split, Client *c);
		void	nick(std::vector<std::string> message_split, Client *c);
		void	user(std::vector<std::string> message_split, Client *c);
		void	quit(std::vector<std::string> message_split, Client *c);
		void	join(std::vector<std::string> message_split, Client *c);
		void	part(std::vector<std::string> message_split, Client *c);
		void	mode(std::vector<std::string> message_split, Client *c);
		void	invite(std::vector<std::string> message_split, Client *c);
		void	kick(std::vector<std::string> message_split, Client *c);
		void	privmsg(std::vector<std::string> message_split, Client *c);
		void	notice(std::vector<std::string> message_split, Client *c);
		void	ping(std::vector<std::string> message_split, Client *c);
		void	topic(std::vector<std::string> message_split, Client *c);

		class InvalidPortException : public std::exception
	{
		public :

			virtual const char *what() const throw()
			{
				return ("Invalid port number");
			}
	};
		class SocketErrorException : public std::exception
	{
		public :

			virtual const char *what() const throw()
			{
				return ("Unable to create socket");
			}
	};
		class BindingErrorException : public std::exception
	{
		public :

			virtual const char *what() const throw()
			{
				return ("Unable to bind socket");
			}
	};
		class ListeningErrorException : public std::exception
	{
		public :

			virtual const char *what() const throw()
			{
				return ("Unable to put socket on listen mode");
			}
	};

		class FctnlErrorException : public std::exception
	{
		public :

			virtual const char *what() const throw()
			{
				return ("Error with fcntl function");
			}
	};
};
