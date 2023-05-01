#include <stdio.h>
#include <gnum.h>
#include <gpoly.h>
#include <reedsolomon.h>


unsigned long rand() {
	FILE* f = fopen("/dev/urandom", "rb");
	unsigned long r;
	fread(&r, 8, 1, f);
	fclose(f);
	return r;
}


int main() {
	int N = 255;
	int K = 128;

	GPoly g = gen_g(N-K+1);

	FILE* f = fopen("data.bin", "rb");

	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	int count = size / K;

	for (int i = 0; i < count; i++) {
		unsigned char data[K];

		fread(data, K, 1, f);

		GPoly p;

		for (int j = 0; j < K; j++)
			p.data.push_back(GNum(data[j]));


		GPoly c = encode(p,g,N,K);

		for (int e = 0; e < 63; e++) {
			unsigned int id = rand() % N;
			unsigned int v = rand() % filed_size;
			c.data[id].value = v;
		}

		GPoly r = decode(c,g,N,K);

		if (!(r == p))
			printf("error\n");
	}

	fclose(f);
}
