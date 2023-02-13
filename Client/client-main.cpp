#include <iostream>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::UdpSocket socket;
    sf::SocketSelector selecteur;
    sf::IpAddress adresseServeur = "127.0.0.1";
    sf::IpAddress adressePaquetEntrant;
    sf::Packet paquetEntrant;
    sf::Packet paquetSortant;

    unsigned short portServeur = 54000;
    unsigned short portClient;
    unsigned short portPaquetEntrant;

    string message;

    setlocale(LC_ALL, "fr");

    // Attacher le socket à un port
    // AnyPort indique d'utiliser un port assigné par le système
    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        cout << "Une erreur est survenue lors de la création du socket." << endl;
        return 1;
    } 
    portClient = socket.getLocalPort();

    // On associe le socket à un sélecteur.
    // Celui-ci permettra de mettre un temps d'attente maximal sur la réception de données.
    selecteur.add(socket);

    cout << "Écho Réseau" << endl;
    cout << "===========" << endl << endl;

    cout << "Le client écoute sur le port " << portClient << "." << endl << endl;

    // Tant que le programme n'est pas arrêté par l'utilisateur
    while (true) {
        cout << "Entrer un message: ";
        getline(cin, message);
        paquetSortant << message;

        socket.send(paquetSortant, adresseServeur, portServeur);

        // On attend la réception de données sur le socket pour un maximum de 5 secondes.
        // Passé ce délai, la méthode `wait` retournera false.
        if (selecteur.wait(sf::seconds(5))) {
            socket.receive(paquetEntrant, adressePaquetEntrant, portPaquetEntrant);

            paquetEntrant >> message;

            cout << "Le serveur (" << adressePaquetEntrant << ":" << portPaquetEntrant
                << ") a retourné : " << message << endl;
        }
        else {
            cout << "Le serveur n'a retourné aucune réponse après 5 secondes." << endl;
        }

        paquetSortant.clear(); // On efface le contenu de paquetSortant pour pouvoir le réutiliser
    }
}
