#!/bin/bash


bash -c 'python -m profile -o profile.out MainSpring.py'
bash -c 'python profile_dump.py'
