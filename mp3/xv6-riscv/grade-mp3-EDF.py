#!/usr/bin/env python3

import re
from gradelib import *

import os

os.system("make clean")
r = Runner(save("xv6.out"))

# @test(3, "task1")
# def test_uthread():
#     r.run_qemu(shell_script([
#         'task1'
#     ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
#     expected = """dispatch thread#1 at 0: allocated_time=2
# thread#1 finish one cycle at 2: 4 cycles left
# dispatch thread#2 at 2: allocated_time=3
# thread#2 finish one cycle at 5: 4 cycles left
# dispatch thread#1 at 5: allocated_time=2
# thread#1 finish one cycle at 7: 3 cycles left
# dispatch thread#2 at 7: allocated_time=3
# thread#2 finish one cycle at 10: 3 cycles left
# dispatch thread#1 at 10: allocated_time=2
# thread#1 finish one cycle at 12: 2 cycles left
# dispatch thread#2 at 12: allocated_time=3
# thread#2 finish one cycle at 15: 2 cycles left
# dispatch thread#1 at 15: allocated_time=1
# thread#1 misses a deadline at 16"""
#     if not re.findall(expected, r.qemu.output, re.M):
#         raise AssertionError('Output does not match expected output')

# @test(3, "task2")
# def test_uthread():
#     r.run_qemu(shell_script([
#         'task2'
#     ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
#     expected = """dispatch thread#1 at 0: allocated_time=5
# thread#1 finish one cycle at 5: 2 cycles left
# dispatch thread#2 at 5: allocated_time=7
# thread#2 finish one cycle at 12: 2 cycles left
# dispatch thread#1 at 12: allocated_time=5
# thread#1 finish one cycle at 17: 1 cycles left
# dispatch thread#2 at 17: allocated_time=3
# dispatch thread#1 at 20: allocated_time=5
# thread#1 finish one cycle at 25: 0 cycles left
# dispatch thread#2 at 25: allocated_time=4
# thread#2 finish one cycle at 29: 1 cycles left
# run_queue is empty, sleep for 3 ticks
# dispatch thread#2 at 32: allocated_time=7
# thread#2 finish one cycle at 39: 0 cycles left"""
#     if not re.findall(expected, r.qemu.output, re.M):
#         raise AssertionError('Output does not match expected output')

# @test(3, "task3")
# def test_uthread():
#     r.run_qemu(shell_script([
#         'task3'
#     ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
#     expected = """dispatch thread#1 at 0: allocated_time=1
# thread#1 finish one cycle at 1: 2 cycles left
# dispatch thread#2 at 1: allocated_time=2
# thread#2 finish one cycle at 3: 2 cycles left
# dispatch thread#4 at 3: allocated_time=2
# thread#4 finish one cycle at 5: 2 cycles left
# dispatch thread#3 at 5: allocated_time=2
# thread#3 finish one cycle at 7: 2 cycles left
# dispatch thread#1 at 7: allocated_time=1
# thread#1 finish one cycle at 8: 1 cycles left
# dispatch thread#2 at 8: allocated_time=2
# thread#2 finish one cycle at 10: 1 cycles left
# dispatch thread#1 at 10: allocated_time=1
# thread#1 finish one cycle at 11: 0 cycles left
# dispatch thread#4 at 11: allocated_time=1
# thread#4 misses a deadline at 12"""
#     if not re.findall(expected, r.qemu.output, re.M):
#         raise AssertionError('Output does not match expected output')

# @test(3, "task4")
# def test_uthread():
#     r.run_qemu(shell_script([
#         'task4'
#     ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
#     expected = """dispatch thread#1 at 0: allocated_time=3
# thread#1 finish one cycle at 3: 2 cycles left
# dispatch thread#1 at 3: allocated_time=3
# thread#1 finish one cycle at 6: 1 cycles left
# dispatch thread#1 at 6: allocated_time=3
# thread#1 finish one cycle at 9: 0 cycles left"""
#     if not re.findall(expected, r.qemu.output, re.M):
#         raise AssertionError('Output does not match expected output')

# Auto-generated, not validated by human
@test(3, "task5")
def test_uthread():
    r.run_qemu(shell_script([
        'task5'
    ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
    expected = """dispatch thread#1 at 0: allocated_time=1
thread#1 finish one cycle at 1: 0 cycles left
dispatch thread#2 at 1: allocated_time=1
thread#2 finish one cycle at 2: 0 cycles left
dispatch thread#3 at 2: allocated_time=2
thread#3 finish one cycle at 4: 0 cycles left
run_queue is empty, sleep for 46 ticks
dispatch thread#4 at 50: allocated_time=3
thread#4 finish one cycle at 53: 1 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#4 at 62: allocated_time=3
thread#4 finish one cycle at 65: 0 cycles left"""
    if not re.findall(expected, r.qemu.output, re.M):
        raise AssertionError('Output does not match expected output')

# Auto-generated, not validated by human
@test(3, "task6")
def test_uthread():
    r.run_qemu(shell_script([
        'task6'
    ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
    expected = """dispatch thread#1 at 0: allocated_time=2
thread#1 finish one cycle at 2: 8 cycles left
run_queue is empty, sleep for 2 ticks
dispatch thread#5 at 4: allocated_time=1
thread#5 finish one cycle at 5: 8 cycles left
dispatch thread#2 at 5: allocated_time=2
dispatch thread#4 at 7: allocated_time=1
thread#4 finish one cycle at 8: 5 cycles left
dispatch thread#2 at 8: allocated_time=1
thread#2 finish one cycle at 9: 4 cycles left
dispatch thread#3 at 9: allocated_time=3
thread#3 finish one cycle at 12: 5 cycles left
dispatch thread#6 at 12: allocated_time=3
thread#6 finish one cycle at 15: 6 cycles left
dispatch thread#7 at 15: allocated_time=5
thread#7 finish one cycle at 20: 9 cycles left
dispatch thread#1 at 20: allocated_time=2
thread#1 finish one cycle at 22: 7 cycles left
dispatch thread#4 at 22: allocated_time=1
thread#4 finish one cycle at 23: 4 cycles left
dispatch thread#5 at 23: allocated_time=1
thread#5 finish one cycle at 24: 7 cycles left
dispatch thread#2 at 24: allocated_time=3
thread#2 finish one cycle at 27: 3 cycles left
dispatch thread#6 at 27: allocated_time=3
thread#6 finish one cycle at 30: 5 cycles left
dispatch thread#7 at 30: allocated_time=3
thread#7 misses a deadline at 33"""
    if not re.findall(expected, r.qemu.output, re.M):
        raise AssertionError('Output does not match expected output')

# Auto-generated, not validated by human
@test(3, "task7")
def test_uthread():
    r.run_qemu(shell_script([
        'task7'
    ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
    expected = """run_queue is empty, sleep for 2 ticks
dispatch thread#1 at 2: allocated_time=4
thread#1 finish one cycle at 6: 2 cycles left
dispatch thread#2 at 6: allocated_time=5
thread#2 finish one cycle at 11: 3 cycles left
dispatch thread#4 at 11: allocated_time=1
thread#4 finish one cycle at 12: 3 cycles left
dispatch thread#3 at 12: allocated_time=2
thread#3 finish one cycle at 14: 0 cycles left
dispatch thread#1 at 14: allocated_time=4
thread#1 finish one cycle at 18: 1 cycles left
dispatch thread#2 at 18: allocated_time=5
thread#2 finish one cycle at 23: 2 cycles left
dispatch thread#4 at 23: allocated_time=1
thread#4 finish one cycle at 24: 2 cycles left
dispatch thread#1 at 24: allocated_time=4
thread#1 finish one cycle at 28: 0 cycles left
run_queue is empty, sleep for 2 ticks
dispatch thread#2 at 30: allocated_time=5
thread#2 finish one cycle at 35: 1 cycles left
dispatch thread#4 at 35: allocated_time=1
thread#4 finish one cycle at 36: 1 cycles left
run_queue is empty, sleep for 6 ticks
dispatch thread#2 at 42: allocated_time=5
thread#2 finish one cycle at 47: 0 cycles left
dispatch thread#4 at 47: allocated_time=1
thread#4 finish one cycle at 48: 0 cycles left"""
    if not re.findall(expected, r.qemu.output, re.M):
        raise AssertionError('Output does not match expected output')

# Auto-generated, not validated by human
@test(3, "task8")
def test_uthread():
    r.run_qemu(shell_script([
        'task8'
    ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
    expected = """run_queue is empty, sleep for 1 ticks
dispatch thread#4 at 1: allocated_time=1
thread#4 finish one cycle at 2: 9 cycles left
run_queue is empty, sleep for 3 ticks
dispatch thread#3 at 5: allocated_time=5
thread#3 finish one cycle at 10: 0 cycles left
dispatch thread#1 at 10: allocated_time=2
thread#1 finish one cycle at 12: 1 cycles left
dispatch thread#2 at 12: allocated_time=1
thread#2 finish one cycle at 13: 0 cycles left
dispatch thread#4 at 13: allocated_time=1
thread#4 finish one cycle at 14: 8 cycles left
run_queue is empty, sleep for 4 ticks
dispatch thread#1 at 18: allocated_time=2
thread#1 finish one cycle at 20: 0 cycles left
run_queue is empty, sleep for 1 ticks
dispatch thread#4 at 21: allocated_time=1
thread#4 finish one cycle at 22: 7 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#4 at 31: allocated_time=1
thread#4 finish one cycle at 32: 6 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#4 at 41: allocated_time=1
thread#4 finish one cycle at 42: 5 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#4 at 51: allocated_time=1
thread#4 finish one cycle at 52: 4 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#4 at 61: allocated_time=1
thread#4 finish one cycle at 62: 3 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#4 at 71: allocated_time=1
thread#4 finish one cycle at 72: 2 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#4 at 81: allocated_time=1
thread#4 finish one cycle at 82: 1 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#4 at 91: allocated_time=1
thread#4 finish one cycle at 92: 0 cycles left"""
    if not re.findall(expected, r.qemu.output, re.M):
        raise AssertionError('Output does not match expected output')

# Auto-generated, not validated by human
@test(3, "task9")
def test_uthread():
    r.run_qemu(shell_script([
        'task9'
    ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
    expected = """dispatch thread#2 at 0: allocated_time=2
thread#2 finish one cycle at 2: 3 cycles left
dispatch thread#5 at 2: allocated_time=3
thread#5 finish one cycle at 5: 2 cycles left
dispatch thread#1 at 5: allocated_time=2
thread#1 finish one cycle at 7: 5 cycles left
dispatch thread#4 at 7: allocated_time=2
thread#4 finish one cycle at 9: 9 cycles left
dispatch thread#3 at 9: allocated_time=5
thread#3 finish one cycle at 14: 0 cycles left
dispatch thread#2 at 14: allocated_time=2
thread#2 finish one cycle at 16: 2 cycles left
dispatch thread#5 at 16: allocated_time=3
thread#5 finish one cycle at 19: 1 cycles left
dispatch thread#1 at 19: allocated_time=2
thread#1 finish one cycle at 21: 4 cycles left
dispatch thread#4 at 21: allocated_time=2
thread#4 finish one cycle at 23: 8 cycles left
dispatch thread#2 at 23: allocated_time=2
thread#2 finish one cycle at 25: 1 cycles left
dispatch thread#5 at 25: allocated_time=3
thread#5 finish one cycle at 28: 0 cycles left
dispatch thread#1 at 28: allocated_time=2
thread#1 finish one cycle at 30: 3 cycles left
dispatch thread#4 at 30: allocated_time=2
thread#4 finish one cycle at 32: 7 cycles left
run_queue is empty, sleep for 1 ticks
dispatch thread#2 at 33: allocated_time=2
thread#2 finish one cycle at 35: 0 cycles left
dispatch thread#1 at 35: allocated_time=2
thread#1 finish one cycle at 37: 2 cycles left
run_queue is empty, sleep for 3 ticks
dispatch thread#4 at 40: allocated_time=2
thread#4 finish one cycle at 42: 6 cycles left
run_queue is empty, sleep for 3 ticks
dispatch thread#1 at 45: allocated_time=2
thread#1 finish one cycle at 47: 1 cycles left
run_queue is empty, sleep for 5 ticks
dispatch thread#4 at 52: allocated_time=2
thread#4 finish one cycle at 54: 5 cycles left
run_queue is empty, sleep for 1 ticks
dispatch thread#1 at 55: allocated_time=2
thread#1 finish one cycle at 57: 0 cycles left
run_queue is empty, sleep for 7 ticks
dispatch thread#4 at 64: allocated_time=2
thread#4 finish one cycle at 66: 4 cycles left
run_queue is empty, sleep for 10 ticks
dispatch thread#4 at 76: allocated_time=2
thread#4 finish one cycle at 78: 3 cycles left
run_queue is empty, sleep for 10 ticks
dispatch thread#4 at 88: allocated_time=2
thread#4 finish one cycle at 90: 2 cycles left
run_queue is empty, sleep for 10 ticks
dispatch thread#4 at 100: allocated_time=2
thread#4 finish one cycle at 102: 1 cycles left
run_queue is empty, sleep for 10 ticks
dispatch thread#4 at 112: allocated_time=2
thread#4 finish one cycle at 114: 0 cycles left"""
    if not re.findall(expected, r.qemu.output, re.M):
        raise AssertionError('Output does not match expected output')

# Auto-generated, not validated by human
@test(3, "task10")
def test_uthread():
    r.run_qemu(shell_script([
        'task10'
    ]), make_args = ["SCHEDPOLICY=THREAD_SCHEDULER_EDF"])
    expected = """run_queue is empty, sleep for 2 ticks
dispatch thread#3 at 2: allocated_time=2
thread#3 finish one cycle at 4: 1 cycles left
dispatch thread#1 at 4: allocated_time=4
thread#1 finish one cycle at 8: 9 cycles left
run_queue is empty, sleep for 1 ticks
dispatch thread#2 at 9: allocated_time=2
thread#2 finish one cycle at 11: 0 cycles left
dispatch thread#3 at 11: allocated_time=2
thread#3 finish one cycle at 13: 0 cycles left
run_queue is empty, sleep for 2 ticks
dispatch thread#1 at 15: allocated_time=4
thread#1 finish one cycle at 19: 8 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#1 at 28: allocated_time=4
thread#1 finish one cycle at 32: 7 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#1 at 41: allocated_time=4
thread#1 finish one cycle at 45: 6 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#1 at 54: allocated_time=4
thread#1 finish one cycle at 58: 5 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#1 at 67: allocated_time=4
thread#1 finish one cycle at 71: 4 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#1 at 80: allocated_time=4
thread#1 finish one cycle at 84: 3 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#1 at 93: allocated_time=4
thread#1 finish one cycle at 97: 2 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#1 at 106: allocated_time=4
thread#1 finish one cycle at 110: 1 cycles left
run_queue is empty, sleep for 9 ticks
dispatch thread#1 at 119: allocated_time=4
thread#1 finish one cycle at 123: 0 cycles left"""
    if not re.findall(expected, r.qemu.output, re.M):
        raise AssertionError('Output does not match expected output')

run_tests()
os.system("make clean")
