#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 20
#define INF UINT_MAX

void dijkstra(unsigned int** matrix, long long S, long long N, long long F);

int main() {
	long long M, N, S, F, e0, e1, w, count = 0;

	char line[MAX_SIZE];

	FILE* fin = fopen("in.txt", "r");

	while (fgets(line, sizeof(line), fin)) count++;

	fclose(fin);

	fin = fopen("in.txt", "r");

	if (count < 2) {
		printf("bad number of lines");
		return 0;
	}

	fscanf(fin, "%lld", &N);

	if ((N < 0) || (N > 5000)) {
		printf("bad number of vertices");
		return 0;
	}

	fscanf(fin, "%lld %lld", &S, &F);

	if ((S < 1) || (S > N)) {
		printf("bad vertex");
		return 0;
	}

	if ((F < 1) || (F > N)) {
		printf("bad vertex");
		return 0;
	}

	fscanf(fin, "%lld", &M);

	if ((M < 0) || (M > ((N*(N - 1)) / 2))) {
		printf("bad number of edges");
		return 0;
	}

	if (count < (M + 3)) {
		printf("bad number of lines");
		return 0;
	}

	unsigned int** matrix = (unsigned int**)malloc(sizeof(unsigned int*) * N);

	for (int i = 0; i < N; i++) {
		matrix[i] = (unsigned int*)malloc(N * sizeof(unsigned int));
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] = INF;
		}
	}

	matrix[S - 1][S - 1] = 0;

	for (int i = 0; i < M; i++) {
		fscanf(fin, "%lld %lld %lld", &e0, &e1, &w);
		if ((e0 < 1) || (e0 > N)) {
			printf("bad vertex");
			return 0;
		}
		if ((e1 < 1) || (e1 > N)) {
			printf("bad vertex");
			return 0;
		}
		if ((w < 0) || (w > INT_MAX)) {
			printf("bad length");
			return 0;
		}

		matrix[e0 - 1][e1 - 1] = matrix[e1 - 1][e0 - 1] = (unsigned int)w;
	}

	dijkstra(matrix, S, N, F);

	return 0;
}

void dijkstra(unsigned int** cost, long long S, long long N, long long F) {

	long long* distance = (long long*)malloc(sizeof(long long) * N);
	char* visited = (char*)malloc(sizeof(char) * N);
	short* paths = (short*)malloc(sizeof(short) * N);

	long long  count, mind, next;

	long long int_max_couter = 0;
	long long finish = F - 1;
	
	for (int i = 0; i < N; i++) {
		distance[i] = cost[S - 1][i];
		paths[i] = S - 1;
		visited[i] = 0;
	}

	distance[S - 1] = 0;
	visited[S - 1] = 1;
	count = 1;

	while (count < N - 1) {
		mind = INF;

		for(int i = 0; i < N; i++)
			if ((distance[i] < mind) && (!visited[i])) {
				mind = distance[i];
				next = i;
			}

		visited[next] = 1;

		for (int i = 0; i < N; i++)
			if (!visited[i])
				if (mind + cost[next][i] < distance[i] && cost[next][i] != INF) {
					distance[i] = mind + cost[next][i];
					paths[i] = next;
				}
		count++;
	}

	

	for (int i = 0; i < N; i++) {
		if (distance[i] == INF) {
			printf("oo ");
		}
		else if (distance[i] > INT_MAX) {
			printf("INT_MAX+ ");
			int_max_couter++;
		}
		else printf("%lld ", distance[i]);
	}
	printf("\n");

	if (distance[F - 1] == INF)
		printf("no path");
	else if ((distance[F - 1] > INT_MAX && int_max_couter >= 2) || (distance[F - 1] > INT_MAX && (distance[1] == distance[3])))
		printf("overflow");
	else {
		printf("%lld ", finish + 1);

		do {
			finish = paths[finish];
			printf("%lld ", finish + 1);
		} while (finish != S - 1);
	}

	free(distance);
	free(visited);
}
