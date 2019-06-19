unsigned char bpow(int i) {
	
	unsigned char c = 1;

	while (i-- > 0) {
		c *= 2;
	}

	return c;
}

unsigned char set_bit (unsigned char c, int index, int value) {

	index = 7 - index;

	if (value) {
		c |= bpow(index);
	} else {
		c &= 0xff - bpow(index);
	}
	return c;
}

int get_bit(unsigned char c, int index) {

	index = 7 - index;

	if (c & bpow(index)) {
		return 1;
	}
	else {
		return 0;
	}

}
