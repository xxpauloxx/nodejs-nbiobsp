#!/bin/bash

nw-gyp configure --target=0.12.2
nw-gyp build

cp build/Release/nbiobsp.node ./example-webkit
