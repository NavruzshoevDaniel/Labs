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

int checkInputRebr(struct graph *gr, int ver, int i) {

  if (gr[i].start < 1 || gr[i].start > ver) {
    return 1;
  }
  if (gr[i].end < 1 || gr[i].end > ver) {
    return 1;
  }
  if (gr[i].weight < 0 || gr[i].weight > INT_MAX) {
    return 2;
  }
}

int checkInput(int ver, int rebr) {
  if ((ver < 0) || (ver > 5000)) {
    return 1;
  }
  if ((rebr < 0) || (rebr > (ver * (ver + 1) / 2))) {
    return 2;
  }
  if (ver == 0) {
    return 3;
  }
}

void prim(struct graph *g, int versh, int rebr, FILE *out) {
  int *st = NULL, *cost = NULL, *path = NULL;
  st = malloc((versh + 1) * sizeof(int));
  cost = malloc((versh + 1) * sizeof(int));
  path = malloc((versh + 1) * sizeof(int));
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
  free(cost);
  free(path);
  free(st);
}

int main() {
  FILE *in = fopen("in.txt", "r");
  FILE *out = fopen("out.txt", "w");
  struct graph *masGr = NULL;
  int versh, rebr, err = 0, j = 0, letter = 0;
  int *isfill = NULL;
  fscanf(in, "%d", &versh);
  fscanf(in, "%d", &rebr);
  int errorCheck = 0;
  errorCheck = checkInput(versh, rebr);

  if (errorCheck == 1) {
    fprintf(out, "bad number of vertices");
    goto fileclose;
  } else if (errorCheck == 2) {
    fprintf(out, "bad number of edges");
    goto fileclose;
  } else if (errorCheck == 3) {
    fprintf(out, "no spanning tree");
    goto fileclose;
  }

  masGr = malloc(rebr * sizeof(struct graph));
  isfill = malloc((versh + 1) * sizeof(int));
  if ((versh == 1) && (rebr == 0)) {
    goto end;
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
      errorCheck=0;
      errorCheck = checkInputRebr(masGr, versh, j);

      if (errorCheck == 1) {
        fprintf(out, "bad vertex");
        goto end;
      } else if (errorCheck == 2) {
        fprintf(out, "bad length");
        goto end;
      }
      isfill[masGr[j].start] = 1;
      isfill[masGr[j].end] = 1;
      j++;
    }
  }
  if (j != rebr) {
    fprintf(out, "bad number of lines");
    goto end;
  }
  for (int i = 1; i <= versh; i++) {
    if (isfill[i] != 1) {
      fprintf(out, "no spanning tree");
      goto end;
    }
  }
  quickSort(masGr, 0, rebr - 1);
  prim(masGr, versh, rebr, out);
  end:
  free(isfill);
  free(masGr);
  fileclose:
  fclose(in);
  fclose(out);
  return 0;
}
