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

    // Attacher le socket � un port
    // AnyPort indique d'utiliser un port assign� par le syst�me
    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        cout << "Une erreur est survenue lors de la cr�ation du socket." << endl;
        return 1;
    } 
    portClient = socket.getLocalPort();

    // On associe le socket � un s�lecteur.
    // Celui-ci permettra de mettre un temps d'attente maximal sur la r�ception de donn�es.
    selecteur.add(socket);

    cout << "�cho R�seau" << endl;
    cout << "===========" << endl << endl;

    cout << "Le client �coute sur le port " << portClient << "." << endl << endl;

    // Tant que le programme n'est pas arr�t� par l'utilisateur
    while (true) {
        cout << "Entrer un message: ";
        getline(cin, message);
        paquetSortant << message;

        socket.send(paquetSortant, adresseServeur, portServeur);

        // On attend la r�ception de donn�es sur le socket pour un maximum de 5 secondes.
        // Pass� ce d�lai, la m�thode `wait` retournera false.
        if (selecteur.wait(sf::seconds(5))) {
            socket.receive(paquetEntrant, adressePaquetEntrant, portPaquetEntrant);

            paquetEntrant >> message;

            cout << "Le serveur (" << adressePaquetEntrant << ":" << portPaquetEntrant
                << ") a retourn� : " << message << endl;
        }
        else {
            cout << "Le serveur n'a retourn� aucune r�ponse apr�s 5 secondes." << endl;
        }

        paquetSortant.clear(); // On efface le contenu de paquetSortant pour pouvoir le r�utiliser
    }
}
