# Ultimate-Penguin-Rampage

Petit jeu, bien bourrin...

## 1. Développement en console.

A partir du 28 Juin 2015, le développement d'UPR reprend mais avec une compilation en console à l'aide d'un fichier Makefile. La branche "compilation_console" sera donc la branche principale jusqu'à ce que le jeu soit suffisamment avancé ou je commence à avoir marre de la compilation en console...

## 2. Comment bien se placer avec la console.

1. Ouvrir l'invite de commande Windows. Il s'agit du programme __cmd__ qui peut être lancer rapidement en cherchant "cmd" dans le menu _Démarrer_.

  Par défaut, __cmd__ démarre dans le répertoire de l'utilisateur. Ainsi vous devriez voir ce genre de texte:
  __C:\Users\"votre_utilisateur_windows">___
	
2. Naviguer jusqu'au répertoire où se situe la _Makefile_ du projet à l'aide de la commande __cd__ (= "**c**hange **d**irectory).
  
  Par exemple, si je souhaite me placer dans mon dossier "C++" lui-même dans le dossier "Creation Projects" de mes Documents, je dois écrire la commande suivante :  __cd "Documents\Creation Projects\C++"__ puis appuyer sur "Entrée". Les guillemets dans le chemin donné à la commande __cd__ sont nécessaires car mes noms de dossier ont des espaces.

  (Astuce : après avoir écrit les quelques premières lettres du nom du dossier, je peux juste appuyer sur "Tab" pour laisse la console auto-compléter le nom).
  
3. Pour vérifier le contenu du dossier dans lequel la console est placée, entrer la commande __dir__ (= **dir**ectory).

4. Naviguer ainsi jusqu'au dossier dans lequel se trouve le ficher _Makefile_ du programme. Dans notre cas, il s'agit des dossiers "UltimatePenguinRampage" et "UltimatePenguinRampage_rebuild" du répertoire GitHub.

## 3. Comment compiler en invite de commande.

1. Vérifier la présence de la suite d'outils MinGW sur l'ordinateur. Si elle a été installée par défaut, elle doit se trouver dans le dossier __C:\MinGW__. Si ce dossier est présent ou si vous savez que vous l'avez installée ailleurs, passer à l'étape 2, sinon suivre les étapes ci-dessous pour télécharger et installer la suite MinGW.
    1. Se rendre sur le site de MinGW : http://www.mingw.org/.
    2. Repérer le lien "Downloads" situé en haut à droite et y accéder.
    3. Accepter les cookies de la part du site SourceForge.
    4. Juste au-dessus de la liste des dossiers et fichiers, repérer le paragraphe "Looking for the latest version?" et cliquer sur le lien donné.
    5. Une fois le téléchargement terminé, exécuter le ficher setup obtenu qui installera l'installateur de MinGW. __Important :__
      - Par défaut le chemin d'installation sera __C:\MinGW__, je conseille de ne pas le changer même si il ne l'installe pas dans l'habituel __C:\Program Files__.
      - Au cours de l'installation, bien vérifier que l'option "graphical user interface" est cochée. Elle l'est par défaut mais il vaut mieux quand même vérifier. Sinon il vous faudra naviguer en ligne de commande pour installer le compilateur...
    6. Une fois l'installation terminée, lancer le programme "MinGW Installer". Il devrait y avoir un raccourci sur votre bureau si vous l'avez demandé au cours de l'installation.
    7. Selectionner l'option "Basic Setup" dans le volet de gauche et repérer les paquets "mingw32-base" et "mingw32-gcc-g++" dans la liste à droite.
    8. Sur chacun de ces deux paquets faire un clic droit puis selectionner "Mark for Installation".
    9. Dans la barre des menus, cliquer sur "Installation > Apply changes". L'installateur téléchargera alors les différents composants de la suite MinGW dont nous aurons besoin et les placera dans le dossier d'installation de MinGW.
    10. Une fois l'installation des paquets terminée, fermer MinGW Installer.

2. Vérifier si le dossier __bin__ de la suite MinGW (par défaut __C:\MinGW\bin__) est présent dans la variable __Path__ du système. Si il s'y trouve déjà, passer à l'étape 3. Si vous n'en n'êtes pas sûr, ou si vous venez d'installer la suite MinGW à l'étape 1, suivre les étapes ci-dessous pour configurer la variable __Path__.
  1. Ouvrir le menu Démarrer, faire un clic droit sur "Ordinateur" et selectionner "Propriétés".
  2. Dans le volet de gauche, cliquer sur "Paramètre système avancés". __Note :__ Vous aurez besoin des privilèges d'administateur pour réaliser cette étape.
  3. Dans la fenêtre qui s'ouvre, cliquer sur le bouton "Variables d'environnement...".
  4. Dans la liste intitulée "Variables système", chercher la variable __Path__, la selectionner et cliquer sur "Modifier".
  5. Dans la fenêtre qui s'ouvre, le champ "Valeur de la variable" devrait déjà être selectionné. Je suggère ici de copier cette valeur vers un éditeur de texte --- tel que Bloc-notes ou Notepad++ --- afin d'en faciliter la modification.
  6. Si elle n'est pas déjà présente au sein de la variable __Path__, ajouter la phrase "C:\MinGW\bin;" (sans les guillemets) au _debut_. Le point virgule est important, c'est lui qui délimite les différents dossiers au sein de la variable. __Attention :__ Si vous avez changé le répertoire d'installation de MinGW, c'est la phrase "chemin_vers_nouveau_dossier_installation\bin;" que vous devez ajouter à la variable __Path__.
  7. Si vous aviez copié la valeur dans un éditeur de texte, il faut remplacer la valeur précédente par la nouvelle qui possède le dosier ajouté puis cliquer trois fois sur "OK" pour fermer les trois fenêres qui ont permis l'accès à la variable __Path__. Vous pouvez également fermer les Propriétés de l'Ordinateur.
  8. Cette modification de la variable __Path__ permet désormais l'appel en invite de commande de tous les programmes installés de la suite MinGW à partir de n'importe quel emplacement.

3. Ouvrir l'invite de commande et se placer dans le dossier contenant le ficher _Makefile_ du programme à compiler. Voir Section 2. "Comment bien se placer avec la console."

4. Compiler le programme avec la commande __mingw32-make__, elle ne prend aucun paramètre. En temps normal, il ne devrait pas y avoir d'erreur, sauf si le répertoire GitHub a été synchronisé avec une compilation défaillante.

5. L'exécutable est créé dans le dossier __bin\Debug__ par rapport à l'emplacement d'exécution de __mingw32-make__.

## 4. Comment lancer l'exécutable du dossier __bin\Debug__.

__Note :__ Cette section ne requiert pas l'installation de MinGW décrit à la Section 3.

1. A l'aide de la Section 2, se placer dans le dossier contenant le ficher _Makefile_ du projet.

2. Exécuter la commande __bin\Debug\upr.exe__ (le '.exe' est facultatif). Cela lance le programme __upr__ à partir du dossier où vous vous situez. 

	Naviguer jusqu'au dossier "bin\Debug" avec l'Explorateur de Fichier Windows et double-cliquer sur l'exécutable "upr.exe" résuletera en une erreur au lancement car les dossiers de ressources nécessaires à l'exécution du programme (tels que le dossier "img") ne sont pas présents dans le dossier "bin\Debug". C'est pour cela qu'il faut le lancer à partir du dossier où se situe le ficher _Makefile_.
