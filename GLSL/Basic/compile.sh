#!/bin/bash
LABNUMBER=6
LAB=lab${LABNUMBER}-trackball
clear
[ -f $LAB ] && rm $LAB
rm -rf $LAB.dSYM
g++ -g -o $LAB -I/home/fac/wrc/SOIL/include $LAB.cpp TrackBall.cpp TrackBall.h ShaderSetup.cpp ShaderSetup.h -L/home/fac/wrc/SOIL/lib -lSOIL -framework GLUT -framework OpenGL -framework CoreFoundation 
chmod +x $LAB
./$LAB
