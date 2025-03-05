#include <stdio.h>
#include <stdlib.h>

int cmp(const void*, const void*);

int main(void) {
	FILE *in, *out;
	int max7[7], curr7[7], storage[14];
	int sumMax, sum, curr, i, j, k, flag, f, counter;
	
	k = 0; f = flag = 1; counter = 0;
	
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
            if (f) {
                for (i = 0; i < 7; ++i) storage[7*counter + i] = curr7[i];
                counter = 1;
                f = 0;
            }
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
			
			if (flag) {
                if (sum > sumMax) {
                    for (i = 0 ; i < 7 ; ++i) max7[i] = curr7[i];
                    sumMax = sum;
                }
                if (counter == 1) {
                    for (i = 0; i < 7; ++i) storage[7*counter + i] = curr7[i];
                    counter++;
                }
			}
		}
	}
	
	fclose(in);

	out = fopen("data.res", "w");
	
	if (k != 7) {
		fprintf(out, "NO");
	} else if (counter < 3) {
        qsort(storage, 7, sizeof(int), cmp);
        qsort(storage + 7, 7, sizeof(int), cmp);
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", storage[i]);
        fprintf(out, "\n");
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", storage[i+7]);
    } else {
        qsort(max7, 7, sizeof(int), cmp);
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", max7[i]);
    }
		
	fclose(out);
	
	return 0;
}

int cmp (const void* aa, const void* bb) {
	int a, b;
	a = *((int*)aa); b = *((int*)bb);
	if (a > b) return 1;
	if (a < b) return -1;
	return 0;
}
