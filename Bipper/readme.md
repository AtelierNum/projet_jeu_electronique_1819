<h1> Projet Arduino : Jeu électronique </h1>
Lúna Azibeiro _ Giulia Savelli _ I3B </br>
</br>

<img src = "bipeur.gif">

<h3> Scénario du jeu : Bipeur</h3>
Nombre de joueur : 1 joueur </br>
Temps d'une partie : 5 secondes </br>
</br>
Un boitier avec trois lumières, chacunes reliées à un bouton. Les lumières s'allument aléatoirement chacune leur tour. Dès qu'une lumière s'allume, il faut appuyer le plus rapidement possible sur le bouton correspondant pour éteindre la led en question. Pour gagner la partie, le but est de parvenir à éteindre plus de 25 fois les lumières en moins de 5 secondes. Si on gagne la partie, toutes les leds s'éteignent. Mais si on se trompe de bouton, on perd la partie et toutes les leds s'allument, le jeu s'arrête. Le résultat s'affiche sur l'ordinateur. Pour recommencer une partie, il suffit d'appuyer sur le bouton reset.</br>
</br>

<h3> Notice de montage </h3>
Lisite du matériel : 
<li> Une carte Arduino </br>
<li> Une breadboard </br>
<li> 3 résistances de 10k </br>
<li> 3 résistances de 1k </br>
<li> 3 leds </br>
<li> 3 boutons d'arcade </br>
<li> Un bouton poussoir</br>
<li> Des câbles </li>
</br>
Assemblage :</br>
1_ Branchement des leds sur la breadboard. Une résistance à été associé à chacune d'entre elles, que nous avons ensuite mis en entrée sur la carte Arduino.</br>
2_ Branchement des boutons poussoirs à la breadboard. Nous avons relié un bouton à chaque led. Nous avons là aussi rajouter des resistances. Les boutons ont été branché en sortie.</br>
3_ Branchement du bouton "reset". Que nous avons branché au reset et à la masse.</br>
4_ Nous avons ensuite rajouter des câbles pour pouvoir ouvrir et fermer correctement à la maquette.</br>
5_ Nous avons ensuite remplacé les boutons poussoirs par des boutons d'arcade que nous avons ajouté à la maquette et relié à la carte Arduino.</br>
6_ Pour finir, nous avons rajouté des câbles au bouton reset pour l'incruster dans notre maquette.</br>
</br>

<img src = "azibeiro_savelli_montage.JPG">

Maquette : </br>
1_ Nous avons construit une boite. Puis positionner notre circuit à l'intérieur.</br>
2_ Nous avons fait des trous sur le dessus de la boîte afin de pouvoir y positionner les boutons d'arcade ainsi que les leds.</br>
3_ Nous avons fait un trou sur le côté de la boîte afin d'y placer le bouton reset.</br>
4_ Enfin, nous avons fait un trou sur le devant de la boîte dans le but de faire ressortir le câble USB qui devra être connecté à l'ordinateur afin de pouvoir lancer le jeu.</br>
</br>

<img src = "azibeiro_savelli_maquette.JPG">

Côtes : </br>
<img src = "cote.png">

<h3> Code Arduino commenté </h3>
<img src = "initialiser.jpg">
Au début du code on initialise toutes les variables pour déclarer les leds et les boutons poussoirs qui sont reliés à la carte Arduino.</br>
</br>

<img src = "void setup.png">
On définit que les boutons poussoirs sont des entrées et que les leds sont des sorties, et que les lumières sont initialement éteintes.</br>
</br>

<img src = "void loop1.png">
On déclare un nombre aléatoire, qui va allumer une première led 
Première boucle réaliser on peut passer au test suivant. </br>
</br>

<img src = "void-loop-2-tirage1.png">
Deuxième test, on lit si le bouton où l’on tape est associé à la led allumée si c’est vérifié la lumière s’éteint. 
Un autre random s’éxecute pour allumer une autre ou la même led aléatoirement.  </br>
</br>

<img src = "void-loop-2-tirage1-else.png">
Si on n’appuie pas sur le bon bouton toutes les leds s’allument, et le jeu est fini. </br>
</br>

<h3> Schémas du circuit électronique </h3>
<img src = "azibeiro_savelli_schema.png" width = "50%"> 
</br>
<img src = "azibeiro_savelli_circuit-electrique.png">