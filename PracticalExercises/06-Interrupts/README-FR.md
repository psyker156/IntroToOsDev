# Implémentation du Système de Gestion des Interruptions

## Objectif de l’Exercice
Dans cet exercice, vous implémenterez le code requis pour **activer les interruptions** sur **x86 32 bits**. Plus précisément, vous implémenterez les fonctions suivantes :

- `ksetupInterrupts()` (**implémentation partielle**)
- `kbuildInterruptGate()`
- `_setIDTR()` (**en assembleur**)
- `_activateInterrupts()` (**en assembleur**)

Les **deux premières** fonctions sont situées dans le fichier `src/x86/interrupt.c`, tandis que les **deux autres** doivent être implémentées dans `src/x86/ASMinterrupt.asm`.

---

## Explications Supplémentaires
Les fonctions `_setIDTR` et `_activateInterrupts` doivent être **implémentées en assembleur** :

- **L’instruction `STI`** active les interruptions.
- **L’instruction `LIDT`** charge le registre **IDTR**, qui est nécessaire pour gérer les interruptions.
- Des **exemples de code** ont été présentés en cours.
- La configuration du **registre IDTR** est **très similaire** à celle du **registre GDTR** (voir l’exercice sur la configuration des segments).

---

## Étapes de l’Exercice
L’exercice comporte **quatre étapes**. Comme les fonctions haut niveau **dépendent** de `_setIDTR` et `_activateInterrupts`, nous commencerons par ces dernières.

### 1. Implémentation de `_activateInterrupts()`
- Cette fonction est située dans `src/x86/ASMinterrupt.asm`.
- L’instruction `STI` peut être utilisée pour activer les interruptions.
  - **Astuce** : Faites des recherches sur cette instruction si nécessaire.
- L’implémentation doit être **simple**, car cette fonction ne fait **que** l’activation des interruptions.
- **Attention au respect de l’ABI !**

### 2. Implémentation de `_setIDTR()`
- Faites une recherche sur **l’instruction `LIDT`** pour bien comprendre son fonctionnement.
- Consultez le code de **`_loadGDTR`** (début de la fonction) pour vous en inspirer.

### 3. Implémentation de `kbuildInterruptGate()`
- Cette fonction construit un **descripteur d’interruption propre**.
- Consultez la **documentation** et la **présentation** pour comprendre son implémentation.

### 4. Finalisation de `ksetupInterrupts()`
- La fonction est **partiellement implémentée**.
- Une section **`Exercise 6 – interrupts`** est marquée dans le code.
  - **C’est ici que vous devez compléter l’implémentation.**

Dans cette fonction, vous devez **construire deux descripteurs d’interruption** :

1. **Interruption de l’horloge** (Timer Interrupt)
   - Gérée par **`_handlerClock`**.
   - Située à **`IDT_BASE + 32`** dans le vecteur d’interruption.

2. **Interruption du clavier** (Keyboard Interrupt)
   - Gérée par **`_handlerKeyboard`**.
   - Située à **`IDT_BASE + 33`** dans le vecteur d’interruption.

ℹ️ **`IDT_BASE`** est défini dans `src/x86/interrupt.h` et représente l’adresse où doit être configuré le **vecteur d’interruption**.

---

## Validation du Bon Fonctionnement
Pour valider que le **système de gestion des interruptions** fonctionne correctement, plusieurs options s’offrent à vous :

- **Accéder à une adresse mémoire interdite** (hors de la zone mappée) devrait déclencher une **erreur de segmentation** affichée par le système.
- **Placer des points d’arrêt** avec un **débogueur** pour suivre l’exécution.
- **Expérimenter avec ces techniques** est fortement recommandé pour bien comprendre le système et son fonctionnement.