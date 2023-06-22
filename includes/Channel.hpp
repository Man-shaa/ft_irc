/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:10 by ajeanne           #+#    #+#             */
/*   Updated: 2023/06/22 19:55:09 by ccheyrou         ###   ########.fr       */
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
		Channel(); 
		Channel(std::string name, Client& owner);
		~Channel(void);

		std::string					getName(void) const;
		std::string					getTopic(void) const;
		std::vector<std::string>	getUsrList(void) const;
		
		void		setLogMsg(std::string logMsg);
		void		setTopic(std::string topic);
		void 		setPassword(std::string password);
		void		setSecured(bool	secured);

		void		addUser(Client &user);
		void		addModo(Client &user);
		void		remUser(Client &user);
		void		remModo(Client &user);
		//void		sendMsg(std::string msg, Client &user) const;

	private:
		
		std::string					_name;
		std::string					_logMsg;
		std::string					_topic;
		std::string					_password;
		bool						_secured;
		int							_owner;
		std::map<int, Client*> 	_usrList;
		std::map<int, Client*>	_modoList;
};

#endif