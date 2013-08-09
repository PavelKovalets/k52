#!/usr/bin/env bash

#Enable only necessary repos - will fix some Ubuntu issues
echo "Modifying Ubuntu repos"
cp /etc/apt/sources.list /etc/apt/sources.list.backup
rm /etc/apt/sources.list
echo "deb http://by.archive.ubuntu.com/ubuntu/ precise main universe" > /etc/apt/sources.list
echo "End modifying Ubuntu repos"

#Install necessary packages
apt-get update -y
apt-get install -y openmpi-bin
apt-get install -y libboost-all-dev
apt-get install -y build-essential
apt-get install -y cmake
