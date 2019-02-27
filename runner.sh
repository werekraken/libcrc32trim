#!/bin/bash

command='cd /vagrant && ./build.sh && ./test.sh'

if [[ $1 == "buildrpm" ]]; then
  command='cd /vagrant && ./buildrpm.sh'
fi

vagrant up
vagrant ssh -c "$command"
[[ "$RUNNER_VAGRANT_DESTROY" == "false" ]] ||
  vagrant destroy -f
