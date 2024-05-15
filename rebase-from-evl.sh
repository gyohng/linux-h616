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
    if ! (git remote | grep -q xenomai); then
        git remote add -t v6.10-evl-rebase xenomai https://gitea.sys.mt/gyohng/linux-evl.git
    fi

    git fetch xenomai v6.10-evl-rebase:v6.10-evl-rebase

    git pull
    git pull --all

    CUR_BRANCH=`git rev-parse --abbrev-ref HEAD`

    git checkout v6.10-evl-rebase
    git pull --no-commit xenomai v6.10-evl-rebase:v6.10-evl-rebase
    git push --set-upstream origin v6.10-evl-rebase

    git checkout "$CUR_BRANCH"
    git rebase -i -s ort --autosquash xenomai/v6.10-evl-rebase
fi
