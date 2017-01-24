#!/bin/bash

sudo apt-get install nodejs-dev

sudo npm install -g node-gyp
sudo npm install -g nw-gyp
sudo npm install -g bindings

node-gyp configure --target=0.12.5
node-gyp build