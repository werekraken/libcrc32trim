#!/bin/bash

vagrant up
vagrant ssh -c 'cd /vagrant && ./test.sh'
[[ "$RUNNER_VAGRANT_DESTROY" == "false" ]] ||
  vagrant destroy -f
