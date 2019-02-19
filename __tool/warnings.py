import os
import sys


"""usage
python warnings.py warnings.txt
"""


def main():
    filename = sys.argv[1]
    data = []
    with open(filename, "r", encoding="utf-8") as fp:
        data = fp.readlines()
    for line in data:
        print("\t\t\t\t\"{}\",".format(line.split("\t")[0]))

if __name__ == "__main__":
    main()