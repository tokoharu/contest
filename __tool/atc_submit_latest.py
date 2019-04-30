#!/usr/bin/python3
import argparse
import glob
import os
import re
import sys
from os.path import expanduser


def latest_path(wd):
    latest_code = None
    latest = -1
    pid = None
    for d in glob.glob(os.path.join(wd, "*")):
        code = os.path.join(d, "main.cpp")
        last = os.stat(code).st_mtime
        if latest < last:
            latest = last
            latest_code = code
            pid = os.path.basename(d)
    return latest_code


def main(prog, args):
    parser = argparse.ArgumentParser(
        prog=prog,
        formatter_class=argparse.RawTextHelpFormatter)

    parser.add_argument("contest", help="contest name")
    print("hoge")
    args = parser.parse_args(args)

    wd = os.path.join(expanduser("~/../.."), "workspace",
                      "contest", args.contest)
    latest_code = latest_path(wd)
    with open(latest_code, 'r', encoding="utf-8") as f:
        code = f.read()

    os.chdir(os.path.dirname(latest_code))
    # print(latest_code)

    case_pattern_match = re.search(
        ".*test[\s]*case[\s]*([0-9]+).*", code, re.MULTILINE)
    if case_pattern_match:
        case = case_pattern_match.group(1)
        os.system(
            "g++ main.cpp -std=c++14 && atcoder-tools test --num {}"
            .format(case)
        )
    else:
        print(os.getcwd())
        tool_path = os.path.join(
            expanduser("~/../..").replace("/", os.sep),
            "workspace",
            "contest", "atcoder-tools", "atcodertools", "atcoder_tools.py")
        os.system(
            "g++ main.cpp -std=c++14 && python {} submit".format(tool_path))


if __name__ == "__main__":
    main(sys.argv[0], sys.argv[1:])
"""
 shell

observe(){
    cwatch atc_submit_latest.py $@
}

obs(){
    observe $@
}
"""
"""
cwatch() {
while [ 1 ]
do
  output=$(eval $@ 2>&1)
  clear
  date
  echo -e "$output"
  sleep 0.1
done
}


"""
