#!/bin/bash

shell="$(getent passwd | grep $USER)"
shell=${shell##*:}

$shell -c 'make && time ./csieve'
