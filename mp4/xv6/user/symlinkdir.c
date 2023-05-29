#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"
#include "kernel/fcntl.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user/user.h"

#define fail(msg) do {printf("FAILURE: " msg "\n"); failed = 1; goto done;} while (0);
static int failed = 0;

static void public12(void);
static void public3(void);
static void public4(void);
static void public5(void);
static void cleanup(void);

int
main(int argc, char *argv[])
{
  cleanup();

  public12();
  cleanup();

  public3();
  cleanup();

  public4();
  cleanup();

  public5();
  cleanup();

  exit(failed);
}

static void
cleanup(void)
{
  unlink("/testsymlink2/p");
  unlink("/testsymlink2/q");
  unlink("/testsymlink3/q/p");
  unlink("/testsymlink3/q");
  unlink("/testsymlink2");
  unlink("/testsymlink3");
}

static void
public12()
{
  int r, fd1 = -1, fd2 = -1;
  char c = 0, c2 = 0;

  printf("Start: test symlinks to directory\n");

  mkdir("/testsymlink2");
  mkdir("/testsymlink3");

  fd1 = open("/testsymlink2/p", O_CREATE | O_RDWR);
  if(fd1 < 0) fail("failed to open p");

  r = symlink("/testsymlink2", "/testsymlink3/q");
  if(r < 0)
    fail("symlink q -> p failed");

  fd2 = open("/testsymlink3/q/p", O_RDWR);
  if(fd2<0) fail("Failed to open /testsymlink3/q/p\n");

  printf("public testcase 1: ok\n");

  c = '#';
  r = write(fd1, &c, 1);
  if(r!=1) fail("Failed to write to /testsymlink2/p\n");
  r = read(fd2, &c2, 1);
  if(r!=1) fail("Failed to read from /testsymlink3/q/p\n");
  if(c!=c2)
    fail("Value read from /testsymlink2/p differs from value written to /testsymlink3/q/p\n");

  printf("public testcase 2: ok\n");
done:
  close(fd1);
  close(fd2);
}

// detect symlink loops
static void
public3()
{
  int r, fd1 = -1;

  printf("Start: test symlinks to directory\n");

  mkdir("/testsymlink2");

  // 1. create symlink chain 1 -> 2 -> 1
  r = symlink("/testsymlink2/p", "/testsymlink2/q");
  if(r) fail("symlink q -> p failed");

  r = symlink("/testsymlink2/q", "/testsymlink2/p");
  if(r) fail("symlink p -> q failed");

  // 2. open dir p, expected failed
  fd1 = open("/testsymlink2/p", O_RDONLY);
  if(fd1!=-1) fail("Open a symlink cycle");

  printf("public testcase 3: ok\n");

done:
  close(fd1);
}

// "/testsymlink2/p" links to its parent "/testsymlink2"
// such that "/testsymlink2/p", "/testsymlink2/p/p", "/testsymlink2/p/p/p", ... are all equivalent
static void
public4()
{
  int r, fd1 = -1, fd2 = -1;
  char c = 0, c2 = 0;

  printf("Start: test symlinks to directory\n");

  mkdir("/testsymlink2");

  r = symlink("/testsymlink2", "/testsymlink2/p");
  if(r)
    fail("symlink /testsymlink2/p -> /testsymlink2 failed");

  // create a file in the directory and write a token to it
  // FIXME:
  fd1 = open("/testsymlink2/q", O_CREATE | O_RDWR);
  if(fd1 < 0) fail("failed to open /testsymlink2/q");

  c = '*';
  r = write(fd1, &c, 1);
  if(r!=1) fail("Failed to write to /testsymlink2/q\n");

  // check token equals to /testsymlink2/p/q
  fd2 = open("/testsymlink2/p/q", O_RDWR);
  if(fd2<0) fail("Failed to open /testsymlink2/p/q\n");

  r = read(fd2, &c2, 1);
  if(r!=1) fail("Failed to read from /testsymlink2/p/q\n");

  if(c!=c2)
    fail("Value read from /testsymlink2/q differs from value written to /testsymlink2/p/q\n");

  close(fd2);

  // check token equals to /testsymlink2/p/p/q
  fd2 = open("/testsymlink2/p/p/q", O_RDWR);
  if(fd2<0) fail("Failed to open /testsymlink2/p/p/q\n");

  r = read(fd2, &c2, 1);
  if(r!=1) fail("Failed to read from /testsymlink2/p/p/q\n");
  if(c!=c2)
    fail("Value read from /testsymlink2/p/p/q differs from value written to /testsymlink2/p/q\n");

  close(fd2);

  printf("public testcase 4: ok\n");

done:
  close(fd1);
  close(fd2);
}

// "/testsymlink2/p" links to its parent "/testsymlink2"
// such that "/testsymlink2/p", "/testsymlink2/p/p", "/testsymlink2/p/p/p", ... are all equivalent
static void
public5()
{
  int r, fd1 = -1, fd2 = -1;
  char c = 0, c2 = 0;

  printf("Start: test symlinks to directory\n");

  mkdir("/testsymlink2");

  r = symlink("/testsymlink2", "/testsymlink2/p");
  if(r)
    fail("symlink /testsymlink2/p -> /testsymlink2 failed");

  // create a file in the directory and write a token to it
  // FIXME:
  fd1 = open("/testsymlink2/p/q", O_CREATE | O_RDWR);
  if(fd1 < 0) fail("failed to open /testsymlink2/q");

  c = '*';
  r = write(fd1, &c, 1);
  if(r!=1) fail("Failed to write to /testsymlink2/q\n");

  // check token equals to /testsymlink2/p/q
  fd2 = open("/testsymlink2/q", O_RDWR);
  if(fd2<0) fail("Failed to open /testsymlink2/p/q\n");

  r = read(fd2, &c2, 1);
  if(r!=1) fail("Failed to read from /testsymlink2/p/q\n");

  if(c!=c2)
    fail("Value read from /testsymlink2/q differs from value written to /testsymlink2/p/q\n");

  close(fd2);

  // check token equals to /testsymlink2/p/p/q
  fd2 = open("/testsymlink2/p/p/q", O_RDWR);
  if(fd2<0) fail("Failed to open /testsymlink2/p/p/q\n");

  r = read(fd2, &c2, 1);
  if(r!=1) fail("Failed to read from /testsymlink2/p/p/q\n");
  if(c!=c2)
    fail("Value read from /testsymlink2/p/p/q differs from value written to /testsymlink2/p/q\n");

  close(fd2);

  printf("public testcase 5: ok\n");

done:
  close(fd1);
  close(fd2);
}