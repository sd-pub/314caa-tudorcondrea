#!/usr/bin/env python3

import os
import sys
import json
import subprocess

ROOT = './'

''' Checker's HOW TO

    @labs - represents a config dictionary/JSON for every lab.
    For each lab number, it can have the following entries:
        MUST HAVE:
            @name = directory name
            @tasks = the number of tasks for the lab
            @points = list containing how many points you can get per each task
        AUXILIARY:
            @taskX_run = Makefile's target to run the taskX program

    For each LAB, create tests/in/task[1-X] and tests/ref/task[1-X], X = No. of Tasks
    In in/ and ref/ create test[1-Z].in and test[1-Z].ref, Z = No. of Tests
'''

labs = {
    1   : { "name" : "01_recap_pc", 
            "tasks" : 1,
            "points": [40] },
    2   : { "name" : "02_simple_linked_list",
            "tasks" : 1,
            "points": [50] },
    3   : { "name" : "03_double_linked_list",
            "tasks" : 1 },
    4   : { "name" : "04_hashmap",
            "tasks" : 1 },
    5   : { "name" : "05_stack_queue",
            "tasks" : 1 },
    6   : { "name" : "06_graph_1", 
            "tasks" : 1 },
    7   : { "name" : "07_graph_2",
            "tasks" : 1 },
    8   : { "name" : "08_tree",
            "tasks" : 2,
            "points" : [40, 30],
            "task2_run" : "run_task2" },
    9   : { "name" : "09_bst_heap",
            "tasks" : 2,
            "points" : [35, 35],
            "task1_run" : "run_task1",
            "task2_run" : "run_task2" },
    10  : { "name" : "10_treap",
            "tasks" : 4,
            "points": [20, 15, 20, 15]},
    11  : { "name" : "11_avl_rbtree", 
            "tasks" : 1 },
    12  : { "name" : "12_recap_sd", 
            "tasks" : 1 },

    99  : { "name" : "99_test",
            "tasks" : 2,
            "points" : [30, 70],
            "task2_run" : "run_task2"}
}

if len(sys.argv) < 2:
    print('Usage: ./checker.py <lab_no>')
    sys.exit()
# You may remove the previous if and put below the wished lab number
lab_no = int(sys.argv[1])

current_lab = os.path.join(ROOT, labs[lab_no]['name'], 'skel/')
print(f'Checking {current_lab}...\n')

# make
rc = subprocess.call(f'make -sC {current_lab}', shell = True)
if rc != 0:
    sys.stderr.write(f'make failed with status {rc}\n')
    sys.exit(rc)

# run tasks
total_score = 0
for task_no in range(1, labs[lab_no]['tasks'] + 1):

    task_score = 0

    run = 'run'
    if f'task{task_no}_run' in labs[lab_no]:
        run = labs[lab_no][f'task{task_no}_run']

    tests_in = os.path.join(current_lab, f'tests/in/task{task_no}')
    tests_no = len(os.listdir(tests_in))

    tests_ref = os.path.join(current_lab, f'tests/ref/task{task_no}')
    tests_out = os.path.join(current_lab, f'tests/out/task{task_no}')

    rc = subprocess.call(f'mkdir -p {tests_out}', shell = True)
    if rc != 0:
        sys.stderr.write(f'mkdir failed with status {rc}\n')
        sys.exit(rc)

    task_total_score = labs[lab_no]['points'][task_no - 1]
    task_test_score = task_total_score / tests_no

    print('=' * 10 + f' Task {task_no}')
    for _ in range(1, tests_no + 1):
        proc = os.popen(f'make {run} -sC {current_lab} \
                        < {os.path.join(tests_in, f"test{_}.in")} \
                        > {os.path.join(tests_out, f"test{_}.out")}')
        proc.close()
        
        res_out = open(f'{os.path.join(tests_out, f"test{_}.out")}').read().strip().strip('\n')
        res_ref = open(f'{os.path.join(tests_ref, f"test{_}.ref")}').read().strip().strip('\n')

        if res_out == res_ref:
            result = 'passed'
            task_score += task_test_score
        else:
            result = 'failed'
        print(f'Test {_}' + '.' * 10 + result)
    
    task_score = int(task_score) if abs(task_score - int(task_score)) < 1e3 else task_score
    print('=' * 3 + f' Task Score: {task_score}/{task_total_score}\n')
    total_score += task_score

print('=' * 5 + f' Total Score: {total_score}/100')

# make clean
rc = subprocess.call(f'make clean -sC {current_lab}', shell = True)
if rc != 0:
    sys.stderr.write(f'make clean failed with status {rc}\n')
    sys.exit(rc)
