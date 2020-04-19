#include <stdio.h>

int song[20000];
int chord[10];
int found_chords[20000];
int n, c, m;


int read_input(const char* file_name) {
  FILE * f_input;
  f_input = fopen(file_name, "rt");
  if (f_input == NULL) {
    printf("ERROR: cannot read from %s\n", file_name);
    return 1;
  }
  fscanf(f_input, "%d", &n);
  for (int i=0; i<n; i++) {
    int temp;
    fscanf(f_input, "%d", &temp);
    song[i] = temp;
  }
  fscanf(f_input, "%d", &c);
  for (int i=0; i<c; i++) {
    int temp;
    fscanf(f_input, "%d", &temp);
    chord[i] = temp;
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

  fprintf(f_output, "%d\n", m);
  for (int i=0; i<m; i++) {
    fprintf(f_output, "%d\n", found_chords[i] + 1);
  }
  fclose(f_output);
  return 0;
}

void simplfy_chord() {
  int lowest_note;
  // find the lowest note
  lowest_note = chord[0];
  for (int i=1; i < c; i++) {
    if (lowest_note > chord[i]) {
      lowest_note = chord[i];
    }
  }
  // simplify the chord
  for (int i = 0; i < c; i++) {
    chord[i] -= lowest_note;
  }
}
/*check if the array a (has count elements) has duplicates or no
if yes, return 1 else return 0
*/
int has_dupes(int count, int a[]) {
  for (int i = 0; i < count - 1; i++) {
    for (int j = i+1; j<count; j++) {
      if (a[i] == a[j])
        return 1;
    }
  }
  return 0;
}
int find_min(int count, int a[]) {
  int min = a[0];
  for (int i=1; i < count; i++) {
    if (min > a[i]) {
      min = a[i];
    }
  }
  return min;
}

int value_in_array(int count, int a[], int value) {
  for (int i = 0; i < count; i++) {
    if (a[i] == value)
      return 1;
  }
  return 0;
}

int find_chords() {
  m = 0;
  simplfy_chord();
  for (int i = 0; i <= n - c; i++) {
    if (has_dupes(c, &song[i]) == 1) {
      continue;
    }
    int min_group = find_min(c, &song[i]);
    int found = 1;
    for (int j=0; j<c; j++) {
      int note = song[i + j] - min_group;
      if (!value_in_array(c, chord, note)) {
          found = 0;
          break;
      }
    }
    if (found == 1) {
      found_chords[m] = i;
      m++;
    }
  }
  return m;
}
int main(int argc, char const *argv[]) {
  /* code */
  read_input(argv[1]);
  find_chords();
  write_output(argv[2]);
  return 0;
}
