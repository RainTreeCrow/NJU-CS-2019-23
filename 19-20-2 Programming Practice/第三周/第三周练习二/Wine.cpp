#include <stdio.h> 
#include <stdlib.h>
#pragma warning( disable : 4996 )

int row, col;

void read_txt(double**& wine) {
	int i, count, r = 0, c = 0;
	char ch, line[100], container[20] = "\0";
	FILE* fp = NULL;
	fp = fopen("./wine.txt", "r");
	if (fp == NULL) {
		printf("Error! \n");
		exit(-1);
	}
	else
		printf("wine.txt has been opened. \n");
	row = 1, col = 1;
	while (!feof(fp)) {
		if (fgetc(fp) == '\n')
			row += 1;
	}
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp)) {
		ch = fgetc(fp);
		if (ch == ',')
			col += 1;
		if (ch == '\n')
			break;
	}
	wine = new double* [row];
	for (i = 0; i < row; i++)
		wine[i] = new double[col];
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp)) {
		fgets(line, 99, fp);
		count = 0, c = 0;
		for (i = 0; line[i] != '\0'; i++) {
			if (line[i] == ',') {
				container[count] = '\0';
				wine[r][c] = atof(container);
				count = 0;
				c += 1;
			}
			else if (line[i] == '#') {
				container[0] = '0';
				container[1] = '\0';
			}
			else {
				container[count] = line[i];
				count += 1;
			}
		}
		if (line[i - 1] == '#') {
			wine[r][c] = 0;
		}
		else {
			container[count] = '\0';
			wine[r][c] = atof(container);
		}
		r += 1;
	}
	fclose(fp);
}

void make_up(double**& wine) {
	int i, j, count;
	double* average = new double[col];
	for (j = 0; j < col; j++) {
		average[j] = 0;
		count = 0;
		for (i = 0; i < row; i++) {
			if (wine[i][j] != 0)
				count += 1;
			average[j] += wine[i][j];
		}
		average[j] /= count;
	}
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (wine[i][j] == 0)
				wine[i][j] = average[j];
		}
	}
}

void fill_dat(double** wine) {
	int i, j;
	FILE* fp = NULL;
	fp = fopen("./wine_cpl.dat", "wb");
	if (fp == NULL) {
		printf("Error! \n");
		exit(-1);
	}
	else
		printf("wine_cpl.dat has been created. \n");
	for (i = 0; i < row; i++) {
		for (j = 0; j < col - 1; j++)
			fprintf(fp, "%0.1f,", wine[i][j]);
		fprintf(fp, "%0.1f\n", wine[i][j]);
	}
	fclose(fp);
}

void normalize(double**& wine) {
	int i, j;
	double** max_min = new double* [col];
	for (j = 0; j < col; j++)
		max_min[j] = new double[2];
	max_min[0][0] = 0.0;
	max_min[0][1] = 0.0;
	for (j = 1; j < col; j++) {
		max_min[j][0] = 0.0;
		max_min[j][1] = 1000.0;
		for (i = 0; i < row; i++) {
			if (wine[i][j] > max_min[j][0])
				max_min[j][0] = wine[i][j];
			else if (wine[i][j] < max_min[j][1])
				max_min[j][1] = wine[i][j];
		}
	}
	for (j = 1; j < col; j++) {
		if (max_min[j][0] == max_min[j][1]) {
			for (i = 0; i < row; i++)
				wine[i][j] = 1.0;
		}
		else {
			for (i = 0; i < row; i++)
				wine[i][j] = (wine[i][j] - max_min[j][1]) * 1.0 / (max_min[j][0] - max_min[j][1]);
		}
	}
}

void fill_csv(double** wine) {
	int i, j;
	FILE* fp = NULL;
	fp = fopen("./wine_norm.csv", "w");
	if (fp == NULL) {
		printf("Error! \n");
		exit(-1);
	}
	else
		printf("wine_norm.csv has been created. \n");
	for (i = 0; i < row; i++) {
		for (j = 0; j < col - 1; j++)
			fprintf(fp, "%0.1f,", wine[i][j]);
		fprintf(fp, "%0.1f\n", wine[i][j]);
	}
	fclose(fp);
}

int main() {
	double** wine = NULL;
	read_txt(wine);
	//for (i = 0; i < row; i++) {
	//	for (j = 0; j < col; j++)
	//		printf("%lf ", wine[i][j]);
	//	printf("\n");
	//}
	make_up(wine);
	fill_dat(wine);
	normalize(wine);
	fill_csv(wine);
}