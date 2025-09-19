#!/bin/sh

# tmux has-session -t fastterm 2>/dev/null || tmux new-session -d -s fastterm
tmux has-session -t fastterm 2>/dev/null || tmux new-session -c ~ -d -s fastterm
picom --config ~/dotfiles/.config/picom/picom.conf &
~/dotfiles/.scripts/cycle_wallpapers.sh &
dunst &
#xrandr --output eDP-1 --primary --mode 1366x768 --pos 277x1080 --rotate normal --output HDMI-1 --mode 1920x1080 --pos 0x0 --rotate normal &
xmodmap ~/.Xmodmap &
#redshift -l -3:-38 & 
redshift -m vidmode -l -3.7319:-38.5267
#xbindkeys &
#dwmblocks & 
# ibus-daemon -rxRd &
xset s off
xset s noblank
xset -dpms

# Lock after 5 minutes (600 seconds) of inactivity
# xautolock -time 5 -locker "dm-tool lock" &



# exec dwm
