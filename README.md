# Sokoban

## Description
Sokoban est un jeu de puzzle classique dans lequel le joueur déplace des boîtes pour les amener sur des points de stockage dans un entrepôt. Cette implémentation en C utilise la bibliothèque ncurses pour créer une interface en mode terminal.

## Caractéristiques
- Rendu graphique en ASCII dans le terminal
- Gestion du déplacement du joueur avec les touches directionnelles
- Détection des victoires et des impasses (deadlocks)
- Possibilité de réinitialiser la partie à tout moment
- Chargement de cartes personnalisées depuis des fichiers texte

## Prérequis
- GCC ou autre compilateur C
- Bibliothèque ncurses
- Make

## Installation
1. Clonez le dépôt:
   ```bash
   git clone git@github.com:Amayyas/Sokoban.git
   cd Sokoban
   ```

2. Compilez le projet:
   ```bash
   make
   ```

## Utilisation
Pour lancer le jeu avec une carte prédéfinie:
```bash
./sokoban maps/map.txt
```

Vous pouvez également utiliser votre propre carte en créant un fichier texte suivant le format:
- `#` représente un mur
- `P` représente le joueur
- `X` représente une boîte
- `O` représente un point de stockage
- ` ` (espace) représente un espace vide

### Contrôles
- Flèches directionnelles: déplacer le joueur
- Espace: réinitialiser la partie
- Échap: quitter le jeu

## Tests
Des tests unitaires sont disponibles dans ce projet. Pour les exécuter:
```bash
make tests_run
```

Pour générer un rapport de couverture:
```bash
make coverage
```

## Structure du projet
```
Sokoban/
├── include/          # Fichiers d'en-tête
│   └── sokoban.h
├── maps/             # Cartes de jeu
│   ├── map.txt
│   └── simple_map.txt
├── src/              # Code source
│   ├── check.c       # Vérifications des conditions du jeu
│   ├── count_elements.c # Comptage des éléments
│   ├── display.c     # Affichage du jeu
│   ├── game.c        # Logique principale du jeu
│   ├── main.c        # Point d'entrée
│   ├── map.c         # Gestion des cartes
│   ├── player.c      # Gestion du joueur
│   ├── reset.c       # Réinitialisation du jeu
│   └── valid_map.c   # Validation des cartes
└── Makefile          # Instructions de compilation
```
