/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:41:05 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/29 17:01:38 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "Server.hpp"

void	Server::initCmd()
{
	_mapFcts["NICK"] = &Server::cmdNick;
	_mapFcts["USER"] = &Server::cmdUser;
	_mapFcts["JOIN"] = &Server::cmdJoin;
	_mapFcts["MODE"] = &Server::cmdMode;
	_mapFcts["PING"] = &Server::cmdPing;
	_mapFcts["PASS"] = &Server::cmdPass;
}

int	Server::parseNickname(std::string &name) const
{
	int	nameSize = name.size();
	for (int i = 0; i < nameSize; ++i)
	{
		if (!isalnum((int)name[i]) && !strchr("{}()[]\\|", name[i]))
			return (1);
	}
	return (0);
}
 
// Returns 1 if [name] is already used by another user, 0 if not
int	Server::usedNickname(std::string &name) const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] && _clients[i]->getNickname() == name)
			return (1);
	}
	return (0);
}

int		Server::cmdNick(std::vector<std::string> args, Client &client)
{
	if (parseNickname(args[0]))
	{
		std::string answer = "432 " + client.getNickname() + " " + args[0] + " :Erroneus nickname\r\n"; // ERR_ERRONEUSNICKNAME
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	else if (usedNickname(args[0]))
	{
		std::string answer = "433 " + client.getNickname() + " " + args[0] + " :Nickname is already in use\r\n"; // ERR_ERRONEUSNICKNAME
		send(client.getSocket(), answer.c_str(), answer.size(), 0);
		return (1);
	}
	client.setNickname(args[0]);
	return (0);
}

int		Server::cmdUser(std::vector<std::string> args, Client &client)
{
	//TODO Gérer le <realname> cf. https://modern.ircdocs.horse/#user-message
	//TODO Gérer le ERR_ALREADYREGISTERED :  "<client> :You may not reregister"
	//TODO Tronquer le username si il dépasse la taille de USERLEN = 12
	// if ( == NULL)
	// 	return (1);
	if (args[0].empty())
		args[0] = "bob";
	std::vector<std::string>::iterator it = (--args.end());
	client.setLastName(*it);
	--it;
	std::string firstName = (*it).substr(1, (*it).size() - 1);
	client.setFirstName(firstName);
	std::string answer = "001 " + args[0] + " :Welcome to the Internet Relay Network " + args[0] + "\r\n";
	send(client.getSocket(), answer.c_str(), answer.size(), 0);
	return (0);
}

int		Server::cmdJoin(std::vector<std::string> args, Client &client)
{
	//TODO Servers MAY restrict the number of channels a client may be joined to at one time cf. https://modern.ircdocs.horse/#chanlimit-parameter

	bool channelExist = false;
	int i;
	
	for (i = 0; _channels[i]; ++i) //Faire une fonction qui recupere le nombre de channel existant
	{
		if (_channels[i]->getName() == args[0])
		{
			channelExist = true;
			//Autorisation ou non d'y acceder
		}
	}
	
	if (!channelExist)
	{
		addChannel(args[0], client);
		std::cout << "Create new channel" << std::endl;
	}
	
	//JOIN sent to client
	std::string JOIN = ":" + client.getNickname() + " JOIN " + args[0] + "\r\n";
	send(client.getSocket(), JOIN.c_str(), JOIN.size(), 0);

	//RPL_RPL_TOPIC sent to client
	std::string RPL_TOPIC =  "332 " + client.getNickname() + " " + args[0] + " :" + _channels[i]->getTopic() + "\r\n";
	send(client.getSocket(), RPL_TOPIC.c_str(), RPL_TOPIC.size(), 0);

	//RPL_NAMREPLY sent to client
	std::vector<std::string> listUsr = _channels[i]->getUsrList();
	std::string RPL_NAMREPLY = "353 " + client.getNickname() + "=" + args[0] + " :";
	for (std::vector<std::string>::const_iterator it = listUsr.begin(); it != listUsr.end(); ++it)
		RPL_NAMREPLY += *it + " ";
	RPL_NAMREPLY += "\r\n";
	send(client.getSocket(), RPL_NAMREPLY.c_str(), RPL_NAMREPLY.size(), 0);
	
	//RPL_ENDOFNAMES sent to client
	std::string RPL_ENDOFNAMES = "366 " + client.getNickname() + " " + args[0] + " :End of /NAMES list\r\n";
	send(_fd, RPL_ENDOFNAMES.c_str(), RPL_ENDOFNAMES.size(), 0);

	return (0);
}

int		Server::cmdPing(std::vector<std::string> args, Client &client)
{
	std::string pong = "server.name " + args[0] + "\r\n";
	send(client.getSocket(), pong.c_str(), pong.size(), 0);
	return (0);
}

//TODO cf. https://modern.ircdocs.horse/#user-message
int		Server::cmdMode(std::vector<std::string> args, Client &client)
{
	(void)args;
	(void)client;
	// bool channelExist = false;
	
	// for (int i = 0; i < MAX_CHANNELS i++)
	// 	if (_channels[i]->getName() == arg1)
	// 		channelExist = true;
	// if (!channelExist)
    // {
    //     std::string ERR_NOSUCHCHANNEL = client.getNickname() + "::No such channel\r\n";
    //     send(client.getSocket(), ERR_NOSUCHCHANNEL.c_str(), ERR_NOSUCHCHANNEL.size(), 0);
    // }
	
	// if (arg2.empty())
	// {
	// 	std::string RPL_CHANNELMODEIS = client.getNickname() + <usermode> + "\r\n";
	// 	send(client.getSocket(), RPL_CHANNELMODEIS.c_str(), RPL_CHANNELMODEIS.size(), 0);
	// }
	// else
	// {
		// Vérifier les privileges	du client
		// 	NON : ERR_CHANOPRIVSNEEDED  "<client> <channel> :You're not channel operator"
		// 	OUI :
	//}
	return (0);
}

int	Server::cmdPass(std::vector<std::string> args, Client &client)
{
	if (args[0] != _password)
	{
		std::string	badPass = "464 " + client.getNickname() + " :Password incorrect\r\n";
		send(client.getSocket(), badPass.c_str(), badPass.size(), 0);
		std::string	quit = "ERROR Closing Link: 127.0.0.1 (Bad Password)\r\n";
		send(client.getSocket(), quit.c_str(), quit.size(), 0);
		close(client.getSocketFd());
		removeClient(client.getSocketFd());
		return (1);
	}
	client.setStatus(REGISTER);
	return (0);
}
