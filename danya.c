#include <stdio.h>
#include <stdlib.h>

int cmp(const void*, const void*);
void swap(int*, int*);
void swapArray(int (*)[7], int (*)[7]);

int main(void) {
	FILE *in, *out;
	int max1[7], max2[7], max3[7], curr7[7];
	int sumMax1, sumMax2, sumMax3, sum, curr, i, j, k, flag, num;
	
	num = 1; k = 0; flag = 1;
	
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
			max1[0] = curr;
			sumMax1 = curr;
			k++;
		} else if (k < 7) {
			flag = 1;
			for (i = 0; i < k; ++i) {
				if (curr == curr7[0]) {
					curr7[0] = curr;
					sum = curr;
					max1[0] = curr;
					sumMax1 = curr;
					k = 1;
					flag = 0;
					break;
				}
			}
			if (flag) {
				curr7[k] = curr;
				sum += curr;
				max1[k] = curr;
				sumMax1 += curr;
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
			
			if (flag) {
                if (num == 1) {
                    for (i = 0; i < 7; ++i) max2[i] = curr7[i];
                    sumMax2 = sum;
                    if (sumMax2 > sumMax1) {
                        swapArray(&max1, &max2);
                        swap(&sumMax1, &sumMax2);
                    }
                } else if (num == 2) {

                    for (i = 0; i < 7; ++i) max3[i] = curr7[i];
                    sumMax3 = sum;

                    if (sumMax3 > sumMax2) {
                        swapArray(&max2, &max3);
                        swap(&sumMax2, &sumMax3);

                        if (sumMax2 > sumMax1) {
                            swapArray(&max1, &max2);
                            swap(&sumMax1, &sumMax2);
                        }

                    }
                } else {
                    if (sum > sumMax3 && sum < sumMax2) {
                        for (i = 0; i < 7; ++i) max3[i] = curr7[i];
                        sumMax3 = sum;
                    } else if (sum > sumMax2 && sum < sumMax1) {
                        swapArray(&max2, &max3);
                        swap(&sumMax2, &sumMax3);
                        for (i = 0; i < 9; ++i) max2[i] = curr7[i];
                        sumMax2 = sum;
                    } else if (sum > sumMax1) {
                        swapArray(&max2, &max3);
                        swap(&sumMax2, &sumMax3);

                        swapArray(&max1, &max2);
                        swap(&sumMax1, &sumMax2);

                        for(i = 0; i < 7; ++i) max1[i] = curr7[i];
                        sumMax1 = sum;
                    }
                }
                num++;
			}
		}
	}
	
	fclose(in);

	out = fopen("data.res", "w");
	
	if (k != 7) {
		fprintf(out, "NO");
	} else if (num == 1) {
        qsort(max1, 7, sizeof(int), cmp);
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", max1[i]);
    } else if (num == 2){
        qsort(max1, 7, sizeof(int), cmp);
        qsort(max2, 7, sizeof(int), cmp);
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", max1[i]);
        fprintf(out, "\n");
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", max2[i]);
    } else {
        qsort(max1, 7, sizeof(int), cmp);
        qsort(max2, 7, sizeof(int), cmp);
        qsort(max3, 7, sizeof(int), cmp);
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", max1[i]);
        fprintf(out, "\n");
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", max2[i]);
        fprintf(out, "\n");
        for (i = 0; i < 7; ++i) fprintf(out, "%d ", max3[i]);
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

void swap(int* a, int* b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swapArray(int (*A)[7], int (*B)[7]) {
    int i;
    for (i = 0; i < 7; ++i) swap((*A)+i, (*B)+i);
}
