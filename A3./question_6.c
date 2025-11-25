#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *xmalloc(size_t n) {
  void *p = malloc(n);
  if (!p) {
    fprintf(stderr, "Memory allocation failed (malloc %zu bytes)\n", n);
    exit(EXIT_FAILURE);
  }
  return p;
}

static void *xrealloc(void *ptr, size_t n) {
  void *p = realloc(ptr, n);
  if (!p && n != 0) {
    fprintf(stderr, "Memory allocation failed (realloc %zu bytes)\n", n);
    exit(EXIT_FAILURE);
  }
  return p;
}

typedef struct {
  char **lines;
  size_t size;
  size_t capacity;
} Editor;

#define INITIAL_CAPACITY 4

char *read_line_stream(FILE *stream) {
  size_t cap = 128;
  size_t len = 0;
  char *buf = xmalloc(cap);
  int ch;

  while ((ch = fgetc(stream)) != EOF) {
    if (ch == '\r')
      continue;
    if (ch == '\n')
      break;

    if (len + 1 >= cap) {
      cap *= 2;
      buf = xrealloc(buf, cap);
    }

    buf[len++] = (char)ch;
  }

  if (len == 0 && ch == EOF) {
    free(buf);
    return NULL;
  }

  buf[len] = '\0';
  return xrealloc(buf, len + 1);
}

char *read_line_stdin(const char *prompt) {
  if (prompt) {
    printf("%s", prompt);
    fflush(stdout);
  }
  return read_line_stream(stdin);
}

void initEditor(Editor *ed) {
  ed->size = 0;
  ed->capacity = INITIAL_CAPACITY;
  ed->lines = xmalloc(ed->capacity * sizeof(char *));
}

void freeAll(Editor *ed) {
  if (!ed)
    return;

  for (size_t i = 0; i < ed->size; i++)
    free(ed->lines[i]);

  free(ed->lines);
  ed->lines = NULL;
  ed->size = 0;
  ed->capacity = 0;
}

void ensureCapacity(Editor *ed, size_t mincap) {
  if (ed->capacity >= mincap)
    return;

  size_t newCap = ed->capacity;
  while (newCap < mincap)
    newCap *= 2;

  ed->lines = xrealloc(ed->lines, newCap * sizeof(char *));
  ed->capacity = newCap;
}

void shrinkToFit(Editor *ed) {
  if (ed->size == ed->capacity)
    return;

  if (ed->size == 0) {
    free(ed->lines);
    ed->capacity = INITIAL_CAPACITY;
    ed->lines = xmalloc(ed->capacity * sizeof(char *));
    return;
  }

  ed->lines = xrealloc(ed->lines, ed->size * sizeof(char *));
  ed->capacity = ed->size;
}

void insertLine(Editor *ed, size_t index, const char *text) {
  if (index > ed->size) {
    fprintf(stderr, "Invalid index. Cannot insert.\n");
    return;
  }

  ensureCapacity(ed, ed->size + 1);

  if (index < ed->size) {
    memmove(&ed->lines[index + 1], &ed->lines[index],
            (ed->size - index) * sizeof(char *));
  }

  char *copy = xmalloc(strlen(text) + 1);
  strcpy(copy, text);

  ed->lines[index] = copy;
  ed->size++;
}

void deleteLine(Editor *ed, size_t index) {
  if (ed->size == 0) {
    fprintf(stderr, "Buffer empty.\n");
    return;
  }
  if (index >= ed->size) {
    fprintf(stderr, "Invalid index. Cannot delete.\n");
    return;
  }

  free(ed->lines[index]);

  if (index + 1 < ed->size) {
    memmove(&ed->lines[index], &ed->lines[index + 1],
            (ed->size - index - 1) * sizeof(char *));
  }

  ed->size--;
}

void appendLine(Editor *ed, const char *text) {
  insertLine(ed, ed->size, text);
}

void printAllLines(const Editor *ed) {
  printf("---- Buffer (%zu lines) ----\n", ed->size);
  for (size_t i = 0; i < ed->size; i++)
    printf("%4zu: %s\n", i + 1, ed->lines[i]);
  printf("----------------------------\n");
}

int saveToFile(const Editor *ed, const char *filename) {
  FILE *fp = fopen(filename, "w");
  if (!fp) {
    fprintf(stderr, "Could not open file for writing.\n");
    return -1;
  }

  for (size_t i = 0; i < ed->size; i++) {
    if (fprintf(fp, "%s\n", ed->lines[i]) < 0) {
      fprintf(stderr, "Write error.\n");
      fclose(fp);
      return -1;
    }
  }

  fclose(fp);
  return 0;
}

int loadFromFile(Editor *ed, const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Could not open file.\n");
    return -1;
  }

  for (size_t i = 0; i < ed->size; i++)
    free(ed->lines[i]);

  ed->size = 0;
  ensureCapacity(ed, 1);

  char *line;
  while ((line = read_line_stream(fp)) != NULL) {
    ensureCapacity(ed, ed->size + 1);
    ed->lines[ed->size++] = line;
  }

  fclose(fp);
  return 0;
}

void print_menu() {
  puts("\nCommands:");
  puts("  a - append line");
  puts("  i - insert line");
  puts("  d - delete line");
  puts("  p - print all");
  puts("  s - save to file");
  puts("  l - load from file");
  puts("  f - free all");
  puts("  r - shrinkToFit");
  puts("  q - quit");
}

size_t parse_index_input(const char *prompt, size_t max) {
  char *line = read_line_stdin(prompt);
  if (!line)
    return SIZE_MAX;

  long v = strtol(line, NULL, 10);
  free(line);

  if (v < 1 || v > (long)max) {
    fprintf(stderr, "Invalid index.\n");
    return SIZE_MAX;
  }

  return (size_t)(v - 1);
}

int main() {
  Editor ed;
  initEditor(&ed);

  puts("Minimal Text Editor (no errno)");

  for (;;) {
    print_menu();
    printf("Enter command: ");
    fflush(stdout);

    int cmd = getchar();
    if (cmd == EOF)
      break;
    while (getchar() != '\n')
      ;

    switch (cmd) {
    case 'a': {
      char *txt = read_line_stdin("Enter line: ");
      if (txt) {
        appendLine(&ed, txt);
        free(txt);
      }
      break;
    }

    case 'i': {
      size_t idx = parse_index_input("Insert at index: ", ed.size + 1);
      if (idx == SIZE_MAX)
        break;

      char *txt = read_line_stdin("Enter line: ");
      if (txt) {
        insertLine(&ed, idx, txt);
        free(txt);
      }
      break;
    }

    case 'd': {
      if (ed.size == 0) {
        puts("Buffer empty.");
        break;
      }
      size_t idx = parse_index_input("Delete index: ", ed.size);
      if (idx != SIZE_MAX)
        deleteLine(&ed, idx);
      break;
    }

    case 'p':
      printAllLines(&ed);
      break;

    case 's': {
      char *fname = read_line_stdin("Save filename: ");
      if (fname) {
        saveToFile(&ed, fname);
        free(fname);
      }
      break;
    }

    case 'l': {
      char *fname = read_line_stdin("Load filename: ");
      if (fname) {
        loadFromFile(&ed, fname);
        free(fname);
      }
      break;
    }

    case 'f':
      freeAll(&ed);
      initEditor(&ed);
      puts("Buffer cleared.");
      break;

    case 'r':
      shrinkToFit(&ed);
      puts("Shrink complete.");
      break;

    case 'q':
      freeAll(&ed);
      return 0;

    default:
      puts("Unknown command.");
    }
  }

  freeAll(&ed);
  return 0;
}
