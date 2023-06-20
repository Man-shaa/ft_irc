/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccheyrou <ccheyrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:17:19 by ccheyrou          #+#    #+#             */
/*   Updated: 2023/06/20 14:13:22 by ccheyrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

const char* welcomeMessage = "Welcome to the IRC server!\r\n";

Server::Server()
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
		_clients[i] = NULL;
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
        return 1;
    }
	_Sockets.push_back(listenSocket);
    _fds_srv.fd= listenSocket;
    _fds_srv.events = POLLIN;
    std::cout << "Creation socket serveur " << _Sockets[0] << std::endl;
	return 0;
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
int Server::link_SocketServer()
{
	if (bind(_Sockets[0], reinterpret_cast<sockaddr*>(&_serverAddress), sizeof(_serverAddress)) == -1) {
		std::cerr << "Erreur lors du bind du socket" << std::endl;
		close(_Sockets[0]);
		return 1;
	}
	return 0;
}

//Mettre le socket en mode écoute de connection
int	Server::listenSocket()
{
	if (listen(_Sockets[0], SOMAXCONN) == -1) {
		std::cerr << "Erreur lors de la mise en écoute du socket" << std::endl;
		close(_Sockets[0]);
		return 1;
	}
	std::cout << "Le serveur est en écoute sur le port " << _port << std::endl;
	return 0;
}

// Accepter les connexions entrantes
int Server::acceptConnexions()
{
    socklen_t clientAddressLength = sizeof(_clientAddress);
    int _clientSocket = accept(_Sockets[0], reinterpret_cast<sockaddr*>(&_clientAddress), &clientAddressLength);
    if (_clientSocket != -1) 
    {
        _Sockets.push_back(_clientSocket);
        addClient("john doe", _clientSocket);
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
        _client = *it;
        _Sockets.erase(std::remove(_Sockets.begin(), _Sockets.end(), _client), _Sockets.end());
        close(_client);
    }
}

int Server::serverManagement()
{
    if (createSocket())
		return (1);
	serverInfo();
	if (link_SocketServer())
		return (1);
	if (listenSocket())
		return (1);
    //Socket d'ecoute en mode non bloquant
    int flags = fcntl(_Sockets[0], F_GETFL, 0);
    fcntl(_Sockets[0], F_SETFL, flags | O_NONBLOCK);
    
    return (0);
}

void    Server::manageClientMsg()
{
	char buffer[BUFFER_SIZE];
    
    ssize_t bytesRead = recv(_client, buffer, sizeof(buffer) - 1, 0);
    //printf("%ld\n", bytesRead);
    if (bytesRead > 0)
    {
        std::string command(buffer, bytesRead);
        buffer[bytesRead] = '\0';
        std::cout << "Message reçu du client " << _client << ": " << buffer << std::endl;

        std::istringstream iss(command);
        std::string cmd, arg1, arg2, arg3, arg4;
        iss >> cmd >> arg1 >> arg2 >> arg3 >> arg4;
        if (cmd == "USER")
        {
            std::string answer = "001 " + arg1 + " :Welcome to the Internet Relay Network " + arg1 + "\r\n";
            _clients[getClientByFd(_client)->getId()]->setNickName(arg1);
            send(_client, answer.c_str(), answer.size(), 0);
        }
        else if (cmd == "/die")
            std::cout << "Commande 'die' reçue. Fermeture du serveur." << std::endl;
        else if (cmd == "NICK") 
            std::cout << "Commande 'nick' reçue. Nouveau pseudo : " << arg1 << std::endl;
        else if (cmd == "/join") 
            std::cout << "Commande 'join' reçue. Rejoindre le canal : " << arg1 << std::endl;
        else if (cmd == "/register") 
            std::cout << "Commande 'register' reçue. Informations d'enregistrement : " << arg1 << " " << arg2 << std::endl;
        //std::string response = "Bien reçu !\r\n";
        //send(_client, response.c_str(), response.size(), 0);
    } 
    else if (bytesRead == 0) 
    {
        _socketsToRemove.push_back(_client);
        std::cout << "Déconnexion du client " << _client << std::endl;
    } 
    else if (errno != EWOULDBLOCK && errno != EAGAIN) 
    {
        _socketsToRemove.push_back(_client);
        std::cerr << "Erreur lors de la lecture du client " << _client << std::endl;
    }
	std::memset(buffer, 0, sizeof(buffer));
}

int Server::dataManagement()
{
    pollfd fds_rd;
    
    _ret = 0;
    while(true)
    {
        for (std::vector<int>::iterator it = _Sockets.begin(); it != _Sockets.end(); ++it) 
        {
            _client = *it;
            if (_client == 3)
                fds_rd = _fds_srv;
            else
                fds_rd = _clients[getClientByFd(_client)->getId()]->getPollstrc();
            if ((_ret = poll(&fds_rd, _client, 0)) <= 0)  
            {
                if (_ret == 0 || errno == EINTR)
                {
                    continue;
                }
                perror("Poll failed");
                return(1);
            }
            if (_client == 3)
            {
                if (acceptConnexions())
                    it = _Sockets.begin();
            }
            else
            {
                _client = *it;
                manageClientMsg();
            }
        }
        socketToRemove();
        //printAllClient();
    }
}

int Server::start(int port) 
{
    _port = port;
    serverManagement();
    dataManagement();
    close(_Sockets[0]);
    return 0;
}

// Add a new Client to [_client[]] in the server
void Server::addClient(std::string nickname, int fd)
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] == NULL)
		{
			_clients[i] = new Client(fd, nickname, i);
			break ;
		}
	}
}

// print all clients in server
void	Server::printAllClient() const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL)
			_clients[i]->printInfo();
	}
}

// return a pointer to the client which have a [_socketFd] matching [fd]
Client	*Server::getClientByFd(int fd) const
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (_clients[i] != NULL && _clients[i]->getSocketFd() == fd)
			return (_clients[i]);
	}
	return (NULL);
}
