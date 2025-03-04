#include <stdio.h>

//int cmp(const void*, const void*);

int main(void) {
	FILE *in, *out;
	int max7[7], curr7[7];
	int sumMax, sum, curr, i, j, k, flag;
	
	k = 0; flag = 1;
	
	in = fopen("data.dat", "r");
	if (in == NULL) {
		out = fopen("data.res", "w");
		fprintf(out, "ERROR\n");
		fclose(out);
		return -1;
	}

	while (fscanf(in, "%d", &curr) == 1) {
		if (k == 0) {
			curr7[0] = curr;
			sum = curr;
			max7[0] = curr;
			sumMax = curr;
			k++;
		} else if (k < 7) {
			flag = 1;
			for (i = 0; i < k; ++i) {
				if (curr == curr7[0]) {
					curr7[0] = curr;
					sum = curr;
					max7[0] = curr;
					sumMax = curr;
					k = 1;
					flag = 0;
					break;
				}
			}
			if (flag) {
				curr7[k] = curr;
				sum += curr;
				max7[k] = curr;
				sumMax += curr;
				k++;
			}
		} else {
			flag = 1;
			sum = 0;
			for (i = 0; i < 6; ++i) {
				curr7[i] = curr7[i+1];
				sum += curr7[i];
			}
			curr7[6] = curr;
			sum += curr;
			
			for (i = 0; i < 7; ++i) {
				for (j = 0; j < 7; ++j) {
					if (i != j && curr7[i] == curr7[j]) {
						flag = 0;
					}
				}
			}
			
			if (flag && sumMax < sum) {
				for (i = 0 ; i < 7 ; ++i) {
					max7[i] = curr7[i];
				}
				sumMax = sum;
			}
		}
	}
	
	fclose(in);

	out = fopen("data.res", "w");
	
	if (k != 7) {
		fprintf(out, "NO");
	} else {
		//qsort(max7, 7, sizeof(int), cmp);
		for (j = 0; j < 7; ++j) {
			for (i = 0; i < 6; ++i) {
				//if (cmp(max7, i, i+1) == 1) {
				//	swap(max7, i, i+1)
				//}
				if (max7[i] > max7[i+1]) {
					//
					max7[i] += max7[i+1];
					max7[i+1] = max7[i] - max7[i+1];
					max7[i] -= max7[i+1];
				}
			}
		}
		
		for (i = 0; i < 7; ++i) fprintf(out, "%d ", max7[i]);
	}
		
	fclose(out);
	
	return 0;
}

//int cmp (const void* aa, const void* bb) {
//	int a, b;
//	a = *((int*)aa); b = *((int*)bb);
//	if (a > b) return 1;
//	if (a < b) return -1;
//	return 0;
//}
