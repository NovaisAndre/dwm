#!/bin/sh

# tmux has-session -t fastterm 2>/dev/null || tmux new-session -d -s fastterm
tmux has-session -t fastterm 2>/dev/null || tmux new-session -c ~ -d -s fastterm
picom --config ~/dotfiles/.config/picom/picom.conf &
~/dotfiles/.scripts/cycle_wallpapers.sh &
dunst &
#xrandr --output eDP-1 --primary --mode 1366x768 --pos 277x1080 --rotate normal --output HDMI-1 --mode 1920x1080 --pos 0x0 --rotate normal &
if [ "$USER" = "husky" ]; then
  xmodmap ~/dotfiles/.XmodmapUs
fi
#sxhkd &

#redshift -l -3:-38 & 
redshift &
#xbindkeys &
#dwmblocks & 
# ibus-daemon -rxRd &
<<<<<<< Updated upstream
ibus-daemon -drx
=======
# start with the regular keyboard active, not the last-used IME engine
( sleep 2 && ibus engine xkb:br::por ) &
# ibus resets the X keyboard map when switching back to the br engine,
# which breaks the CapsLock-as-mod custom .Xmodmap; keep it applied
( while :; do
    xmodmap -pke 2>/dev/null | grep -q 'keycode  66 = Caps_Lock' && xmodmap ~/.Xmodmap
    sleep 1
  done ) &
>>>>>>> Stashed changes
xset s off
xset s noblank
xset -dpms

xset s 600 600 &
xss-lock --transfer-sleep-lock -- i3lock -i ~/dotfiles/.wallpapers/archive/lock.png --nofork --bg-max &

# Lock after 5 minutes (600 seconds) of inactivity
# xautolock -time 5 -locker "dm-tool lock" &



# exec dwm
