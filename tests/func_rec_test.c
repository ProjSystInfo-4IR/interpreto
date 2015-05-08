/*int a = 1 + 2 * 2 + - 1 ;
int b = a/2 ; */
int a = -3 ;  
p() {
	printf(a);
	if (a) {
		a = a + 1;
		p();
	}
printf(a) ; 
}

main() {
	p();
}
