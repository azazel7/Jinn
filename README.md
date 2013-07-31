Jinn
====

Description
-----------
Jinn est un jeu de sorcélerie en « tour par tour » inspiré de la bourbasse. Jeu que l'on voit apparaître à plusieurs reprise dans le roman « Les Magiciens » de Lev Grossman.
Le jeu met en face deux équipes de magiciens qui tentent de prendre le contrôle des cases situées sur le terrain devant eux.

Jeu et Régles
-------------
Le principe reste ici le même. Les joueurs doivent constituer au moins deux équipes et se dote d'une liste de sort grâce auxquels ils tenteront de de prendre le contrôle des case.
Les régles fournis par Lev Grossman restant un peu obscures j'y ai inséré un peu mon grain de sel.

La partie débute avec toutes les cases libres et l'objéctif et de toutes les contrôler pour gagner.
S'il ne reste qu'une équipe, elle gagne automatiquement la partie.
Un sort doit avoir une case d'origine et une case cible. (Même si ce ne sera pas une régle absolue.)
Un sort sans case d'origine ne peut viser que des cases en bordure du plateau.
Si le mana d'un joueur atteint 0, il meurt. Ses sorts encore actifs sont retirés de la partie et les cases qu'il possédait deviennent sans propriétaire.
Certains sorts sont appelé des sort élite, car trop puissant. Il n'est possible d'avoir qu'un seul sort élite par joueur. (Ce principe est issue de Guild Wars.)
Le coût en mana d'un sort est exprimé en « mana par case », donc plus le sort vise loin, plus il consomme de mana.

Pour le moment, il y a peu de sorts, mais à l'avenir, il ne serai pas surprenant que certains sort bouleverse les régles établis.

Installation
============

Prés-Requis
-----------
Il est necessaire d'avoir installé boost et ncurse sur votre machine avant une quelconque compilation
Il est possible que la librairie des regex de boost ne soit pas trouvé. (libboost_regex.so)
Si le chemin d'accés à cette librairie est different de « /usr/lib/libboost_regex.so », il vous sera necessaire de le modifier dans le makefile.

Compilation
-----------

Pour créer l'executable, effectuer la commande suivante :
$ make Jinn
$ make ClientJinn

Le premier compile l'application serveur, la seconde l'application cliente.

Lancement
=========

Le lancement des deux parties partie de l'application s'effectue de la manière suivante :
$ Jinn
ou
$ ClientJinn

L'application se lancera alors avec les paramétres par défauts. 
Les deux executables proposent und aide minimale via l'option « -h ».

Usage du client
===============

Création du joueur
------------------

Lors du démarrage, le client va se connecter au serveur fourni en argument et y récupérer toutes les informations possible.
Ensuite il vous sera proposé de créer un joueur pour la partie. Untilisez les flêches gauche-droite pour changer d'un menu à l'autre et les flêches du haut et du bas pour évoluer dans les listes.
La première colonne correspond à la liste des équipes actuellement sur le serveur et la seconde colonne correspond à la liste des sorts disponibles sur le serveur.
Ensuite, il vous sera necessaire de saisir votre nom et le nom de votre équipe.

Pressez F3 pour rentrer sur la partie.
 
Jouer
-----

Une fois qu'il y a suffisament de joueur dans la partie, cette dernière débute immédiatement.

La touche tabulation permet de passer du paneau contenant le plateau au paneau contenant la discussion et inversement.

Le paneau en bas à gauche est un paneau de notification.
Le paneau en haut à gauche est une liste des joueurs.
Le paneau au milieu à droite liste les sorts et leurs touches associées.(F2 pour le premier sort, F3 pour le second ...)
Le paneau en haut à droite contient les informations sur la case courante.


Si vous êtes sur le plateau, les flêches servent à voguer entre les cases.
La touche espace permet d'ajouter ou de retirer la case courante aux cibles du prochain sort.
La touche « + » permet de mettre la case courante en tant que case d'origine du prochain sort.
Les touche Fm avec m >= 2 permettent de lancer le sort associé à la touche.

Si vous êtes sur le paneau de discussion, la touche entrée enverra le message au serveur.

Pensez à appuyer sur les touches pour raffraichir l'affichage.

Protocole Réseau
================

Je vais récapituler les commande du protocole.
Le protocole est plutôt instable et il est possible qu'il ai évolué depuis que vous l'ayez lu.
Normalement, toutes les constantes sont listées dans « reseau/constanteReseau.h »
La constante CHAMP_VIDE peut téchniquement remplacer n'importe quel argument pour dire qu'il n'y à par d'information.

Pour séparer deux commandes on use pour le moment du #.
Pour séparer les éléments d'une commande on use du ;.
C'est pourquoi il est possible de taper ses commandes à la main dans le mini-chat. Il suffit de débuter le message par un # et la suite sera considéré comme une commande differente et interprétée comme telle.
De part ce fait, les joueurs ne peuvent pas posséder de nom ou des nom d'équipe avec des # ou des ;.
Notez qu'il est problématique de ne pas pouvoir taper ces deux caractéres, c'est pourquoi il est possible que la séquence des caractéres séparateurs puisse changer dans l'avenir.

Le protocole contient des commandes inutilisée ou déjà obsolétes. Toutes les informations de certains objets ne sont pas transmisent (prenez les cases pour exemple).
Le mieux pour se tenir à jour de ce dernier et encore de décortiquer les sources de ReceptionServeur, ReceptionClient et Joueur.

Client
------
tourde;<Nom du joueur>; -> Cela indique quel joueur doit joueur.
fintourpartie; -> Indique que tous les joueurs on jouer une fois et que l'on recommence. (Cela implique que les sorts à effet font leurs effets et que les cases regagnent leurs defenses et les joueurs regagnent leurs mana)
mort;<Nom du joueur>; -> Inquique que le joueur nommé est mort.
demaragepartie; -> Indique que la partie démarre.
finpartie;<Nom équipe> -> Indique que la partie est finis et le nom de l'équipe correspond à l'équipe gagnante.
quitterpartie;<Nom joueur> -> Indique que le joueur ainsi nommé vient de quitter la partie.
infosort;<nom>;<id>;<nom du joueur qui à effectué le sort>;<durée restante du sort>;<abscice>;<ordonnée>; -> Informe d'un sort, généralement les siens. L'abscice et l'ordonnée correspondent aux coordonnées de la case sur laquelle est le sort
infojoueur;<nom>;<equipe>;<mana actuel>;<mana max>;<gain mana>;<abilite>;<niveau abilite>; -> Informe d'un joueur. equipe peut valoir le champ vide et les valeurs à -1 sont des valeurs inconnus.
infocase;<abscice>;<ordonné>;<Nom propriétaire>;<def initiale>;<defense réel>;<defense actuel>;<regénération de defense>;<apport mana>;<bonus offensif initial>;<bonus offensif réel>; -> Informe d'une case
joueur;<nom>;<equipe>;<mana actuel>;<mana max>;<gain mana>;<abilite>;<niveau abilite>;<nom sort 1>;<nom sort 2>;<nom sort n>; -> Indique la bonne création du joueur avec ses stats et sa liste de sort.
message;<Nom joueur>;<msg>; -> Le joueur ainsi nommé vient d'envoyer un message
erreur;<msg>; -> Une erreur vient de se produire sur l'une des commande envoyées. (le msg est optionnel.)
equipe;<nom equipe>;<nom equipe 1>;<...>; -> Renvoie la liste des équipes présentes
sort;<nom sort>;<description>;<elite>;<coup mana>;<duree>;<portée max>;<nombre de cible max>;<Pourcentage de réussite>; -> La séquence d'arguments peut se répéter et elle donne des informations sur les sorts qui sont utilisables dans la partie.
informationpartie;<nombre de place>;<nombre actuel de joueur>;<nombre de sort par joueur>; -> Des informations sur la partie.

Serveur
-------
sort; -> Indique une demande de la liste des sorts utilisables
equipe; -> Indique une demande de la liste des équipes actuelles
informationpartie; -> indique une demande des informations relatives à la partie
joueur;<nom du joueur>;<nom équipe>;<sort 1>;<sort 2>;<...>; -> Demande la création d'un joueur avec un nom et dans une équipe. Il y a aussi la liste des sorts du joueur. S'il y en a plus que necessaire, le surplus est ignoré.
message;<msg>; -> Envoyer un message à tous les joueurs
quitter; -> Quitte le serveur
fintour; -> Déclare son tour finis
action;<sort>;<abscice origine>;<ordonnée origine>;<abscice cible 1>;<ordonnée cible 1>;<abscice cible 2>;<ordonnée cible 2>; -> Envoye un sort depuis l'origine vers les cibles. Il peut y avoir plus de deux cibles, mais ce nombre doit rester dans  la limite du sort.

