#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int
occurrence(const char *str, char c)
{
    const char *p = str;
    int cnt = 0;

    while (*p) {
        cnt += (*p++ == c);
    }

    return cnt;
}

// Traverse directory with recursive implementation.
// Return (dir_num) << 16 + (file_num)
int
tree(const char *fname, char key)
{
    struct dirent dirent = { };
    struct stat st = { };
    char buf[64], *p;
    int ans = 0;
    int fd = 0;

    if ((fd = open(fname, O_RDONLY)) < 0) {
        fprintf(2, "%s [error opening dir]\n", fname);
        return 0;
    }

    // ! Silent fail.
    if (fstat(fd, &st) < 0) {
        goto end;
    }

    // * Traverse current inode.
    printf("%s %d\n", fname, occurrence(fname, key));
    if (st.type == T_FILE) {
        ans = 1; goto end;
    }

    // * Traverse tree leaves.
    ans = 1 << 16;

    strcpy(buf, fname);
    p = buf + strlen(buf); *p++ = '/';
    while (read(fd, &dirent, sizeof(dirent)) == sizeof(dirent)) {
        if (dirent.inum == 0)
            continue;

        // Avoid current dir and parent dir
        if (!strcmp(dirent.name, ".") || !strcmp(dirent.name, ".."))
            continue;

        p = memcpy(p, dirent.name, DIRSIZ);
        ans += tree(buf, key);
    }

end:
    close(fd);

    return ans;
}

/**
 * xv6 mine-sweeping
 * - `exit(0)` instead `return 0`
 * - frequently commit your code
 */
int
main(int argc, char *argv[])
{
    // Program is expected to receive these arguments
    // mp0 <root_directory> <key>
    //
    // Testcase Specifications
    //
    // 6. The testcases are guaranteed to have sufficient parameters when executing the command.
    // We will not execute the mp0 command without providing <root directory> and <key>.
    if (argc != 3) {
        fprintf(2, "Usage: %s <root_directory> <key>\n", argv[0]);
        exit(0);
    }

    const char * const dirname = argv[1];
    const char key = *argv[2];
    int ans = 0, pid = 0;
    int pipe_fds[2];

    // Open pipe. Parent is reader and child is writer.
    if (pipe(pipe_fds) != 0) {
        fprintf(2, "Failed to open pipe.\n"); exit(0);
    }

    // fork a process.
    pid = fork();
    if (pid != 0) {
        close(pipe_fds[1]); pipe_fds[1] = -1;

        if (read(pipe_fds[0], &ans, sizeof(ans)) != sizeof(ans)) {
            fprintf(2, "Unexpected read() result.\n");
        }
        close(pipe_fds[0]); pipe_fds[0] = -1;
        printf("\n%d directories, %d files\n", (ans >> 16) ? ((ans >> 16) - 1) : 0, ans & 0xFFFF);
        wait(0); exit(0);
    }

    // The child process has to traverse the files and directories under <root directory>, output the path and
    // the number of occurrences of the given key, and analyze the total number of traversed files and directories.
    // The testcases only contain files and directories (no devices). The path and the number of occurrences
    // should be separated by a space. The traversing order should be the same as the ls command. Note that
    // if the path is aa/a, the occurrence should be 3.
    //
    // Note that you should separate the <root directory> and its sub-directory with a single “/”. That is, if
    // <root directory> contains one or more “/”, then you should keep all, append a “/”, and then append
    // the name of the sub-directory. Sample outputs are provided in Section 5.5.
    // However, if the <root directory> does not exist or is not a directory, you should print the following line:
    close(pipe_fds[0]); pipe_fds[0] = -1;
    ans = tree(dirname, key);

    // Sends two integers, file_num and dir_num, to parent.
    if (write(pipe_fds[1], &ans, sizeof(ans)) != sizeof(ans)) {
        fprintf(2, "Unexpected write() result.\n");
    }

    close(pipe_fds[1]); pipe_fds[1] = -1;
    exit(0);
}
