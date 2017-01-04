#include "helper.h"

BigInt max(BigInt a, BigInt b) {
	if (a > b) {
		return a;
	}
	return b;
}

void checkPointer(void * ptr, std::string msg) {
	if (ptr == NULL) {
		std::cerr << msg;
		throw ERR_CODE;
	}
}