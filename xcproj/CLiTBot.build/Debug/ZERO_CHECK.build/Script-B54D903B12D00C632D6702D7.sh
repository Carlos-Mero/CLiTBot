#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/huangyanxing/Desktop/程设/CLiTBot/xcproj
  make -f /Users/huangyanxing/Desktop/程设/CLiTBot/xcproj/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/huangyanxing/Desktop/程设/CLiTBot/xcproj
  make -f /Users/huangyanxing/Desktop/程设/CLiTBot/xcproj/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/huangyanxing/Desktop/程设/CLiTBot/xcproj
  make -f /Users/huangyanxing/Desktop/程设/CLiTBot/xcproj/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/huangyanxing/Desktop/程设/CLiTBot/xcproj
  make -f /Users/huangyanxing/Desktop/程设/CLiTBot/xcproj/CMakeScripts/ReRunCMake.make
fi

