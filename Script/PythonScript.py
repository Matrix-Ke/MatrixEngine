from ast import main
from fileinput import filename
import re
import os


def readFileList(directory, fileList=[]):
    files = os.listdir(directory)
    for Element in files:
        fullpath = os.path.join(directory, Element)
        if os.path.isdir(fullpath):
            readFileList(fullpath, fileList)
        else:
            fileList.append(fullpath)



def findPreIncludeRecursive(targetFlie, directory, preInclude=[""]):
    files = os.listdir(directory)
    for Element in files:
        fulldir = os.path.join(directory, Element)
        if os.path.isfile(fulldir):
            if Element == targetFlie:
                preInclude[0] = directory
                return
        elif os.path.isdir(fulldir):
            findPreIncludeRecursive(targetFlie, fulldir, preInclude)


def findFilePreInclude(tarFlie, directory):
    preInclude = [""]
    findPreIncludeRecursive(tarFlie, directory, preInclude)
    preStr = preInclude[0]
    result = preStr
    if preStr:
        # console.log(preStr);
        # temp = preStr.replaceAll('\\', '/');
        # result = temp.replace("Function/", "");
        temp = re.sub('\\\\', '/', preStr)
        temp1 = re.sub("\\./", "", temp)
        if(re.search("Function/", temp1)):
            result = re.sub("Function/", "", temp1)
    return result





def Main(RegPatten, dirname):
    fileList = []
    readFileList(dirname, fileList)
    for file in fileList:
        fileSteam = open(file, mode = "w+")
        fileData = fileSteam.read()
        if fileData:
            matchList = re.findall(RegPatten, fileData)
            replaceStr = fileData
            if matchList:
                for regElement in matchList:
                    filename = re.sub('"', '', regElement)
                    preInclude = findFilePreInclude(filename, dirname)
                    if preInclude:
                        newSubStr = '"' + preInclude + '/' + filename + '"'
                        result = re.sub(regElement, newSubStr, replaceStr)
                        replaceStr = result
                    else:
                        if preInclude == '':
                            preInclude = findFilePreInclude(
                                filename, "./Container")
                        if preInclude == '':
                            preInclude = findFilePreInclude(filename, "./Math")
                        if preInclude == '':
                            preInclude = findFilePreInclude(
                                filename, "./Platform")
                        if preInclude == '':
                            preInclude = findFilePreInclude(
                                filename, "./Primitive")
                        newSubStr = '"' + preInclude + '/' + filename + '"'
                        result = re.sub(regElement, newSubStr, replaceStr)
                        replaceStr = result
            fileSteam.write(replaceStr)

RegPatten = r'"[\w]+.h"'
dirname = "./Function"
# Main(RegPatten, dirname)


# fileList= []
# readFileList(dirname, fileList)
# print (fileList)

# filename = "ASYNLoader.cpp"
# preInclude = findFilePreInclude(filename, dirname)
# print(preInclude)
# listname = ['']
# listname[0] = "kkk"
# listname[0] = "kkl"
# print(listname[0])

# curDir = os.curdir
# file = open("D:/GitDemo/MatrixEngine/Engine/Source/Runtime/Function/Asyn/ASYNLoader.cpp", mode='r+')
file = open("./Function\\Asyn\\ASYNLoader.cpp", mode='r+')
data = file.read()

pattern = r'"[\w]+.h"'
matchList = re.findall(pattern, data)

replaceStr = re.sub(pattern, "test.h", data)
file = open("./temp.h", 'w+')
file.write(replaceStr)
# print(curDir)
