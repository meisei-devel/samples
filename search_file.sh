#!/bin/sh

if [ "$2" = "" ]; then
 echo "Usage: $0 directory keyword"
 exit 0
fi

find $1 -type f | while read FILE
do
# if [ ! `echo ${FILE} | grep $2` ] ; then
 if [ `echo ${FILE} | grep $2` ] ; then
  echo ${FILE}
 fi
done
