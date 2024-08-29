#!/bin/sh

picom &
~/dotfiles/.scripts/cycle_wallpapers.sh &
dunst &
xrandr --output eDP-1 --primary --mode 1366x768 --pos 277x1080 --rotate normal --output HDMI-1 --mode 1920x1080 --pos 0x0 --rotate normal &
xmodmap ~/.Xmodmap &
redshift -l -3:-38 & 
xinput --set-prop 11 'Coordinate Transformation Matrix' 0.5 0 0 0 0.5 0 0 0 1 &
xbindkeys &
dwmblocks & 

exec dwm
