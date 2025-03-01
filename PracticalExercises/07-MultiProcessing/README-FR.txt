# Implémentation du Système de Multi-Programmation

## Objectif de l’Exercice
Dans cet exercice, vous implémenterez la **fonction principale** du **process scheduler** (aiguilleur de processus). Comme le code du système d’aiguillage est relativement long, nous nous concentrerons uniquement sur la fonction **`runScheduler()`**, située dans `src/kProcessManagement/processManagement.c`.

Avant de commencer cet exercice, assurez-vous de bien **comprendre le principe d’aiguillage** dans **LOS**. Bien que la fonction à implémenter soit relativement simple, le **système d’aiguillage lui-même est complexe**.

---

## Avant de Commencer l’Exercice
Lisez attentivement les fichiers suivants :

- `src/kProcessManagement/processManagement.c`
- `src/kProcessManagement/processManagement.h`
- `src/x86/ASMprocessManagement.asm`

Assurez-vous d’en **comprendre les grandes lignes**, car vous devrez utiliser plusieurs fonctions de ces fichiers pour implémenter `runScheduler()`.

### Note sur le Paramètre `addToReadyQueue`
- Si **`addToReadyQueue == true`**, le **processus en cours d’exécution** doit être ajouté à la **liste des processus prêts**.

**Réflexion :**
1. **Dans quelles conditions un processus peut-il être ajouté à cette liste ?**
2. **Dans quels cas un processus ne sera-t-il pas ajouté à cette liste ?**

---

## Fonctions Utiles
Plusieurs fonctions sont mises à votre disposition. Vous pourriez avoir besoin des fonctions suivantes :

- `addProcessToReadyQueue()` : Ajoute un processus à la **liste des processus prêts**.
- `klistRemoveEntryAtIndex()` : Retire une entrée d’une **liste de processus**.
- `_switchStack()` : Permet au **nouveau processus** de prendre le contrôle du processeur.

Vous aurez aussi probablement besoin de la **macro** :
- `DEFAULT_TIME_SLICE` : Définit la **durée d’exécution normale** d’un processus avant qu’il ne perde le contrôle.

---

## Détails de l’Implémentation de `runScheduler()`
Votre implémentation doit suivre ces **étapes** :

1. **Ajouter le processus en cours d’exécution** à la **liste des processus prêts** si `addToReadyQueue == true`.
2. **Trouver un processus prêt à s’exécuter** dans la **liste des processus en attente**.
3. Une fois le **nouveau processus trouvé**, appeler la fonction **`_switchStack()`** pour transférer l’exécution à ce processus.

Bien que cette fonction semble **simple**, son implémentation peut être plus complexe qu’il n’y paraît. **Assurez-vous de bien comprendre le fonctionnement du système** avant de commencer.

💡 **Conseil :** Vous serez prêt à implémenter `runScheduler()` lorsque vous serez capable d’**expliquer clairement le fonctionnement de l’aiguillage des processus dans LOS**.

---

## Validation du Fonctionnement
Une fois l’implémentation terminée, si tous les exercices ont été correctement réalisés **et qu’aucun bogue caché n’est présent**, le système devrait :

✅ **Afficher des numéros** à l’écran lors de l’exécution.  
✅ **Affichage des touches alphabétiques** du clavier lorsqu’elles sont pressées.

---

## Bonus : Un Bogue Caché
Il existe un **bogue dans l’implémentation de la pile du noyau**. Ce bogue pourrait **se révéler à ce stade de l’exercice**. 

❓ **Même si vous ne le rencontrez pas immédiatement, pouvez-vous identifier le problème et proposer des solutions pour le corriger ?**
