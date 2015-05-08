# interpreto
Interpréteur du langage ASM généré par [compilo](https://github.com/ProjSystInfo-4IR/compilo) 

### Instructions
 
## Utilisation 
1- Makefile : obtention du programme "simpleGCC", notre compilateur C simplifié : 

`~/compilo$ make`

2- Compilation d'un fichier C (*cf plus bas les fonctionalités C supportées*) :

`~/compilo$ ./simpleGCC [fichier_a_compiler.c] [flags]`


- Sans flags, seules les erreurs de compilation apparaissent et le fichier de sortie (par default) est output.asm .
- Rajouter le flag `-v` permet d'avoir des informations concernant la compilation du fichier C (affichage de la table des symboles finale, affichage de la table des fonctions, ...). 
- Rajouter le flag `-o` permet de spécifier le nom de fichier de sortie du compilateur.


## Précisions de codage liées à notre compilateur simplifié :
* Variables et constantes : le seul type accepté est integer (int) 
* Variables locales : les déclarations dans la fonction doivent se faire avant toute instruction 
* Déclarations des variables globales : elles doivent se faire au tout début du fichier C (avant toute déclaration de fonctions)  
* Expressions arithmétiques : elles ne sont possibles que sur des integers ( '(', ')', '+', '-', '*', '/' uniquement) 
* Expressions conditionnelles IF et WHILE : 0 vaut "false", les autres integers valent "true" 
* Fonctions déclarées / définies : Toute déclaration (et définitions) de fonctions peut se faire avant ou après le main ; notez que le compilateur sait faire la différence entre déclarations et définitions de fonctions
* Arguments des fonctions : 0, 1  ou plusieurs aarguments pour les fonctions, sauf pour main (pas d'arguments)
* Affichage : Prise en charge de printf(arg1) avec arg1 de type int ou string (char*).   
* Traitement des erreurs : Affiche la ligne du fichier C où une erreur est détectée. 


## Limites (ce qu'il faudrait revoir)
* Fonctions (main compris) : les fonctions ne retournent rien, elles sont déclarées directement sans type défini ( ex : `fonction1(arg1, arg2) { ...} ` )  
* Affichage avec printf (string) : retransciption en `ASM PRI {string}` à revoir ? Ajouter le type string/char* dans la table des symboles ?


## Informations complémentaires 
* Instructions ASM utilisés en supplément de celles proposées dans le sujet du projet :  
    - `CALL {ligneASM}` ; appel à une fonction
    - `RET` ; retour fonction précédente
    - `PUSH @adresse` ; empiler l'argument situé à adresse @adresse dans la table des symboles 
    - `POP @adresse` ; récupérer le dernier élément empilé et l'affecter à la variable d'adresse @adresse de la table des symboles
    - `LEAVE` ; instruction pour quitter le programme
* Gestion des arguments : `PUSH` de chaque argument lors de l'appel d'une fonction (dans le main  par exemple). Une fois dans la fonction en question, on affecte les arguments (variables locales) avec des `POP`.   
* Table des symboles contenue dans *tab_symboles.c* : Tableau C définissant chaque variable déclarée. Chaque variable est liée à une fonction (ou à GLOBAL pour des variables globales) 
* Table des instructions contenue dans *tab_ic.c* : Tableau C permettant de manipuler les expressions conditionnelles IF et WHILE
* Table des fonctions contenue dans *tab_fct.c* : Tableau C définissant chaque fonction déclarée. 
* Traitement des erreurs : supprime le fichier ASM créé si il y a eu des erreurs de compilation




