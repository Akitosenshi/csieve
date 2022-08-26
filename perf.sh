#!/bin/bash

make && perf record ./csieve > /dev/null
