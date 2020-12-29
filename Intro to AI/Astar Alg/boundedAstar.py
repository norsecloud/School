# Finn Raae
# intro to ai
# A* algorithm with visualization
# imports
import heapq
import math
from sys import exit
import pygame
from pygame.locals import *
from shapely.geometry import LineString, Polygon


# functions
def get_children(parent, constraint, polys=[], vlist=[]):
    # get kids of nodeState
    # if parent.children is empty
    if not parent.children:
        # cycle through vertex list(vList)
        for x in vlist:
            # create line from parent to vertex
            testLine = LineString([(parent.location.x, parent.location.y), (x.x, x.y)])
            notChild = False
            # if x is parent location
            if x.x == parent.location.x and x.y == parent.location.y or testLine.length > constraint:
                notChild = True
            else:
                # cycle through polygon list(poly)
                for y in polys:
                    # if testline crosses a polygon
                    if testLine.crosses(y):
                        notChild = True
                        # if testline is within a polygon
                    elif testLine.within(y):
                        notChild = True
                # if notchild is false
                if not notChild:
                    # new node and append to parent
                    new = nodeState(x, parent)
                    parent.children.append(new)

    # pygame functions


def drawPath(path):
    i = 0
    while i < len(path):
        if i == len(path) - 1:
            i += 2
        else:
            pygame.draw.line(display, purple, (path[i].x, path[i].y),
                             (path[i + 1].x, path[i + 1].y), 3)
            i += 1
    pygame.display.update()
    pygame.time.delay(5)


def messageDisp(text):
    TextSurf, TextRect = text_objects(text, largeText)
    TextRect.center = (500, 300)


def text_objects(text, font):
    textSurface = font.render(text, True, black)
    return textSurface, textSurface.get_rect()


def quitGame():
    pygame.quit()
    quit()


def button(text, x, y, width, height, color, colorb, size, action=None):
    mouse = pygame.mouse.get_pos()
    click = pygame.mouse.get_pressed()
    if x + width > mouse[0] > x and y + height > mouse[1] > y:
        pygame.draw.rect(display, color, (x, y, width, height))
        if click[0] == 1 and action != None:
            action()
    else:
        pygame.draw.rect(display, colorb, (x, y, width, height))
    textSurf, textRectG = text_objects(text, size)
    textRect = (x + 30), y
    display.blit(textSurf, textRect)


def input():
    num = ""
    while True:
        for event in pygame.event.get():
            if event.type == KEYDOWN:
                if event.unicode.isdigit():
                    num += event.unicode
                elif event.key == K_BACKSPACE:
                    num = num[:-1]
                elif event.key == K_RETURN:
                    return int(num)
        display.fill(white)
        pygame.draw.rect(display, green, (120, 190, 130, 50))
        textSurf, textRectG = text_objects("INPUT NUM:", smallText)
        textRect = (100 + 30), 200
        display.blit(textSurf, textRect)

        block = smallText.render(num, True, black)
        rect = block.get_rect()
        rect.center = 280, 210
        display.blit(block, rect)
        pygame.display.flip()


def startMenu():
    intro = True
    while intro:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
        display.fill(white)
        TextSurf, TextRect = text_objects("Choose Project:", largeText)
        TextRect.center = (500, 300)
        display.blit(TextSurf, TextRect)

        button("P1", 100, 450, 200, 100, green, greenlow, largeText, astarP1)
        button("P2", 350, 450, 200, 100, blue, bluelow, largeText, astarP2)
        button("Quit", 600, 450, 300, 100, red, redlow, largeText, quitGame)
        pygame.display.flip()


def finish(text):
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
        TextSurf, TextRect = text_objects(text, largeText)
        TextRect.center = (500, 300)
        display.blit(TextSurf, TextRect)
        button("P1", 100, 500, 140, 30, green, greenlow, smallText, astarP1)
        button("P2", 300, 500, 140, 30, blue, bluelow, smallText, astarP2)
        button("Quit", 600, 500, 140, 30, red, redlow, smallText, quitGame)
        pygame.display.flip()


def createBackgroundP1():
    # shapes
    # start
    pygame.draw.circle(display, blue, (50, 500), 5)
    # end
    pygame.draw.circle(display, green, (950, 100), 5)
    # polygons
    pygame.draw.polygon(display, black, [(300, 400), (400, 400), (350, 200)], 4)
    pygame.draw.polygon(display, black, [(250, 380), (300, 220), (220, 100), (100, 220), (110, 340)], 4)
    pygame.draw.polygon(display, black, [(400, 240), (400, 100), (480, 80), (580, 140)], 4)
    pygame.draw.polygon(display, black, [(500, 340), (540, 500), (640, 440)], 4)
    pygame.draw.polygon(display, black, [(720, 440), (720, 540), (780, 580), (880, 540), (880, 440), (820, 400)], 4)
    pygame.draw.polygon(display, black, [(840, 140), (890, 100), (930, 160), (900, 400)], 4)
    # rect
    pygame.draw.polygon(display, black, [(600, 80), (800, 80), (800, 380), (600, 380)], 4)
    pygame.draw.polygon(display, black, [(100, 450), (100, 550), (500, 550), (500, 450)], 4)
    # update screen
    pygame.display.flip()


def createBackgroundP2():
    # shapes
    # start
    pygame.draw.circle(display, blue, (10, 10), 5)
    # end
    pygame.draw.circle(display, green, (990, 590), 5)
    # polygons
    pygame.draw.polygon(display, black, [(30, 10), (40, 10), (40, 200), (30, 200)], 4)
    pygame.draw.polygon(display, black, [(0, 240), (300, 300), (0, 300)], 4)
    pygame.draw.polygon(display, black, [(280, 10), (150, 150), (150, 90)], 4)
    pygame.draw.polygon(display, black, [(970, 560), (970, 500), (900, 580)], 4)
    pygame.draw.polygon(display, black, [(500, 200), (600, 200), (600, 400), (500, 400)], 4)
    pygame.draw.polygon(display, black, [(320, 280), (450, 280), (450, 360), (320, 360) ], 4)
    pygame.draw.polygon(display, black, [(630, 0), (800, 0), (800, 380), (630, 380)], 4)
    pygame.draw.polygon(display, black, [(300, 450), (300, 550), (850, 550), (850, 450)], 4)
    # update screen

    pygame.display.flip()


def astarP1():
    # hard coded shapes
    poly1 = Polygon([(300, 400), (400, 400), (350, 200)])
    poly2 = Polygon([(250, 380), (300, 220), (220, 100), (100, 220), (110, 340)])
    poly3 = Polygon([(400, 240), (400, 100), (480, 80), (580, 140)])
    poly4 = Polygon([(500, 340), (540, 500), (640, 440)])
    poly5 = Polygon([(720, 440), (720, 540), (780, 580), (880, 540), (880, 440), (820, 400)])
    poly6 = Polygon([(840, 140), (890, 100), (930, 160), (900, 400)])
    poly7 = Polygon([(600, 80), (800, 80), (800, 380), (600, 380)])
    poly8 = Polygon([(100, 450), (100, 550), (500, 550), (500, 450)])
    # polyList
    polyList = [poly1, poly2, poly3, poly4, poly5, poly6, poly7, poly8]

    # vertexes
    # start
    startV = vertex(50, 500)
    # end
    endV = vertex(950, 100)
    # other
    v11 = vertex(300, 400)
    v12 = vertex(400, 400)
    v13 = vertex(350, 200)
    v21 = vertex(250, 380)
    v22 = vertex(300, 220)
    v23 = vertex(220, 100)
    v24 = vertex(100, 220)
    v25 = vertex(110, 340)
    v31 = vertex(400, 240)
    v32 = vertex(400, 100)
    v33 = vertex(480, 80)
    v34 = vertex(580, 140)
    v41 = vertex(500, 340)
    v42 = vertex(540, 500)
    v43 = vertex(640, 440)
    v51 = vertex(720, 440)
    v52 = vertex(720, 540)
    v53 = vertex(780, 580)
    v54 = vertex(880, 540)
    v55 = vertex(880, 440)
    v56 = vertex(820, 400)
    v61 = vertex(840, 140)
    v62 = vertex(890, 100)
    v63 = vertex(930, 160)
    v64 = vertex(900, 400)
    v71 = vertex(600, 80)
    v72 = vertex(800, 80)
    v73 = vertex(800, 380)
    v74 = vertex(600, 380)
    v81 = vertex(100, 450)
    v82 = vertex(100, 550)
    v83 = vertex(500, 550)
    v84 = vertex(500, 450)

    # list that holds all nodes
    vList = [startV, v11, v12, v13, v21, v22, v23, v24, v25, v31, v32, v33, v34, v41, v42, v43, v51, v52, v53, v54,
             v55, v56, v61, v62, v63, v64, v71, v72, v73, v74, v81, v82, v83, v84, endV]

    constraint = input()
    display.fill(white)
    createBackgroundP1()

    a = Astar(startV, endV, polyList, vList)
    a.calculate(createBackgroundP1, constraint)


def astarP2():
    # hard coded shapes
    poly1 = Polygon([(30, 10), (40, 10), (40, 200), (30, 200)])
    poly2 = Polygon([(0, 240), (300, 300), (0, 300)])
    poly3 = Polygon([(280, 10), (150, 150), (150, 90)])
    poly4 = Polygon([(970, 560), (970, 500), (900, 580)])
    poly5 = Polygon([(500, 200), (600, 200), (600, 400), (500, 400)])
    poly6 = Polygon([(320, 280), (450, 280), (450, 360), (320, 360)])
    poly7 = Polygon([(630, 0), (800, 0), (800, 380), (630, 380)])
    poly8 = Polygon([(300, 450), (300, 550), (850, 550), (850, 450)])
    # polyList
    polyList = [poly1, poly2, poly3, poly4, poly5, poly6, poly7, poly8]

    # vertexes
    # start
    startV = vertex(10, 10)
    # end
    endV = vertex(990, 590)
    # other
    v11 = vertex(30, 10)
    v12 = vertex(40, 10)
    v13 = vertex(40, 200)
    v14 = vertex(30, 200)
    v21 = vertex(0, 240)
    v22 = vertex(300, 300)
    v23 = vertex(0, 300)

    v31 = vertex(280, 10)
    v32 = vertex(150, 150)
    v33 = vertex(150, 90)
    v41 = vertex(970, 560)
    v42 = vertex(970, 500)
    v43 = vertex(900, 580)

    v51 = vertex(500, 200)
    v52 = vertex(600, 200)
    v53 = vertex(600, 400)
    v54 = vertex(500, 400)

    v61 = vertex(320, 280)
    v62 = vertex(450, 280)
    v63 = vertex(450, 360)
    v64 = vertex(320, 360)

    v71 = vertex(630, 0)
    v72 = vertex(800, 0)
    v73 = vertex(800, 380)
    v74 = vertex(630, 380)
    v81 = vertex(300, 450)
    v82 = vertex(300, 550)
    v83 = vertex(850, 550)
    v84 = vertex(850, 450)

    # list that holds all nodes
    vList = [startV, v11, v12, v13, v14, v21, v22, v23, v31, v32, v33, v41, v42, v43, v51, v52, v53, v54,
             v61, v62, v63, v64, v71, v72, v73, v74, v81, v82, v83, v84, endV]

    constraint = input()
    display.fill(white)
    createBackgroundP2()

    a = Astar(startV, endV, polyList, vList)
    a.calculate(createBackgroundP2, constraint)


# classes
class vertex(object):
    # constructor
    def __init__(self, x, y):
        self.x = x
        self.y = y


class node(object):
    # constructor
    def __init__(self, vertex0, parent, vertexS=0, vertexE=0):
        self.location = vertex0
        self.children = []
        self.hScore = 0
        self.gScore = 0
        self.fScore = 0
        if parent:
            self.path = parent.path[:]
            self.path.append(vertex0)
            self.start = parent.start
            self.end = parent.end
        else:
            self.start = vertexS
            self.end = vertexE
            self.path = [vertex0]

    def get_hScore(self):
        pass

    def get_gScore(self):
        pass


class nodeState(node):
    def __init__(self, vertex0, parent, vertexS=0, vertexE=0, ):
        super(nodeState, self).__init__(vertex0, parent, vertexS, vertexE)
        self.gScore = self.get_gScore()
        self.hScore = self.get_hScore()
        self.fScore = self.gScore + self.hScore

    # comparator for heapq
    def __lt__(self, other):
        return self.fScore < other.fScore

    def get_hScore(self):
        if self.location.x == self.end.x and self.location.y == self.end.y:
            return 0
        else:
            h = math.sqrt(math.pow(self.location.x - self.end.x, 2) + math.pow(self.location.y - self.end.y, 2))
            return h

    def get_gScore(self):
        if self.location.x == self.start.x and self.location.y and self.start.y:
            return 0
        else:  # complicated way of getting length by getting all lines and finding .length

            g = math.sqrt(math.pow(self.location.x - self.start.x, 2) + math.pow(self.location.y - self.start.y, 2))
            return g


# Astar class
class Astar:
    # constructor
    def __init__(self, start, end, polyList, vList):
        self.visitedQ = []
        self.openQ = []
        self.path = []
        self.start = start
        self.end = end
        self.polyList = polyList
        self.vList = vList
        heapq.heapify(self.openQ)

    def calculate(self, redraw, constraint):
        # a star formula
        # create start node
        startNode = nodeState(self.start, 0, self.start, self.end)
        # put start node into openQ
        heapq.heappush(self.openQ, startNode)
        while self.openQ:
            # set closesetChild = lowest fscore in openQ
            closesetChild = heapq.heappop(self.openQ)
            # get closesetChild children
            get_children(closesetChild, constraint, self.polyList, self.vList)
            # append closesetChild to visitedQ
            self.visitedQ.append((closesetChild.location.x, closesetChild.location.y))
            # cycle through closesetChild.children
            for child in closesetChild.children:
                # if child not int visitedQ
                if (child.location.x, child.location.y) not in self.visitedQ:
                    # draw path
                    display.fill(white)
                    redraw()
                    drawPath(child.path)
                    # for p in child.path:
                    #     print("childpath:", p.x, p.y)
                    # print(self.visitedQ)
                    # print("\n\n")
                    # if we reach the end vertex
                    if child.hScore == 0:
                        # return child.path
                        self.path = child.path
                        finish("Goal Reached")
                    # append child to openQ
                    heapq.heappush(self.openQ, child)
        finish("Failed")


# end classes

# visualization
pygame.init()
# colors
white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)
redlow = (200, 0, 0)
blue = (0, 0, 255)
bluelow = (0, 0, 200)
green = (0, 255, 0)
greenlow = (0, 200, 0)
cyan = (0, 255, 255)
yellow = (255, 255, 0)
purple = (255, 0, 255)
# fonts
smallText = pygame.font.Font("freesansbold.ttf", 20)
largeText = pygame.font.Font("freesansbold.ttf", 115)
# display
display = pygame.display.set_mode((1000, 600))
display.fill(white)
pygame.display.set_caption("A Star")

# main
startMenu()
# end prog
