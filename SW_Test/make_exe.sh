#!/bin/bash

cd /home/xinda/1320
/home/xinda/venv/bin/pyinstaller --clean --name CNC-1320 --exclude 'PySide2' --exclude 'PyQt5' --collect-submodules libfcitx5platforminputcontextplugin.so -F -p /home/xinda/venv/lib/python3.11/site-packages/ MainSpring.py


