#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Tflags flags = {.err = 0, .aim_found = 0};
  int options[argc], aims[argc], files[argc];
  setTo0(options, argc), setTo0(aims, argc), setTo0(files, argc);
  Tgrep grep = {0};
  Tarrs arr = {.argc = argc,
               .options = options,
               .aims = aims,
               .files = files,
               .argv = argv};
  checker(&grep, &arr, &flags);
  if (flags.err == 0) {
    filesOpening(&grep, &arr, &flags);
    (flags.e_aim) ? free(arr.new_aim) : 0;
  }
  if (flags.err != 0 && !grep.sup_err) {
    fprintf(stderr, "Error\n");
  }
  return 0;
}

void setTo0(int *arr, int len) {
  for (int i = 0; i < len; i++) {
    arr[i] = 0;
  }
}

void checker(Tgrep *grep, Tarrs *arr, Tflags *flags) {
  if (arr->argc < 3) {
    flags->err = 1;
  } else {
    for (int i = 1; i < arr->argc && flags->err == 0; i++) {
      (arr->argv[i][0] == '-') ? locateOption(grep, arr, flags, i) : NULL;
    }
    for (int i = 1; i < arr->argc; i++) {
      (!arr->options[i]) ? locateAimAndFile(grep, arr, flags, i) : NULL;
    }
  }
}

void locateOption(Tgrep *grep, Tarrs *arr, Tflags *flags, int i) {
  int fl = 0, len = (int)strlen(arr->argv[i]);
  for (int j = 1; j < len && !flags->err && !flags->e_aim; j++) {
    char c = arr->argv[i][j];
    (c == 'i') ? grep->ign_case |= 1, fl++ : 0;
    (c == 'v') ? grep->vert |= 1, fl++ : 0;
    (c == 'c') ? grep->count_fit |= 1, fl++ : 0;
    (c == 'l') ? grep->list_fit |= 1, fl++ : 0;
    (c == 'n') ? grep->num_str |= 1, fl++ : 0;
    (c == 'h') ? grep->hide_files |= 1, fl++ : 0;
    (c == 's') ? grep->sup_err |= 1, fl++ : 0;
    (c == 'o') ? grep->out_match |= 1, fl++ : 0;
    (c == 'f') ? grep->file_reg |= 1, arr->options[i] -= 2, fl++ : 0;
    if (c == 'e') {
      grep->example |= 1, arr->options[i] -= 1, fl++;
      (j + 1 < len) ? optionE(arr, flags, len, i, j + 1) : 0;
    }
    flags->err = (fl) ? 0 : 1;
  }
  if (fl && !arr->options[i]) {
    arr->options[i] = 1;
  }
}

void optionE(Tarrs *arr, Tflags *flags, int len, int i, int j) {
  int buffer = 16 * sizeof(char);
  arr->new_aim = malloc(buffer);
  if (arr->new_aim) {
    int k;
    for (k = j; k < len; k++) {
      arr->new_aim[k - j] = arr->argv[i][k];
      (k - j > buffer - 2) ? increaseStr(flags, arr->new_aim, &buffer) : 0;
    }
    arr->new_aim[k - j] = '\0';
    flags->aim_found = 1;
    flags->e_aim = 1;
  } else {
    flags->err = 1;
  }
}

void locateAimAndFile(Tgrep *grep, Tarrs *arr, Tflags *flags, int i) {
  if (grep->example && arr->options[i - 1] == -1 && !flags->e_aim) {
    arr->aims[i] = 1;
    flags->aim_found = 1;
  } else if (grep->file_reg && arr->options[i - 1] == -2) {
    arr->aims[i] = -1;
    flags->aim_found = 1;
  } else if (!flags->aim_found && !grep->file_reg &&
             !(arr->options[i - 1] == 1 && grep->example)) {
    arr->aims[i] = 1;
    flags->aim_found = 1;
  } else {
    arr->files[i] = 1;
    grep->files += 1;
  }
}

void filesOpening(Tgrep *grep, Tarrs *arr, Tflags *flags) {
  if (grep->files == 0) {
    flags->err = 1;
  } else {
    for (int i = 2; i < arr->argc && flags->err == 0; i++) {
      if (arr->files[i] == 1) {
        Tfile file = {.main = fopen(arr->argv[i], "r"), .name = arr->argv[i]};
        file.reg = file.main;
        arr->count = (grep->count_fit) ? 0 : 1;
        flags->stream_end = 0, flags->matched_file = 0;
        if (file.main) {
          fileCycle(*grep, arr, file, flags, i);
          flags->matched_file = 0;
          fclose(file.main);
        } else {
          printFileError(*grep, file.name);
        }
      }
    }
  }
}

void fileCycle(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, int i) {
  flags->file_reg_supply = 0, flags->last_aims = 0;
  while (!flags->stream_end && !flags->err) {
    arr->str = getString(file, flags);
    strCycle(grep, arr, file, flags);
    free(arr->str);
  }
  arr->files[i] = (flags->matched_file) ? 2 : 1;
  (grep.count_fit || grep.list_fit) ? printAlter(grep, *arr, file, *flags, i)
                                    : 0;
}

void strCycle(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags) {
  if (!(flags->stream_end && !strlen(arr->str))) {
    flags->str_end = 0, flags->already_print = 0, flags->matched = 0;
    int len_str = (int)strlen(arr->str);
    Tregm rm = {.shift = 0, rm.start = len_str, .end = len_str, .len = len_str};
    while (!flags->str_end && !flags->err &&
           ((grep.out_match) ? 1 : !flags->matched)) {
      aimsCycle(grep, arr, file, flags, &rm);
      flags->matched_file = (flags->matched) ? 1 : flags->matched_file;
      printStates(grep, arr, file, flags, &rm);
    }
    arr->count += (!flags->print_state && grep.count_fit) ? 0 : 1;
  }
}

void aimsCycle(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, Tregm *rm) {
  int flag_in = 0;
  for (int i = 1; i < arr->argc; i++) {
    if (arr->aims[i] || flags->e_aim) {
      flags->print_state = 1;
      if (flags->e_aim && !flag_in) {
        arr->aim = arr->new_aim;
        isManyMatched(grep, arr, flags, rm);
        flag_in = 1;
      } else if (grep.file_reg && arr->aims[i] == -1) {
        file.reg_name = arr->argv[i];
        fileReg(grep, arr, file, flags, rm);
      } else {
        arr->aim = arr->argv[i];
        isManyMatched(grep, arr, flags, rm);
      }
    }
  }
}

char *getString(Tfile file, Tflags *flags) {
  int buffer = 16 * sizeof(char);
  char *str = malloc(buffer);
  if (str) {
    int i = 0, flag_cycle = 1;
    char c = ' ';
    while (!flags->err && flag_cycle) {
      c = getc((flags->file_reg_supply) ? file.reg : file.main);
      if (feof(file.main) && !flags->last_aims) {
        flags->stream_end = 1, flags->last_aims = 1;
        flag_cycle = 0;
      } else if (c == '\n' || feof(file.reg)) {
        flag_cycle = 0;
      } else {
        str[i++] = c;
        str = (i > buffer - 2) ? increaseStr(flags, str, &buffer) : str;
      }
    }
    str[i] = '\0';
  } else {
    flags->err = 1;
  }
  return str;
}

void fileReg(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, Tregm *rm) {
  file.reg = fopen(file.reg_name, "r");
  flags->file_reg_supply = 1;
  if (file.reg) {
    while (!feof(file.reg) && ((grep.out_match) ? 1 : !flags->matched)) {
      arr->aim = getString(file, flags);
      isManyMatched(grep, arr, flags, rm);
      free(arr->aim);
    }
    flags->str_end = (!flags->matched) ? 1 : 0;
    flags->file_reg_supply = 0;
    fclose(file.reg);
  } else {
    printFileError(grep, file.reg_name);
    flags->str_end = 1;
  }
}

void isManyMatched(Tgrep grep, Tarrs *arr, Tflags *flags, Tregm *rm) {
  regex_t re;
  int err = regcomp(&re, arr->aim, (grep.ign_case) ? REG_ICASE : REG_EXTENDED);
  regmatch_t match;
  rm->temp_match = (int)strlen(arr->str);
  rm->t_shift = rm->shift;
  if (err == 0) {
    int reg_flag = (rm->shift) ? REG_NOTBOL : 0;
    if (!regexec(&re, arr->str + rm->shift, 1, &match, reg_flag)) {
      flags->matched |= 1;
      (grep.out_match) ? findClosestMatch(rm, match) : NULL;
    } else if (!flags->file_reg_supply) {
      flags->str_end = 1;
    }
  } else {
    flags->err = 1;
  }
  regfree(&re);
}

void findClosestMatch(Tregm *rm, regmatch_t match) {
  if (match.rm_so < rm->temp_match) {
    rm->temp_match = match.rm_so;
    rm->start = match.rm_so + rm->shift;
    rm->end = match.rm_eo + rm->shift;
  }
}

void printStates(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, Tregm *rm) {
  flags->print_state =
      (flags->matched && !grep.vert) || (!flags->matched && grep.vert);
  if (grep.out_match) {
    if (grep.vert) {
      printer(grep, arr, file, flags, *rm);
      flags->str_end = 1;
    } else {
      rm->shift += (rm->start >= rm->end) ? rm->len : rm->end - rm->shift;
      flags->str_end =
          (rm->shift > rm->len || rm->t_shift == rm->shift) ? 1 : 0;
      printer(grep, arr, file, flags, *rm);
    }
  } else {
    printer(grep, arr, file, flags, *rm);
  }
}

void printer(Tgrep grep, Tarrs *arr, Tfile file, Tflags *flags, Tregm rm) {
  if (flags->print_state && !grep.count_fit && !grep.list_fit) {
    if (!flags->already_print) {
      (grep.files > 1 && !grep.hide_files) ? printf("%s:", file.name) : 0;
      (grep.num_str) ? printf("%d:", arr->count) : 0;
      flags->already_print = 1;
    }
    if (grep.out_match && !grep.vert) {
      int flag = 0;
      for (int i = rm.start; i < rm.end && !flags->str_end; i++) {
        printf("%c", arr->str[i]);
        flag = 1;
      }
      (flag) ? putchar('\n') : 0;
    } else {
      printf("%s\n", arr->str);
    }
  }
}

void printAlter(Tgrep grep, Tarrs arr, Tfile file, Tflags flags, int i) {
  if (grep.list_fit && grep.count_fit) {
    if (grep.files > 1 && !grep.hide_files) {
      if (arr.files[i] == 2) {
        printf("%s:%d\n%s\n", file.name, flags.matched_file, file.name);
      } else {
        printf("%s:%d\n", file.name, flags.matched_file);
      }
    } else {
      printf("%d\n%s\n", flags.matched_file, file.name);
    }
  } else if (grep.list_fit && arr.files[i] == 2) {
    printf("%s\n", file.name);
  } else if (grep.count_fit) {
    if (grep.files > 1 && !grep.hide_files) {
      printf("%s:%d\n", file.name, arr.count);
    } else {
      printf("%d\n", arr.count);
    }
  }
}

void printFileError(Tgrep grep, char *filename) {
  if (!grep.sup_err) {
    fprintf(stderr, "grep: %s:  No such file or directory\n", filename);
  }
}