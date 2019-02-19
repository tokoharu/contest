export PATH=$PATH:/c/MinGW/bin
alias python3='python'

function atcoder-gen (){ python /c/workspace/contest/atcoder-tools/atcoder-tools gen $@ --workspace /c/workspace/contest/ --template /c/workspace/contest/__tool/atcoder_template.cpp.tmp ;  }
function atcoder-test (){ python /c/workspace/contest/atcoder-tools/atcoder-tools test ;  }
function atcoder-submit () { python /c/workspace/contest/atcoder-tools/atcoder-tools submit $@ ; }

