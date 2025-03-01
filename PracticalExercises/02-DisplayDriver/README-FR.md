# Implémentation du pilote d’affichage

## Explications générales sur les laboratoires
Avant de commencer, faites une copie du répertoire `LOS-PracticalExercises` puisque l’ensemble des exercices pratiques utilisera cette même base. Les exercices étant incrémentiels, cette base servira à toutes les étapes de la formation. L’ensemble des exercices aura comme point de départ le fichier `src/kinit/init.c`.

Vous devriez vous familiariser immédiatement avec ce fichier. 
Chaque exercice possède un point de départ à l’intérieur de la fonction `LOS_init` présente à l’intérieur de ce fichier. Veuillez retirer les commentaires d’exercice au début de chaque exercice. Par exemple, le commentaire à la ligne 9 du fichier `src/kinit/init.c` doit être retiré avant de pouvoir commencer le laboratoire. En cas de doute ou de questionnement, veuillez demander de l’aide.

## Explication sur le laboratoire
Dans ce laboratoire, vous allez devoir terminer l’implémentation du pilote d’affichage utilisé par **LOS**. Pour ce faire, vous allez utiliser le code source présent dans le répertoire `LOS-PracticalExercises`. Le pilote d’affichage se trouve à l’emplacement `src/kio/display`.  
L’exercice se déroule en **2 étapes** :

### Première partie
Les macros devant être implémentées se trouvent à l’intérieur du fichier `src/kio/display/display.h` aux lignes 46 et 47.

- La macro `buildDisplayColor(fg, bg)` doit utiliser l’énumération `STANDARD_COLOR` afin de construire un nombre de **8 bits** au format `0bBBBB FFFF`, où `B` représente la couleur de fond (*background*) et `F` représente la couleur des caractères (*foreground*).
- La macro `buildDisplayChar(character, color)` doit construire un nombre de **16 bits** visant à créer un caractère pouvant être affiché à l’écran. Le caractère doit être au format `0xCCRR` où `C` représente la couleur d’affichage et `R` représente le caractère (*ASCII*) devant être affiché.

### Deuxième partie
Assurez-vous d’avoir fait la lecture du fichier `display.h` avant de commencer cette portion de l’exercice. Plusieurs éléments sont mis à votre disposition afin de vous faciliter la tâche. Cette partie dépend fortement de la **mémoire d’affichage**. Cette mémoire est située à l’emplacement défini par la macro `SCREEN_BUFFER`. Cette mémoire est organisée en un tableau de **80 colonnes par 25 lignes**.

1. **Implémenter `disp_clear()`**
   - Cette fonction ne prend aucun paramètre.
   - Elle doit effacer l’ensemble de l’affichage de manière à afficher une page noire.

2. **Implémenter `disp_printLine(uint32_t* line)`**
   - Cette fonction permet l’affichage d’une ligne sur la ligne inférieure (*la ligne située le plus bas sur l’écran*).
   - Elle appelle `disp_scrollUp()` afin de faire défiler l’affichage.
   - **Note importante** : Le paramètre `line` est un pointeur vers une zone mémoire déjà prête à être affichée. Vous **n’avez pas** à utiliser les macros `buildDisplayColor` et `buildDisplayChar` sur ces données.
   - Vous pouvez examiner le code des fonctions appelant `disp_printLine()` pour mieux comprendre son contexte d’utilisation.

3. **Implémenter `disp_scrollUp()`**
   - Cette fonction ne prend aucun paramètre.
   - Elle permet de faire défiler le texte sur l’affichage en insérant une ligne « vide » en bas de l’écran.

Lorsque l’exercice sera terminé, **LOS** sera en mesure d’exécuter les lignes **10 à 15** du fichier `init.c`. Vous pouvez vérifier le bon fonctionnement de votre code en exécutant le script `buildRun`.
