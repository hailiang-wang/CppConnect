#! /bin/bash 
###########################################
#
###########################################

# constants
baseDir=$(cd `dirname "$0"`;pwd)
rDir=$baseDir
binary=build64_release/projects/connect/Src/Connect

# functions
function recursive(){
    if [ -f "BLADE_ROOT" ]; then
        $binary
    elif [ $rDir!="/" ]; then
        cd ..
        recursive
    else
        echo $rDir
        echo "Not found BLADE_ROOT"
    fi
}

# main 
[ -z "${BASH_SOURCE[0]}" -o "${BASH_SOURCE[0]}" = "$0" ] || return
cd $baseDir/..
recursive
