#!/usr/bin/env python

import sys
from pysat.solvers import Solver

def read_graph():
    graph = []
    try:
        size = int(sys.stdin.readline())
    except:
        sys.exit(0)
    for i in range(size):
        m = map(int, sys.stdin.readline().strip().split())
        num = next(m)
        graph.append(list(m))
    return graph

def read_vector():
    size = int(sys.stdin.readline())
    return list(map(int, sys.stdin.readline().strip().split()))


def write_vector(v):
    print(len(v), ' '.join(map(str, v)), flush=True)


def read_cnf():
    cnf = []
    size = int(sys.stdin.readline())
    for i in range(size):
        cnf.append(list(map(int, sys.stdin.readline().strip().split())))
    return cnf

while True:
    graph = read_graph()
    players = read_vector()
    cnf = read_cnf()
    
    solver = Solver('m22', cnf)
    has_sol = solver.solve()
    solver.delete()
    
    if has_sol:
        write_vector(players)
