#include <stdio.h>
#include <string.h>
#include <math.h>

void check(unsigned char word[], unsigned char str[], int ind, int a) {
    int k=strlen(word);
    for (int i = 0; i < k; i++) {
        printf("%d ", ind + i - k + 1);
        if (word[i] != str[i + a - k])
            break;
    }
}

long hashFunction(unsigned char word[], int count) {
    long sum = 0;
    int power[] = { 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907,
                    43046721 };
    for (int i = 0; i < count; i++) {
        sum += (word[i] % 3)*power[i];
    }
    return sum;
}

int main() {
    unsigned char word[255] = { 0 };
    gets(word);
    long hashword = hashFunction(word, strlen(word));
    int ind = 1;
    long hashcount = 0;
    int power[] = { 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907,
                    43046721 };
    unsigned long k = 0, fchar = 0, len = 0;
    int l = strlen(word);
    printf("%ld ", hashword);
    long step = power[ l - 1];
    char buf[100] = { 0 };
    int dlina=strlen(buf);
    while (fgets(buf + len, 100, stdin)) {
        int i = 0, j = 0;
        hashcount = 0;
        while (i != (dlina)) {
            k = buf[i];

            if (i + 1 == l) {
                hashcount = hashFunction(buf, i + 1);

            }
            else if (i + 1 > l) {
                hashcount = ((hashcount - fchar % 3) / 3) + (k % 3) * step;
                j++;
            }

            if (hashcount == hashword) {
                check(word, buf, ind, i + 1);
            }
            fchar = buf[j];
            ind++;
            i++;
        }
        memmove(buf, buf + (dlina - (l - 1)), l-1);
    }



    return 0;
}
