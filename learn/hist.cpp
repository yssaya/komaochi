#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count = 0;

int main(int argc, char *argv[])
{
	FILE *fp = fopen("handicap_history.txt","r");
	if ( fp==NULL ) { printf("fopen err.\n"); exit(0); }
	int prev[7] = { -1 };
	for (;;) {
		const int MAX_LINE = 512;
		char buf[MAX_LINE];
		if ( fgets(buf,MAX_LINE,fp)==NULL ) break;
		int sum = 0;
		int view[7] = { -1,-1,-1,-1,-1,-1,-1 };
		int view_n = 0;
		for (int i=0;i<7;i++) {
			int n = atoi(buf+   i*16);
			int r = atoi(buf+11+i*16);
//			printf("%d:%7d,%3d,",i,n,r);
			if ( r != prev[i] ) {
//				printf("%d:%7d,%3d,",i,n,r);
				view_n = n;
				prev[i] = r;
				view[i] = r;
				sum++;
			} else {
//				printf("%d:       ,   ,",i);
			}
		}
		if ( view_n == 0 ) printf("Err!\n\n");
		if ( view_n < 906058 ) continue;
		if ( view_n == 906058 ) {
			printf("%7d\t  0\t  0\t  0\t  0\t  0\t  0\t  0\n",900000);
		}
		printf("%7d",view_n);
		for (int i=0;i<7;i++) {
			printf("\t");
			if ( view[i] > 0 ) printf("%3d",view[i]);
//			else printf("   ");
		}
		printf("\n");
//		printf("  =%d\n",sum);
		count++;
	}
	fclose(fp);
	printf("count = %d\n",count);
	return 0;
}
