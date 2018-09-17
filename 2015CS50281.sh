#!/bin/bash
if [ "$1" = "-kmeans" ]; then
	./kmeans $2 $3
elif [ "$1" = "-dbscan" ]; then
	./dbscan $2 $3 $4
elif [ "$1" = "-optics" ]; then
	./optics $2 $3 $4
fi
