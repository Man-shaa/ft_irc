/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:17:19 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/07/03 15:47:47 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

const char* welcomeMessage = "Welcome to the IRC server!\r\n";

Server::Server()
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
		_clients[i] = NULL;
	for (int i = 0; i < MAX_CHANNEL; ++i)
		_channels[i] = NULL;
}

Server::~Server()
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL)
			delete(_clients[i]);
	}
}

/* Creation socket d'écoute (listen socket) est un type de socket utilisé \
par un serveur pour écouter les connexions entrantes des clients. */
int	Server::createSocket()
{
	int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == -1) 
	{
		std::cerr << "Erreur lors de la création du socket" << std::endl;
		return (1);
	}
	_sockets.push_back(listenSocket);
	_fds_srv.fd= listenSocket;
	_fds_srv.events = POLLIN;
	return (0);
}

/* Définir les informations de l'adresse du serveur \
pour spécifier sur quelle adresse IP et quel port le serveur \
va écouter les connexions entrantes des clients.*/
void	Server::serverInfo()
{
	std::memset(&_serverAddress, 0, sizeof(_serverAddress));
	_serverAddress.sin_family = AF_INET; //type d'adresse utilise par le socket IPv4
	_serverAddress.sin_addr.s_addr = INADDR_ANY; //socket ecoute toutes les connexions entrantes sur IP dispo du serveur
	_serverAddress.sin_port = htons(_port);
}

/*Lié socket d'ecoute à une adresse IP et\
à un numéro de port spécifiques à l'aide de la fonction bind()*/
int Server::linkSocketServer()
{
	if (bind(_sockets[0], reinterpret_cast<sockaddr*>(&_serverAddress), sizeof(_serverAddress)) == -1) {
		std::cerr << "Erreur lors du bind du socket" << std::endl;
		close(_sockets[0]);
		return (1);
	}
	return (0);
}

//Mettre le socket en mode écoute de connection
int	Server::listenSocket()
{
	if (listen(_sockets[0], SOMAXCONN) == -1) {
		std::cerr << "Erreur lors de la mise en écoute du socket" << std::endl;
		close(_sockets[0]);
		return (1);
	}
	std::cout << "Le serveur est en écoute sur le port " << _port << std::endl;
	return (0);
}

// Accepter les connexions entrantes
int Server::acceptConnexions()
{
	socklen_t clientAddressLength = sizeof(_clientAddress);
	int _clientSocket = accept(_sockets[0], reinterpret_cast<sockaddr*>(&_clientAddress), &clientAddressLength);
	if (_clientSocket != -1)
	{
		_sockets.push_back(_clientSocket);
		addClient("bob", _clientSocket);
		std::cout << "Nouvelle connexion acceptée. Socket : " << _clientSocket << std::endl;
		int flags = fcntl(_clientSocket, F_GETFL, 0);
		fcntl(_clientSocket, F_SETFL, flags | O_NONBLOCK);
		//send(_clientSocket, welcomeMessage, std::strlen(welcomeMessage), 0);
		return (1);
	}
	return (0);
}

// Supprimer les sockets clients déconnectés de la liste
void Server::socketToRemove()
{
	for (std::vector<int>::iterator it = _socketsToRemove.begin(); it != _socketsToRemove.end(); ++it) 
	{
		_fd = *it;
		_sockets.erase(std::remove(_sockets.begin(), _sockets.end(), _fd), _sockets.end());
		close(_fd);
	}
	_socketsToRemove.clear();
}

int Server::serverManagement()
{
	if (createSocket())
		return (1);
	serverInfo();
	if (linkSocketServer())
		return (1);
	if (listenSocket())
		return (1);
	//Socket d'ecoute en mode non bloquant
	int flags = fcntl(_sockets[0], F_GETFL, 0);
	fcntl(_sockets[0], F_SETFL, flags | O_NONBLOCK);

	return (0);
}

int	Server::executeCommand(std::string newcmd)
{

	std::istringstream iss(newcmd);
	std::vector<std::string> args;
	std::string cmd;
	iss >> cmd;
	
	std::string arg;
	while (iss >> arg)
		args.push_back(arg);
	if (args.empty() == true)
		return (1);
	cmdFct fPtr = _mapFcts[cmd];
	if (fPtr)
		if ((this->*fPtr)(args, *getClientByFd(_fd)))
			return (1);
	return (0);
}

int	Server::manageClientMsg()
{
	char buffer[BUFFER_SIZE];

	ssize_t bytesRead = recv(_fd, buffer, sizeof(buffer) - 1, 0);
	if (bytesRead > 0)
	{
		std::string command(buffer, bytesRead);
		buffer[bytesRead] = '\0';
		std::cout << "Message reçu du client " << _fd << ": " << buffer << std::endl;

		std::size_t startpos = 0;
		std::size_t endpos = command.find("\r\n", startpos);

		while (endpos != std::string::npos)
		{
			std::string newcmd = command.substr(startpos, endpos - startpos);
			if (executeCommand(newcmd))
			{
				std::memset(buffer, 0, sizeof(buffer));
				return (1) ;
			}
			startpos = endpos + 2;
			endpos = command.find("\r\n", startpos);
		}
	}
	else if (bytesRead == 0) 
	{
		_socketsToRemove.push_back(_fd);
		std::cout << "Déconnexion du client " << _fd << std::endl;
		return (1) ;
	} 
	else if (errno != EWOULDBLOCK && errno != EAGAIN) 
	{
		_socketsToRemove.push_back(_fd);
		std::cerr << "Erreur lors de la lecture du client " << _fd << std::endl;
		return (1) ;
	}
	std::memset(buffer, 0, sizeof(buffer));
	return (0);
}

int Server::dataManagement()
{
	pollfd fds_rd;

	_ret = 0;
	while (true)
	{
		for (std::vector<int>::iterator it = _sockets.begin(); it != _sockets.end(); ++it) 
		{
			_fd = *it;
			if (_fd == *_sockets.begin())
				fds_rd = _fds_srv;
			else
				fds_rd = _clients[getClientByFd(_fd)->getId()]->getPollStrc();
			if ((_ret = poll(&fds_rd, 1, 0)) <= 0)
			{
				if (_ret == 0 || errno == EINTR)
					continue;
				perror("Poll failed");
				return (1);
			}
			if (_fd == *_sockets.begin())
			{
				if (acceptConnexions())
					it = _sockets.begin();
			}
			else
				if (manageClientMsg())
					break ;
		}
		socketToRemove();
		//printAllClient();
	}
	return (0);
}

int Server::start(int port, std::string password) 
{
	_port = port;
	_password = password;
	serverManagement();
	initCmd();
	dataManagement();
	close(_sockets[0]);
	return 0;
}

// Add a new Client to [_client[]] in the server
void	Server::addClient(std::string nickname, int fd)
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] == NULL)
		{
			_clients[i] = new Client(fd, nickname, i);
			break ;
		}
		if (i == MAX_CLIENTS - 1)
			std::cout << "Can not add more clients to the server" << std::endl;
	}
}

// Remove an existing client from [_clients[]] in the server
void	Server::removeClient(int fd)
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL && _clients[i]->getSocketFd() == fd)
		{
			_socketsToRemove.push_back(fd);
			delete(_clients[i]);
			_clients[i] = NULL;
			return ;
		}
	}
}

// void	Server::removeSocketByFd(int socketFd)
// {
// 	for (std::vector<int>::iterator it = _sockets.begin(); it != _sockets.end(); ++it)
// 	{
// 		if (*it == socketFd)
// 			_sockets.erase(it);
// 	}
// }


// Print all clients in server
void	Server::printAllClient() const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL)
			_clients[i]->printInfo();
	}
}

// Return a pointer to the client which have a [_socketFd] matching [fd]
Client	*Server::getClientByFd(int fd) const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL && _clients[i]->getSocketFd() == fd)
			return (_clients[i]);
	}
	return (NULL);
}

void Server::addChannel(std::string channelName, Client &client)
{
	for (int i = 0; i < MAX_CHANNEL; ++i)
	{
		if (_channels[i] == NULL)
		{
			_channels[i] = new Channel(channelName, client);
			break ;
		}
		if (i == MAX_CHANNEL - 1)
			std::cout << "Can not add more channels to the server" << std::endl;
	}
}

// Print all channels in server
void	Server::printAllChannel() const
{
	for (int i = 0; i < MAX_CHANNEL; ++i)
	{
		if (_channels[i] != NULL)
		{
			std::cout << _channels[i]->getName() << std::endl;
			break;
		}
	}
}
