# Finn Raae
# cop4620
# lexical analizer: basically reads txt and see what each word or number is for programming
# imports
import sys
import re


class semanticAnalyzer:
    def __init__(self):
        self.listList = []
        self.counter = -1
        self.gvarCounter = 0

    def newList(self):
        scope = []
        self.counter += 1
        self.listList.append(scope)

    def removeList(self):
        self.listList.pop()
        self.counter -= 1

    def checkMain(self):
        x = len(self.listList[0])
        while x >= len(self.listList):
            x -= 1
        if self.listList[0][len(self.listList[0])-1]["ID"] == "main":
            for value in self.listList[x]:
                if "PARAM" in value:
                    if value["KEY"] == "void": return True
                    # else: return False
        # else: return False

    def checkFunc(self, check):
        for value in self.listList[0]:
            if check["ID"] == value["ID"]: return True
        # return False

    def checkParam(self, check):
        scope = 0
        params = []
        curScope = []
        for value in self.listList[0]:
            if check[0] == value["ID"]:
                scope = self.listList[0].index(value)
        scope += 1
        scope += self.gvarCounter
        for pvalue in self.listList[scope]:
            if "PARAM" in pvalue: params.append(pvalue)
        check.pop(0)
        for cvalue in check:
            if cvalue in (",", "(", ")"): pass
            elif cvalue.isdigit(): curScope.append(cvalue)
            else:
                for xvalue in self.listList[self.counter]:
                    if cvalue == xvalue["ID"]: curScope.append(xvalue)
        # if len(curScope) != len(params): return False
        j = 0
        while j != len(curScope):
            if "ARR" in params[j]:
                if "ARR" in curScope[j]: pass
                # else: return False
            elif curScope[j].isdigit and params[j]["KEY"] == "int": pass
            elif params[j]["KEY"] == curScope[j]["KEY"]: pass
            # else: return False
            j += 1
        return True

    def checkExp(self, check):
        funcNameList = []
        varNameList = []
        expCheck = ""
        for x in self.listList[0]: funcNameList.append(x["ID"])
        for z in self.listList[self.counter]: varNameList.append(z["ID"])
        for x in self.listList[self.counter]:
            if check[0] == x["ID"]:
                expCheck = x["KEY"]
                if "ARR" in x:
                    arrCount = x["ARR"]
                    arrBool = True
                    if len(check) > 2:
                        if check[1] == "[": pass
                        elif check[1] in ("+", "*", "=", "-", "/"): return False
                    # else: pass
        if expCheck == "void": return False
        for value in check:
            if value in ("+", "-", "=", "*", "/", "[", "]", "(", ")", ",", "=="): pass
            elif value.isdigit(): pass
            else:
                if value in funcNameList:
                    for y in self.listList[0]:
                        if value == y["ID"]:
                            if expCheck == "": pass
                            # else:
                            #     if y["KEY"] == expCheck:
                            #         if y["KEY"] == "int": pass
                                    # else:
                                        # x = check.index(y["ID"])
                                        # if x >= len(check) - 1: return False
                                        # else:
                                        #     if check[x + 1] == "(": return True
                                        #     else: return False
                                #         return False
                                # else: return False
                elif value in varNameList:
                    for dict in self.listList[self.counter]:
                        if value == dict["ID"]:
                            if dict["KEY"] != expCheck: pass
                                # return False
                            elif "ARR" in dict:
                                x = check.index(dict["ID"])
                                if x >= len(check)-1: pass
                                    # return False
                                else:
                                    if check[x+1] == "[":
                                        if check[x+2].isdigit():
                                            if check[x+3] == "]": pass
                                        elif check[x+2].isalpha():
                                            for dic in self.listList[self.counter]:
                                                if check[x+2] == dic["ID"]:
                                                    if "ARR" in dic: pass
                                                        # return False
                                    else: pass
                                    # return False
                else: pass
                # return False
        return True

    def checkReturn(self, check):
        retCheck = self.listList[0][len(self.listList[0])-1]["KEY"]
        funcNameList = []
        varNameList = []
        if retCheck == "int":
            if not check: pass
                # return False
            else:
                for x in self.listList[0]: funcNameList.append(x["ID"])
                for z in self.listList[self.counter]: varNameList.append(z["ID"])
                for value in check:
                    if value in ("+", "-", "=", "*", "/", "[", "]", "(", ")", ",", "=="): pass
                    elif value.isdigit(): pass
                    else:
                        if value in funcNameList:
                            for y in self.listList[0]:
                                if value == y["ID"]:
                                    if y["KEY"] != retCheck: pass
                                    # return False
                        elif value in varNameList:
                            for dict in self.listList[self.counter]:
                                if value == dict["ID"]:
                                    if dict["KEY"] != retCheck: pass
                                    # return False
                                    elif "ARR" in dict:
                                        x = check.index(dict["ID"])
                                        if x >= len(check) - 1: pass
                                        #     return False
                                        else:
                                            if check[x + 1] == "[":
                                                if check[x + 2].isdigit():
                                                    if check[x + 3] == "]": pass
                                                elif check[x + 2].isalpha():
                                                    for dic in self.listList[self.counter]:
                                                        if check[x + 2] == dic["ID"]:
                                                            if "ARR" in dic: pass
                                                            # return False
                        #                     else:
                        #                         return False
                        # else: return False
            return True
        elif retCheck == "void":
            if not check: return True
            # else: return False

    def addFunc(self, add):
        for value in self.listList[0]:
            if value["ID"] == add["ID"]:
                if value["TYPE"] == add["TYPE"]: pass
                # return False
            if add["TYPE"] == "gvar":
                self.gvarCounter += 1
                self.listList[0].insert(0,add)
            else:
                self.listList[0].append(add)
            return True
        if add["TYPE"] == "gvar":
            self.gvarCounter += 1
            self.listList[0].insert(0, add)
        else:
            self.listList[0].append(add)
        return True

    def addVoid(self, add):
        self.listList[self.counter].append(add)

    def addItem(self, add):
        if "KEY" not in add:
            for value in self.listList[self.counter]:
                if value["ID"] == add["ID"]:
                    if "VAL" in value:
                        value["VAL"] = add["VAL"]
                        return True
        else:
            for value in self.listList[self.counter]:
                if "ID" in value:
                    if value["ID"] == add["ID"]: pass
                    #     return False
            self.listList[self.counter].append(add)
            return True


class assembler:
    def __init__(self):
        self.counter = 0
        self.temp = -1
        self.lastComp = ""
        self.loopPlace = ""

    def counterPlus(self):
        self.counter += 1

    def Startout(self):
        print("--------------------------------------------------")

    def assignOut(self, val, var):
        self.counterPlus()
        print(self.counter, "\t\t", "assign", "\t", val, "\t\t\t\t\t\t", var)

    def allocOut(self, var):
        self.counterPlus()
        print(self.counter, "\t\t alloc", "\t\t", "4", "\t\t\t\t\t\t", var)

    def allocOutArr(self, var, val):
        self.counterPlus()
        x = int(val) * 4
        print(self.counter, "\t\t alloc", "\t\t", x, "\t\t\t\t\t", var)

    def funcOutS(self, func, type):
        self.counterPlus()
        if type == "int":
            print(self.counter, "\t\t", "func", "\t\t", func, "\t\t", type, "\t\t", 1)
        else:
            print(self.counter, "\t\t", "func", "\t\t", func, "\t\t", type, "\t\t", 0)

    def funcOutE(self, func):
        self.counterPlus()
        print(self.counter, "\t\t", "end", "\t\t", func)

    def callOut(self, func, type):
        self.counterPlus()
        if type == "int":
            print(self.counter, "\t\t", "func", "\t\t", func, "\t\t", 1, "\t\t", "_t", self.temp)
        else:
            print(self.counter, "\t\t", "func", "\t\t", func, "\t\t", 0)

    def param(self, params):
        self.counterPlus()
        print(self.counter, "\t\t", "param", "\t\t\t\t\t\t\t\t", params)
        self.allocOut(params)

    def arg(self, arg):
        self.counterPlus()
        print(self.counter, "arg", "\t\t\t", arg)

    def returnOut(self, list):
        self.orderOfOp(list)
        self.counterPlus()
        s = str(self.temp)
        v = "_t" + s
        print(self.counter, "\t\t", "return\t\t\t\t\t\t\t\t", v)

    def expOut(self, list):
        self.orderOfOp(list)
        if "=" in list:
            self.assignOut(list[2], list[0])

    def orderOfOp(self, list):
        self.temp += 1
        for x in list:
            if x == "(":
                z = list.index("(")
                q = list.index(")")
                newList = list[z+1:q]
                del list[z:q+1]
                self.orderOfOp(newList)
                list.insert(z, newList[0])
                if z != 0:
                    if list[z-1] in ["*", "/", "+", "-", ")", "="]:
                        pass
                    else:
                        list.insert(z, "*")
                        z += 1
                if z >= len(list):
                    if list[z+1] in ["*", "/", "+", "-", ")", "="]:
                        pass
                    else: list.insert(z+1, "*")
        for x in list:
            if x == "*":
                self.counterPlus()
                z = list.index("*")
                w = "_t" + str(self.temp)
                print(self.counter, "\t\t", "mult\t\t", list[z-1], "\t\t", list[z+1], "\t\t", w)
                self.temp += 1
                del list[z-1:z+2]
                list.insert(z-1, w)
        for x in list:
            if x == "/":
                self.counterPlus()
                z = list.index("/")
                w = "_t" + str(self.temp)
                print(self.counter, "\t\t", "div\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w)
                self.temp += 1
                del list[z - 1:z + 2]
                list.insert(z - 1, w)
        for x in list:
            if x == "+":
                self.counterPlus()
                z = list.index("+")
                w = "_t" + str(self.temp)
                print(self.counter, "\t\t", "add\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w)
                del list[z - 1:z + 2]
                list.insert(z - 1, w)
        for x in list:
            if x == "-":
                self.counterPlus()
                z = list.index("-")
                w = "_t" + str(self.temp)
                print(self.counter, "\t\t", "sub\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w)
                self.temp += 1
                del list[z - 1:z + 2]
                list.insert(z - 1, w)
        for x in list:
            if x in ["<", ">", "<=", ">="]:
                self.lastComp = x
                self.counterPlus()
                z = list.index(x)
                w = "_t" + str(self.temp)
                print(self.counter, "\t\t compr\t\t", list[z-1], "\t\t\t", list[z+1], "\t\t\t", w)

    def ifOut(self, list):
        self.orderOfOp(list)
        # print compare statment
        w = "_t" + str(self.temp)
        self.counterPlus()
        self.loopPlace = self.counter
        if self.lastComp == ">":
            print(self.counter, "\t\t brle\t\t", w, "\t\t\t\t\t", "asd   bpw =", self.counter)
        elif self.lastComp == ">=":
            print(self.counter, "\t\t brleq\t\t", w, "\t\t\t\t\t", "asd   bpw =", self.counter)
        elif self.lastComp == "<":
            print(self.counter, "\t\t brgr\t\t", w, "\t\t\t\t\t", "asd   bpw =", self.counter)
        elif self.lastComp == "<=":
            print(self.counter, "\t\t brgrq\t\t", w, "\t\t\t\t\t", "asd   bpw =", self.counter)

    def elseOut(self):
        self.counterPlus()
        z = self.counter + 1
        print(self.counter, "\t\t br\t\t\t\t\t\t\t\t\t", z, "bpo =", self.counter)

    def whileOutS(self, list):
        firstExp = True
        self.temp += 1
        for x in list:
            if x == "(":
                z = list.index("(")
                q = list.index(")")
                newList = list[z + 1:q]
                del list[z:q + 1]
                self.orderOfOp(newList)
                list.insert(z, newList[0])
                if z != 0:
                    if list[z - 1] in ["*", "/", "+", "-", ")", "="]:
                        pass
                    else:
                        list.insert(z, "*")
                        z += 1
                if z >= len(list):
                    if list[z + 1] in ["*", "/", "+", "-", ")", "="]:
                        pass
                    else:
                        list.insert(z + 1, "*")
        for x in list:
            if x == "*":
                self.counterPlus()
                z = list.index("*")
                w = "_t" + str(self.temp)
                if firstExp == True:
                    self.loopPlace = self.counter
                    print(self.counter, "\t\t", "mult\t\t", list[z - 1], "\t\t\t", list[z + 1], "\t\t", w, "bpw =", self.counter)
                    firstExp = False
                else:
                    print(self.counter, "\t\t", "mult\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w)
                self.temp += 1
                del list[z - 1:z + 2]
                list.insert(z - 1, w)
        for x in list:
            if x == "/":
                self.counterPlus()
                z = list.index("/")
                w = "_t" + str(self.temp)
                if firstExp == True:
                    self.loopPlace = self.counter
                    print(self.counter, "\t\t", "div\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w, "bpw =", self.counter)
                    firstExp = False
                else:
                    print(self.counter, "\t\t", "div\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w)
                self.temp += 1
                del list[z - 1:z + 2]
                list.insert(z - 1, w)
        for x in list:
            if x == "+":
                self.counterPlus()
                z = list.index("+")
                w = "_t" + str(self.temp)
                if firstExp == True:
                    self.loopPlace = self.counter
                    print(self.counter, "\t\t", "add\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w, "bpw =", self.counter)
                    firstExp = False
                else:
                    print(self.counter, "\t\t", "add\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w)
                del list[z - 1:z + 2]
                list.insert(z - 1, w)
        for x in list:
            if x == "-":
                self.counterPlus()
                z = list.index("-")
                w = "_t" + str(self.temp)
                if firstExp == True:
                    self.loopPlace = self.counter
                    print(self.counter, "\t\t", "sub\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w, "bpw =", self.counter)
                    firstExp = False
                else:
                    print(self.counter, "\t\t", "sub\t\t", list[z - 1], "\t\t", list[z + 1], "\t\t", w)
                self.temp += 1
                del list[z - 1:z + 2]
                list.insert(z - 1, w)
        for x in list:
            if x in ["<", ">", "<=", ">="]:
                self.lastComp = x
                self.counterPlus()
                z = list.index(x)
                w = "_t" + str(self.temp)
                if firstExp == True:
                    self.loopPlace = self.counter
                    print(self.counter, "\t\t compr\t\t", list[z - 1], "\t\t\t", list[z + 1], "\t\t\t", w, "bpw =", self.counter)
                    firstExp = False
                else:
                    print(self.counter, "\t\t compr\t\t", list[z - 1], "\t\t\t", list[z + 1], "\t\t\t", w)


        # print actual loop statment
        w = "_t" + str(self.temp)
        self.counterPlus()
        if self.lastComp == ">":
            print(self.counter, "\t\t brle\t\t", w, "\t\t\t\t\t", "asd   bpo =", self.counter)
        elif self.lastComp == ">=":
            print(self.counter, "\t\t brleq\t\t", w, "\t\t\t\t\t", "asd   bpo =", self.counter)
        elif self.lastComp == "<":
            print(self.counter, "\t\t brgr\t\t", w, "\t\t\t\t\t", "asd   bpo =", self.counter)
        elif self.lastComp == "<=":
            print(self.counter, "\t\t brgrq\t\t", w, "\t\t\t\t\t", "asd   bpo =", self.counter)

    def whileOutE(self):
        self.counterPlus()
        print(self.counter, "\t\t br\t\t\t\t\t\t\t\t\t", self.loopPlace)


class Tokens:
    # constructor
    def __init__(self, toke, value=None):
        self.toke = toke
        self.value = value


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
    # try:
    parser = Parser(tokens)
    fin = parser.parse()
    # except:
    #     print("REJECT")
    #     sys.exit()
    # if fin: print("ACCEPT")
    # else: print("REJECT")


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
                for i, c in enumerate("letter"):
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
                for i, c in enumerate("letter"):
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

    elif key in ("\n", "", " ", "\r", "\t"):
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
        self.listMain = semanticAnalyzer()
        self.ass = assembler()
        self.addDiction = {}
        self.checkList = []
        self.inExp = False

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
        self.listMain.newList()
        return self.program()

    # start the grammar functions
    def program(self):
        self.ass.Startout()
        if self.declarationList():
            if self.index < len(self.tokens):
                self.next()
                self.program()
            else:
                self.ass.Startout()
                if self.listMain.checkMain(): return True
                else: return False
        else:
            # self.ass.Startout()
            return False

    def declarationList(self):
        if self.current.value == "int":
            self.addDiction = {"KEY": "int"}
            self.next()
            if self.current.toke == "ID":
                self.addDiction["ID"] = self.current.value
                if self.tokens[self.index + 1].value == "(":
                    self.addDiction["TYPE"] = "func"
                else:
                    self.addDiction["TYPE"] = "gvar"
                funcName = self.addDiction["ID"]
                funcType = self.addDiction["KEY"]
                self.ass.funcOutS(funcName, funcType)
                if self.listMain.addFunc(self.addDiction): pass
                # else: return False
                self.next()
                if self.aFactor(): return True
                # else: return False
            self.ass.funcOutE(funcName)
            return True
            # else: return False
        elif self.current.value == "void":
            self.addDiction = {"KEY": "void"}
            self.next()
            if self.current.toke == "ID":
                self.addDiction["ID"] = self.current.value
                self.addDiction["TYPE"] = "func"
                if self.listMain.addFunc(self.addDiction): pass
                # else: return False
                funcName = self.addDiction["ID"]
                funcType = self.addDiction["KEY"]
                self.ass.funcOutS(funcName, funcType)
                self.next()
                if self.aFactor():
                    self.ass.funcOutE(funcName)
                    return True
            # else: return False

        # else: return False

    def declarationList2(self):
        if self.current.value == "int":
            self.addDiction = {"KEY": "int"}
            self.next()
            if self.current.toke == "ID":
                self.addDiction["ID"] = self.current.value
                if self.tokens[self.index + 1].value == "(":
                    self.addDiction["TYPE"] = "func"
                else:
                    self.addDiction["TYPE"] = "gvar"
                if self.listMain.addFunc(self.addDiction): pass
                # else: return False
                funcName = self.addDiction["ID"]
                funcType = self.addDiction["KEY"]
                self.ass.funcOutS(funcName, funcType)
                self.next()
                if self.aFactor():
                    self.ass.funcOutE(funcName)
                    return True
            # else: return False
        elif self.current.value == "void":
            self.addDiction = {"KEY": "void"}
            self.next()
            if self.current.toke == "ID":
                self.addDiction["ID"] = self.current.value
                self.addDiction["TYPE"] = "func"
                if self.listMain.addFunc(self.addDiction): pass
                # else: return False
                funcName = self.addDiction["ID"]
                funcType = self.addDiction["KEY"]
                self.ass.funcOutS(funcName, funcType)
                self.next()
                if self.aFactor():
                    self.ass.funcOutE(funcName)
                    return True
            else:
                if self.listMain.addFunc(self.addDiction): pass
                # else: return False
                # return False
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
                self.listMain.listList[self.listMain.counter][
                    len(self.listMain.listList[self.listMain.counter]) - 1][
                    "ARR"] = self.current.value
                self.next()
                if self.current.value == "]":
                    self.next()
                    if self.current.value == ";":
                        self.next()
                        if self.declarationList2(): return True
                    # else: return False
                # else: return False
            # else: return False
        elif self.current.value == "(":
            self.listMain.newList()
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
                                    if self.declarationList2():
                                        self.next()
                                        return True
                                # else: return False
                    # else: return False
                # else: return False
            # else: return False
        # else: return False

    def params(self):
        if self.current.value == "int":
            self.addDiction = {"KEY": "int",  "PARAM": "Y"}
            self.next()
            if self.current.toke == "ID":
                self.addDiction["ID"] = self.current.value
                if self.listMain.addItem(self.addDiction): pass
                self.ass.param(self.addDiction["ID"])
                # else: return False
                self.next()
                if self.arr():
                    self.next()
                    if self.paramList2(): return True
            # else: return False
        elif self.current.value == "void":
            self.addDiction = {"KEY": "void", "PARAM": "Y", "ID": "PARAM"}
            self.listMain.addVoid(self.addDiction)
            self.next()
            if self.current.toke == "ID": pass
                # return False
            self.last()
            return True
        # else: return False

    def paramList2(self):
        if self.current.value == ",":
            self.next()
            if self.param(): return True
        else:
            self.last()
            return True

    def param(self):
        if self.current.value == "int":
            self.addDiction = {"KEY": "int",  "PARAM": "Y"}
            self.next()
            if self.current.toke == "ID":
                self.addDiction["ID"] = self.current.value
                if self.listMain.addItem(self.addDiction): pass
                # else: return False
                self.next()
                if self.arr():
                    self.next()
                    if self.paramList2(): return True
            # else: return False
        elif self.current.value == "void":
            self.addDiction = {"KEY": "void",  "PARAM": "Y", "ID": "PARAM"}
            self.listMain.addVoid(self.addDiction)
            self.next()
            if self.current.toke == "ID": pass
                # return False
            else:
                self.last()
                return True
        # else: return False

    def arr(self):
        if self.current.value == "[":
            self.next()
            if self.current.value == "]":
                self.listMain.listList[self.listMain.counter][
                    len(self.listMain.listList[self.listMain.counter]) - 1][
                    "ARR"] = "Y"
                return True
        else:
            self.last()
            return True

    def varDec(self):
        if self.current.value == "int":
            self.addDiction = {"KEY": "int"}
            self.next()
            if self.current.toke == "ID":
                self.addDiction["ID"] = self.current.value
                if self.listMain.addItem(self.addDiction): pass
                # else: return False
                self.next()
                if self.bFactor():
                    self.next()
                    if self.varDec(): return True
                # else: return False
            # else: return False
        elif self.current.value == "void":
            self.addDiction = {"KEY": "void"}
            self.next()
            if self.current.toke == "ID":
                # return False
                self.next()
                if self.bFactor():
                    self.next()
                    if self.varDec(): return True
                # else: return False
            # else: return False
        else:
            self.last()
            return True

    def bFactor(self):
        if self.current.value == ";":
            self.ass.allocOut(self.addDiction["ID"])
            return True
        elif self.current.value == "[":
            self.next()
            if self.current.toke == "INT":
                self.ass.allocOutArr(self.addDiction["ID"], self.current.value)
                self.listMain.listList[self.listMain.counter][
                    len(self.listMain.listList[self.listMain.counter]) - 1][
                    "ARR"] = self.current.value
                self.next()
                if self.current.value == "]":
                    self.next()
                    if self.current.value == ";": return True
                    # else: return False
                # else: return False
            # else: return False
        # else: return False

    def statementList(self):
        if self.statement():
            self.next()
            if self.statementList(): return True
        else:
            self.last()
            return True

    def statement(self):
        if self.current.value == ";":
            self.inExp = False
            return True
        elif self.expression():
            self.next()
            if self.current.value == ";":
                self.inExp = False
                return True
            # else: return False
        elif self.current.value == "{":
            self.listMain.newList()
            self.next()
            if self.varDec():
                self.next()
                if self.statementList():
                    self.next()
                    if self.current.value == "}":
                        self.listMain.removeList()
                        return True
                    # else: return False
                # else: return False
            # else: return False
        elif self.current.value == "if":
            self.next()
            if self.current.value == "(":
                self.next()
                temp = ""
                temp1 = 1
                self.checkList = [self.current.value]
                while ")" not in temp:
                    temp = self.tokens[self.index + temp1].value
                    self.checkList.append(temp)
                    temp1 += 1
                self.checkList.pop()
                self.ass.ifOut(self.checkList)
                self.inExp = True
                if self.expression():
                    self.next()
                    if self.current.value == ")":
                        self.inExp = False
                        self.next()
                        if self.statement():
                            self.next()
                            if self.statement2(): return True
                        # else: return False
                    # else: return False
                # else: return False
            # else: return False
        elif self.current.value == "while":
            self.next()
            if self.current.value == "(":
                self.next()
                temp = ""
                temp1 = 1
                self.checkList = [self.current.value]
                while ")" not in temp:
                    temp = self.tokens[self.index + temp1].value
                    self.checkList.append(temp)
                    temp1 += 1
                self.checkList.pop()
                self.ass.whileOutS(self.checkList)
                self.inExp = True
                if self.expression():
                    self.next()
                    if self.current.value == ")":
                        self.inExp = False
                        self.next()
                        if self.whileStmt(): return True
                        # else: return False
                    # else: return False
                # else: return False
            # else: return False
        elif self.current.value == "return":

            temp = ""
            temp1 = 1
            self.inExp = True
            self.checkList = []
            while not ";" in temp:
                temp = self.tokens[self.index + temp1].value
                self.checkList.append(temp)
                temp1 += 1
            self.checkList.pop()
            self.ass.returnOut(self.checkList)
            # if self.listMain.checkReturn(self.checkList): return True
            # else: return False
            self.next()
            if self.expressionStmt(): return True
            # else: return False
        # else: return False

    def statement2(self):
        if self.current.value == "else":
            self.next()
            self.ass.elseOut()
            if self.statement():
                return True
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
                    if self.current.value == "}":
                        self.ass.whileOutE()
                        return True
                    # else: return False
                # else: return False
            # else: return False
        # else: return False

    def expressionStmt(self):
        if self.current.value == ";":
            self.inExp = False
            return True
        elif self.expression():
            self.next()
            if self.current.value == ";":
                self.inExp = False
                return True
        # else: return False

    def expression(self):
        if self.current.toke == "ID":
            self.addDiction = {"ID": self.current.value}
            if self.tokens[self.index + 1].value == "(":
                temp = ""
                temp1 = 1
                self.checkList = [self.current.value]
                while ")" not in temp:
                    temp = self.tokens[self.index + temp1].value
                    self.checkList.append(temp)
                    temp1 += 1
                # if self.listMain.checkParam(self.checkList): pass
                # else: return False
            if self.inExp == True: pass
            else:
                    temp = ""
                    temp1 = 1
                    if not self.inExp:
                        self.checkList = [self.current.value]
                        while temp not in (";", "{", "}"):
                            temp = self.tokens[self.index + temp1].value
                            self.checkList.append(temp)
                            temp1 += 1
                        self.checkList.pop()
                        # if self.listMain.checkExp(self.checkList): pass
                        # else: return False
                        self.ass.expOut(self.checkList)
                    self.inExp = True
            self.next()
            if self.exp2(): return True
            # else: return False
        elif self.current.toke == "INT":
            self.addDiction["VAL"] = self.current.value
            self.listMain.addItem(self.addDiction)
            # self.listMain.addItem(self.diction)
            # self.listMain.listList[self.listMain.counter][len(self.listMain.listList[self.listMain.counter]) - 1][
            #     "VAL"] = self.current.value
            # self.listMain.addItem(self.diction)
            self.next()
            if self.mAR(): return True
        elif self.current.value == "(":
            if self.tokens[self.index-1].toke == "ID":
                self.addDiction["KEY"] = "FUNC"
                # if self.listMain.checkFunc(self.addDiction):
                #     if self.listMain.addItem(self.addDiction): pass
                    # else: return False
                # else: return False
            self.next()
            if self.expression():
                self.next()
                if self.current.value == ")":
                    self.next()
                    if self.mAR(): return True
                # else: return False
            # else: return False
        # else: return False

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
                # else: return False
            # else: return False
        elif self.current.value == "(":
            if self.tokens[self.index-1].toke == "ID":
                self.addDiction["KEY"] = "FUNC"
                if self.listMain.checkFunc(self.addDiction):
                    if self.listMain.addItem(self.addDiction): pass
                    # else: return False
                # else: return False
            self.next()
            if self.argList():
                self.next()
                if self.mAR(): return True
                # else: return False
            # else: return False
        elif self.mAR(): return True
        # else: return False

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
            # else: return False
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
            # else: return False
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
            # else: return False
        else:
            self.last()
            return True

    def factor(self):
        if self.current.value == "(":
            self.next()
            if self.expression():
                self.next()
                if self.current.value == ")": return True
                # else: return False
            # else: return False
        elif self.current.toke == "INT": return True
        elif self.current.toke == "ID":
            self.next()
            if self.args(): return True
        # else: return False

    def args(self):
        if self.current.value == "[":
            self.next()
            if self.expression():
                self.next()
                if self.current.value == "]": return True
                # else: return False
            # else: return False
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
                # else: return False
            # else: return False
        # else: return False

    def argList2(self):
        if self.current.value == ",":
            self.next()
            if self.expression():
                self.next()
                if self.argList2(): return True
            # else: return False
        else:
            self.last()
            return True

# start main
main()
