#!/bin/bash

if [ $# -ne 1 ]; then
	printf "Invalid commit message !!!\n"
	printf "USAGE: sync <Commit Message>\n"
	exit 1
fi

#Check for modified/changed files
STAT=`git status -s | wc -l`

if [ $STAT == 0 ]; then
	echo "NOTHING TO COMMIT/NO RECENT CHANGES : up-to-date with Cloud !!! ('origin/master')"
	exit 1
fi

printf "Syncing project to GitHub...\n"

#Add new/modified files to index/statge
ADD="git add -A"
echo $ADD
$ADD

#Commit all changes
COMMIT=`git commit -a -m "$1"`
#echo $COMMIT
#$COMMIT

if [ $? -ne 0 ]; then
	echo "Failed to commit the changes !!!"
	exit 1
fi

#Push to cloud
PUSH="git push -u origin master"
echo $PUSH
$PUSH

if [ $? -ne 0 ]; then
	echo "Failed to push the changes to cloud !!!"
	exit 1
fi

echo "Done."
exit 0

#### EOF ####

