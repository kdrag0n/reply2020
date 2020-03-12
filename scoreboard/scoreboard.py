#!/usr/bin/env python3
# sourcery off

import sys
import collections

# log = open(sys.argv[1]).read().split("\n")
# lines = [[int(v) for v in s.split()] for s in log]
# teams, logs = lines[1]
# cases = lines[2:]

Sub = collections.namedtuple("Sub", ("time", "team", "problem", "input", "score"))
SubId = collections.namedtuple("SubId", ("team", "problem", "input"))
Team = collections.namedtuple("Team", ("id", "score"))
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

dbg = False
for ci, case in enumerate(cases):
    case_n = ci + 1

    seen_sub = set()
    teams = []
    for tid in range(1, case.n_teams + 1):
        if dbg: print("team", tid)
        score = 0
        for sub in case.subs:
            if sub.team != tid:
                continue

            score += sub.input * 1_000_000 if sub.score else 0  # max time 10,000
            if dbg: print(" - score", score)
            key = SubId(sub.team, sub.problem, sub.input)
            if key not in seen_sub and sub.score:
                score -= sub.time
                if dbg: print(" - penalty", sub.time)
                if dbg: print(" - score", score)
                seen_sub.add(key)

        teams.append(Team(tid, score))

    t_ranked = sorted(teams, key=lambda t: t.score, reverse=True)
    print(f"Case #{case_n}:", " ".join(str(t.id) for t in t_ranked))  # team id
