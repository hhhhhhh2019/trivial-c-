#include <stdio.h>
#include <gnum.h>
#include <gpoly.h>
#include <reedsolomon.h>
#include <stdio.h>


char rand() {
	FILE* f = fopen("/dev/urandom", "rb");
	char r;
	fread(&r, 1, 1, f);
	fclose(f);
	return r;
}


int main() {
	int N = 15;
	int K = 9;

	GPoly p(9, GNum(1),GNum(2),GNum(3),GNum(4),GNum(5),GNum(6),GNum(7),GNum(8),GNum(9));

	GPoly g(7, GNum(12),GNum(10),GNum(12),GNum(3),GNum(9),GNum(7),GNum(1));

	for (int _ = 0; _ < 1000; _++) {
		printf("----------\n");

		GPoly c = encode(p, g, N, K);

		for (int i = 0; i < 3; i++) {
			int id = rand()%c.data.size();
			int v = rand()%filed_size;
			c.data[id] = GNum(v);

			printf("%d %d\n", id, v);
		}

		/*c.data[7] = GNum(1);
		c.data[8] = GNum(5);
		c.data[13] = GNum(4);*/

		GPoly r = decode(c, g, N, K);

		//p.print("p = ");
		//r.print("r = ");

		if (!(p == r)) {
			printf("error\n");
			break;
		}
	}
}
