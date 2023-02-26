from gradelib import *

r = Runner()


@test(5, "mp0 command with public testcase 0")
def test_mp0_0():
    r.run_qemu(shell_script([
        'testgen',
        'mp0 os2202 a',
    ]))
    r.match(
        'os2202 [error opening dir]',
        '',
        '0 directories, 0 files',
    )


@test(5, "mp0 command with public testcase 1")
def test_mp0_1():
    r.run_qemu(shell_script([
        # 'testgen',
        'mp0 os2202/ o',
    ]))
    r.match(
        'os2202/ [error opening dir]',
        '',
        '0 directories, 0 files',
    )


@test(5, "mp0 command with public testcase 2")
def test_mp0_2():
    r.run_qemu(shell_script([
        # 'testgen',
        'mp0 os2023 o',
    ]))
    r.match(
        'os2023 1',
        'os2023/d1 1',
        'os2023/d2 1',
        'os2023/d2/a 1',
        'os2023/d2/b 1',
        'os2023/d2/c 1',
        'os2023/d3 1',
        'os2023/d3/a 1',
        'os2023/d3/b 1',
        '',
        '6 directories, 2 files',
    )


@test(5, "mp0 command with public testcase 3")
def test_mp0_3():
    r.run_qemu(shell_script([
        # 'testgen',
        'mp0 os2023/ o',
    ]))
    r.match(
        'os2023/ 1',
        'os2023//d1 1',
        'os2023//d2 1',
        'os2023//d2/a 1',
        'os2023//d2/b 1',
        'os2023//d2/c 1',
        'os2023//d3 1',
        'os2023//d3/a 1',
        'os2023//d3/b 1',
        '',
        '6 directories, 2 files',
    )


@test(10, "mp0 command with public testcase 4")
def test_mp0_4():
    r.run_qemu(shell_script([
        # 'testgen',
        'mp0 a a',
    ]))
    r.match(
        'a 1',
        'a/0 1',
        'a/1 1',
        'a/2 1',
        'a/3 1',
        'a/4 1',
        'a/5 1',
        'a/6 1',
        'a/7 1',
        'a/8 1',
        'a/9 1',
        'a/10 1',
        '',
        '11 directories, 0 files',
    )

@test(10, "mp0 command with public testcase 5")
def test_mp0_5():
    r.run_qemu(shell_script([
        # 'testgen',
        'mp0 a/ a',
    ]))
    r.match(
        'a/ 1',
        'a//0 1',
        'a//1 1',
        'a//2 1',
        'a//3 1',
        'a//4 1',
        'a//5 1',
        'a//6 1',
        'a//7 1',
        'a//8 1',
        'a//9 1',
        'a//10 1',
        '',
        '11 directories, 0 files',
    )

@test(1, "mp0 command with self-implemented testcase 0")
def test_mp0_private_0():
    r.run_qemu(shell_script([
        'mp0 p/ p',
    ]))
    r.match(
        'p/ 1',
        'p//q 1',
        'p//q/p 2',
        'p//q/p/q 2',
        'p//q/p/q/p 3',
        '',
        '4 directories, 0 files',
    )

@test(1, "mp0 command with self-implemented testcase 1")
def test_mp0_private_1():
    r.run_qemu(shell_script([
        'mp0 p//// p',
    ]))
    r.match(
        'p//// 1',
        'p/////q 1',
        'p/////q/p 2',
        'p/////q/p/q 2',
        'p/////q/p/q/p 3',
        '',
        '4 directories, 0 files',
    )

@test(1, "mp0 command with self-implemented testcase 2")
def test_mp0_private_2():
    r.run_qemu(shell_script([
        'mp0 abcdefghij/klmnopqrst/abcdefghij/klmnopqrst/abcdefghij a',
    ]))
    r.match(
        'abcdefghij/klmnopqrst/abcdefghij/klmnopqrst/abcdefghij 3',
        '',
        '0 directories, 0 files',
    )


@test(1, "mp0 command with self-implemented testcase 3")
def test_mp0_private_3():
    r.run_qemu(shell_script([
        'mp0 abcdefghij/klmnopqrst/abcdefghij a',
    ]))
    r.match(
        'abcdefghij/klmnopqrst/abcdefghij 2',
        'abcdefghij/klmnopqrst/abcdefghij/klmnopqrst 2',
        'abcdefghij/klmnopqrst/abcdefghij/klmnopqrst/abcdefghij 3',
        '',
        '2 directories, 0 files',
    )

@test(1, "mp0 command with self-implemented testcase 4")
def test_mp0_private_4():
    r.run_qemu(shell_script([
        # 'testgen',
        'mp0 os2023/d2 o',
    ]))
    r.match(
        'os2023/d2 1',
        'os2023/d2/a 1',
        'os2023/d2/b 1',
        'os2023/d2/c 1',
        '',
        '2 directories, 1 files',
    )

# xv6 ls() sorts files and directories by inode.
@test(1, "mp0 command with self-implemented testcase 5")
def test_mp0_private_5():
    r.run_qemu(shell_script([
        'mp0 xxxxxxxxxx x',
    ]))
    r.match(
        'xxxxxxxxxx 10',
        'xxxxxxxxxx/yyyyyyyyyy 10',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx 30',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/aaaaaaaaaa 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/oooooooooo 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/pppppppppp 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/ssssssssss 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/yyyyyyyyyy/zzzzzzzzzz 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/cccccccccc 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/ffffffffff 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/gggggggggg 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/kkkkkkkkkk 20',
        'xxxxxxxxxx/yyyyyyyyyy/xxxxxxxxxx/uuuuuuuuuu 20',
        'xxxxxxxxxx/yyyyyyyyyy/bbbbbbbbbb 10',
        'xxxxxxxxxx/yyyyyyyyyy/hhhhhhhhhh 10',
        'xxxxxxxxxx/yyyyyyyyyy/tttttttttt 10',
        'xxxxxxxxxx/yyyyyyyyyy/mmmmmmmmmm 10',
        'xxxxxxxxxx/yyyyyyyyyy/rrrrrrrrrr 10',
        '',
        '4 directories, 15 files',
    )

run_tests()
