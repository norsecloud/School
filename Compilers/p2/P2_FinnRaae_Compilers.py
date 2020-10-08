# Finn Raae
# cop4620
# lexical analizer: basically reads txt and see what each word or number is for programming
# imports
import sys
import re


class Tokens:
    # constructor
    def __init__(self, toke, value=None):
        self.toke = toke
        self.value = value

    # output
    def __repr__(self):
        if self.value: return f'{self.toke}:{self.value}'
        return f'{self.type}'


def main():
    # variables
    key = ""  # variable to check strings to see what they are
    tokens = []  # append tokens into
    # open files
    # check this for next project
    try:
        # file = open(sys.argv[1], 'r')
        file = open("test_fn.txt", 'r')
    except IndexError:
        print("could not open file")
        sys.exit()
    lines = file.readlines()
    file.close()
    # loop through lines
    for line in lines:
        x = line.strip()
        while line:
            # print("input2:", line)
            for letter in line:
                key = lexical(key, letter, tokens)
                line = line[1::]
    key = lexical(key, " ", tokens)
    # end lexical analyzer
    # start parser
    parser = Parser(tokens)
    fin = parser.parse()
    if fin: print("ACCEPT")
    else: print("REJECT")


# lexical analyzer
def lexical(key, letter, tokens):
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
        # elif "\n" in letter or " " in letter:
        #     print("/")
        #     return ""
        elif letter == "*":
            key += letter
            return key
        else:
            # print("/")
            newtoke = Tokens("MULOP", key)
            tokens.append(newtoke)
            return letter
    # words
    elif key[0].isalpha():
        if letter not in (";", "(", ")", ",", " ", "{", "}", "[", "]", "/", "-", "*", "+", "\n", "=", "<", ">"):
            key += letter
            return key
        # elif "if" in key or "else" in key or "while" in key or "int" in key or "return" in key or "void" in key:
        elif re.match('\\bif\\b|\\belse\\b|\\bwhile\\b|\\bint\\b|\\breturn\\b|\\bvoid\\b', key):
            # print("keyword:", key)
            newtoke = Tokens("KEYWORD", key)
            tokens.append(newtoke)
            return letter

        elif letter in (";", "(", ")", ",", " ", "{", "}", "[", "]", "/", "-", "*", "+", "\n", "=", "<", ">"):
            if key.isalpha():
                # print("ID:", key)
                newtoke = Tokens("ID", key)
                tokens.append(newtoke)
                return letter
            else:
                for i, c in enumerate('letter'):
                    if not key[i].isalpha():
                        # print("ID:", key[:i])
                        # print("ERROR:", key[i:])
                        newtoke = Tokens("ERROR", key)
                        tokens.append(newtoke)
                        return letter
    # numbers
    elif key[0].isdigit():
        if letter not in (";", "(", ")", ",", " ", "{", "}", "[", "]", "/", "-", "*", "+", "\n", "=", "<", ">"):
            key += letter
            return key
        elif letter in (";", "(", ")", ",", " ", "{", "}", "[", "]", "/", "-", "*", "+", "\n", "=", "<", ">"):
            if key.isdigit():
                # print("INT:", key)
                newtoke = Tokens("INT", key)
                tokens.append(newtoke)
                return letter
            else:
                for i, c in enumerate('letter'):
                    if not key[i].isdigit():
                        # print("NUM:", key[:i])
                        # print("ERROR:", key[i:])
                        newtoke = Tokens("ERROR", key)
                        tokens.append(newtoke)
                        return letter
    # special
    elif key in (";", "(", ")", ",", "{", "}", "[", "]"):
        # print(key)
        newtoke = Tokens("EXTRA", key)
        tokens.append(newtoke)
        return letter
    elif key in "*":
        newtoke = Tokens("MULOP", key)
        tokens.append(newtoke)
        return letter
    elif key in ("+", "-"):
        newtoke = Tokens("ADDOP", key)
        tokens.append(newtoke)
        return letter
    elif "=" in key:
        if letter == "=":
            key += letter
            # print("==")
            newtoke = Tokens("RELOP", key)
            tokens.append(newtoke)
            return ""
        else:
            # print("=")
            newtoke = Tokens("OP", key)
            tokens.append(newtoke)
            return letter

    elif "!" in key:
        if letter == "=":
            key += letter
            # print("!=")
            newtoke = Tokens("RELOP", key)
            tokens.append(newtoke)
            return ""
        else:
            # print("error: !")
            newtoke = Tokens("ERROR", key)
            tokens.append(newtoke)
            return letter

    elif "<" in key:
        if letter == "=":
            # print("<=")
            key += letter
            newtoke = Tokens("RELOP", key)
            tokens.append(newtoke)
            return ""
        else:
            # print("<")
            newtoke = Tokens("RELOP", key)
            tokens.append(newtoke)
            return letter

    elif ">" in key:
        if letter == "=":
            # print(">=")
            key += letter
            newtoke = Tokens("RELOP", key)
            tokens.append(newtoke)
            return ""
        else:
            # print(">")
            newtoke = Tokens("RELOP", key)
            tokens.append(newtoke)
            return letter

    elif key in ("\n", "", " ", "\r"):
        return letter
    else:
        # print("error:", key)
        newtoke = Tokens("ERROR", key)
        tokens.append(newtoke)
        return letter


class Parser(object):
    def __init__(self, tokens):
        self.tokens = tokens
        self.index = -1
        self.next()

    # iterate through tokens
    def next(self):
        self.index += 1
        if self.index < len(self.tokens):
            self.current = self.tokens[self.index]
        return self.current

    def last(self):
        self.index -= 1
        if self.index < len(self.tokens):
            self.current = self.tokens[self.index]
        return self.current

    def parse(self):
        return self.program()

    # start the grammar functions
    def program(self):
        if self.declarationList():
            if self.index != len(self.tokens)-1:
                self.next()
                self.program()
            else:
                return True
        else: return False

    def declarationList(self):
        if self.current.value == "int":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.aFactor(): return True
            else: return False
        elif self.current.value == "void":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.aFactor(): return True
            else: return False
        else: return False

    def declarationList2(self):
        if self.current.value == "int":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.aFactor(): return True
            else: return False
        elif self.current.value == "void":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.aFactor(): return True
            else: return False
        else:
            self.last()
            return True

    def aFactor(self):
        if self.current.value == ";":
            self.next()
            if self.declarationList2(): return True
        elif self.current.value == "[":
            self.next()
            if self.current.toke == "INT":
                self.next()
                if self.current.value == "]":
                    self.next()
                    if self.current.value == ";":
                        self.next()
                        if self.declarationList2(): return True
                    else: return False
                else: return False
            else: return False
        elif self.current.value == "(":
            self.next()
            if self.params():
                self.next()
                if self.current.value == ")":
                    self.next()
                    if self.current.value == "{":
                        self.next()
                        if self.varDec():
                            self.next()
                            if self.statementList():
                                self.next()
                                if self.current.value == "}":
                                    self.next()
                                    if self.declarationList2(): return True
                                else: return False
                    else: return False
                else: return False
            else: return False
        else: return False

    def params(self):
        if self.current.value == "int":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.arr():
                    self.next()
                    if self.paramList2(): return True
            else: return False
        elif self.current.value == "void":
            self.next()
            if self.paramList(): return True
        else: return False

    def paramList(self):
        if self.current.toke == "ID":
            self.next()
            if self.arr():
                self.next()
                if self.paramList2(): return True
        else:
            self.last()
            return True

    def paramList2(self):
        if self.current.value == ",":
            self.next()
            if self.param(): return True
        else:
            self.last()
            return True

    def param(self):
        if self.current.value == "int":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.arr():
                    self.next()
                    if self.paramList2(): return True
            else: return False
        elif self.current.value == "void":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.arr():
                    self.next()
                    if self.paramList2(): return True
            else: return False
        else: return False

    def arr(self):
        if self.current.value == "[":
            self.next()
            if self.current.value == "]": return True
        else:
            self.last()
            return True

    def varDec(self):
        if self.current.value == "int":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.bFactor():
                    self.next()
                    if self.varDec(): return True
                else: return False
            else: return False
        elif self.current.value == "void":
            self.next()
            if self.current.toke == "ID":
                self.next()
                if self.bFactor():
                    self.next()
                    if self.varDec(): return True
                else: return False
            else: return False
        else:
            self.last()
            return True

    def bFactor(self):
        if self.current.value == ";": return True
        elif self.current.value == "[":
            self.next()
            if self.current.toke == "INT":
                self.next()
                if self.current.value == "]":
                    self.next()
                    if self.current.value == ";": return True
                    else: return False
                else: return False
            else: return False
        else: return False

    def statementList(self):
        if self.statement():
            self.next()
            if self.statementList(): return True
        else:
            self.last()
            return True

    def statement(self):
        if self.current.value == ";": return True
        elif self.expression():
            self.next()
            if self.current.value == ";": return True
            else: return False
        elif self.current.value == "{":
            self.next()
            if self.varDec():
                self.next()
                if self.statementList():
                    self.next()
                    if self.current.value == "}": return True
                    else: return False
                else: return False
            else: return False
        elif self.current.value == "if":
            self.next()
            if self.current.value == "(":
                self.next()
                if self.expression():
                    self.next()
                    if self.current.value == ")":
                        self.next()
                        if self.statement():
                            self.next()
                            if self.statement2(): return True
                        else: return False
                    else: return False
                else: return False
            else: return False
        elif self.current.value == "while":
            self.next()
            if self.current.value == "(":
                self.next()
                if self.expression():
                    self.next()
                    if self.current.value == ")":
                        self.next()
                        if self.whileStmt(): return True
                        else: return False
                    else: return False
                else: return False
            else: return False
        elif self.current.value == "return":
            self.next()
            if self.expressionStmt(): return True
            else: return False
        else: return False

    def statement2(self):
        if self.current.value == "else":
            self.next()
            if self.statement(): return True
        else:
            self.last()
            return True

    def whileStmt(self):
        if self.current.value == "{":
            self.next()
            if self.varDec():
                self.next()
                if self.statementList():
                    self.next()
                    if self.current.value == "}": return True
                    else: return False
                else: return False
            else: return False
        else: return False

    def expressionStmt(self):
        if self.current.value == ";": return True
        elif self.expression():
            self.next()
            if self.current.value == ";": return True
        else: return False

    def expression(self):
        if self.current.toke == "ID":
            self.next()
            if self.exp2(): return True
            else: return False
        elif self.current.toke == "INT":
            self.next()
            if self.mAR(): return True
        elif self.current.value == "(":
            self.next()
            if self.expression():
                self.next()
                if self.current.value == ")":
                    self.next()
                    if self.mAR(): return True
                else: return False
            else: return False
        else: return False

    def exp2(self):
        if self.current.value == "=":
            self.next()
            if self.expression(): return True
        elif self.current.value == "[":
            self.next()
            if self.expression():
                self.next()
                if self.current.value == "]":
                    self.next()
                    if self.cFactor(): return True
                else: return False
            else: return False
        elif self.current.value == "(":
            self.next()
            if self.argList():
                self.next()
                if self.mAR(): return True
                else: return False
            else: return False
        elif self.mAR(): return True
        else: return False

    def cFactor(self):
        if self.current.value == "=":
            self.next()
            if self.expression(): return True
        elif self.mAR(): return True

    def mAR(self):
        if self.mulop():
            self.next()
            if self.addop():
                self.next()
                if self.relop():
                    # self.next()
                    return True

    def relop(self):
        if self.current.toke == "RELOP":
            self.next()
            if self.factor():
                self.next()
                if self.mulop():
                    self.next()
                    if self.addop(): return True
            else: return False
        else:
            self.last()
            return True

    def addop(self):
        if self.current.toke == "ADDOP":
            self.next()
            if self.factor():
                self.next()
                if self.mulop():
                    self.next()
                    if self.addop(): return True
            else: return False
        else:
            self.last()
            return True

    def mulop(self):
        if self.current.toke == "MULOP":
            self.next()
            if self.factor():
                self.next()
                if self.mulop():
                    self.next()
                    if self.addop(): return True
            else: return False
        else:
            self.last()
            return True

    def factor(self):
        if self.current.value == "(":
            self.next()
            if self.expression():
                self.next()
                if self.current.value == ")": return True
                else: return False
            else: return False
        elif self.current.toke == "INT": return True
        elif self.current.toke == "ID":
            self.next()
            if self.args(): return True
        else: return False

    def args(self):
        if self.current.value == "[":
            self.next()
            if self.expression():
                self.next()
                if self.current.value == "]": return True
                else: return False
            else: return False
        elif self.current.value == "(":
            self.next()
            if self.argList(): return True
        else:
            self.last()
            return True

    def argList(self):
        if self.current.value == ")": return True
        elif self.expression():
            self.next()
            if self.argList2():
                self.next()
                if self.current.value == ")": return True
                else: return False
            else: return False
        else: return False

    def argList2(self):
        if self.current.value == ",":
            self.next()
            if self.expression():
                self.next()
                if self.argList2(): return True
            else: return False
        else:
            self.last()
            return True


# start main
main()
