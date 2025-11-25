#include <stdio.h>
#include <string.h>

struct Book {
  int id;
  int popularity;
  int lastAccess;
};

int main() {
  int capacity, Q;
  scanf("%d %d", &capacity, &Q);

  struct Book shelf[100];
  int count = 0;
  int timer = 0;

  for (int i = 0; i < Q; i++) {
    char command[10];
    scanf("%s", command);

    if (strcmp(command, "ADD") == 0) {
      int id, pop;
      scanf("%d %d", &id, &pop);

      int found = -1;

      for (int j = 0; j < count; j++) {
        if (shelf[j].id == id) {
          found = j;
          break;
        }
      }

      if (found != -1) {
        shelf[found].popularity = pop;
        shelf[found].lastAccess = ++timer;
      } else {
        if (count < capacity) {
          shelf[count].id = id;
          shelf[count].popularity = pop;
          shelf[count].lastAccess = ++timer;
          count++;
        } else {
          int lruIndex = 0;
          for (int j = 1; j < count; j++) {
            if (shelf[j].lastAccess < shelf[lruIndex].lastAccess) {
              lruIndex = j;
            }
          }

          shelf[lruIndex].id = id;
          shelf[lruIndex].popularity = pop;
          shelf[lruIndex].lastAccess = ++timer;
        }
      }
    }

    else if (strcmp(command, "ACCESS") == 0) {
      int id;
      scanf("%d", &id);

      int found = -1;

      for (int j = 0; j < count; j++) {
        if (shelf[j].id == id) {
          found = j;
          break;
        }
      }

      if (found == -1) {
        printf("-1\n");
      } else {
        shelf[found].lastAccess = ++timer;
        printf("%d\n", shelf[found].popularity);
      }
    }
  }

  return 0;
}
