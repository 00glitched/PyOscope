#!/bin/bash
mypath= pwd

virtualenv -p python3 .pyoscvenv

source .pyoscvenv/bin/activate 

pip install -r deplist.md
