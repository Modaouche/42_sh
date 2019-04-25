# 42-Sh

42sh est le projet de fin de branche UNIX, il consiste à implémenter (à 4 ou 5) un shell complet, solide et utilisable.
  ### 1 - Ce dernier comporte une partie obligatoire pour un shell basique tel que :
        - Exécution de commandes avec leurs paramètres et gestion du PATH.
        - Gestion des erreurs, sans utiliser errno, et de la valeur de retour des commandes.
        - ◦ Gestion correcte des espaces et des tabulations.
        - ◦ Édition complète de la ligne de commande.
        - Les opérateurs de redirection et d’aggrégation (>, >>, <, <<, >&, <&).
        - Gestion des Pipe "|" et des separateurs ";".
        - Operateur && et ||.
        - gestion des variables internes au shell.
        - Job control (bg, fg, jobs, &) + signaux.
        - built-in cd, echo, exit, type, export, set, unset.
        - built-in avec options dictées par le standard POSIX, sauf set et unset.
        
 ### 2 - Par la suite il y a la partie modulaire qui nous demande d'ajouter des fonctionnalité plus avancé.
        - Les inhibiteurs ” (double quote), ’ (simple quote) et \ (backslash)
        - • La gestion complète de l’historique
        - (d'autres a ajouter en fonction de l'avancement)...
        
        
 ### 3 - Bonus :
        - Nous avons décidé en plus d'ajouter le fait de pouvoir faire des scripts shell.



#### Remarque :
      Lors du projet nous avons remarqué que notre parser du projet précédent etait vraiment insuffisant.
      C'est ainsi que nous avons décidé pour nous entraîner d'utiliser la grammaire d'un vrai shell. Nous avons ainsi implémenté un simple Parser LL(1) à partir de la grammaire du shell (LR que nous avons converti en LL cf. http://pubs.opengroup.org/onlinepubs/007904975/utilities/xcu_chap02.html).
      Ce dernier nous génére un AST qui permet d'éxecuter la commande de l'utilisateur proprement.


## Compétences :
    - Ce projet nous à permis de travailler en groupe et de voir les différentes contraintes/avantage à travailler en groupe.
    - Nous avons pu avoir plus de connaissance dans le systeme UNIX.
    - Decouverte et apprentissage d'une analyse syntaxique (Lexing, Parsing, AST).
    - Connaissance en shell
