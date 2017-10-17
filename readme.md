## Introduction

- Midterm Project for ENPM808x


[![Build Status](https://travis-ci.org/PranavDhulipala/DstarLite.svg?branch=master)](https://travis-ci.org/PranavDhulipala/DstarLite)
[![Coverage Status](https://coveralls.io/repos/github/PranavDhulipala/DstarLite/badge.svg?branch=master)](https://coveralls.io/github/PranavDhulipala/DstarLite?branch=master)
---

## Overview

This is a simple path planner implemetation in C++ .


The project's objective is to implement a simple path planner namely D* lite which has been very much popular with mobile robot and autonomous vehicle navigation. The problem includes a robot with a known goal position in an unknown terrain and the robot must navigate to the goal avoiding the obstacles. The robot initially assumes that the map is free from obstacles and plans the shortest path from goal to the start position, whenever it comes across a new obstacle which it had no idea about before it adds the information to the map and re-plans a new path from the current position to goal or determine if it is not possible to reach the goal. 

Algorithm:
- D* Lite

## Product Backlog,Iteration Backlogs and Worklog

Link to the spreadsheet https://docs.google.com/spreadsheets/d/17pHmtAirQ_ssRiRcsVRYO3rvNcxaiY6u7N-sm8TDlV0/edit#gid=0

## License

This software is released under the MIT license.

## Generating doxygen documentation


- In your git home directory

```bash
doxygen DstarLite
```

- Doxygen files will be generated to /docs folder



