#!/usr/bin/env python3
# sourcery off

import sys
import collections
import functools

# log = open(sys.argv[1]).read().split("\n")
# lines = [[int(v) for v in s.split()] for s in log]
# teams, logs = lines[1]
# cases = lines[2:]

Sub = collections.namedtuple("Sub", ("time", "team", "problem", "input", "score"))
SubId = collections.namedtuple("SubId", ("team", "problem", "input"))
Team = collections.namedtuple("Team", ("id", "score", "penalty"))
Case = collections.namedtuple("Case", ("n_teams", "subs"))

line_vals = [[int(v) for v in line.split()] for line in open(sys.argv[1], "r")]
line_vals = [l for l in line_vals if l]  # rm empty
n_cases = line_vals.pop(0)[0]
cases = []
for ci in range(n_cases):
    vals = line_vals.pop(0)
    n_teams, n_logs = vals
    subs = []
    for li in range(n_logs):
        log = line_vals.pop(0)
        subs.append(Sub(*log))
    cases.append(Case(n_teams, subs))


def cmp_team(a, b):
    # a <  b  -1
    # a == b   0
    # a >  b   1
    if a.score < b.score:
        return -1
    elif a.score > b.score:
        return 1

    # penalty
    if a.penalty > b.penalty:
        return -1
    elif b.penalty > a.penalty:
        return 1

    # num order
    if a.id > b.id:
        return -1
    else:
        return 1


dbg = False
for ci, case in enumerate(cases):
    case_n = ci + 1

    seen_subs = set()
    teams = []
    for tid in range(1, case.n_teams + 1):
        if dbg: print("team", tid)
        score = 0
        penalty = 0
        for sub in case.subs:
            if sub.team != tid:
                continue

            if dbg: print(" - score", score)
            key = SubId(sub.team, sub.problem, sub.input)
            if key not in seen_subs and sub.score:
                score += sub.input * 100
                seen_subs.add(key)
                penalty += sub.time
                if dbg: print(" - penalty", sub.time)

        teams.append(Team(tid, score, penalty))

    if dbg: print(f"{case_n} scores:", " ".join(f"{t.id}={t.score}" for t in teams))
    t_ranked = sorted(teams, key=functools.cmp_to_key(cmp_team), reverse=True)
    print(f"Case #{case_n}:", " ".join(str(t.id) for t in t_ranked))  # team id
