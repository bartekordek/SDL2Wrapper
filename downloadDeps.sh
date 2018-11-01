#!/bin/bash

function getNewest()
{
    local repoLocalPath=$1
    local repoRemotePath=$2
    echo "repoLocalPath = $repoLocalPath"
    echo "repoRemotePath = $repoRemotePath"
    if [ ! -d "$repoLocalPath" ]; then
        git clone "$repoRemotePath"
    fi 
        
    cd "$repoLocalPath";
    git fetch
    git reset --hard origin/master
    cd -;
}

cd deps;
getNewest "CUL" "https://github.com/bartekordek/CUL.git"
cd -;