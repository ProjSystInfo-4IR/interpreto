p(int a) {
	printf(a);
	if (a) {
		p(a-1);
	}
}

main() {
	p(1000);
}