int a = 10;

p() {
	printf(a);
	if (a) {
		a = a - 1;
		//p();
	}
}

main() {
	p();
}