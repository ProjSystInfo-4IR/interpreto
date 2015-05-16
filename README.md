# interpreto
Interpréteur du langage ASM généré par [compilo](https://github.com/ProjSystInfo-4IR/compilo) 

## Récupération du projet
* Avant tout, il vous faut absolument le répertoire compilo de la partie précédente, et avoir obtenu le fichier simpleGCC avec le Makefile. De même que précédemment, il suffit de “cloner” notre répertoire Git interpreto :

` ~/compilo$ cd .. ` 

` ~$ git clone https://github.com/ProjSystInfo-4IR/interpreto.git `

* Les deux dossiers interpreto et compilo doivent impérativement être dans le même répertoire. Toute la partie interpréteur du projet se trouve dans le répertoire interpreto .

 Il est possible d’interpréter un fichier ASM ou bien de demander à compiler un fichier C donné avec simpleGCC du répertoire compilo puis interpreter le fichier ASM o.tmp.asm obtenu.


## Contenu du projet (partie interpreto) :
* Analyseur lexical ASM source.lex
* Analyseur syntaxique ASM  source.yacc
* Fichier code.c : Tableau C contenant toutes les instructions du fichier ASM interprété. Ce fichier contient également une méthode permettant de simuler l’execution du fichier ASM. 
* Fichier  mem.c : Simulation de la mémoire par un tableau C. Ce fichier permet de manipuler les variables et les constantes (correspondances entre adresse et valeur).
* Fichier stack.c : Simulation d’une pile avec un tableau C. Ce fichier permet de manipuler deux piles ; la pile des adresses de retour de fonctions et la pile des arguments.
* Script mygcc : Script permettant de compiler un fichier C donné (création d’un fichier o.tmp.asm) et ensuite de l’interpréter avec notre interpreteur. (cf plus bas)
* Gestionnaire de l’affichage et des erreurs de compilation : Intégration de la partie  dumb-logger développé (fichier dumb-logger.c). 

## Utilisation de l’interpreteur “maison” 

* Makefile : obtention du programme itp, notre interpréteur de fichier assembleur. 

`~/interpreto$ make `

* Lancement de l'interpréteur 

1.  Interprétation d'un fichier ASM :

` ~/interpreto$ ./itp [fichier.asm] [flags] `

Sans flags, le contenu des printf (et éventuellement les erreurs d’interprétation) apparaissent. Rajouter le flag -v permet d'avoir des informations concernant la compilation du fichier C (Affichage d’infos sur le bas de pile, etc.).

2. Interprétation d’un fichier C : 

`~/interpreto$ ./mygcc [fichier.c] `

Ce script fait appel à simpleGCC du répertoire compilo ; ensuite le script fait appel à l’interpréteur itp pour compiler le fichier ASM créé o.tmp.asm. 
A noter que différents fichiers C de tests sont fournis dans le répertoire interpreto/test_files.


## Précisions 


* Le parsing consiste à remplir le tableau EXEC_CODE du fichier code.c, EXEC_CODE devant contenir toutes les instructions du fichier ASM interprété à la fin du parsing. Une fois le parsing terminé, le fichier code.c simule l’execution du programme (fonction code_run(); ).  

* Gestion variables locales / globales : 
	* Le premier CALL est un appel au main et donc le deuxième argument représente le nombre de variables globales. On mémorise cette valeur là dans mem.c. 
	* Dans mem.c, pour les fonctions mem_get(adr) / mem_set(adr), si adr est inférieur au nombre de variables globales, alors il n’ y a pas de sauts relatif car il s’agit du cas où on traite une variable globale. 
Dans le cas contraire, il s’agit d’une variable locale, donc on affecte adr = ebp + adr  , avec ebp le bas de pile de la mémoire.
	* On initialise egalement le bas de pile ebp à 0 au tout début. A chaque fois qu’on rencontre un CALL @adresse nb_var, on indique que ebp = ebp + nb_var
	* A chaque fois qu’on rencontre un RET, on indique que ebp = ebp précédent (pop)
* Pour implémenter la gestion des fonctions, nous avons deux piles : 
  1. Pile des arguments :
   * A chaque fois que l’interpréteur rencontre un PUSH @adresse, il va chercher la valeur V1 du symbole stockée dans la mémoire (mem.c) à l’adresse @adresse et empile cette valeur V1 (la place en haut de la pile). 
   * A chaque fois que l’interpréteur rencontre un POP @adresse, il dépile (prend la valeur V1 la plus en haut de la pile des arguments) et le symbole stocké à l’adresse @adresse dans la mémoire (mem.c) est affecté à cette valeur V1. 
   2. Pile des adresses de retour / bas de pile :
   * A chaque fois que l’interpréteur rencontre un CALL @ nb_var à la ligne X, il empile la valeur ebp puis il empile la valeur X+1 (place ebp puis X+1 en haut de la pile) et exécute le code à partir de la ligne @. La valeur de ebp est changé à  ebp + nb_var
   * A chaque fois que l’interpréteur rencontre un RET, il dépile Y puis Z (prend la valeur du dessus Y, puis prend la valeur du dessus Z). Z est le précédent ebp empilé, on affecte donc ebp = Z. 
Y est la ligne ASM de retour, le code s’execute par la suite à partir de la ligne Y.

* La fonction printf({string}) prend en charge les retours à la ligne ‘ \n ‘ ; penser à faire des retours à la ligne (ou au moins affichage d’espaces) après chaque printf({integer})  pour une meilleure lisibilité. 


* Gestion des erreurs : La ligne du fichier ASM où une erreur est détectée est informée.

## Limites (ce qu'il faudrait revoir) : 
* Nous voulions simuler la pile ASM classique (telle que nous l’avons vu en cours de sécurité/buffer overflow) mais n’avons pas réussi à correctement l’implémenter (problème notamment en cas de fonctions récurrentes). Nous avons choisi la facilité en distinguant deux piles distinctes. 
* Il n’est possible d’interprêter qu’un seul caractère ‘\n’. Mettre plusieurs ‘\n’ à la suite (que ce soit dans le même printf ou dans deux printf consécutifs) nous fait afficher une erreur surprenante : 

` *** Error in ./itp: malloc(): memory corruption: 0x0000000000a3b000 ***
./mygcc: line 14:  7869 Aborted                 (core dumped) ./itp o.tmp.asm `





