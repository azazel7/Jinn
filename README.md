Jinn (English)
=============
The french version is behind.

Description
-----------
Jinn is a turned-base wizard game. It is inspired from the bourbasse which is a game you could see in « The Magicians » by Lev Grossman.
The init game put two wiard's teams against themselve which try to take over the squares on the ground in front of them.

Game and rules
--------------
In Jinn it's nearly the same thing. There is two or more team and each player have to choose some spell in a list with what they could take over all the ground.
Lev Grossman didn't really explain the rules so I had to create some.

At the beginning, all the square are free and to win each team have to take over all square.
If it left one team, this team win.
A spell have to got target square.
A spell without source square could only target an edge square on the ground.
If a mana's player reach 0, he die. All his active spells are remove and all his square are free.
Some spell was elite spell because they are very powerfull. A player can't have more than one elite spell. (This idea come from Guild Wars.)
The cost of mana is in mana per square. That mean if you want to target a far square, the spell will cost more mana.

Currently, there is few spell in the game but some future spell will be able to break those rules.

Set up
======

Required
--------
Jinn require boost and ncurse on your computer.
There is possible that the library of boost regex will not be found.
Check if the path of it is « /usr/lib/libboost_regex.so » else change the Makefile

Compilation
-----------
$ make Jinn
$ make ClientJinn

The first is the server and the second the client.

Start
=====
$ ./Jinn
or 
$ ./ClientJinn

If you want some help about option, try « -h » option.

Use of the client
=================

Create a wizard
---------------
Use arrow keys to switch between each panel.
On the spell panel, « + » key allow you to choose a spell.
The same key allow you to choose an existing team in the first panel.

If you want to cancel, use « F2 » key and if you want to validate, use « F3 » key.

Play
----
Once there is enough player, the game begin.
The escape key allow you to quit the game.

The center panel is the map.
You could use the arrow key to move the cursor.
The space key allow you to add or remove a target.
The « + » key allow you to choose a source square for your spell.
Use the function key to perform a spell and « t » to declare your end's turn.

Use the tab key to switch between the panels.

Think to press a key to refresh the screen.

Network protocol
================

Server
------
To fill

Client
------
To fill


Jinn (Français)
===============

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
Un sort doit avoir une case cible. (Même si ce ne sera pas une régle absolue.)
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

