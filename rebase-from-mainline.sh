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

    FIRSTXENOMAI="$(git log --author="rpm@xenomai.org" --since="2024-01-01" --reverse --format='%H' | head -n 1)"
    OLDLINUXTIP="$(git merge-base "$CUR_BRANCH" "linux-mainline-master")"
    XENOMAILINUXTIP="$(git rev-parse "$FIRSTXENOMAI^")"
    NEWLINUXTIP="$(git rev-parse linux-mainline-master)"

    if [ "$OLDLINUXTIP" != "$XENOMAILINUXTIP" ]; then
        echo Something is wrong with the repository history - cannot find convergence
        exit 1
    fi

    if ! git merge-base --is-ancestor "$OLDLINUXTIP" linux-mainline-master; then
        echo Attempted to rebase unrelated histories
        exit 1
    fi

    git rebase -i -s ort --autosquash --onto "$NEWLINUXTIP" "$OLDLINUXTIP"
fi
