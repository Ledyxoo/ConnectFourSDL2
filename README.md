# Connect Four (Puissance 4) - SDL2

Un jeu de Puissance 4 classique développé en C utilisant la bibliothèque SDL2. Ce projet a été porté de Windows vers Linux et est désormais compatible avec les deux plateformes.

## 🎮 Comment jouer

Le but est d'aligner 4 pions de votre couleur (horizontalement, verticalement ou diagonalement).

1. Lancez le jeu.
2. Choisissez si vous voulez jouer contre l'IA ou contre un autre joueur local.
3. Utilisez les touches numériques pour placer vos pions :
   - **0 à 6** : Choisir la colonne correspondante.
   - **Échap** : Quitter le jeu.

## 🛠️ Installation et Compilation

### Prérequis
Vous devez avoir installé les bibliothèques SDL2 suivantes :
- SDL2
- SDL2_image
- SDL2_mixer
- SDL2_ttf

#### Sur Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

#### Sur Windows
1. Installez [CMake](https://cmake.org/download/).
2. Installez un compilateur (ex: Visual Studio avec C++, ou MinGW).
3. Téléchargez les versions de développement de SDL2, SDL2_image, SDL2_mixer et SDL2_ttf sur le site de [libsdl.org](https://www.libsdl.org/).

### Compilation (Toutes plateformes)
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 📦 Exécutables (Releases)

Si vous ne souhaitez pas compiler le code vous-même, vous pouvez trouver des exécutables pré-compilés dans la section **Releases** de ce dépôt GitHub.
- **Linux** : Téléchargez `ConnectFour-Linux.tar.gz`, extrayez-le et lancez `./ConnectFour`.
- **Windows** : Téléchargez `ConnectFour-Windows.zip`, extrayez-le et lancez `ConnectFour.exe`.

## 📁 Structure du Projet
- `src/` : Fichiers sources (.c)
- `include/` : Fichiers d'en-tête (.h)
- `Assets/` : Images et ressources du jeu
- `CMakeLists.txt` : Fichier de configuration pour la compilation multiplateforme

---
Développé par Killian dans le cadre de ses études et mis à jour pour Linux.
