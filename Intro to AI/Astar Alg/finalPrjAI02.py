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
def get_children(parent, polys=[], vlist=[]):
    # get kids of nodeState
    # if parent.children is empty
    if not parent.children:
        # cycle through vertex list(vList)
        for x in vList:
            # create line from parent to vertex
            testLine = LineString([(parent.location.x, parent.location.y), (x.x, x.y)])
            notChild = False
            # if x is parent location
            if x.x == parent.location.x and x.y == parent.location.y:
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
                    new = nodeState(parent.W, x, parent)
                    parent.children.append(new)


def createBackground():
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


def redraw(w, g, child):
    display.fill(white)
    drawG("W: ", w, 600, 530)
    drawG("G: ", g, 600, 550)
    createBackground()
    i = 0
    while i < len(child.path):
        if i == len(child.path) - 1:
            i += 2
        else:
            pygame.draw.line(display, purple, (child.path[i].x, child.path[i].y),
                             (child.path[i + 1].x, child.path[i + 1].y), 3)
            i += 1
    pygame.display.update()
    pygame.time.delay(5)


def drawG(txt, gg, x, y):
    text = smallText.render(str(txt) + str(gg), 1, black)
    display.blit(text, (x, y))


# classes
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

    def get_hScore(self):
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
        if self.location.x == self.end.x and self.location.y == self.end.y:
            return 0
        else:
            h = math.sqrt(math.pow(self.location.x - self.end.x, 2) + math.pow(self.location.y - self.end.y, 2))
            return h * w

    def get_gScore(self):
        if self.location.x == self.start.x and self.location.y and self.start.y:
            return 0
        else:  # complicated way of getting length by getting all lines and finding .length
            array = []
            for x in self.path:
                cx = str(x.x)
                cy = str(x.y)
                z = "(" + cx + ", " + cy + ")"
                array.append(eval(z))
            g = LineString(array).length
            return g


# Astar class
class Astar:
    # constructor
    def __init__(self, start, end):
        self.visitedQ = []
        self.openQ = []
        # self.path = []
        # self.fPath = []
        self.start = start
        self.end = end
        self.G = 100000000  # high number to get less then
        self.incumbent = start
        self.W = 100
        self.deltaW = 1
        self.bestW = 0
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
                print("current W:", self.W, "NEW G: ", self.G, "\n")
            else:
                print("newsol = none\n")
                # return self.incumbent
            self.W -= self.deltaW
            # update keys in open and prune nodes with g() + h() >= G
            # print("openQ1:")
            # for x in self.openQ:
            #     print(x.location.x, x.location.y, x.fScore, x.gScore)
            for z in self.openQ:
                z.hScore = z.get_hScore(self.W)
                z.fScore = z.gScore + z.hScore
                if z.gScore >= self.G:
                    print("remove: ", z.location.x, z.location.y, z.fScore, z.gScore)
                    self.openQ.remove(z)
            # print("\nopenQ2:")
            # for x in self.openQ:
            #     print(x.location.x, x.location.y, x.fScore, x.gScore)
        print("final return from alg 3")
        return self.incumbent

    def alg4(self):
        while self.openQ:
            # set closesetChild = lowest fscore in openQ
            closesetChild = heapq.heappop(self.openQ)
            # get closesetChild children
            get_children(closesetChild, polyList)
            # append closesetChild to visitedQ
            self.visitedQ.append(closesetChild)
            if self.G <= closesetChild.gScore:
                print("current W: ", self.W, "EXIT: G:", self.G, " < child.gScore: ", closesetChild.gScore)
                return None
            # cycle through closesetChild.children
            for child in closesetChild.children:
                # if child not in visitedQ
                # if child not in self.openQ:
                checker = 0
                for value in self.openQ:
                    if (child.location.x, child.location.y) == (value.location.x, value.location.y):
                        checker = 1
                if checker == 0:
                    redraw(self.W, self.G, child)
                    if child.gScore < self.G:
                        if child.hScore == 0:
                            # self.path = child.path
                            print("final gScore: ", child.gScore, "final fScore: ", child.fScore, "final hScore: ",
                                  child.hScore)
                            return child
                    heapq.heappush(self.openQ, child)
        return None

    def calculate(self):
        # a star formula
        # create start node
        startNode = nodeState(self.W, self.start, 0, self.start, self.end)
        # put start node into openQ
        self.alg3(startNode)



# end classes

# visualization
pygame.init()
# colors
white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)
blue = (0, 0, 255)
green = (0, 255, 0)
cyan = (0, 255, 255)
yellow = (255, 255, 0)
purple = (255, 0, 255)
# display
display = pygame.display.set_mode((1000, 600))
display.fill(white)
# pixAR = pygame.PixelArray(display)
pygame.display.set_caption("A Star")
smallText = pygame.font.Font("freesansbold.ttf", 20)
largeText = pygame.font.Font("freesansbold.ttf", 115)
# create background
createBackground()
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

# main
a = Astar(startV, endV)
a.calculate()

# this is the loop for drawing
while True:
    for event in pygame.event.get():
        # draw final path
        if event.type == QUIT:
            pygame.quit()
            exit()
        redraw(a.bestW, a.G, a.incumbent)
        # i = 0
        # while i < len(draw):
        #     if i == len(draw) - 1:
        #         i += 2
        #     else:
        #         pygame.draw.line(display, purple, (draw[i].x, draw[i].y),
        #                          (draw[i + 1].x, draw[i + 1].y), 3)
        #         i += 1
        pygame.display.update()
# end prog
