#include <stdio.h>
#include <unistd.h>
#define READ 0
#define WRITE 1

void get_input(char *string, int length) {
  fgets(string, length, stdin);
  while (*string) {
    if (*string == '\n') {
      *string = '\0';
    }
    else {
      string ++;
    }
  }
}

void capitalize(char *string) {
  while (*string) {
    if ('a' <= *string && *string <= 'z') {
      *string -= 32;
    }
    string ++;
  }
}

int main() {
  int parent_to_child[2];
  pipe(parent_to_child);
  int child_to_parent[2];
  pipe(child_to_parent);
  char line[1000];
  if (fork()) {
    close(parent_to_child[READ]);
    close(child_to_parent[WRITE]);

    get_input(line, sizeof line);
    write(parent_to_child[WRITE], line, sizeof line);
    read(child_to_parent[READ], line, sizeof line);
    printf("[%s]\n", line);
  }
  else {
    close(parent_to_child[WRITE]);
    close(child_to_parent[READ]);

    read(parent_to_child[READ], line, sizeof line);
    capitalize(line);
    write(child_to_parent[WRITE], line, sizeof line);
  }
  return 0;
}
