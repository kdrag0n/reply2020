package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"sort"
	"strconv"
	"strings"
)

func check(err error) {
	if err != nil {
		panic(err)
	}
}

type SubId struct {
	team int
	problem int
	input int
}

type Sub struct {
	time int
	team int
	problem int
	input int
	score int

	id SubId
}

type Team struct {
	id int
	score int
	penalty int
}

type Case struct {
	nTeams int
	subs []Sub
}

func cmpTeam(a, b Team) bool {
	if a.score < b.score { return true}
	if a.score > b.score { return false }

	// penalty
	if a.penalty > b.penalty { return true }
	if b.penalty > a.penalty { return false }

	// num
	if a.id > b.id {
		return true
	} else {
		return false
	}
}

func main() {
	data, err := ioutil.ReadFile(os.Args[1])
	check(err)

	sData := string(data)
	lines := strings.Split(sData, "\n")
	lineVals := make([][]int, 0, len(lines))
	for _, line := range lines {
		if len(line) == 0 {
			continue
		}

		vals := make([]int, 0, 5)
		sVals := strings.Split(line, " ")
		for _, val := range sVals {
			iVal, err := strconv.Atoi(val)
			check(err)
			vals = append(vals, iVal)
		}
		lineVals = append(lineVals, vals)
	}

	nCases := lineVals[0][0]
	cases := make([]Case, 0, nCases)
	pos := 1
	for ci := 0; ci < nCases; ci++ {
		vals := lineVals[pos]
		pos += 1
		nTeams := vals[0]
		nLogs := vals[1]
		subs := make([]Sub, 0, nLogs)
		for li := 0; li < nLogs; li++ {
			log := lineVals[pos]
			pos += 1
			sub := Sub{
				log[0], log[1], log[2], log[3], log[4],
				SubId{log[1], log[2], log[3]},
			}
			subs = append(subs, sub)
		}
		cases = append(cases, Case{nTeams, subs})
	}

	for ci, cse := range cases {
		caseN := ci + 1

		seenSubs := make(map[SubId]bool, len(cse.subs))
		teams := make([]Team, 0, cse.nTeams)
		for tid := 1; tid <= cse.nTeams; tid++ {
			score := 0
			penalty := 0
			for _, sub := range cse.subs {
				if sub.team != tid {
					continue
				}

				if _, ok := seenSubs[sub.id]; !ok && sub.score == 1 {
					score += sub.input * 100
					seenSubs[sub.id] = true
					penalty += sub.time
				}
			}

			teams = append(teams, Team{tid, score, penalty})
		}

		sort.SliceStable(teams, func(i, j int) bool {
			return !cmpTeam(teams[i], teams[j])
		})

		tidStrings := make([]string, 0, cse.nTeams)
		for _, team := range teams {
			tidStrings = append(tidStrings, strconv.Itoa(team.id))
		}

		fmt.Printf("Case #%d: %s\n", caseN, strings.Join(tidStrings, " "))
	}
}
