#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void run_tree(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    char full_path[1024];

    if (!(dir = opendir(path))) return;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, 
"..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, 
entry->d_name);

        if (lstat(full_path, &info) == -1) continue;

        for (int i = 0; i < depth; i++) {
            printf("  "); 
        }

        printf("|-- %s\n", entry->d_name);

        if (S_ISDIR(info.st_mode) && !S_ISLNK(info.st_mode)) {
            run_tree(full_path, depth + 1);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    char *start;
    if (argc < 2) start = ".";
    else start = argv[1];

    printf("%s\n", start);
    run_tree(start, 0);
    return 0;
}
