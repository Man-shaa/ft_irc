/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeanne <ajeanne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:10 by ajeanne           #+#    #+#             */
/*   Updated: 2023/06/20 23:39:15 by ajeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# define CHANLIMIT 24

# include "Client.hpp"

class Client;

class	Channel	{
	
	public:

		Channel(void);
		Channel(std::string name, Client &owner);
		~Channel(void);

		std::string			getName(void) const;
		std::vector<Client>	getUsrList(void) const;
		
		void		setLogMsg(std::string logMsg);
		void		setTopic(std::string topic);
		void 		setPassword(std::string password);
		void		setSecured(bool	secured);

		void		addUser(Client &user);
		void		addModo(Client &user);
		void		remUser(Client &user);
		void		remModo(Client &user);
		void		sendMsg(std::string msg, Client &user) const;

	private:
		
		std::string			_name;
		std::string			_logMsg;
		std::string			_topic;
		std::string			_password;
		bool				_secured;
		Client				*_owner;
		std::vector<Client> _usrList;
		std::vector<Client>	_modoList;
};

#endif