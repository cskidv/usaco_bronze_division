#include <stdio.h>
int day, hour, minute, result;

int read_input(const char* file_name) {
  FILE * f_input;
  f_input = fopen(file_name, "rt");
  if (f_input == NULL) {
    printf("ERROR: cannot read from %s\n", file_name);
    return 1;
  }
  int count = fscanf(f_input, "%d%d%d", &day, &hour, &minute);
  if (count != 3) {
    printf("ERROR: wrong input format\n");
    return 1;
  }
  fclose(f_input);
  return 0;
}
int write_output(const char* file_name) {
  FILE * f_output;
  f_output = fopen(file_name, "wt");
  if (f_output == NULL) {
    printf("ERROR: cannot write to %s\n", file_name);
    return 1;
  }

  fprintf(f_output, "%d\n", result); 
  return 0;
}
void calculate(){
  result = (day - 11) * 24 * 60 + (hour - 11) * 60 + (minute - 11);
  if (result < 0) {
    result = -1;
  }
}
int main(int argc, char const *argv[]) {
  read_input(argv[1]);
  calculate();
  write_output(argv[2]);
  return 0;
}
