deadlock-proof-server
=====================

Ce programme simule un modèle client-serveur utilisant des sockets comme moyen de communication.

D’un côté l’application serveur représente un système d’exploitation qui gère l’allocation des ressources, comme par example la mémoire, le disque dur et les imprimantes. Ce serveur reçoit simultanément des demandes de ressources des différents clients à travers des connexions. Pour chaque connexion, le serveur doit décider si les ressources peuvent être allouées ou non au client, de façon à éviter les interblocages.
De l’autre côté, l’application client simule l’activité de N clients différents dans différents fils d’exécution (threads). Ces clients peuvent demander des ressources si elles sont disponibles ou libérer des ressource qu’ils ont à ce moment.

L'application Client reçoit quatre paramètres. Premièrement, l’IP du serveur auquel se connecter (e.g. 192.168.1.1), suivi du numéro du port, ensuite le nombre N de clients à simuler et finalement le nombre M de requêtes aléatoires à générer.

Les messages envoyés par le client sont des chaînes de caractères qui contiennent cinq nombres entiers (int), séparés par des espaces. Le premier entier indique l’index du client, le deuxième entier, R, indique la quantité des différents types de ressources (trois dans notre cas) et les entiers suivants (au nombre de R) indiquent le nombre d’instances de chaque ressource demandée ou libérée.

Par example, le message “2 3 -5 -1 0” représente une requête du client 2 pour demander 5 instances de mémoire et 1 instance du disque dur tandis que le message “0 3 0 1 2” représente une requête du client 0, pour libérer 1 instance du disque dur et 2 instances d’imprimantes.