#include <stdio.h>
#include <string.h>

int n, d;
char str[100001];
int read_input(const char* file_name) {
  FILE *f_input;
  f_input = fopen(file_name, "rt");
  if (f_input == NULL) {
    printf("ERROR: cannot read from %s\n", file_name);
    return 1;
  }
  int count = fscanf(f_input, "%d", &n);

  printf("read n=%d\n",n);
  if (count != 1) {
    printf("ERROR: wrong input format\n");
    return 1;
  }

  fgets(str, 100000, f_input);
  if (str[0] == '\n') {
    fgets(str, 100000, f_input);
  }

  fclose(f_input);
  str[n]=0;
  return 0;
}

int write_output(const char* file_name) {
  FILE *f_output;
  f_output = fopen(file_name, "wt");
  if (f_output == NULL) {
    printf("ERROR: cannot write to %s\n", file_name);
    return 1;
  }
  fprintf(f_output, "%d\n", d);
  fclose(f_output);
  return 0;
}

int is_all_zeros() {
  for (int i = 0;i < n; i++) {
    if (str[i] == '1') {
      return 0;
    }
  }
  return 1;
}

void calculate(void) {
  int g1, g2, cur, b1, b2, cur_b;
  // initializing variables
  g1 = 0;
  g2 = 0;
  cur = 0;
  b1 = 1;
  b2 = 1;
  // checking for corner case: all zeros
  if (is_all_zeros() == 1) {
    d = n - 1;
    return;
  }
  // checking for unbound

  if (str[0] == '0') {
    cur_b = 0;
  } else {
    cur_b = 1;
  }

  //for loop
  for (int i = 0;i < n; i++) {
    if (str[i] == '0') {
      cur++;
    } else if (str[i] == '1') {
      if (cur > 0) {
        if (cur > g1) {
          g2 = g1;
          b2 = b1;
          g1 = cur;
          b1 = cur_b;
        } else if (cur > g2) {
          g2 = cur;
          b2 = cur_b;
        }
        cur = 0;
        cur_b = 1;
      }
    } else {
      printf("Wrong input string\n");
      return;
    }
  }
  if (cur > 0) {
    if (cur > g1) {
      g2 = g1;
      b2 = b1;
      g1 = cur;
      b1 = 0;
    } else if (cur > g2) {
      g2 = cur;
      b2 = 0;
    }
  }
  //checking gap amount
  if (g2 == 0) {
    if (b1==0) {
      d = g1 / 2;
    } else {
      d = (g1 + 1) / 3;
    }
  } else {
    if (b2==0) {
      d = g2;
    } else {
      d = (g2 + 1) / 2;
    }
  }
}

int main(int argc, char const *argv[]) {
  read_input(argv[1]);
  calculate();
  write_output(argv[2]);
  return 0;
}
