void main(void) {

	unsigned short *arr = (unsigned short *) 0xB8000;

	*arr = (((0 << 4) | 5) << 8) | 'A'; 

	while (1) {}
}
