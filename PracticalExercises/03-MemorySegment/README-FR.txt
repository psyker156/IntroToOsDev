# Implémentation de la Segmentation

## Objectifs de l’exercice
Dans cet exercice, vous devez implémenter la **segmentation** à l’intérieur de **LOS**. Plus précisément, vous devez implémenter la fonction `setupGDT()` située dans le fichier `src/x86/memory.c`. Cette fonction doit utiliser la fonction `loadGDTR(uint32_t* gdtrBuffer)`, qui appelle à son tour la fonction `_loadGDTR(uint32_t* gdtrBuffer)`, afin de **charger le registre GDTR** et d’activer les nouveaux segments.

Après avoir implémenté la fonction `setupGDT()`, vous pouvez analyser le code de la fonction `_loadGDTR` afin de comprendre le code assembleur qui procédera au chargement du registre GDTR et à l’activation des nouveaux segments.

Avant de commencer l’exercice, il est fortement conseillé de vous **familiariser avec le fichier** `src/x86/memory.h`, qui contient des déclarations pouvant vous aider.

## Détails de la fonction `setupGDT()`
La fonction `setupGDT()` doit préparer toutes les configurations nécessaires pour **charger le registre GDTR** et les nouveaux segments. Cette fonction doit principalement :

1. **Créer un segment NULL** (tous les champs à 0) comme premier champ de la table GDT.
2. **Créer un segment CODE privilégié** comme deuxième champ de la table GDT :
   - Ce segment doit couvrir **l’ensemble de la mémoire**.
3. **Créer un segment DONNÉES privilégié** comme troisième champ de la table GDT :
   - Ce segment doit couvrir **l’ensemble de la mémoire**.
4. **Copier ces segments en mémoire** au bon endroit (voir `GDT_BASE` et chercher la fonction `kmemcpy()` qui vous aidera à copier les données).
5. **Préparer les données** pour appeler la fonction `loadGDTR(uint32_t* gdtrBuffer)` (voir la structure `_DTR`).
6. **Appeler la fonction `loadGDTR(uint32_t* gdtrBuffer)`**.

À toutes les étapes, vous êtes libre **d’adapter ou modifier le code existant** si nécessaire. 

Vous pouvez obtenir de l’aide pour configurer les différents segments en consultant le **manuel de programmation Intel** (Volume 3A, chapitre 3) ou en posant des questions à un instructeur. Cependant, il est recommandé de consulter la documentation Intel avant de poser des questions, car il est utile de se familiariser avec ces ressources officielles.

## Validation du bon fonctionnement de la segmentation
Après avoir réalisé ces étapes, si votre code fonctionne correctement, vous pouvez **retirer le commentaire** associé à l’exercice 3 dans le fichier `src/kinit/init.c` et **construire le système** à l’aide du script `buildRun`.

L’état du système après la configuration de la segmentation devrait alors s’afficher. Si tout fonctionne bien, **aucune différence visuelle ne devrait être perceptible**. Cependant, si une erreur a été commise, l’affichage devrait rapidement **devenir chaotique**, indiquant clairement qu’un problème est survenu.
