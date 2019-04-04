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

void checkInputRebr(struct graph *gr,
                    int ver,
                    int i,
                    FILE *in,
                    FILE *out,
                    int *status,
                    int *cost,
                    int *path,
                    int *isfill,
                    int **masGr) {

  if (gr[i].start < 1 || gr[i].start > ver) {
    fprintf(out, "bad vertex");
    free(cost);
    free(path);
    free(isfill);
    free(status);
    free(masGr);
    fclose(in);
    fclose(out);
    exit(0);
  }
  if (gr[i].end < 1 || gr[i].end > ver) {
    fprintf(out, "bad vertex");
    free(cost);
    free(path);
    free(isfill);
    free(status);
    free(masGr);
    fclose(in);
    fclose(out);
    exit(0);
  }
  if (gr[i].weight < 0 || gr[i].weight > INT_MAX) {
    fprintf(out, "bad length");
    free(cost);
    free(path);
    free(isfill);
    free(status);
    free(masGr);
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

void prim(struct graph *g, int *st, int *cost, int *path, int versh, int rebr, FILE *out) {
  int j = 0;
  for (int i = 0; i <= versh; i++) {
    cost[i] = INT_MAX;
    st[i] = 0;
    path[i] = -1;
  }
  st[g[0].start] = 1;
  j++;

  while (j != versh) {
    for (int i = 0; i < rebr; i++) {
      if (((st[g[i].start] == 1) && (st[g[i].end] == 0))) {
        cost[g[i].end] = g[i].weight;
        st[g[i].end] = 1;
        path[g[i].end] = g[i].start;

        j++;
        break;
      }
      if (((st[g[i].start] == 0) && (st[g[i].end] == 1))) {
        cost[g[i].start] = g[i].weight;
        st[g[i].start] = 1;
        path[g[i].start] = g[i].end;
        j++;
        break;
      }
    }

  }
  for (int i = 0; i <= versh; i++) {

    if (path[i] != -1) {
      fprintf(out, "%d %d\n", i, path[i]);
    }

  }

}

int main() {
  FILE *in = fopen("in.txt", "r");
  FILE *out = fopen("out.txt", "w");
  struct graph *masGr = NULL;
  int versh, rebr, err = 0, j = 0, letter = 0;
  int *status = NULL, *isfill = NULL, *cost = NULL, *path = NULL;
  fscanf(in, "%d", &versh);
  fscanf(in, "%d", &rebr);
  checkInput(versh, rebr, in, out);
  masGr = malloc(rebr * sizeof(struct graph));
  status = malloc((versh + 1) * sizeof(int));
  cost = malloc((versh + 1) * sizeof(int));
  path = malloc((versh + 1) * sizeof(int));
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
      checkInputRebr(masGr, versh, j, in, out, status, cost, path, isfill, masGr);
      isfill[masGr[j].start] = 1;
      isfill[masGr[j].end] = 1;
      j++;
    }
  }
  if (j != rebr) {
    fprintf(out, "bad number of lines");
    free(cost);
    free(path);
    free(isfill);
    free(status);
    free(masGr);
    fclose(in);
    fclose(out);
    exit(0);
  }
  for (int i = 1; i <= versh; i++) {
    if (isfill[i] != 1) {
      fprintf(out, "no spanning tree");
      free(cost);
      free(path);
      free(isfill);
      free(status);
      free(masGr);
      fclose(in);
      fclose(out);
      exit(0);
    }
  }
  quickSort(masGr, 0, rebr - 1);
  prim(masGr, status, cost, path, versh, rebr, out);
  free(cost);
  free(path);
  free(isfill);
  free(status);
  free(masGr);
  fclose(in);
  fclose(out);
  return 0;
}
