# Fichier d'automatisation pour la physique numérique (BA 3 physique EPFL)

Le programme fonctionne sous Linux. Une seule règle: si vous trouvez ce fichier, vous pouvez l'utiliser. Je vous demanderai simplement de ne pas le diffuser en masse. Merci. Le fichier "Convergence.m" permet de dessiner le graphe dans MatLAB du fichier de sortie généré par le programme en C++. Le fichier "Exercice1_3cEmec.m" permet de générer une figure pour une partie de l'exercice 1.3 c).

<h2>Objectif du programme</h2>
Le but du programme est de simplifier la gestion de tâches pouvant être automatisées. Il est notamment utile dans l'étude de convergence puisqu'il permet de faire plusieurs simulations à la fois et d'enregistrer les nsteps ainsi qu'une donnée choisie par l'utilisateur dans le fichier nouvellement généré: "ValeursMatLab.txt" .

<h2>Avant de commencer</h2>
<p>Les premiers réglages sont assez simples. Il faut commencer par modifier des informations au début du fichier entre les balises : "// //!\\ IMPORTANT: A MODIFIER".
  
L'utilisateur doit commencer par spécifier son fichier de configuration, l'exécutable de son exercice, son fichier d'output, ainsi que la colonne du fichier d'output qu'il veut utiliser pour l'analyse de convergence dans MatLAB (Attention, on se réfère à la première colonne avec l'indice 1 (et non 0)).</p>

<h2>Fonctionnement</h2>
<p>Le programme crée une copie du fichier de configuration si elle n'existe pas pour pouvoir le réinialiser plus tard. Puis il propose trois options à l'utilisateur: modifier complètement le fichier de configuration en appuyant sur 'o' et effectuer plusieurs simulations (ou une seule, au choix de l'utilisateur), réinitialiser le fichier de configuration grâce à la copie en choisissant 'r', et finalement effectuer simplement plusieurs simulations sans modifier le reste du fichier de configuration en appuyant sur toute autre touche.</p>

<p>Dans le cas où l'utilisateur choisit toute touche en dehors de 'r', le programme lui demande 3 informations: le nombre de nsteps voulu pour la première simulation, le nombre de simulations à effectuer, ainsi que le coefficient entre les nsteps de deux simulations.
  
  _Exemple: On choisit nsteps = 1'000, 4 simulations à faire, et un coefficient de 2. Alors le programme effectuera respectivement les simulations avec comme nombre de nsteps les valeurs suivantes: 1'000, 2'000, 4'000, 8'000 et 16'000._ </p>

<p> Choisir 'o' permet de modifier toutes les valeurs du fichier d'output avant de lancer les simulations. De plus, appuyer sur la touche 'r' restaure simplement le fichier de configuration puis ferme le programme.</p> 

  
