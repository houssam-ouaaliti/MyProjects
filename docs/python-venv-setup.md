# Setup Guide

## Problème initial
À chaque ouverture du projet dans VS Code, il fallait réinstaller les dépendances (vpython, opencv, etc.).

## Solution : Configurer un environnement virtuel avec VS Code

### Étape 1 : Créer l'environnement virtuel

```bash
python3 -m venv venv --copies
```

Le flag `--copies` est important sur WSL pour éviter les problèmes de liens symboliques.

### Étape 2 : Activer l'environnement virtuel

```bash
source venv/bin/activate
```

### Étape 3 : Installer les dépendances

```bash
pip install vpython opencv-python
```


### Étape 4 : Configurer VS Code

Créez un fichier `.vscode/settings.json` à la racine du projet :

```json
{
    "python.defaultInterpreterPath": "${workspaceFolder}/venv/bin/python3"
}
```

### Étape 5 : Relancer VS Code

Fermez complètement VS Code et rouvrez-le. Il devrait maintenant détecter automatiquement l'interpréteur Python du venv.

## Vérification

Pour vérifier que tout fonctionne :

```bash
which python3
```

Cela devrait afficher un chemin qui contient `venv/bin/python3` et non `/usr/bin/python3`.

## Utilisation

Une fois tout configuré :
- Plus besoin de réinstaller les packages à chaque fois
- VS Code utilisera automatiquement le venv du projet
- Lancez vos scripts normalement : `python3 main.py`

## Note pour WSL

Si vous êtes sur Windows Subsystem for Linux (WSL), assurez-vous d'utiliser le flag `--copies` lors de la création du venv pour éviter les problèmes de liens symboliques.

## Structure du projet

Chaque projet doit avoir son propre environnement virtuel :

```
Projects/
├── Rubiks_cube/
│   ├── venv/
│   ├── .vscode/
│   │   └── settings.json
│   ├── 2D
│   └── 3D
│
└── Mastermind/
    ├── venv/
    ├── .vscode/
    │   └── settings.json
    └── ...
```

Chaque projet a son propre `venv/` et son propre `.vscode/settings.json` qui pointe vers son venv respectif.

## .gitignore

Chaque développeur créera son propre venv en clonant le repo.
