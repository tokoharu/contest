import sys
import os


def read_library():

    output_format = """
    "{nameA}" :{{
        "prefix": "{nameB}",
        "body":[ 
{body}
        ]

    }},
    """

    result = []
    for curDir, dirs, files in os.walk("./library", topdown=False):
        for filename in files:

            if not filename.split(".")[1] == "cpp":
                continue
            with open(curDir + os.sep + filename, "r", encoding="utf-8") as stream:
                data = stream.readlines()
            # print(filename)
            name1, name2 = filename.split(".")[0].split("_")

            code = ""
            for line in data:
                tmp = line[:-1]
                tmp = tmp.replace("\"", "\\\"")
                code += "\t\t\t\"{}\",\n".format(tmp)
            
            result.append(output_format.format(
                nameA=name1,
                nameB=name2,
                body=code))
    return result


def main():   
    lib = read_library()

    with open("cpp.json", "r", encoding="utf-8") as stream:
        data = stream.readlines()
    for i, line in enumerate(data):
        if line.find("}") >= 0:
            insert_pos = i
    
    print("".join(data[:insert_pos]))
    for code in lib:
        print(code)
    print("".join(data[insert_pos:]))


if __name__ == "__main__":
    main()
