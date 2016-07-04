#!/bin/bash

SS_DEST=/home/str/daten/SCREENSHOT

FILENAME=sshot-$(date +%Y-%m-%d__%H_%M_%S).png

echo $SS_DEST
echo $FILENAME

import $SS_DEST/$FILENAME
