#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct graph {
  int start;
  int end;
  int weight;
};

void quickSort(struct graph *gr, int l, int r) {
  int i = l, j = r;
  int mid = gr[(l + r) / 2].weight;

  do {
    while (gr[i].weight < mid)
      i++;
    while (gr[j].weight > mid)
      j--;
    if (i <= j) {
      struct graph c = gr[i];
      gr[i] = gr[j];
      gr[j] = c;
      i++;
      j--;
    }
  } while (i < j);

  if (l < j) quickSort(gr, l, j);
  if (i < r) quickSort(gr, i, r);
}

void makeSet(int *status, int x) {
  status[x] = x;
}

int find(int *status, int x) {
  if (status[x] == x) return x;
  return status[x] = find(status, status[x]);
}

void unit(int x, int y, int *rank, int *status) {
  x = find(status, x);
  y = find(status, y);
  if (rank[x] < rank[y])
    status[x] = y;
  else {
    status[y] = x;
    if (rank[x] == rank[y])
      rank[x]++;
  }
}

void crascal(int *status, struct graph *gr, int versh, int rebr, int *rank, FILE *out) {

  for (int i = 1; i <= versh; i++) {
    makeSet(status, i);
  }

  for (int i = 0; i < rebr; i++) {
    if (find(status, gr[i].start) != find(status, gr[i].end)) {
      unit(gr[i].start, gr[i].end, rank, status);
      fprintf(out, "%d %d\n", gr[i].start, gr[i].end);
    }
  }
}

void checkInputRebr(struct graph *gr, int ver, int i, FILE *in, FILE *out, int *rank, int *isfill, int *status) {

  if (gr[i].start < 1 || gr[i].start > ver) {
    fprintf(out, "bad vertex");
    free(status);
    free(rank);
    free(isfill);
    free(gr);
    fclose(in);
    fclose(out);
    exit(0);
  }
  if (gr[i].end < 1 || gr[i].end > ver) {
    fprintf(out, "bad vertex");
    free(status);
    free(rank);
    free(isfill);
    free(gr);
    fclose(in);
    fclose(out);
    exit(0);
  }
  if (gr[i].weight < 0 || gr[i].weight > INT_MAX) {
    fprintf(out, "bad length");
    free(status);
    free(rank);
    free(isfill);
    free(gr);
    fclose(in);
    fclose(out);
    exit(0);
  }
}

void checkInput(int ver, int rebr, FILE *in, FILE *out) {
  if ((ver < 0) || (ver > 5000)) {
    fprintf(out, "bad number of vertices");
    fclose(in);
    fclose(out);
    exit(0);
  }
  if ((rebr < 0) || (rebr > (ver * (ver + 1) / 2))) {
    fprintf(out, "bad number of edges");
    fclose(in);
    fclose(out);
    exit(0);
  }
  if (ver == 0) {
    fprintf(out, "no spanning tree");
    fclose(in);
    fclose(out);
    exit(0);
  }
}

int main() {
  FILE *in = fopen("in.txt", "r");
  FILE *out = fopen("out.txt", "w");
  struct graph *masGr = NULL;
  int versh, rebr, err = 0, j = 0, letter = 0;
  int *status = NULL, *rank = NULL, *isfill = NULL;
  fscanf(in, "%d", &versh);
  fscanf(in, "%d", &rebr);
  checkInput(versh, rebr, in, out);
  masGr = malloc(rebr * sizeof(struct graph));
  status = malloc((versh + 1) * sizeof(int));
  rank = malloc((versh + 1) * sizeof(int));
  isfill = malloc((versh + 1) * sizeof(int));

  if ((versh == 1) && (rebr == 0)) {
    fclose(in);
    exit(0);
  }
  while ((fscanf(in, "%d", &letter)) != EOF) {
    switch (err) {
      case 0:masGr[j].start = letter;
        err++;
        break;
      case 1:masGr[j].end = letter;
        err++;
        break;
      case 2:masGr[j].weight = letter;
        err = 0;
        break;
    }
    if (err == 0) {
      checkInputRebr(masGr, versh, j, in, out, rank, isfill, status);
      isfill[masGr[j].end] = 1;
      isfill[masGr[j].start] = 1;
      j++;
    }
  }
  if (j != rebr) {
    fprintf(out, "bad number of lines");
    fclose(in);
    fclose(out);
    exit(0);
  }
  for (int i = 1; i <= versh; i++) {
    if (isfill[i] != 1) {
      fprintf(out, "no spanning tree");
      fclose(in);
      fclose(out);
      exit(0);
    }
  }
  quickSort(masGr, 0, rebr - 1);
  crascal(status, masGr, versh, rebr, rank, out);
  free(status);
  free(rank);
  free(isfill);
  free(masGr);
  fclose(in);
  fclose(out);
  return 0;
}
