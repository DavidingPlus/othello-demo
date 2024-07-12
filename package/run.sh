dirPath=$(cd "$(dirname "$0")"; pwd) 

echo $dirPath

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$dirPath

${dirPath}/OthelloDemo

