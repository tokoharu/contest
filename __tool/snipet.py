import sys
import os


def main():

    output_format = """
    "{nameA}" :{{
        "prefix": "{nameB}",
        "body":[ 
{body}
        ]

    }},
    """

    for curDir, dirs, files in os.walk("./library", topdown=False):
        for filename in files:

            if not filename.split(".")[1] == "cpp":
                continue
            with open(curDir + os.sep + filename, "r", encoding="utf-8") as stream:
                data = stream.readlines()
            name1, name2 = filename.split(".")[0].split("_")

            code = ""
            for line in data:
                tmp = line[:-1]
                tmp = tmp.replace("\"", "\\\"")
                code += "\t\t\t\"{}\",\n".format(tmp)
            print(output_format.format(
                nameA=name1,
                nameB=name2,
                body=code))


if __name__ == "__main__":
    main()
