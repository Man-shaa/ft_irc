#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <sys/stat.h>

// FEATURE2 MODIF

int startServer(int port) {
	// Créer une socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		std::cerr << "Erreur lors de la création de la socket" << std::endl;
		return -1;
	}

	// Résoudre l'adresse IP locale
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	// Lier la socket à l'adresse IP et au port
	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		std::cerr << "Erreur lors du bind" << std::endl;
		close(serverSocket);
		return -1;
	}

	// Mettre la socket en mode écoute
	if (listen(serverSocket, SOMAXCONN) == -1) {
		std::cerr << "Erreur lors de la mise en écoute" << std::endl;
		close(serverSocket);
		return -1;
	}

	// Obtenir le numéro de port assigné
	struct sockaddr_in serverAddressActual;
	socklen_t serverAddressActualLength = sizeof(serverAddressActual);
	getsockname(serverSocket, (struct sockaddr*)&serverAddressActual, &serverAddressActualLength);
	int assignedPort = ntohs(serverAddressActual.sin_port);

	std::cout << "Serveur IRC démarré sur le port : " << assignedPort << std::endl;

	// Boucle principale pour accepter les connexions entrantes
	while (true) {
		// Gérer les connexions des clients
		struct sockaddr_in clientAddress;
		socklen_t clientAddressLength = sizeof(clientAddress);
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
		if (clientSocket == -1) {
			std::cerr << "Erreur lors de l'acceptation de la connexion client" << std::endl;
			continue;
		}

		// Traitez la connexion du client ici

		// Fermez la socket du client après la communication
		close(clientSocket);
	}

	// Fermer la socket du serveur
	close(serverSocket);

	return 0;
}

int main() {
	int port = 12345; // Remplacez par le port de votre choix
	startServer(port);
	return 0;
}
