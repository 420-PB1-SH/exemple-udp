#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::UdpSocket socket;
    sf::IpAddress adresseClient;
    sf::Packet paquetEntrant;
    sf::Packet paquetSortant;

    unsigned short portServeur = 54000;
    unsigned short portClient;

    string message;

    setlocale(LC_ALL, "fr");

    // Attacher le socket au port du serveur
    if (socket.bind(portServeur) != sf::Socket::Done) {
        cout << "Une erreur est survenue lors de la cr�ation du socket." << endl;
        return 1;
    }

    cout << "Le serveur �coute sur le port " << portServeur << "." << endl;

    // Tant que le programme n'est pas arr�t� par l'utilisateur
    while (true) {
        // socket.receive est bloquant.
        // L'ex�cution ne continuera pas tant que des donn�es ne sont pas re�ues.
        socket.receive(paquetEntrant, adresseClient, portClient);

        paquetEntrant >> message;

        cout << adresseClient << " a envoy�: " << message << endl;

        // Renvoyer le m�me message au client
        paquetSortant << message;
        socket.send(paquetSortant, adresseClient, portClient);

        paquetSortant.clear(); // On efface le contenu de paquetSortant pour pouvoir le r�utiliser
    }
}
