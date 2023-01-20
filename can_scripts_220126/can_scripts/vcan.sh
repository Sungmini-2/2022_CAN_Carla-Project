#!/bin/bash
sudo modprobe can
sudo ip link add dev can0 type can
sudo ip link set up can0
echo Virual CAN Bus has been opened!
