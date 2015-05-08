const int b = 4 ; // constante globale
int variable = -3 *  b / 2 ;  // variable initialisée à -6

// déclaration de fonction 
ok3(int a) ; ok4() ; 

// définition de la fonction ok(const int b) 
ok(const int b2, int c, int d){   

  printf("fonction ok : ") ; 
  variable = 77 ; 

  // affichage des arguments
  printf(b2) ; printf(" ") ; 
  printf(c) ; printf(" ") ; 
  printf(d) ; printf(" ") ;
  printf((b2+c+d)*-5) ; // depuis main, affiche -1105 mais devrait afficher -1085
                        // depuis ok2 devrait afficher -70
  printf("\n") ;
}

ok5() ; 

ok2(){ 
  int z = 14 ; 
  // int test11 = 7 ; // en décomentant, il n'y a plus de soucis avec cpt  
  int cpt = 4 ;  

  printf("\n");
  printf("fonction ok2\n") ; 
  
  printf("cpt = ") ; 
  printf(cpt) ;
  printf("\n");

  ok(5,7,2) ; 

  printf("cpt = ") ; 
  printf(cpt) ;
  printf("\n");

 ok3(5+z/(b+b)) ; 

  printf("cpt = ") ; 
  printf(cpt) ;
  printf("\n");


  if (b/7) { 
    z = 7 ; 
  }  
 
  printf("variable = ") ; 
  printf(variable) ;
  printf("\n");

  while(0) {
    variable = -z * 5 + 2 / b ; 
    cpt = cpt - 1 ; 
    printf(cpt) ; 
    printf(" ") ; 
  }
  printf("\n");
} 

// programme principal 
main() { 
  const int c1,c2,c3 = 1 ; 
  // int test11 = 7 ; // en decommentant, il n'y a plus de soucis avec a  mais toujors avec c3
  int a = 1, j, i = 7, z = 12;  
  int test1 = 3 *  b / 2 + 15/5 ; // 9   

  printf("\n") ;
  printf("Lancement programme\na= ") ; 

  printf(a) ; printf("\n") ; 

  printf("test1 = ") ; 
  printf(test1) ; 
  printf("\n") ;

  test1 = b - 2 + -7 * 2 ; // -12    
  printf("\ntest1 = ") ; 
  printf(test1) ; 

  printf("\nvariable = ") ; printf(variable) ;
  variable = ( z + a ) + 2 * -5 +  1  ; // égal à 4  
  printf("\nvariable - a = ") ; 
  printf(variable) ; printf(" - ") ; printf(a) ;
  printf("\n") ;

  printf("\nz = ") ;
  printf(z) ; 
  printf("\na = ") ; 
  printf(a) ;
  printf("\n ") ;  

  /* appel à deux fonctions */ 
  ok2() ;  // en comentant, regle soucis plus bas

  printf("z - b - a = ") ;
  printf(z) ; printf(" ") ;
  printf(b) ; printf(" ") ; 
  printf(a) ; printf("\n") ; 

  printf((z*b*2+9-a)) ; printf(" "); // donne 101 et devrait etre 104 ! 
  printf(c3) ; printf(" \n") ; // donne 8 et devrait etre 1 ! 
  ok((z*b*2+9-a),4/3+c3,111)  ; // somme des args theorique = 217
  
  printf("z - b - a = ") ;
  printf(z) ; printf(" ") ;
  printf(b) ; printf(" ") ; 
  printf(a) ; printf("\n") ; 


  printf("\nvariable = ") ; 
  printf(variable) ; 

  variable = 0 ; 
  printf("\nvariable = ") ; 
  printf(variable) ; 
  printf("\n") ;
  
  if(variable) { 
    a = 444; 
    printf("Dans la boucle if\n") ; 
  } 
  else { 
    if(a-77) {
      printf("Dans la deuxième boucle if\n") ;
    }    
  }


}

/* ancienne définition de la fonction ok3(int a) précédemment déclarée
   ok3(int a){
   int z = 44 ;  
   while(111) {
   printf(z) ;
   } 
   } */


// définition de la fonction ok3(int a) précédemment déclarée
ok3(int a){
  int z = 4 ;  
  printf("fonction ok3\n") ; 
  while(z) {
    z = z - 1 ; 
    printf(z) ;
    printf("\n") ;
    if(z) { 
      printf("z est différent de 0\n") ;
    }
    else { 
      printf("z = 0\n") ;
    }  
  } 
} 
