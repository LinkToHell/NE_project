#!/bin/sh
(./filter_players | ./players_to_PPH | ./to_PPH | ./solve_PPH.py) < graphs.txt > orders.txt
(./graph_gen | ./players_gen_filtered | ./to_PH | ./process_cnf.py) < graphs.txt
