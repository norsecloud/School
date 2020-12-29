import heapq
import pygame
import sys
import math
import random


def roundDown(x):
    return int(math.ceil(x / 10.0)) * 10 - 10


def get_children(parent, visitQ, blackList=[]):
    # get kids of nodeState
    if not parent.children:
        if (parent.location[0] + 10, parent.location[1]) not in blackList:
            new = nodeState(parent.W, (parent.location[0] + 10, parent.location[1]), parent)
            parent.children.append(new)
        if (parent.location[0], parent.location[1] + 10) not in blackList:
            new = nodeState(parent.W, (parent.location[0], parent.location[1] + 10), parent)
            parent.children.append(new)
        if (parent.location[0] + 10, parent.location[1] + 10) not in blackList:
            new = nodeState(parent.W, (parent.location[0] + 10, parent.location[1] + 10), parent)
            parent.children.append(new)
        if (parent.location[0] - 10, parent.location[1]) not in blackList:
            new = nodeState(parent.W, (parent.location[0] - 10, parent.location[1]), parent)
            parent.children.append(new)
        if (parent.location[0], parent.location[1] - 10) not in blackList:
            new = nodeState(parent.W, (parent.location[0], parent.location[1] - 10), parent)
            parent.children.append(new)
        if (parent.location[0] - 10, parent.location[1] - 10) not in blackList:
            new = nodeState(parent.W, (parent.location[0] - 10, parent.location[1] - 10), parent)
            parent.children.append(new)
        if (parent.location[0] - 10, parent.location[1] + 10) not in blackList:
            new = nodeState(parent.W, (parent.location[0] - 10, parent.location[1] + 10), parent)
            parent.children.append(new)
        if (parent.location[0] + 10, parent.location[1] - 10) not in blackList:
            new = nodeState(parent.W, (parent.location[0] + 10, parent.location[1] - 10), parent)
            parent.children.append(new)


class vertex(object):
    # constructor
    def __init__(self, x, y):
        self.x = x
        self.y = y


class node(object):
    # constructor
    def __init__(self, w, vertex0, parent, vertexS=0, vertexE=0):
        self.location = vertex0
        self.children = []
        self.hScore = 0
        self.gScore = 0
        self.fScore = 0
        self.parentN = parent
        self.W = w
        if parent:
            self.path = parent.path[:]
            self.path.append(vertex0)
            self.start = parent.start
            self.end = parent.end
        else:
            self.start = vertexS
            self.end = vertexE
            self.path = [vertex0]

    def get_hScore(self, w):
        pass

    def get_gScore(self):
        pass


class nodeState(node):
    def __init__(self, w, vertex0, parent, vertexS=0, vertexE=0):
        super(nodeState, self).__init__(w, vertex0, parent, vertexS, vertexE)
        self.gScore = self.get_gScore()
        self.hScore = self.get_hScore(self.W)
        self.fScore = self.gScore + self.hScore

    # comparator for heapq
    def __lt__(self, other):
        return self.fScore < other.fScore

    def get_hScore(self, w):
        if self.location[0] == self.end[0] and self.location[1] == self.end[1]:
            return 0
        else:
            h = math.sqrt(math.pow(self.location[0] - self.end[0], 2) + math.pow(self.location[1] - self.end[1], 2))
            return h * w

    def get_gScore(self):
        if self.location[0] == self.start[0] and self.location[1] and self.start[1]:
            return 0
        else:  # complicated way of getting length by getting all lines and finding .length
            g = math.sqrt(math.pow(self.location[0] - self.start[0], 2) + math.pow(self.location[1] - self.start[1], 2))
            return g


# Astar class
class Astar:
    # constructor
    def __init__(self, start, end, W, blackList, GUI):
        self.visitedQ = []
        self.openQ = []
        # self.path = []
        # self.fPath = []
        self.blackList = blackList
        self.start = start
        self.end = end
        self.G = 100000000  # high number to get less then
        self.incumbent = start
        self.W = W
        self.deltaW = 1
        self.bestW = 0
        self.GUI = GUI
        heapq.heapify(self.openQ)

    def alg3(self, s):
        heapq.heappush(self.openQ, s)
        while self.openQ:
            if self.W == 0:
                return
            newSol = self.alg4()
            if newSol is not None:
                self.bestW = self.W
                self.G = newSol.gScore
                self.incumbent = newSol

            self.W -= self.deltaW
            for z in self.openQ:
                z.hScore = z.get_hScore(self.W)
                z.fScore = z.gScore + z.hScore
                if z.gScore >= self.G:
                    self.openQ.remove(z)
        return self.incumbent

    def alg4(self):
        while self.openQ:
            # set closesetChild = lowest fscore in openQ
            closesetChild = heapq.heappop(self.openQ)
            pygame.display.update(pygame.draw.rect(self.GUI.display, self.GUI.green,
                                                   (closesetChild.location[0], closesetChild.location[1], 10, 10)))
            # get closesetChild children
            get_children(closesetChild, self.GUI, self.blackList)
            # append closesetChild to visitedQ
            self.visitedQ.append(closesetChild)
            if self.G <= closesetChild.gScore:
                return None
            # cycle through closesetChild.children
            for child in closesetChild.children:
                pygame.display.update(
                    pygame.draw.rect(self.GUI.display, self.GUI.purple, (child.location[0], child.location[1], 10, 10)))
                # if child not in visitedQ
                # if child not in self.openQ:
                checker = 0
                for value in self.openQ:
                    if (child.location[0], child.location[1]) == (value.location[0], value.location[1]):
                        checker = 1
                if checker == 0:
                    self.GUI.redraw(self.W, self.G, child, self.blackList)
                    if child.gScore < self.G:
                        if child.hScore == 0:
                            # self.path = child.path
                            return child
                    heapq.heappush(self.openQ, child)
        return None

    def calculate(self):
        # a star formula
        # create start node
        startNode = nodeState(self.W, self.start, 0, self.start, self.end)
        # put start node into openQ
        self.alg3(startNode)


class GUI:

    def __init__(self):
        # visualization
        pygame.init()
        # colors
        self.white = (255, 255, 255)
        self.black = (0, 0, 0)
        self.red = (255, 0, 0)
        self.blue = (0, 0, 255)
        self.green = (0, 255, 0)
        self.cyan = (0, 255, 255)
        self.yellow = (255, 255, 0)
        self.purple = (255, 0, 255)
        self.grey = (150, 150, 150)
        # display
        self.blocksWidthLength = 10
        self.width = 1400
        self.height = 600
        self.display = pygame.display.set_mode((self.width, self.height))
        self.display.fill(self.white)
        self.grid = list(list())
        # pixAR = pygame.PixelArray(display)
        pygame.display.set_caption("Potential All in One")
        self.smallText = pygame.font.Font("freesansbold.ttf", 20)
        self.largeText = pygame.font.Font("freesansbold.ttf", 115)
        self.background()

    def background(self):
        self.display.fill(self.white)
        for x in range(0, self.width, 10):
            x = x + 10
            pygame.draw.line(self.display, self.black, (x, 0), (x, self.height), 1)
        # vertical
        for y in range(0, self.height, 10):
            y = y + 10
            pygame.draw.line(self.display, self.black, (0, y), (self.width, y), 1)
        pygame.display.flip()

    def backgroundBL(self, child, blacklist=[]):
        self.display.fill(self.white)
        for x in range(0, self.width, 10):
            x = x + 10
            pygame.draw.line(self.display, self.black, (x, 0), (x, self.height), 1)
        # vertical
        for y in range(0, self.height, 10):
            y = y + 10
            pygame.draw.line(self.display, self.black, (0, y), (self.width, y), 1)
        pygame.draw.rect(self.display, self.blue, (child.start[0], child.start[1], 10, 10))
        pygame.draw.rect(self.display, self.red, (child.end[0], child.end[1], 10, 10))
        for z in blacklist:
            pygame.draw.rect(self.display, self.black, (z[0], z[1], 10, 10))
        pygame.display.flip()

    def text_objects(self, text, font):
        textSurface = font.render(text, True, self.black)
        return textSurface, textSurface.get_rect()

    def inputW(self):
        num = ""
        while True:
            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.unicode.isdigit():
                        num += event.unicode
                    elif event.key == pygame.K_BACKSPACE:
                        num = num[:-1]
                    elif event.key == pygame.K_RETURN:
                        return int(num)
            self.display.fill(self.white)
            pygame.draw.rect(self.display, self.green, (120, 190, 130, 50))
            textSurf, textRectG = self.text_objects("INPUT W:", self.smallText)
            textRect = (100 + 30), 200
            self.display.blit(textSurf, textRect)

            block = self.smallText.render(num, True, self.black)
            rect = block.get_rect()
            rect.center = 280, 210
            self.display.blit(block, rect)
            pygame.display.flip()

    def inputRandomShapes(self):
        num = ""
        while True:
            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.unicode.isdigit():
                        num += event.unicode
                    elif event.key == pygame.K_BACKSPACE:
                        num = num[:-1]
                    elif event.key == pygame.K_RETURN:
                        return int(num)
            self.display.fill(self.white)
            pygame.draw.rect(self.display, self.green, (120, 190, 380, 50))
            textSurf, textRectG = self.text_objects("INPUT NUMBER OF BLACK SQUARE:", self.smallText)
            textRect = (100 + 30), 200
            self.display.blit(textSurf, textRect)

            block = self.smallText.render(num, True, self.black)
            rect = block.get_rect()
            rect.center = 550, 210
            self.display.blit(block, rect)
            pygame.display.flip()

    def randomShapes(self, amount):
        temp = 0
        list = []
        while temp != amount:
            x = random.randint(0, 140) * 10
            y = random.randint(0, 60) * 10
            if (x, y) not in list:
                pygame.display.update(pygame.draw.rect(self.display, self.black, (x, y, 10, 10)))
                list.append((x, y))
                temp += 1
        return list

    def drawG(self, txt, gg, x, y):
        text = self.smallText.render(str(txt) + str(gg), 1, self.red)
        self.display.blit(text, (x, y))

    def redraw(self, w, g, child, blackList):
        self.display.fill(self.white)
        self.backgroundBL(child, blackList)
        for x in child.path:
            pygame.draw.rect(self.display, self.green, (x[0], x[1], 10, 10))
        pygame.draw.rect(self.display, self.blue, (child.start[0], child.start[1], 10, 10))
        pygame.draw.rect(self.display, self.red, (child.end[0], child.end[1], 10, 10))
        self.drawG("W: ", w, 600, 530)
        self.drawG("G: ", g, 600, 550)
        pygame.display.update()
        # pygame.time.delay(10)

    def gameLoop(self, W, blackList):
        starChec = 0

        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

                if event.type == pygame.MOUSEBUTTONDOWN:
                    if starChec == 0:
                        x1 = roundDown(event.pos[0])
                        y1 = roundDown(event.pos[1])
                        # start = vertex(x, y)
                        pygame.display.update(pygame.draw.rect(self.display, self.blue, (x1, y1, 10, 10)))
                        pygame.display.flip()
                        starChec += 1
                    elif starChec == 1:
                        x2 = roundDown(event.pos[0])
                        y2 = roundDown(event.pos[1])
                        # end = vertex(x, y)
                        pygame.display.update(pygame.draw.rect(self.display, self.red, (x2, y2, 10, 10)))
                        pygame.display.flip()
                        starChec += 1
                    elif starChec == 2:
                        astar = Astar((x1, y1), (x2, y2), W, blackList, self)
                        astar.calculate()
                        astar.GUI.redraw(astar.bestW, astar.G, astar.incumbent, blackList)


def main():

    gui = GUI()
    W = gui.inputW()
    randBlocks = gui.inputRandomShapes()
    gui.background()
    blackList = gui.randomShapes(randBlocks)
    gui.gameLoop(W, blackList)


import time
main()
