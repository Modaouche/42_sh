# 42-Sh

42sh est le projet de fin de branche UNIX à 42, il consiste à implémenter (à 4 ou 5) un shell complet, solide et clairement utilisable.

  ### 1 - il dois comporter une partie obligatoire pour un shell basique tel que :
        - Affichage d'un Promp + exécution de commandes avec leurs paramètres et gestion du PATH.
        - Gestion des erreurs, sans utiliser errno, et de la valeur de retour des commandes.
        - Gestion correcte des espaces et des tabulations.
        - Édition complète de la ligne de commande.
        - Les opérateurs de redirection et d’aggrégation (>, >>, <, <<, >&, <&).
        - Gestion des Pipe "|" et des separateurs ";".
        - Operateur && et ||.
        - gestion des variables internes au shell.
        - Job control (bg, fg, jobs, &) + signaux.
        - built-in cd, echo, exit, type, export, set, unset.
        - built-in avec options dictées par le standard POSIX, sauf set et unset.
        
 ### 2 - Par la suite il y a la partie modulaire qui nous demande d'ajouter des fonctionnalité plus avancé:
        - Les inhibiteurs ” (double quote), ’ (simple quote) et \ (backslash)
        - La gestion complète de l’historique
        - Built-in test
        - Autocompletion + completion avancée.
        - Built-in alias
        - Param expansion.
        - (d'autres a ajouter en fonction de l'avancement)...
        

#### Remarque :
      Nous avons  implémenté un simple Parser LL(1) à partir de la grammaire du shell 
      (LR que nous avons converti en LL, Cf. Wiki).
      Ce dernier nous génére un AST qui permet d'éxecuter la commande de l'utilisateur proprement, avec
      les ordres de priorités


## Compétences :
    - Ce projet nous à permis de travailler en groupe et de voir les différentes
      contraintes/avantage à travailler en groupe.
    - Nous avons pu avoir plus de connaissance dans le systeme UNIX.
    - Decouverte et apprentissage d'une analyse syntaxique (Lexing, Parsing, AST).
    - Connaissance en shell
 
