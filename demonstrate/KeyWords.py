'''
@author: Jing Chen
what I do:
what's my input:
what's my output:
'''

import os, sys
import string
import collections
from os import path
from sets import Set
from collections import defaultdict
from collections import OrderedDict
from wordcloud import WordCloud
import matplotlib.pyplot as plt

def read_doc_feature_list(doc_feature_file):
    doc_feature_list = []
    for line in open(doc_feature_file):
        doc_feature = defaultdict(int)
        print line.strip().split()[1:]
        for pair in line.strip().split()[1:]:
            print pair
            word, tf = pair.split(":")
            if doc_feature.has_key(word):
                print "multiple same key ! "
                assert False
            doc_feature[word] = int(tf)
        doc_feature_list.append(doc_feature)
    return doc_feature_list

def read_topic_doc_list(topic_file):
    topic_doc_list = []
    for line in open(topic_file, 'r'):
        docs = line.strip().split()
        if len(docs) <= 1:
            continue
        topic_doc_list.append([int(i)-1 for i in docs[1:]])
    return topic_doc_list

def get_topic_word(doc_feature_list, topic_doc_list, sort):
    word_df = defaultdict(Set)
    topic_word_list = []
    for topic_id in range(0, len(topic_doc_list)):
        topic_word = defaultdict(int)
        for doc_id in topic_doc_list[topic_id]:
            for word, tf in doc_feature_list[doc_id].items():
                topic_word[word] += tf
                word_df[word].add(topic_id)
        if sort:
            topic_word = OrderedDict(sorted(topic_word.items(), key=lambda t: t[1], reverse=True))
        topic_word_list.append(topic_word)
    return topic_word_list, word_df

def get_topic_keyword(k, word_df, topic_word_list):
    text_list = []
    topic_keyword_list = []
    for topic_id in range(0, len(topic_word_list)):
        text = ""
        topic_keyword = []
        k_count = 0
        for word, tf in topic_word_list[topic_id].items():
            # remove common words
            if len(word_df[word]) >= 0.3 * len(topic_word_list):
                continue

            topic_keyword.append((word, tf))
            for t in range(0, tf):
                text += word+" "
            k_count += 1
            if k_count >= k:
                topic_keyword_list.append(topic_keyword)
                text_list.append(text)
                break
    return topic_keyword_list, text_list

if __name__ == "__main__":

    year = sys.argv[1]
    doc_feature_file = "/Users/Jing/Documents/16Spring/10708/Project/pgm/data/Year/year"+year
    doc_feature_list = read_doc_feature_list(doc_feature_file)

    topic_file = "/Users/Jing/Documents/16Spring/10708/Project/pgm/out/clusterdd_"+year+".txt"
    topic_doc_list = read_topic_doc_list(topic_file)

    topic_word_list, word_df = get_topic_word(doc_feature_list, topic_doc_list, True)

    k = int(sys.argv[2])
    topic_keyword_list, text_list = get_topic_keyword(k, word_df, topic_word_list)

    for text in text_list:
        wordcloud = WordCloud().generate(text)
        plt.imshow(wordcloud)
        plt.axis("off")
        plt.show()

    # d = "/Users/Jing/Documents/16Spring/10708/Project/pgm/data/Year"
    # text = open(path.join(d, 'year1995')).read()
    # wordcloud = WordCloud().generate(text)
    # plt.imshow(wordcloud)
    # plt.axis("off")
    # plt.show()

    # text = open(path.join(d, 'year1996')).read()
    # wordcloud = WordCloud().generate(text)
    # plt.imshow(wordcloud)
    # plt.axis("off")
    # plt.show()





