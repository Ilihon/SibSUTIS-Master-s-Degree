import random
import math
import matplotlib.pyplot as plt

NODES_COUNT = 100
FAILS_MAX_COUNT = 15
MIN_NODE_DISTANCE = 5
MAX_NODE_DISTANCE = 150
MIN_CONNECTION_DISTANCE = 5
MAX_CONNECTION_DISTANCE = 100
maxdeg = 4

A = 1
B = 2
nodesList = []
distancesMatrix = []
edgesMatrix = [[0 for j in range(NODES_COUNT)] for i in range(NODES_COUNT)]


class CustomNode:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.deg = 0

    def show(self):
        print(self.x, ":", self.y)

    def toString(self):
        return str(self.x) + ":" + str(self.y)


class CustomPath:
    def __init__(self, dst, prob):
        self.dst = dst
        self.prob = prob

    def show(self):
        print(self.dst, " = ", self.prob)

    def toString(self):
        return str(self.dst) + " = " + str(self.prob)


def distance(x1, y1, x2, y2):
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)


def generateNodes():
    firstNode = CustomNode(random.uniform(0, 100), random.uniform(0, 100))
    nodesList.append(firstNode)

    generatedNodesCount = 1

    currentRootIndex = len(nodesList) - 1
    failsCount = 0
    while generatedNodesCount < NODES_COUNT:
        newX = random.uniform(max(0, nodesList[currentRootIndex].x - MAX_NODE_DISTANCE),
                              min(100, nodesList[currentRootIndex].x + MAX_NODE_DISTANCE))
        newY = random.uniform(max(0, nodesList[currentRootIndex].y - MAX_NODE_DISTANCE),
                              min(100, nodesList[currentRootIndex].y + MAX_NODE_DISTANCE))
        newNode = CustomNode(newX, newY)
        # print("NEW Coords: " + newNode.toString())

        isCorrectDistance = True
        # isCorrectDistance = False
        for tempNode in nodesList:
            tempDistance = distance(newNode.x, newNode.y, tempNode.x, tempNode.y)
            # print(currentRootIndex, generatedNodesCount, tempDistance)
            if tempDistance < MIN_NODE_DISTANCE or tempDistance > MAX_NODE_DISTANCE:
                isCorrectDistance = False
                break
            # if MIN_NODE_DISTANCE <= tempDistance <= MAX_NODE_DISTANCE:
            #     isCorrectDistance = True
            #     break

        if isCorrectDistance:
            nodesList.append(newNode)
            generatedNodesCount += 1
            currentRootIndex = len(nodesList) - 1
            failsCount = 0
        else:
            failsCount += 1
            if failsCount == FAILS_MAX_COUNT:
                currentRootIndex = max(0, currentRootIndex - 1)
                failsCount = 0


def calculateDistances():
    for i in range(NODES_COUNT):
        nodeI = nodesList[i]
        tempRow = []
        for j in range(NODES_COUNT):
            nodeJ = nodesList[j]
            tempDistance = distance(nodeI.x, nodeI.y, nodeJ.x, nodeJ.y)
            tempRow.append(tempDistance)
        distancesMatrix.append(tempRow)


def printMatrix(someMatrix):
    for row in someMatrix:
        for column in row:
            print("%5.2f" % column, end=" ")
        print()


def displayGraph(someColor, someAlpha):
    plt.axis([0, 101, 0, 101])

    # Рисуем точки
    xNodes = []
    yNodes = []
    for i in nodesList:
        xNodes.append(i.x)
        yNodes.append(i.y)
    plt.scatter(xNodes, yNodes, color='red')  # , alpha=1)
    '''for i in range(len(NODES_COUNT)):
        plt.annotate(xNodes, yNodes, NODES_COUNT[i])'''
    for i in range(NODES_COUNT):
        plt.text(xNodes[i] + 0.5, yNodes[i], i + 1)
        '''print("xNode",i, xNodes[i])
      print("yNode", i, yNodes[i])'''
    # print(NODES_COUNT)

    mdeg = 0
    # Рисуем рёбра графа
    for i in range(NODES_COUNT):
        for j in range(NODES_COUNT):
            if nodesList[i].deg < maxdeg:
                if edgesMatrix[i][j] == 1:
                    # firstNode = nodesList[i]
                    # secondNode = nodesList[j]
                    # x1 = firstNode.x
                    # x2 = secondNode.x
                    # y1 = firstNode.y
                    # y2 = secondNode.y
                    plt.plot([nodesList[i].x, nodesList[j].x], [nodesList[i].y, nodesList[j].y], color=someColor, alpha=someAlpha)
                    nodesList[i].deg += 1
                    nodesList[j].deg += 1
                    if nodesList[i].deg > mdeg:
                        mdeg = nodesList[i].deg

    # for i in range(NODES_COUNT):
    #   print("v[",i+1,"]", deg[i])
    print("Ограничение на степень: ", maxdeg)
    print("Максимальная степень вершины:", mdeg)
    print("Вершины с максимальной степенью: ", end=' ')
    for i in range(NODES_COUNT):
        if nodesList[i].deg == mdeg:
            print(i + 1, end="  ")
    plt.show()


def buildGraph(isExpFormula):
    rootNodeIndex = int(random.uniform(0, NODES_COUNT))
    print("RootNode: ", rootNodeIndex)
    paths = {}
    currNodeIndex = rootNodeIndex
    while len(paths.keys()) < NODES_COUNT - 1:
        currRow = distancesMatrix[currNodeIndex].copy()
        somePaths = []

        # Добавляем новую вершину
        for i in range(len(currRow)):
            if i not in paths.keys() and MIN_CONNECTION_DISTANCE <= currRow[i] <= MAX_CONNECTION_DISTANCE:
                if i != currNodeIndex:
                    newTempProb = 0
                    if isExpFormula:
                        newTempProb = math.pow(math.e, -A * math.pow(currRow[i], B))  # Вариант 1 (exp)
                        # print(newTempProb)
                    else:
                        newTempProb = 1 / math.pow(currRow[i], B)  # Вариант 2 (1/x)

                    tempPath = CustomPath(i, newTempProb)  # <nodeIndex, prob>
                    somePaths.append(tempPath)

        # Удаляем новую вершину из старых путей
        for someKey in paths.keys():
            someKeysPaths = paths.get(someKey)
            for j in someKeysPaths:
                if j.dst == currNodeIndex:
                    someKeysPaths.remove(j)
                    break

        paths.update({currNodeIndex: somePaths})

        # Нормализуем вероятности
        newTempProbsSum = 0
        for someKey in paths.keys():
            someKeysPaths = paths.get(someKey)
            for j in someKeysPaths:
                newTempProbsSum += j.prob

        newTestSum = 0
        for someKey in paths.keys():
            someKeysPaths = paths.get(someKey)
            for j in someKeysPaths:
                j.prob = j.prob / newTempProbsSum
                newTestSum += j.prob
        # print("SUM: ", newTestSum)

        newTestRand = random.uniform(0, 1)
        newTestCumulativeProb = 0
        isStop = False
        for someKey in paths.keys():
            someKeysPaths = paths.get(someKey)
            for j in someKeysPaths:
                newTestCumulativeProb += j.prob
                if newTestCumulativeProb >= newTestRand:
                    edgesMatrix[someKey][j.dst] = 1
                    currNodeIndex = j.dst
                    isStop = True
                    break
            if isStop:
                break
        # print("currNodeIndex: ", currNodeIndex)


if __name__ == '__main__':
    generateNodes()
    # for someNode in nodesList:
    #     someNode.show()

    calculateDistances()
    # printMatrix(distancesMatrix)

    # buildGraph(True)
    # displayGraph('magenta', 1)

    # edgesMatrix = [[0 for j in range(NODES_COUNT)] for i in range(NODES_COUNT)]

    buildGraph(False)
    displayGraph('orange', 1)

