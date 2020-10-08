# Finn Raae
# cop4620
# lexical analizer: basically reads txt and see what each word or number is for programming
# imports
import sys


def main():
    # variables
    key = ""
    # open files
    file = open(sys.argv[1], 'r')
    #file = open("test_fn.txt", 'r')
    lines = file.readlines()
    file.close()
    # loop through lines
    for line in lines:
        x = line.strip()
        if x:
            print("input:", x)
        while line:
            # print("input2:", line)
            for letter in line:
                key = checker(key, letter)
                # line minus first char
                line = line[1::]


def checker(key, letter):
    # empty string
    if not key:
        key = letter
        return key
    # comment stuff
    elif key.startswith("/"):
        if key.startswith("/*"):
            if key.endswith("*/"):
                return letter
            else:
                key += letter
                return key
        elif letter == "/":
            return "//"
        elif key.startswith("//"):
            if key.endswith("\n"):
                return letter
            else:
                key += letter
                return key
        elif "\n" in letter or " " in letter:
            print("/")
            return ""
        elif letter == "*":
            key += letter
            return key
        else:
            print("/")
            return letter
    # words
    elif key[0].isalpha():
        if letter not in (";", "(", ")", ",", " ", "{", "}", "[", "]", "/", "-", "*", "+", "\n"):
            key += letter
            return key
        elif "if" in key or "else" in key or "while" in key or "int" in key or "return" in key or "void" in key:
            if " " in letter or "(" in letter or "/" in letter:
                print("keyword:", key)
                return letter
            elif letter.isalpha():
                key += letter
                print("error:", key)
                return ""
            else:
                print(letter)
                return letter
        elif letter in (";", "(", ")", ",", " ", "{", "}", "[", "]", "/", "-", "*", "+", "\n"):
            if key.isalpha():
                print("ID:", key)
                if letter == " ":
                    return ""
                else:
                    return letter
            else:
                for i, c in enumerate('letter'):
                    if not key[i].isalpha():
                        print("ID:", key[:i])
                        print("ERROR:", key[i:])
                        if letter == " ":
                            return ""
                        else:
                            return letter
    # numbers
    elif key[0].isdigit():
        if letter not in (";", "(", ")", ",", " ", "{", "}", "[", "]", "/", "-", "*", "+", "\n"):
            key += letter
            return key
        elif letter in (";", "(", ")", ",", " ", "{", "}", "[", "]", "/", "-", "*", "+", "\n"):
            if key.isdigit():
                print("INT:", key)
                if letter == " ":
                    return ""
                else:
                    return letter
            else:
                for i, c in enumerate('letter'):
                    if not key[i].isdigit():
                        print("NUM:", key[:i])
                        print("ERROR:", key[i:])
                        if letter == " ":
                            return ""
                        else:
                            return letter
    # special
    elif key in (";", "(", ")", ",", "{", "}", "[", "]", "/", "-", "*", "+"):
        print(key)
        return letter
    elif "=" in key:
        if "\n" in letter or " " in letter:
            print("=")
            return ""
        elif letter == "=":
            print("==")
            return ""
    elif "!" in key:
        if "\n" in letter or " " in letter:
            print("Error: !")
            return ""
        elif letter == "=":
            print("!=")
            return ""
    elif "<" in key:
        if "\n" in letter or " " in letter:
            print("<")
            return ""
        elif letter == "=":
            print("<=")
            return ""
    elif ">" in key:
        if "\n" in letter or " " in letter:
            print(">")
            return ""
        elif letter == "=":
            print(">=")
            return ""
    elif key in ("\n", "", " ", "\r"):
        return letter
    else:
        print("error:", key)
        return letter


# start main
main()
