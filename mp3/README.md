# README

## Brief

- Raise flag `handler_state` as `RUNNABLE` in `usertrap()` or `kerneltrap()`
- Store context when `thrdstop()` is invoked.
- Does long jump (overwrite `pc` and `a0`) inside `usertrapret()`

## Complementary Spec

1. There are no cases involves the behavior "resume to another thread handler".
2. There are only single test process executing.
3. Assume `syscall()` is short enough, it does not take more than 1 tick.
4. It is necessary to make another system call to restore the context.

## Configure GDB

Execute the following commands in container.

```bash
echo "add-auto-load-safe-path /home/xv6-riscv/.gdbinit" >> ~/.gdbinit
echo "set auto-load safe-path /" >> ~/.gdbinit
```

The completed init script looks like the following section.

```gdbscript
set confirm off
set architecture riscv:rv64
target remote 127.0.0.1:25000
symbol-file kernel/kernel
set disassemble-next-line auto
set riscv use-compressed-breakpoints yes

add-auto-load-safe-path /home/xv6-riscv/.gdbinit
set auto-load safe-path /
```
