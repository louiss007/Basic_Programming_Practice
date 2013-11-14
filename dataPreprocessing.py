#!/usr/bin/python
#!-*- coding=utf-8 -*-

##############################################################################################
#Function:  These functions preprocess the data file that Other programs produced for further work, 
#           which is written by Python shell, many other useful python shells will be published in next time!
#Author:    ZhengFu
#Date:      20130808
#Copyright: All rights reserved!
#Version:   V1.0
##############################################################################################

import re,string,sys
reload(sys)
sys.setdefaultencoding('utf8')

################################################################################
## filterWav: This function extract file format like
##D:\ZhengFu\K009-test\test1800\channel1_1201_12011001.wav from the ref file.
################################################################################

def filterWav(list_file,result_file):
    fr=open(list_file,'rb')
    fw=open(result_file,'wb')
    lines=[]
    lines=fr.readlines()
    path="D:\\ZhengFu\\zh-CN-new-test1\\"   #According to the specific program, you can modify the path!!!
    form=".wav"
   
    for line in lines:
        s=line.split('\t')[-1]
        lenth=len(s)
        for i in range(lenth):
            if s[i]=='(':
                s_new=s.replace(s[i],path)
            if s[i]==')':
                s_new=s_new.replace(s[i],form)
        fw.write(s_new)

if __name__=="__main__":
    func=filterWav('realData_words.txt','result_file.txt')
   
#############################################################################
## splitFile: This function can split a whole into several pecieces
#############################################################################

def splitFile(filename):
    fn=filename.split(".")
    fr=open(filename)
    count=0
    i=0
    num=1
    listfile=fr.readlines()
    #listfile.sort()
    lines=len(listfile)
    while(lines>450):
        fw=open(fn[0]+"_"+str(num)+".list","ab")
        for i in range((num-1)*450,num*450):
            fw.write(listfile[i])
        num +=1
        i=0
        lines -=450
    if(lines<=450):
        fw=open(fn[0]+"_"+str(num)+".list","ab")
        for i in range(lines):
            fw.write(listfile[i])
    fr.close()
    fw.close()

if __name__=="__main__":
    file_name=raw_input("Please input filename:")   
    spf=splitFile(file_name)

################################################################################################################
## dataProcessing: This function extract file name and the recognition result from every line ,the format like
## D:\ZhengFu\speechOcean-test\speechOceanTest\Speaker0003_0000.wav 10月1日八点大巴准时出发前往河源 。 0.994428
## and the processing result format like this: 1 0 月 1 日 八 点 大 巴 准 时 出 发 前 往 河 源 (0003-0000)
#################################################################################################################

def dataProcessing(file_src):
    result_filename=[]
    result_speechrec=[]
    i=0
    fr=open(file_src,"rb")
##    fw=open(file_res,"ab")
    pattern=re.compile(r'(.+)\t(.+)\t(.+)')
    pattern_utf8=re.compile(u'[，。？！]')   #此处前缀用u,不能用r
    file_name_pattern=re.compile(r'\D+(\d+_\d+)\.wav')  #不同音频格式，正则表达式稍有不同，需自己修改！！！
    for line in fr:
        #print line
        line_format=re.match(pattern,line)    #去掉非语音识别结果行模式，返回所需模式
        if(line_format!=None):
            line_str=line_format.group()  #match()方法返回的是str对象
            line_list=line_str.split("\t")
            file_name=line_list[0].split("\\")[-1]
            file_name_new=re.search(file_name_pattern,file_name).group(1)
            file_name_new=file_name_new.replace(r'_','-')
##            file_speech_result_uni=unicode(line_list[1],"GBK") #此种方法(一)可行
            recog_result=re.sub(pattern_utf8,"",line_list[1].decode('GBK'))   #file_speech_result_uni)方法二;去掉中文标点
##            speech_result_len=len(match_obj_utf8) #Python可以求中文字符串长度
            for w in recog_result:
                recog_result= recog_result.replace(w,w+" ") #在每个汉字中间添加空格
            recog_result=re.sub(u"\s{2,}"," ",recog_result).strip()
##            recog_result=re.sub(r"$","\t",recog_result).replace('\t','    ')
            file_name_new=re.sub(r"$",")",re.sub(r"^","(",file_name_new))   #添加括号
            result_filename.append(file_name_new)
            result_speechrec.append(recog_result)
            print "%s\t%s" % (result_speechrec[i],result_filename[i])
            i += 1
        else:
            continue
 
    fr.close()
##    fw.close()

if __name__=="__main__":
    cn_result_file_name=raw_input("Please input the file to be preprocessed: ")
    dt=dataProcessing(cn_result_file_name)

#############################################################################################
## ideas: delete all the space in each line, and then add a space between words, 
## finally reduce more than one space between words to one space
## function: equal to ideas
##############################################################################################
def deleteSpace(filename):
    fr=open(filename,"rb")
    lines=fr.readlines()
    for line in lines:
    sentence=unicode(line.split('\t')[0].strip(),'utf-8')
    name=line.split('\t')[1].strip()
    #sentence_new=re.sub(r'\s+',"",sentence)
    #sentence=sentence.replace(" ","")
    name=re.sub(r'channel\d_','',name)
    name=re.sub('_','-',name)
    sentence=sentence.replace(u' ','')#louis@20130905 add this sentence, effeciency is enhanced more than 500000 times
    for w in sentence:
        sentence=sentence.replace(w,w+" ")
    sentence=re.sub(u'\s{2,}'," ",sentence)
    final_result=sentence.strip()+'\t'+name
    print final_result

    fr.close()

if __name__=='__main__':
    file_name=raw_input()
    dt=deleteSpace(file_name)