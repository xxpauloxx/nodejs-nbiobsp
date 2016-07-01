#!/bin/bash

node-gyp configure --target=0.12.5
node-gyp build

cp build/Release/nbiobsp.node ./example-webkit
