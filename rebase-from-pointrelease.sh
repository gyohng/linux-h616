#!/bin/bash

set -e

KERNEL_VERSION=6.12.y

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
    if ! (git remote | grep -q linux-mainline-kernelorg); then
        git remote add -t linux-$KERNEL_VERSION linux-mainline-kernelorg https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
    fi

    git fetch linux-mainline-kernelorg linux-$KERNEL_VERSION:linux-mainline-$KERNEL_VERSION

    git pull
    git pull --all

    CUR_BRANCH=`git rev-parse --abbrev-ref HEAD`

    git checkout linux-mainline-$KERNEL_VERSION
    git pull --no-commit linux-mainline-kernelorg linux-$KERNEL_VERSION:linux-mainline-$KERNEL_VERSION
    git push --set-upstream origin linux-mainline-$KERNEL_VERSION

    git checkout "$CUR_BRANCH"

    FIRSTXENOMAI="$(git log --author="rpm@xenomai.org" --since="2024-01-01" --reverse --format='%H' | head -n 1)"
    OLDLINUXTIP="$(git merge-base "$CUR_BRANCH" "linux-mainline-$KERNEL_VERSION")"
    XENOMAILINUXTIP="$(git rev-parse "$FIRSTXENOMAI^")"
    NEWLINUXTIP="$(git rev-parse linux-mainline-$KERNEL_VERSION)"

    if [ "$OLDLINUXTIP" != "$XENOMAILINUXTIP" ]; then
        echo Something is wrong with the repository history - cannot find convergence
        exit 1
    fi

    if ! git merge-base --is-ancestor "$OLDLINUXTIP" linux-mainline-$KERNEL_VERSION; then
        echo Attempted to rebase unrelated histories
        exit 1
    fi

    git rebase -i -s ort --autosquash --onto "$NEWLINUXTIP" "$OLDLINUXTIP"
fi
