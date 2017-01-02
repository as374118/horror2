#include "helper.h"

BigInt max(BigInt a, BigInt b) {
	if (a > b) {
		return a;
	}
	return b;
}