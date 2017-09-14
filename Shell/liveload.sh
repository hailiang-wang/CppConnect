#! /bin/bash 
###########################################
#
###########################################

# constants
baseDir=$(cd `dirname "$0"`;pwd)
# functions

# main 
[ -z "${BASH_SOURCE[0]}" -o "${BASH_SOURCE[0]}" = "$0" ] || return
cd $baseDir
inotifywait -mrq -e modify --exclude "\.(swp|swo)$" $baseDir/../Src | while read file; do
# log deleted file
    echo ">>" `date` "$file is modified"
    $baseDir/build.sh
    if [ 0 -eq $? ]; then
        $baseDir/exec.sh
    fi
done
