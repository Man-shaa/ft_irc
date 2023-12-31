/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 21:22:10 by ajeanne           #+#    #+#             */
/*   Updated: 2023/08/08 16:29:11 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# define CHANLIMIT 24
# include <ctime>
# include "Client.hpp"

class Client;

class	Channel
{
	private:

		std::string					_creationTime;
		std::string					_setat;
		std::string					_name;
		std::string					_logMsg;
		std::string					_topic;
		std::string					_password;
		bool						_secured;
		int							_owner;
		int							_maxUsr;
		std::map<int, Client*> 		_usrList;
		std::map<int, Client*>		_OpeList;
		std::map<char, bool> 		_mode;

	public:

		Channel(); 
		Channel(std::string name, Client& owner);
		~Channel(void);

		std::string					getCreationTime(void) const;
		std::string					getSetat(void) const;
		std::string					getName(void) const;
		std::string					getPassword(void) const;
		std::string					getTopic(void) const;
		std::string 				getModeChannel(void) const;
		std::vector<std::string>	getUsrList(void);
		std::vector<std::string>	getOpeList(void) const;
		int							getOwner(void) const;
		bool						getSecured(void) const;
		int    						getUserNumber(void) const;
		int							getMaxUsr(void) const;
		std::map<int, Client*>		getUsrListMap(void);
		int							getOpNumber(void) const;


		void						setLogMsg(std::string logMsg);
		int							setTopic(std::string topic, Client &user);
		void 						setPassword(std::string password, bool change);
		void						setSecured(bool	secured);
		void						setMode(bool active, char i);
		int							setMaxUsr(int maxUsr, bool change);

		void						addUser(Client &user);
		void						addModo(Client &user);
		int							remUser(Client &user);
		void						remOperator(Client &user);
		void						sendMsg(std::string msg, Client &user) const;
		void						sendMsgNoBot(std::string msg, Client &user) const;
		void						sendMsgOpe(std::string msg, Client &user) const;
		void						sendMode(std::string msg, Client &client) const;
		void						sendTopic(std::string msg, Client &user) const;
		void						sendMsgToChannel(std::string msg) const;

		int							clientIsOp(int socket) const;
		int							isChannelInviteOnly() const;
};

#endif
