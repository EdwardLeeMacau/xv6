#include "kernel/types.h"

#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "user/user.h"
void mkfile(char *filename) {
    int fd = open(filename, O_CREATE | O_RDWR);
    write(fd, "hi", 3);
    close(fd);
}

void mkd(char *dirname) {
    if (mkdir(dirname) < 0) {
        fprintf(2, "mkdir %s failed.", dirname);
        exit(1);
    }
}
void test0() {
    mkd("os2023");

    mkd("os2023/d1");
    mkd("os2023/d2");
    mkd("os2023/d3");

    mkd("os2023/d2/a");
    mkd("os2023/d2/b");
    mkfile("os2023/d2/c");

    mkd("os2023/d3/a");
    mkfile("os2023/d3/b");
}

void test1() {
    mkd("a");
    mkd("a/0");
    mkd("a/1");
    mkd("a/2");
    mkd("a/3");
    mkd("a/4");
    mkd("a/5");
    mkd("a/6");
    mkd("a/7");
    mkd("a/8");
    mkd("a/9");
    mkd("a/10");
}

void test2() {
    mkd("p");
    mkd("p/q");
    mkd("p/q/p");
    mkd("p/q/p/q");
    mkd("p/q/p/q/p");
}

void test3() {
    mkd("abcdefghij");
    mkd("abcdefghij/klmnopqrst");
    mkd("abcdefghij/klmnopqrst/abcdefghij");
    mkd("abcdefghij/klmnopqrst/abcdefghij/klmnopqrst");
    mkd("abcdefghij/klmnopqrst/abcdefghij/klmnopqrst/abcdefghij");
}

void test4() {
    mkd("xxxxxxxxxx");
    mkd("xxxxxxxxxx/yyyyyyyyyy");
    mkd("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx");
    mkd("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy");
    mkd("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/bbbbbbbbbb");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/hhhhhhhhhh");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/tttttttttt");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/mmmmmmmmmm");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/rrrrrrrrrr");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/cccccccccc");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/ffffffffff");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/gggggggggg");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/kkkkkkkkkk");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/uuuuuuuuuu");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/aaaaaaaaaa");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/oooooooooo");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/pppppppppp");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/ssssssssss");
    mkfile("xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/zzzzzzzzzz");
}

int main(int argc, char *argv[]) {
    test0();
    test1();
    test2();
    test3();
    test4();
    exit(0);
}
