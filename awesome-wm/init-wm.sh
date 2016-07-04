#!/bin/bash

synclient TapButton2=2
synclient TapButton3=3
synclient TapButton1=1

setxkbmap de

#killall qasmixer
#killall pnmixer
#killall volumeicon
#killall cryptkeeper
killall nm-applet
killall xcompmgr

dbus-launch nm-applet &
#qasmixer -t &
#pnmixer &
#volumeicon &
#cryptkeeper &
#nm-applet &
xcompmgr -c &
xrdb -merge /home/bazi/.Xresources
