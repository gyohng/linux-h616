#!/bin/bash

set -e

if [[ ! -z $(git status -s) ]]; then
    echo Uncommitted changes are present. Please commit first
    exit 1
fi

if [ "$1" == "push" ]; then
    # reintegrate
    git push --force-with-lease
    git pull --no-commit
    git pull --all --no-commit
    git push
else
    if ! (git remote | grep -q linux-mainline-github); then
        git remote add -t master linux-mainline-github https://github.com/torvalds/linux.git
    fi

    git fetch linux-mainline-github master:linux-mainline-master

    git pull
    git pull --all

    CUR_BRANCH=`git rev-parse --abbrev-ref HEAD`

    git checkout linux-mainline-master
    git pull --no-commit linux-mainline-github master:linux-mainline-master
    git push --set-upstream origin linux-mainline-master

    git checkout "$CUR_BRANCH"
    git rebase -i -s ort --autosquash linux-mainline-github/master
fi
