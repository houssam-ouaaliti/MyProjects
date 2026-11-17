**Powershell:**
wsl hostname -I
netsh interface portproxy show v4tov4

=> Si l'IP WSL n'a pas changé, tout est bon

**WSL:**

sudo service mysql start


Réinitialiser la base:

mysql -u root -p -e "DROP DATABASE jeux; CREATE DATABASE jeux;"

Mdp: root



Réimporter la base:

cd /mnt/c/Users/HP/Desktop/Projects/jeu-cartes-multijoueurs/backend

mysql -u root -p jeux < src/main/resources/init.sql

Mdp: root




Terminal 1:

cd /mnt/c/Users/HP/Desktop/Projects/jeu-cartes-multijoueurs/backend

./mvnw spring-boot:run



Terminal 2:

cd /mnt/c/Users/HP/Desktop/Projects/jeu-cartes-multijoueurs/frontend

npm run dev





**Sur un seul pc:**

Chrome normale et privé:

http://localhost:5173


**Sur 2 pc:**

* pc1:

Terminal 1:

cd /mnt/c/Users/HP/Desktop/Projects/jeu-cartes-multijoueurs/backend

./mvnw spring-boot:run



Terminal 2:

cd /mnt/c/Users/HP/Desktop/Projects/jeu-cartes-multijoueurs/frontend

npm run dev -- --host 0.0.0.0



Terminal 3:

hostname -I



* pc2:

chrome: http://192.168.1.105:5173/