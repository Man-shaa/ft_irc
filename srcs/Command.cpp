/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:41:05 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/28 20:05:56 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#define VALID_CHAR "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_"

void	Server::initCmd()
{
	_mapFcts["NICK"] = &Server::cmdNick;
	_mapFcts["USER"] = &Server::cmdUser;
	_mapFcts["JOIN"] = &Server::cmdJoin;
	_mapFcts["MODE"] = &Server::cmdMode;
	_mapFcts["PING"] = &Server::cmdPing;
	_mapFcts["PRIVMSG"] = &Server::cmdPrivmsg;
}

int		Server::cmdNick(std::vector<std::string> args, Client &client)
{
	// bool nicknameExist = false;
	
	// if (args.size() == 1 || args[0].empty)
	// {
	// 	std::string ERR_NONICKNAMEGIVEN =  "431 :No nickname given\r\n";
	// 	send(client.getSocket(), ERR_NONICKNAMEGIVEN.c_str(), ERR_NONICKNAMEGIVEN.size(), 0);
	//	voir pour le return	
	// }
	// //https://cplusplus.com/reference/string/string/find_first_not_of/ 
	// if (args[0].find_first_not_of(VALID_CHAR))
	// {
	// 	std::string ERR_ERRONEUSNICKNAME =  "42 " + args[0] + " :Erroneusnickname\r\n";
	// 	send(client.getSocket(), ERR_ERRONEUSNICKNAME.c_str(), ERR_ERRONEUSNICKNAME.size(), 0);	
	//	voir pour le return	
	// }
	// for (int i = 0; _clients[i]; ++i)
	// {
	// 	//nickname deja utilisé
	// 	if (_clients[i]->getNickname() == args[0])
	// 	{
	// 		nicknameExist = true;
	// 		std::string RPL_TOPIC =  "433 " + args[0] + " :Nickname is already in use\r\n";
	// 		send(client.getSocket(), RPL_TOPIC.c_str(), RPL_TOPIC.size(), 0);
	//		voir pour le return	
	// 	}
	// }
	// if (!nicknameExist)
	// {
		_clients[client.getId()]->setNickName(args[0]);
		std::string nick = ":" + client.getNickname() + " NICK " + args[0] + "\r\n";
		send(client.getSocket(), nick.c_str(), nick.size(), 0);
	//}
	return (0);
}

int		Server::cmdUser(std::vector<std::string> args, Client &client)
{
	//TODO Gérer le <realname> cf. https://modern.ircdocs.horse/#user-message
	//TODO Gérer le ERR_ALREADYREGISTERED :  "<client> :You may not reregister"
	//TODO Tronquer le username si il dépasse la taille de USERLEN = 12
	if (args[0].empty())
		args[0] = "default name";
	std::string answer = "001 " + client.getNickname() + " :Welcome to the Internet Relay Network " + args[0] + "\r\n";
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	return (0);
}

int		Server::cmdJoinRPL(std::string channel, Client &client, int i)
{
	//JOIN sent to client
	std::string JOIN = ":" + client.getNickname() + " JOIN " + channel + "\r\n";
	send(client.getSocket(), JOIN.c_str(), JOIN.size(), 0);

	//RPL_RPL_TOPIC sent to client
	std::string RPL_TOPIC =  "332 " + client.getNickname() + " " + channel + " :" + _channels[i]->getTopic() + "\r\n";
	send(client.getSocket(), RPL_TOPIC.c_str(), RPL_TOPIC.size(), 0);

	//RPL_NAMREPLY sent to client
	std::vector<std::string> listUsr = _channels[i]->getUsrList();
	std::string RPL_NAMREPLY = "353 " + client.getNickname() + " = " + channel + " :";
	for (std::vector<std::string>::const_iterator it = listUsr.begin(); it != listUsr.end(); ++it)
	{
		if (it == listUsr.begin())
			RPL_NAMREPLY += *it;
		else
			RPL_NAMREPLY += " " + *it;
	}
	RPL_NAMREPLY += "\r\n";
	std::cout << RPL_NAMREPLY << std::endl;
	send(client.getSocket(), RPL_NAMREPLY.c_str(), RPL_NAMREPLY.size(), 0);
	
	//RPL_ENDOFNAMES sent to client
	std::string RPL_ENDOFNAMES = "366 " + client.getNickname() + " " + channel + " :End of NAMES list\r\n";
	send(client.getSocket(), RPL_ENDOFNAMES.c_str(), RPL_ENDOFNAMES.size(), 0);
	
	client.addChannel(*_channels[i]);
	return (0);
}

int		Server::cmdJoin(std::vector<std::string> args, Client &client)
{
	//TODO Servers MAY restrict the number of channels a client may be joined to at one time cf. https://modern.ircdocs.horse/#chanlimit-parameter
	//TODO Definir le type de channel accepte cf.https://modern.ircdocs.horse/#chantypes-parameter
	bool channelExist = false;
	int i;
	
	for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
	{
		for (i = 0; _channels[i]; ++i) 
		{
			if (_channels[i]->getName() == *it)
			{
				channelExist = true;
				//Autorisation ou non d'y acceder
					//OUI
					_channels[i]->addUser(client);
					cmdJoinRPL(*it, client, i);
					std::cout << BLUE << client.getNickname() << " intègre le channel déjà existant " << CLOSE << *it << std::endl;
					//NON
			}
		}
		
		if (!channelExist)
		{
			createChannel(*it, client);
			std::cout << GREEN << client.getNickname() << " a crée un nouveau channel " << CLOSE << *it << std::endl;
			cmdJoinRPL(*it, client, i);
		}
	}

	//TEST voir les channels du client
	client.printAllClientChannel();
	return (0);
}

int		Server::cmdPrivmsg(std::vector<std::string> args, Client &client)
{
	//cf. https://modern.ircdocs.horse/#privmsg-message
	for (int i = 0; _channels[i]; ++i) 
	{
		if (_channels[i]->getName() == args[0])
		{
			std::string msg = ":" + client.getNickname() + " PRIVMSG " + args[0] + " " + args[1] + "\r\n";
			_channels[i]->sendMsg(msg, client);
			break;
		}
	}
	return (0);
}

int		Server::cmdPing(std::vector<std::string> args, Client &client)
{
	std::string pong = "server.name " + args[0] + "\r\n";
	send(client.getSocket(), pong.c_str(), pong.size(), 0);
	return (0);
}

int		Server::cmdMode(std::vector<std::string> args, Client &client)
{
	//TODO Gerer le mode client




	//TODO Gerer le mode server
	bool 	channelExist = false;
	int		i;
	
	if (args[0][0] == '#')
	{
		for (i = 0; _channels[i]; i++)
		{
			if (_channels[i]->getName() == args[0])
			{
				channelExist = true;
				break;
			}
		}
		if (!channelExist)
		{
			std::string ERR_NOSUCHCHANNEL = "403 " + client.getNickname() + ":No such channel\r\n";
			send(client.getSocket(), ERR_NOSUCHCHANNEL.c_str(), ERR_NOSUCHCHANNEL.size(), 0);
		}
		if (args.size() == 1 || args[1].empty())
		{
			std::string RPL_CHANNELMODEIS = "324 " + client.getNickname() + " " + args[0] + " " +  _channels[i]->getModeChannel() + "\r\n";
			send(client.getSocket(), RPL_CHANNELMODEIS.c_str(), RPL_CHANNELMODEIS.size(), 0);

			std::string RPL_CREATIONTIME = "329 " + client.getNickname() + " " + args[0] + " " + _channels[i]->getCreationTime() + "\r\n";
			send(client.getSocket(), RPL_CREATIONTIME.c_str(), RPL_CREATIONTIME.size(), 0);
		}
		else
		{
			if (client.getSocket() != _channels[i]->getOwner())
			{
				std::string ERR_CHANOPRIVSNEEDED = "482 " + client.getNickname() + args[0] + " :You're not channel operator\r\n";
				send(client.getSocket(), ERR_CHANOPRIVSNEEDED.c_str(), ERR_CHANOPRIVSNEEDED.size(), 0);	
			}
			else
			{
				std::string::size_type addPos = args[1].rfind('+');
				std::string::size_type delPos = args[1].rfind('-');
				
				if (addPos != std::string::npos)
				{
					addPos++;
					std::string modeAdd = args[1].substr(addPos);
					while (!modeAdd.empty() || modeAdd[0]!= '-')
					{
						if (modeAdd[0] == 'k' && !args[3].empty())
						{
							_channels[i]->setMode(true, i);
							_channels[i]->setPassword(args[3]);
							_channels[i]->setSecured(true);
						}
						else if (modeAdd[0] == 't')
							_channels[i]->setMode(true, i);
						else if (modeAdd[0] == 'i')
							_channels[i]->setMode(true, i);
						else if (modeAdd[0] == 'o' && !args[3].empty())
							_channels[i]->setMode(true, i);
						addPos++;
						modeAdd = args[1].substr(addPos);
					}
				}
				
				if (delPos != std::string::npos)
				{
					delPos++;
					std::string modeDel = args[1].substr(delPos);
					while (delPos < args[1].size() || modeDel[0] != '+')
					{
						modeDel = args[1].substr(delPos);
						std::cout << modeDel << std::endl;
						if (modeDel[0] == 'k')
						{
							_channels[i]->setMode(false, i);
							_channels[i]->setSecured(false);
						}
						else if (modeDel[0] == 't')
							_channels[i]->setMode(false, i);
						else if (modeDel[0] == 'i')
							_channels[i]->setMode(false, i);
						else if (modeDel[0] == 'o' && !args[3].empty())
							_channels[i]->setMode(false, i);
						delPos++;
					}
				}
				_channels[i]->sendMode(args[1], client);
			}
		}
	}
	return (0);
}