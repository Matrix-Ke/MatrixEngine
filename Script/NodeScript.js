const { dir } = require("console");
const fs = require("fs");
const path = require("path");
var util = require('util');
var iconv = require('iconv-lite');
const StringDecoder = require('node:string_decoder');
var encoding = require('encoding');

var dirname = "./Function";

function readFileList(dir, filesList = []) {
    const files = fs.readdirSync(dir);
    files.forEach((item, index) => {
        var fullPath = path.join(dir, item);
        const stat = fs.statSync(fullPath);
        if (stat.isDirectory()) {
            readFileList(path.join(dir, item), filesList);  //递归读取文件
        } else {
            filesList.push(fullPath);
        }
    });
}

function findPreIncludeRecursive(tarFlie, directory, preInclude = []) {
    const files = fs.readdirSync(directory);
    files.forEach(Element => {
        if (Element == tarFlie) {
            preInclude[0] = directory;
        }
        else {
            var fullPath = path.join(directory, Element);
            var fsStat = fs.statSync(fullPath);
            if (fsStat.isDirectory()) {
                findPreIncludeRecursive(tarFlie, fullPath, preInclude);
            }
        }
    })
}
function findFilePreInclude(tarFlie, directory) {
    var preInclude = [];
    findPreIncludeRecursive(tarFlie, directory, preInclude);
    var preStr = "";
    var result = "";
    preStr = preInclude[0];
    if (preStr) {
        // console.log(preStr);
        var temp = preStr.replaceAll('\\', '/');
        result = temp.replace("Function/", "");
    }
    return result;
}

const RegPatten = new RegExp("[\w]+.h", 'g','u');
var resultfiles = [];
var filename = "";

readFileList(dirname, resultfiles);


var preInclude = findFilePreInclude("SkyLight.h", dirname);
console.log(preInclude);


resultfiles.forEach((Element, index) => {
    var fileData = fs.readFileSync(Element, { encoding: "utf16le" });
    if (fileData) {
        var buffer = encoding.convert(fileData, "utf16le", "utf8");
        const str = buffer.toString("utf8")
        var matchList = str.match(RegPatten);

        // var str = fileData.toString({ encoding: "utf16le" });
        // matchList = str.match(RegPatten);
        var replaceStr = fileData;
        if (matchList) {
            matchList.forEach(regElement => {

                filename = regElement.replaceAll('"', "");
                // console.log(filename);
                preInclude = findFilePreInclude(filename, dirname);
                if (preInclude) {
                    var newSubstr = util.format('"%s/%s"', preInclude, filename);
                    var result = replaceStr.replaceAll(regElement, newSubstr);
                    replaceStr = result;
                } else {
                    if (preInclude == "") {
                        preInclude = findFilePreInclude(filename, "./Container");
                    }
                    if (preInclude == "") {
                        preInclude = findFilePreInclude(filename, "./Math");
                    }
                    if (preInclude == "") {
                        preInclude = findFilePreInclude(filename, "./Platform");
                    }
                    if (preInclude == "") {
                        preInclude = findFilePreInclude(filename, "./Primitive");
                    }

                    var newSubstr = util.format('"%s/%s"', preInclude, filename);
                    var result = replaceStr.replaceAll(regElement, newSubstr);
                    replaceStr = result;
                }
            })
            // 重新写入文件中
            var res = iconv.decode(replaceStr, "gbk");
            fs.writeFileSync(Element, res, { encoding: "utf16le" });
        }
    }
})


var fileData = fs.readFileSync("D:/GitDemo/MatrixEngine/Engine/Source/Runtime/Function/Core/Stream/Property.h", { encoding: "utf16le" });
var buffer = encoding.convert(fileData, "utf16le", "utf8");
const str = buffer.toString("utf8")
var matchStr = str.match(RegPatten);
console.log(matchStr);
// var str = fileData.replaceAll("matrix", "Engine");
// var to16Str = encoding.convert(str,  "utf8" ,"utf16le").toString("utf16le");
fs.writeFileSync("temp.h", str, { encoding: "utf16le" });

var fileData = fs.readFileSync("D:/GitDemo/MatrixEngine/Engine/Source/Runtime/Function/Core/Stream/Property.h",{ encoding: "utf16le" } );
// console.log(" fileData %d", fileData.length);
// var buffer = encoding.convert(fileData, "utf16le", "utf8");
// const str8 = buffer.toString("utf8")
var matchStr = fileData.match(/[\w]+.h/gu);
console.log(matchStr);


buffer = encoding.convert("a",  "utf8", "utf16");
const str16 = buffer.toString("utf16le")
// var matchStr = str16.match(RegPatten);
// console.log(" str: %d",str16.length);

var str = fileData.replaceAll(str16, "");
// var to16Str = encoding.convert(str,  "utf8" ,"utf16le").toString("utf16le");
// fs.writeFileSync("temp.h",  , { encoding: "utf16le" });