sudo pacman -Syy base-devel 

sudo pacman -S libx11 libxext libxft feh alacritty firefox nemo

sudo pacman -S libxinerama libxrandr libxrender

sudo pacman -S xcb-util

sudo pacman -S xcb-util-wm

sudo pacman -S xcb-util-keysyms

sudo pacman -S libxcomposite

sudo pacman -S libxrender

sudo pacman -S libxcb-util-cursor

sudo pacman -S libxss

sudo pacman -S libx11-xcb

sudo pacman -S libxcb

sudo pacman -S libxft

gcc -o mywm mywm.c -lX11 -lXext -lXft
