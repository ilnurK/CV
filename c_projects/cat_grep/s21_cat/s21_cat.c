#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Tcat cat = {0};
  Tflags flags = {.err = 0};
  int files[argc];
  checker(&cat, argc, argv, files, &flags);
  if (!flags.err) {
    if (argc == 1) {
      onlyShow();
    } else {
      printer(&cat, argc, argv, files, &flags);
    }
  } else {
    fprintf(stderr, "Error");
  }
  return 0;
}

void checker(Tcat *cat, int argc, char *argv[], int *files, Tflags *flags) {
  for (int i = 1; i < argc && flags->err == 0; i++) {
    if (argv[i][0] == '-' && i != argc - 1) {
      if (argv[i][1] == '-') {
        isLongOption(cat, argv[i], flags);
      } else {
        for (int j = 1; j < (int)strlen(argv[i]) && flags->err == 0; j++) {
          isSmallOption(cat, argv[i][j], flags);
        }
      }
      cat->option_on = 1;
      files[i] = 0;
    } else {
      cat->file_on = 1;
      files[i] = 1;
    }
  }
}

void isLongOption(Tcat *cat, char *option, Tflags *flags) {
  int cr = 0;
  !strcmp(option, "--number-nonblank") ? cat->number_nonblank |= 1, cr++ : 0;
  !strcmp(option, "--number") ? cat->number |= 1, cr++ : 0;
  !strcmp(option, "--squeeze-blank") ? cat->squeeze_blank |= 1, cr++ : 0;
  flags->err = (cr) ? 0 : 1;
}

void isSmallOption(Tcat *cat, char c, Tflags *flags) {
  int cr = 0;
  (c == 'b') ? cat->number_nonblank |= 1, cr++ : 0;
  (c == 'e') ? cat->end_show |= 1, cat->view |= 1, cr++ : 0;
  (c == 'E') ? cat->end_show |= 1, cr++ : 0;
  (c == 'n') ? cat->number |= 1, cr++ : 0;
  (c == 's') ? cat->squeeze_blank |= 1, cr++ : 0;
  (c == 't') ? cat->tab_show |= 1, cat->view |= 1, cr++ : 0;
  (c == 'T') ? cat->tab_show |= 1, cr++ : 0;
  (c == 'v') ? cat->view |= 1, cr++ : 0;
  flags->err = (cr) ? 0 : 1;
}

void printer(Tcat *cat, int argc, char *argv[], int *files, Tflags *flags) {
  for (int i = 1; i < argc && !flags->err; i++) {
    int cr = 1;
    if (cat->file_on) {
      if (files[i] == 1) {
        FILE *f = fopen(argv[i], "r");
        if (f) {
          doWhatOptionMean(f, *cat, &cr, flags);
          fclose(f);
        } else {
          fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
        }
      }
    } else {
      doWhatOptionMean(NULL, *cat, &cr, flags);
    }
  }
}

void onlyShow() {
  int c;
  while ((c = getchar()) != EOF) {
    putchar(c);
  }
}

void doWhatOptionMean(FILE *f, Tcat cat, int *cr, Tflags *flags) {
  int last_str_emp = 0;
  flags->stream_end = 0;
  while (!flags->stream_end && !flags->err) {
    char *str = getString(f, cat, flags);
    flags->str_emp = (strlen(str)) ? 0 : 1;
    if (!(flags->stream_end && !strlen(str))) {
      int state_for_skip = cat.squeeze_blank && flags->str_emp && last_str_emp;
      if (!state_for_skip) {
        if ((cat.number_nonblank && !flags->str_emp) ||
            (cat.number && !cat.number_nonblank)) {
          counter(cr);
        }
        printf("%s", str);
        if (!flags->stream_end) {
          (cat.end_show) ? endShow() : NULL;
          putchar('\n');
        }
      }
    }
    free(str);
    last_str_emp = flags->str_emp;
  }
}

char *getString(FILE *file, Tcat cat, Tflags *flags) {
  int buffer = 16 * sizeof(char);
  char *str = malloc(buffer);
  if (str) {
    int i = 0, flag_cycle = 1;
    char c = ' ';
    while (!flags->err && flag_cycle) {
      c = (file) ? getc(file) : getc(stdin);
      if ((!file && c == EOF) || (file && feof(file))) {
        flags->stream_end = 1;
        flag_cycle = 0;
      } else if (c == '\n') {
        flag_cycle = 0;
      } else {
        if (cat.view) {
          view(cat, str, &i, c);
        } else {
          str[i++] = c;
        }
        str = (i > buffer - 5) ? increaseStr(flags, str, &buffer) : str;
      }
    }
    str[i] = '\0';
  } else {
    flags->err = 1;
  }
  return str;
}

void view(Tcat cat, char *str, int *i, char c) {
  if (c >= 32 && c != 127) {
    str[(*i)++] = c;
  } else if ((c >= 0 && c < 32) || c == 127) {
    if (c == '\t' && !cat.tab_show) {
      str[(*i)++] = c;
    } else {
      str[(*i)++] = '^', str[(*i)++] = (c != 127) ? c + 64 : c - 64;
    }
  } else if ((c < -128 + 32) || c == -1) {
    str[(*i)++] = 'M', str[(*i)++] = '-', str[(*i)++] = '^',
    str[(*i)++] = (c != -1) ? c + 128 + 64 : 64;
  } else {
    str[(*i)++] = 'M', str[(*i)++] = '-', str[(*i)++] = c + 128;
  }
}

void counter(int *cr) { printf("%6d\t", (*cr)++); }

void endShow() { putchar('$'); }