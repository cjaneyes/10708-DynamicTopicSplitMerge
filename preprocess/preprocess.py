'''
@author: Jing Chen
what I do:
what's my input:
what's my output:
'''

import os, sys
import string
from collections import defaultdict

#  field = ["#*", "#@", "#year", "#conf", "#citation", "#index", "#arnetid", "#%", "#!", "holder"]
field = ["#year", "#index", "#conf", "#!", "holder"]
year = ["year1995", "year1996", "year1997", "year1998", "year1999"]

def preprocess(lines, cnt):
    item = {}
    if lines.find("#!") == -1:
        print cnt
        return None
    else:
        lines = lines.strip().split("\n")
    for l in lines:
        for f in field:
            if l.find(f) > -1:
                break
        if not f == "holder":
            # print f, l
            c = l.strip().split(f)[1]
            item[f] = c
    return item

def process(line):
    content = line.strip().lower()
    s = ""
    for c in content:
        if c in string.punctuation:
            c = " "
        s += c
    # content = ''.join([c for c in content if c not in string.punctuation])
    content = s
    return content

if __name__ == "__main__":
    lines = open("/Users/Jing/Documents/16Spring/10708/Project/pgm/data/acm_output.txt", 'r').readlines()
    year_group = defaultdict(list)

    paperString = ""
    cnt = 0
    for i in range(1, len(lines)):
        if lines[i] == "\n":
            item = preprocess(paperString, cnt)
            cnt += 1

            if cnt > 1470000:
            # if cnt > 1000:
                break

            if item == None:
                continue
            print "item ", item["#index"]

            for f, c in item.items():
                if f == "#year":
                    year_group[c].append(item)
                    break
            paperString = ""

        paperString += lines[i]

    for y, itemList in year_group.items():
        print y
        output = open("/Users/Jing/Documents/16Spring/10708/Project/pgm/data/RawYear/year"+str(y), 'w')
        for item in itemList:
            for f, c in item.items():
                # if y == "year2008":
                #     print f, c
                if f == "#!":
                    content = process(c)
                    output.write(content+" ")
                if f == "#conf":
                    if len(c.split()) > 1:
                        content = ''.join([i[0] for i in c.upper().split()])
                    else:
                        content = c.upper()
                    output.write(content+" ")
                # output.write("\n")
            output.write("\n")
        output.close()


    filePath = "/Users/Jing/Documents/16Spring/10708/Project/pgm/data/RawYear/"
    outputPath = "/Users/Jing/Documents/16Spring/10708/Project/pgm/data/Year/"
    dirs = os.listdir(filePath)

    year_doc_list = defaultdict(list)
    vocab = defaultdict(int)
    vocab_inex = 1

    for fn in dirs:
        if not fn in year:
            continue
        inFile = filePath+fn
        outFile = outputPath+fn
        f = open(inFile, 'r')
        docList = []
        for line in f:
            if line == "\n":
                continue
            content = line.strip().split()
            for w in content:
                if not vocab.has_key(w):
                    vocab[w] = vocab_inex
                    vocab_inex += 1
            docList.append(content)
        f.close()
        year_doc_list[fn] = docList

    for year, docList in year_doc_list.items():
        f_info = open(outputPath+year+".meta", 'w')
        f_info.write(str(len(docList))+" "+str(vocab_inex-1)+"\n")
        f_info.close()
        f = open(outputPath+year, 'w')
        f_sparse = open(outputPath+year+".sparse", 'w')
        doc_index = 0
        for doc in docList:
            doc_index += 1
            doc_info = defaultdict(int)
            for w in doc:
                doc_info[vocab[w]] += 1
            f.write(str(len(doc_info))+" ")
            for k, v in doc_info.items():
                f.write(str(k)+":"+str(v)+" ")
                f_sparse.write(str(doc_index)+" "+str(k)+" "+str(v)+"\n")
            f.write("\n")
        f.close()
        f_sparse.close()