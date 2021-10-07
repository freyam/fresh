#include "global.h"

extern char tilda[100];
extern char previous[1000];
extern char buffer[100000];

void RUN_ls(char *arr1, char *arr2, int arg1, int arg2) {
    if (arg2) {
        int ss = access(arr2, F_OK);
        if (ss == -1) {
            perror("ls: cannot access. No such file or directory\n");
            return;
        }
    }
    if (arg1 == 0 && arg2 == 0) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        char *pointer = NULL;
        pointer = cwd;
        DIR *dp = NULL;
        dp = opendir((char *)pointer);
        struct dirent *sd = NULL;
        while ((sd = readdir(dp)) != NULL) {
            if (sd->d_name[0] != '.')
                printf("%s\t", sd->d_name);
        }
    } else if (arg1 && arg2 == 0) {

        if (!strcmp(arr1, "-a")) {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            DIR *thedirectory;
            struct dirent *thefile;
            struct stat thestat;

            char buf[2048];

            thedirectory = opendir(cwd);

            while ((thefile = readdir(thedirectory)) != NULL) {
                sprintf(buf, "%s/%s", cwd, thefile->d_name);
                stat(buf, &thestat);

                printf("%s\t", thefile->d_name);
            }
            closedir(thedirectory);
        } else if (!strcmp(arr1, "-la") || !strcmp(arr1, "-al") || !strcmp(arr1, "-l")) {
            int flag = 0;
            if (!strcmp(arr1, "-l"))
                flag = 1;
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));

            DIR *thedirectory;
            struct dirent *thefile;
            struct stat thestat;
            struct passwd *tf;
            struct group *gf;

            char buf[2048];

            thedirectory = opendir(cwd);

            while ((thefile = readdir(thedirectory)) != NULL) {
                if (thefile->d_name[0] == '.' && flag == 1) {
                    continue;
                }
                sprintf(buf, "%s/%s", cwd, thefile->d_name);
                stat(buf, &thestat);
                switch (thestat.st_mode & S_IFMT) {
                case S_IFBLK:
                    printf("b ");
                    break;
                case S_IFCHR:
                    printf("c ");
                    break;
                case S_IFDIR:
                    printf("d ");
                    break;
                case S_IFIFO:
                    printf("p ");
                    break;
                case S_IFLNK:
                    printf("l ");
                    break;
                case S_IFSOCK:
                    printf("s ");
                    break;
                default:
                    printf("- ");
                    break;
                }

                printf((thestat.st_mode & S_IRUSR) ? "r" : "-");
                printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
                printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
                printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
                printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
                printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
                printf((thestat.st_mode & S_IROTH) ? "r" : "-");
                printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
                printf((thestat.st_mode & S_IXOTH) ? "x" : "-");

                printf("\t%1lu", thestat.st_nlink);
                tf = getpwuid(thestat.st_uid);
                printf("\t%1s", tf->pw_name);
                gf = getgrgid(thestat.st_gid);
                printf("\t%1s", gf->gr_name);
                printf("\t%1zu", thestat.st_size);

                printf("\t%30s", thefile->d_name);
                printf("\t%30s", ctime(&thestat.st_mtime));
            }
            closedir(thedirectory);

        } else {
            int ss = access(arr1, F_OK);
            if (ss == -1) {
                printf("ls: cannot access. No such file or directory\n");

                return;
            }

            char *pointer = NULL;
            DIR *dp = NULL;
            struct dirent *sd = NULL; // directory
            pointer = arr1;
            dp = opendir((char *)pointer);

            while ((sd = readdir(dp)) != NULL) {
                if (sd->d_name[0] != '.')
                    printf("%s\t", sd->d_name);
            }
        }

    } else if (arg1 && arg2) {
        if (!strcmp(arr1, "-a")) {

            DIR *thedirectory;
            struct dirent *thefile;
            struct stat thestat;

            char buf[512];

            thedirectory = opendir(arr2);

            while ((thefile = readdir(thedirectory)) != NULL) {
                sprintf(buf, "%s/%s", arr2, thefile->d_name);
                stat(buf, &thestat);

                printf("%s\t", thefile->d_name);
            }
            closedir(thedirectory);
        } else if (!strcmp(arr1, "-la") || !strcmp(arr1, "-al") || !strcmp(arr1, "-l")) {
            int flag = 0;
            if (!strcmp(arr1, "-l"))
                flag = 1;

            DIR *thedirectory;
            struct dirent *thefile;
            struct stat thestat;
            struct passwd *tf;
            struct group *gf;

            char buf[512];

            thedirectory = opendir(arr2);

            while ((thefile = readdir(thedirectory)) != NULL) {
                if (thefile->d_name[0] == '.' && flag == 1) {
                    continue;
                }

                sprintf(buf, "%s/%s", arr2, thefile->d_name);
                stat(buf, &thestat);

                switch (thestat.st_mode & S_IFMT) {
                case S_IFBLK:
                    printf("b ");
                    break;
                case S_IFCHR:
                    printf("c ");
                    break;
                case S_IFDIR:
                    printf("d ");
                    break;
                case S_IFIFO:
                    printf("p ");
                    break;
                case S_IFLNK:
                    printf("l ");
                    break;
                case S_IFSOCK:
                    printf("s ");
                    break;
                default:
                    printf("- ");
                    break;
                }

                printf((thestat.st_mode & S_IRUSR) ? "r" : "-");
                printf((thestat.st_mode & S_IWUSR) ? "w" : "-");
                printf((thestat.st_mode & S_IXUSR) ? "x" : "-");
                printf((thestat.st_mode & S_IRGRP) ? "r" : "-");
                printf((thestat.st_mode & S_IWGRP) ? "w" : "-");
                printf((thestat.st_mode & S_IXGRP) ? "x" : "-");
                printf((thestat.st_mode & S_IROTH) ? "r" : "-");
                printf((thestat.st_mode & S_IWOTH) ? "w" : "-");
                printf((thestat.st_mode & S_IXOTH) ? "x" : "-");

                printf("\t%1lu", thestat.st_nlink);
                tf = getpwuid(thestat.st_uid);
                printf("\t%1s", tf->pw_name);

                gf = getgrgid(thestat.st_gid);
                printf("\t%1s", gf->gr_name);

                printf("\t%1zu", thestat.st_size);
                printf("\t%1s %1s", thefile->d_name, ctime(&thestat.st_mtime));
            }
            closedir(thedirectory);
        }
    }
    printf("\n");
}

// turtle happy