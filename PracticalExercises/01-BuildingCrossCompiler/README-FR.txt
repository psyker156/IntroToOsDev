# Construction du compilateur croisé

## Prérequis :
Assurez-vous d’avoir suivi les directives de préparation à la formation. Plus précisément, les paquets suivants devraient être installés :

- `libgmp-dev`
- `libmpfr-dev`
- `libmpc-dev`
- `libisl-dev`

Vous devriez aussi avoir téléchargé le code source pour **GCC 6.2** et **Binutils 2.27**.

## La construction du compilateur :

1. Créer le dossier `~/src`
2. Extraire **GCC** à l’emplacement `~/src/gcc`
3. Extraire **Binutils** à l’emplacement `~/src/binutils`
4. Créer les répertoires suivants :
   ```sh
   mkdir ~/i686-elf-CC
   mkdir ~/i686-elf-CC/binutils-i686-elf-obj
   mkdir ~/i686-elf-CC/i686-elf
   ```
5. Positionnez-vous à l’intérieur du répertoire `~/i686-elf-CC/binutils-i686-elf-obj`
6. Émettre les commandes suivantes :
   ```sh
   ~/src/binutils/configure --prefix=/home/user/i686-elf-CC/i686-elf --target=i686-elf --disable-werror
   make
   make install
   ```
7. Après l’exécution de ces commandes, les binaires formant **Binutils** seront dans le répertoire `~/i686-elf-CC/i686-elf`.  
   Il est important d’ajouter ce répertoire à votre `PATH`. Vous pouvez utiliser la commande suivante :
   ```sh
   export PATH="/home/user/i686-elf-CC/i686-elf/bin:$PATH"
   ```
8. Vous pouvez vérifier que la commande a bien fonctionné en utilisant :
   ```sh
   echo $PATH
   ```
9. Créer le répertoire et déplacer vous à l’intérieur de ce dernier :
   ```sh
   mkdir ~/i686-elf-CC/gcc-i686-elf-obj
   cd ~/i686-elf-CC/gcc-i686-elf-obj
   ```
10. Émettre la commande suivante :
    ```sh
    ~/src/gcc/configure --prefix=/home/user/i686-elf-CC/i686-elf --target=i686-elf --program-prefix=i686-elf --without-headers --enable-languages=c,c++
    ```
11. Vous pouvez maintenant émettre les commandes suivantes :
    ```sh
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
    ```
12. Si tout a bien fonctionné, le **compilateur croisé** devrait être dans le répertoire `~/i686-elf-CC/i686-elf/bin`.

---

## Validation du bon fonctionnement du compilateur

Afin de valider le bon fonctionnement de votre compilateur, ouvrez le dossier **Validation** et exécutez le script `buildRun`.  
Si votre compilateur fonctionne correctement, un message devrait s’afficher dans la fenêtre de **qemu**.  

En cas de doute, demandez de l’aide.
