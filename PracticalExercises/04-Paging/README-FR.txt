# Implémentation de la Pagination

## Objectif de l’exercice
Dans cet exercice, vous implémenterez la **pagination** dans **LOS**. Plus précisément, vous construirez les **tables requises par x86** pour activer la pagination. De plus, vous implémenterez le **code assembleur** nécessaire à l’activation de la pagination. Tout le code à implémenter se trouve dans les fichiers :

- `src/x86/memory.c`
- `src/x86/ASMmemory.asm`

Assurez-vous de bien **connaître le contenu** du fichier `src/x86/memory.h` avant de commencer. Ce fichier contient plusieurs éléments qui vous aideront. Les constantes clés pour cet exercice sont :

- `KERNEL_PDT` : Indique l’adresse mémoire où la **Page Directory Table (PDT)** doit être construite.
- `PAGE_SIZE` : Définit la taille d’une page mémoire.

---

## Description des tâches
Avant de commencer, un élément **essentiel** doit être compris : **Seuls les 8 premiers Mo de la mémoire doivent être cartographiés en mode identitaire**. Cela signifie que les **8 premiers Mo de mémoire doivent être mappés à une adresse virtuelle égale à leur adresse physique**.

Une **Page Directory Table (PDT)** ne nécessite que **2 entrées** pour mapper **8 Mo** de mémoire.

### Fonctions disponibles
Trois fonctions sont fournies pour vous aider :

- `kbuildPDE()` : Construit une entrée de **Page Directory**.
- `kbuildPTE()` : Construit une entrée de **Page Table**.
- `kbuildCR3()` : Construit la valeur à placer dans le **registre CR3**.
  - Cette fonction prend **3 paramètres** :
    1. L’adresse de la **Page Directory Table**.
    2. **Doit être 0** pour cet exercice.
    3. **Doit être 0** pour cet exercice.

---

## Déroulement de l’exercice
L’exercice se divise en **deux étapes** :

### 1. Implémentation de `kinitiatePagingStructuresForBaseOS()`
Cette fonction permet de construire les **structures de données** requises pour l’activation de la pagination **32 bits**.

1. Construire les **structures de données** permettant la cartographie des **8 premiers Mo** de mémoire en mode identitaire.
2. Construire la **valeur du registre CR3** en utilisant la fonction `kbuildCR3()`.
3. Appeler la fonction `_setCR3()` avec la nouvelle valeur de **CR3**.
4. Appeler la fonction `_activatePaging()`.

### 2. Implémentation de `_setCR3()`
Cette fonction possède le prototype suivant :
```c
void _setCR3(uint32_t cr3Value)
```

- **Cette fonction doit être implémentée en assembleur.**
- Elle doit **copier la valeur** de `cr3Value` dans le **registre CR3** et retourner.
- **Attention !** Vous devez respecter l’**ABI**.

---

## Validation du bon fonctionnement de la pagination

Pour vérifier que la pagination fonctionne bien avec une **cartographie identitaire**, vous pouvez :

1. **Écrire une valeur** à une adresse mémoire située entre **4 et 8 Mo** (dans `init.c`, après le code de l’exercice 4).
2. **Lancer QEMU** et inspecter la mémoire lors de l’exécution.
3. Utiliser les **commandes `x` et `xp`** pour inspecter la mémoire **virtuelle et physique**.

### Exemple d’utilisation de la commande `x` :
```sh
x /10x <adresse>
```
La commande `xp` fonctionne de manière similaire.

Si vous terminez l’exercice plus tôt que prévu, vous pouvez examiner le **code de la fonction `_activatePaging()`** pour mieux comprendre son fonctionnement.

En cas de besoin, consultez le **manuel 3A** de la documentation publiée par **Intel**.
