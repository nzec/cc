#!/bin/bash

./a.out > image.ppm 2> cerr
xdg-open image.ppm
