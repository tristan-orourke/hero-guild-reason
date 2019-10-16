#!/bin/sh
if [ -z "$(git status --porcelain)" ]
then 
    # Working directory clean
    sed -i '/build/d' ./.gitignore
    git add .
    git commit -m "Edit .gitignore to publish"
    git push origin `git subtree split --prefix gh-pages master`:gh-pages --force
    git reset HEAD~
    git checkout .gitignore
else 
    # Uncommitted changes
    echo "Need clean working directory to publish"
fi