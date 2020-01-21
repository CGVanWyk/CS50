from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    listA = a.split("\n")
    listB = b.split("\n")
    listSimilarities = []
    for i in listA:
        for j in listB:
            if i == j and j not in listSimilarities:
                listSimilarities.append(j)
    return listSimilarities

def sentences(a, b):
    """Return sentences in both a and b"""
    listA = sent_tokenize(a)
    listB = sent_tokenize(b)
    listSimilarities = []
    for i in listA:
        for j in listB:
            if i == j and j not in listSimilarities:
                listSimilarities.append(j)
    return listSimilarities

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    listSimilaritiesA = []
    for i in range(len(a) - n + 1):
        listSimilaritiesA.append(a[i:n + i])
    listA = listSimilaritiesA
    listSimilaritiesB = []
    for i in range(len(b) - n + 1):
        listSimilaritiesB.append(b[i:n + i])
    listB = listSimilaritiesB
    listSimilarities = []
    for i in listA:
        for j in listB:
            if i == j and j not in listSimilarities:
                listSimilarities.append(j)
    return listSimilarities