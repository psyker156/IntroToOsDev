# Implémentation de la Pile (Heap) du Noyau

## Objectif de l’Exercice
Dans cet exercice, vous implémenterez une partie des fonctions composant le **système de gestion de la pile du noyau** de **LOS**. Plus précisément, vous implémenterez le code de la fonction `kmalloc()`. La première implémentation de cette fonction sera **naïve**. Nous la revisiterons plus tard lors de l’étude du **multi-processing**.

---

## Courte Explication sur la Pile du Noyau dans LOS
La pile du noyau de **LOS** repose principalement sur **deux zones mémoire** :

- **`_kernelHeapArray`** : Un **bitmap** des allocations effectuées dans `_kernelHeap`.
- **`_kernelHeap`** : La mémoire réellement utilisée pour la pile du noyau.

Le fonctionnement est relativement simple :
- `_kernelHeap` est une mémoire de **1 Mo**.
- `_kernelHeapArray` est une mémoire de **16 384 octets**.
- Cela permet d’utiliser `_kernelHeapArray` comme un **bitmap** (à l’octet), avec une résolution de **64 octets** à l’intérieur de `_kernelHeap`.
- En résumé, `_kernelHeapArray` est un tableau **indiquant les allocations faites** dans `_kernelHeap`.
- Ces deux variables sont définies à la **fin du fichier** `kernelStart.asm`.

### Étape Préliminaire
Avant de commencer, **lisez le fichier** `src/x86/kernelHeap.c`. 
- De nombreuses **fonctions de support** y sont déjà présentes.
- Vous êtes libre de **réimplémenter ces fonctions** si nécessaire.
- Cependant, **l’interface** des fonctions `kmalloc`, `kfree`, et `kinitHeap` **doit rester identique**.
- Pour une question de temps, **seule la fonction `kmalloc`** sera implémentée dans cet exercice.

---

## Exercice
La fonction `kmalloc()` est située dans le fichier `src/x86/kernelHeap.c`. C’est cette fonction que vous devez implémenter.

### Responsabilités de la Fonction `kmalloc()`
Votre implémentation doit respecter les **objectifs suivants** :

- **Vérifier que la pile est initialisée** avant utilisation.
- **Retourner un pointeur de type `void*`**.
- **Calculer le nombre de blocs** nécessaires (résolution de **64 octets** par allocation).
- **Trouver et réserver** un bloc de mémoire disponible.
- **Calculer l’adresse mémoire** correspondant à l’allocation.
- **Retourner l’adresse de l’allocation**.

---

## Validation du Bon Fonctionnement de la Pile
Si votre implémentation est correcte, vous devriez pouvoir **utiliser `kmalloc()` et `kfree()`** après l’appel à la fonction `kinitHeap()` dans `init.c`.

Il est conseillé, si le temps le permet, **d’analyser le fonctionnement de la pile avec un débogueur** pendant l’exécution de **LOS**.

---

## Question « Bonus »
Pourquoi notre implémentation est-elle **naïve** ?
À quels types de problèmes devons-nous nous attendre ?
