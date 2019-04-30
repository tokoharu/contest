#!/bin/bash
export PATH=$PATH:/c/MinGW/bin
alias python3='python'

TOOL=/c/workspace/contest/atcoder-tools/atcodertools/atcoder_tools.py
function atcoder-gen (){
	CONTEST=$@
	TASK=${CONTEST//-/_}
	URL=https://atcoder.jp/contests/${CONTEST}/tasks/${TASK}
	/c/Program\ Files\ \(x86\)/Google/Chrome/Application/chrome.exe ${URL}_a ${URL}_b ${URL}_c ${URL}_d
	python $TOOL gen $@ --workspace /c/workspace/contest/ --template /c/workspace/contest/__tool/atcoder_template.cpp.tmp ;  }
function atcoder-test (){ python $TOOL test ;  }
function atcoder-submit () { python $TOOL submit $@ ; }

