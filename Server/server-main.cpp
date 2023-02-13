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
        cout << "Une erreur est survenue lors de la création du socket." << endl;
        return 1;
    }

    cout << "Le serveur écoute sur le port " << portServeur << "." << endl;

    // Tant que le programme n'est pas arrêté par l'utilisateur
    while (true) {
        // socket.receive est bloquant.
        // L'exécution ne continuera pas tant que des données ne sont pas reçues.
        socket.receive(paquetEntrant, adresseClient, portClient);

        paquetEntrant >> message;

        cout << adresseClient << " a envoyé: " << message << endl;

        // Renvoyer le même message au client
        paquetSortant << message;
        socket.send(paquetSortant, adresseClient, portClient);

        paquetSortant.clear(); // On efface le contenu de paquetSortant pour pouvoir le réutiliser
    }
}
