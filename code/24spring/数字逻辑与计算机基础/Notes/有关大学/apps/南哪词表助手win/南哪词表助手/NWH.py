#!/usr/bin/env python
# -*- coding: utf-8 -*-

# python 3.6.8
# pyinstaller 4.9


import tkinter as tk
import tkinter.font as tkFont
from PIL import Image, ImageTk
import time
from pygame import mixer  # pygame 1.9.6
import random


# 创建组件


def createtitle(frame, text, columnspan=1, height=2):
    '''create a title'''

    title = tk.Label(frame, text=text, font=tkFont.Font(
        family='微软雅黑', size=rootheight // 22, weight=tkFont.BOLD), fg='purple', height=height)
    title.grid(row=0, column=0, columnspan=columnspan)


def createlabel(frame, location, text, columnspan=1, padx=0, pady=0, size='middle', style=0, width='auto'):
    '''create a label'''

    if size == 'small':
        s = rootheight // 55
    elif size == 'middle':
        s = rootheight // 44
    else:
        s = rootheight // 33

    label = tk.Label(frame, text=text, font=('微软雅黑', s))
    label.grid(row=location[0], column=location[1],
               columnspan=columnspan, padx=padx, pady=pady)

    if style == 1:
        label['fg'] = 'purple'
    elif style == 2:
        label['fg'] = 'red'

    if width != 'auto':
        label['width'] = width
        label['anchor'] = 'w'


def createbutton(frame, style, location, text=None, image=None, command=None, columnspan=1, padx=0, pady=0, compound='top', bd=0, width='auto', size='big'):
    '''create a button'''

    button = tk.Button(frame, text=text, image=image, font=('微软雅黑', rootheight // 44 if size ==
                       'big' else rootheight // 55), bd=bd, command=command, compound=compound, relief='solid', cursor='hand2')
    button.grid(row=location[0], column=location[1],
                columnspan=columnspan, padx=padx, pady=pady)

    if width != 'auto':
        button['width'] = width

    if style == 0:
        button['fg'] = button['activeforeground'] = 'purple'
    elif style == 1:
        button['fg'] = button['activeforeground'] = 'white'
        button['bg'] = button['activebackground'] = 'purple'
    elif style == 2:
        button['fg'] = button['activeforeground'] = 'purple'
        button['bg'] = button['activebackground'] = 'silver'
        if mode == '检测':
            button['state'] = 'disable'
            button['cursor'] = 'arrow'
    elif style == 3:
        button['bg'] = button['activebackground'] = 'gold'
    elif style == 4:
        button['bg'] = button['activebackground'] = 'plum'
    elif style == 5:
        button['fg'] = 'purple'
        button['activebackground'] = 'purple'
        button['activeforeground'] = 'white'
    elif style == 6:
        button['state'] = 'disable'
        button['cursor'] = 'arrow'
        button['bg'] = button['activebackground'] = 'silver'


def createentry(frame, location):
    '''create an entry'''

    global entry

    entry = tk.Entry(frame, textvariable=tk.StringVar, font=(
        '微软雅黑', rootheight // 44), relief='solid')
    entry.grid(row=location[0], column=location[1])
    entry.delete(0, tk.END)
    entry.focus_set()
    entry.bind('<Return>', changequestion)


def createscrollbar(frame):
    '''create a scrollbar'''

    global scrollbar

    scrollbar = tk.Scrollbar(frame, command=text.yview)
    text.config(yscrollcommand=scrollbar.set)
    scrollbar.pack(side='left', fill='y')


def createtext(frame, width, height, size='small', font='微软雅黑', fg='black'):
    '''create a text'''

    global text

    text = tk.Text(frame, width=width, height=height, font=(font, rootheight // 55 if size ==
                   'small' else (rootheight // 44 if size == 'middle' else rootheight // 25)), bd=0, bg='#F0F0F0', fg=fg)
    text.pack(side='left', fill='y')


# 界面切换


def changeframe(oldframe, new, reset=False):
    '''change frame'''

    if reset == True:
        global number
        number = 1

    oldframe.destroy()
    new()


def changeword(text):
    '''change word'''

    global number

    if text == 'next':
        if number == min(len(words[level]) - (unit - 1) * 25, 25):
            number = 1
        else:
            number += 1
    else:
        if number == 1:
            number = min(len(words[level]) - (unit - 1) * 25, 25)
        else:
            number -= 1

    learnframe.destroy()
    learn()


def changequestion(event):
    '''things to do when return key is pressed'''

    global number

    if questions == 0:
        CtoEans[questionlist.index(testlist[number - 1])] = entry.get()
    elif questions == 1:
        LandWans[questionlist.index(testlist[number - 1])] = entry.get()
    elif questions == 2:
        EtoCans[questionlist.index(testlist[number - 1])] = entry.get()

    if number == len(testlist):
        number = 1
    else:
        number += 1

    if questions == 0:
        changeframe(CtoEframe, CtoE if number != 1 else LandW)
    elif questions == 1:
        changeframe(LandWframe, LandW if number != 1 else (
            Fill if settings[1][1] == 'Fill' else Choose))
    elif questions == 2:
        changeframe(Fillframe, Fill if number != 1 else marks)


def changelevel(l):
    '''things to do when a level button is clicked'''

    global level
    level = l

    if mode == '学习':
        changeframe(wordlistframe, wordlist)
    else:
        changeframe(mistakeframe, mistake)


def changehelper(item):
    '''things to do when a helper item button is clicked'''

    global helperitem
    helperitem = item

    changeframe(helperframe, helper)


# 信息读写


def readwordlist():
    '''read wordlists and dispose them'''

    global words

    words = {}.fromkeys(['a', 'b'])
    for i in words.keys():
        with open('lib/' + i + 'levelwords.cfg', encoding='utf-8') as fp:
            words[i] = fp.readlines()
            for j in range(len(words[i])):
                words[i][j] = words[i][j].split()
                for k in range(1, 4):
                    words[i][j][k] = words[i][j][k].replace('_', ' ')


def readrecord():
    '''read records and dispose them'''

    global records
    records = {}.fromkeys(['a', 'b'])

    for i in records.keys():
        with open('data/' + i + 'record.cfg') as fp:
            records[i] = fp.readlines()
            for j in range(len(records[i])):
                records[i][j] = records[i][j].split()


def readsetting():
    '''read settings and dispose them'''

    global settings, language, languagecode

    with open('data/setting.cfg', encoding='utf-8') as settings:
        settings = settings.readlines()
        for i in range(len(settings)):
            settings[i] = settings[i].split()

    language = settings[0][1]
    languagecode = 0 if settings[0][1] == 'uk' else 1


def readhelper():
    '''read helper and dispose them'''

    global helpers

    with open('data/helper.cfg', encoding='utf-8') as helpers:
        helpers = helpers.readlines()
        for i in range(len(helpers)):
            helpers[i] = [helpers[i].split()[0], '\n'.join(
                helpers[i].split()[1:]).replace('_', ' ')]


def writerecord():
    '''dispose data and write in records'''

    nowtime = int(time.time())
    for i in range(len(testlist)):
        records[level][questionlist[i]].append(
            str(nowtime) + str(CtoEans[i]) + str(LandWans[i]) + str(EtoCans[i]))
    for j in range(len(records[level])):
        records[level][j] = ' '.join(records[level][j]) + '\n'

    with open('data/' + level + 'record.cfg', 'w') as fp:
        fp.writelines(records[level])


# 按钮事件


def homeclk(j):
    '''things to do when a button on home page is clicked'''

    if j == 0:
        learnclk()
    elif j == 1:
        testclk()
    elif j == 2:
        mistakeclk()
    elif j == 3:
        wordlistclk()
    elif j == 4:
        settingclk()
    else:
        helperclk()


def learnclk():
    '''things to do when learn button is clicked'''

    global mode
    mode = '学习'

    readwordlist()
    readrecord()
    readsetting()

    changeframe(homeframe, units)


def testclk():
    '''things to do when test button is clicked'''

    global mode
    mode = '检测'

    readwordlist()
    readrecord()
    readsetting()

    changeframe(homeframe, units)


def mistakeclk():
    '''things to do when mistake button is clicked'''

    global level
    level = 'a'

    readwordlist()
    readsetting()

    changeframe(homeframe, mistake)


def wordlistclk():
    '''things to do when wordlist button is clicked'''

    global level
    level = 'a'

    readwordlist()
    readsetting()

    changeframe(homeframe, wordlist)


def settingclk():
    '''things to do when setting button is clicked'''

    readsetting()

    changeframe(homeframe, setting)


def helperclk():
    '''things to do when helper button is clicked'''

    global helperitem

    readhelper()
    helperitem = 0
    changeframe(homeframe, helper)


def unitclk(u, l):
    '''things to do when a unit button is clicked'''

    global unit, level, number, testlist, questionlist
    unit = u
    level = l
    number = 1
    testlist = list(range((unit - 1) * 25, min(unit * 25, len(words[level]))))
    questionlist = testlist.copy()

    if mode == '学习':
        changeframe(unitsframe, learn)
    else:
        changeframe(unitsframe, CtoE)


def soundclk(wordnumber):
    '''things to do when sound button is clicked'''

    mixer.init()
    mixer.music.load('sound/' + words[level]
                     [wordnumber][0] + '_' + language + '.mp3')
    mixer.music.play()


def settingsclk(key, value):
    '''things to do when a setting button is clicked'''

    global settings

    settings[key][1] = value
    changeframe(settingframe, setting)

    with open('data/setting.cfg', 'w') as fp:
        settinglist = [0] * 4
        for i in range(4):
            settinglist[i] = ' '.join(settings[i]) + '\n'
        fp.writelines(settinglist)


def meaningclk(i):
    '''things to do when a meaning button is clicked'''

    global number

    EtoCans[questionlist.index(testlist[number - 1])
            ] = words[level][optionslist[i]][1]
    if number == len(testlist):
        number = 1
    else:
        number += 1
    changeframe(Chooseframe, Choose if number != 1 else marks)


def displaynju():
    '''display nju anniversary text, 彩蛋相关请跳过'''

    global char

    if char == len(njutext):
        return
    else:
        text.insert(tk.END, njutext[char])
        char += 1
        text.after(100, displaynju)


# 界面创建


def nju():
    '''enter nju anniversary page, 彩蛋相关请跳过'''

    global njuframe, njutext, char

    njuframe = tk.Frame(root)
    njuframe.pack()
    njusub = tk.Frame(njuframe)
    njusub.grid(row=0, column=0, pady=rootheight // 12)
    createtext(njusub, 48, 12, size='big', font='楷体', fg='purple')
    njutext = '    金陵故地，南京新城。钟山毓秀，大江恢宏。历百廿之光阴，诚耀四海；经十纪之风雨，雄绝八方。广宇微子，穷万物之根本；古今中外，传千载之辞章。集天下之英才，汇于南大；聚当世之俊杰，盛举共襄。\n    起于三江，成乎中央。二源汇流，一泻汪洋。昏昏其世，举民主之旗帜；衰衰其国，望百姓之安康。昭昭其志，求民族之复兴；敦敦其行，谋国家之富强。承前启后，立新世之潮峰；继往开来，谱吾辈之华章。\n    翠林青瓦，证鼓楼之雄厚；缓丘低峦，彰仙林之静朴。隔江而眺，忆浦口之旧事；顺江而下，观姑苏之新篇。双城四校，各具千秋；并力而前，奔涌磅礴。\n    壬寅三至，轮回复始。戮力同心，勇创一流！'
    char = 0
    displaynju()
    createbutton(njuframe, 1, (1, 0), text='进入',
                 command=lambda: changeframe(njuframe, home))

    mixer.init()
    mixer.music.load('sound/nju.mp3')
    mixer.music.play(loops=120)


def home():
    '''enter home page'''

    global homeframe, learnpic, testpic, mistakepic, wordlistpic, settingpic, helperpic

    if year == 2022 and day == 'anniversary':
        mixer.music.stop()
    homeframe = tk.Frame(root)
    homeframe.pack()
    createtitle(homeframe, '南哪词表助手', 3)

    learnpic = Image.open('image/learn.png')
    learnpic = learnpic.resize([rootheight // 8] * 2, Image.ANTIALIAS)
    learnpic = ImageTk.PhotoImage(learnpic)

    testpic = Image.open('image/test.png')
    testpic = testpic.resize([rootheight // 8] * 2, Image.ANTIALIAS)
    testpic = ImageTk.PhotoImage(testpic)

    mistakepic = Image.open('image/mistake.png')
    mistakepic = mistakepic.resize([rootheight // 8] * 2, Image.ANTIALIAS)
    mistakepic = ImageTk.PhotoImage(mistakepic)

    wordlistpic = Image.open('image/wordlist.png')
    wordlistpic = wordlistpic.resize([rootheight // 8] * 2, Image.ANTIALIAS)
    wordlistpic = ImageTk.PhotoImage(wordlistpic)

    settingpic = Image.open('image/setting.png')
    settingpic = settingpic.resize([rootheight // 8] * 2, Image.ANTIALIAS)
    settingpic = ImageTk.PhotoImage(settingpic)

    helperpic = Image.open('image/helper.png')
    helperpic = helperpic.resize([rootheight // 8] * 2, Image.ANTIALIAS)
    helperpic = ImageTk.PhotoImage(helperpic)

    locationlist = [(1, 0), (1, 1), (1, 2), (2, 0), (2, 1), (2, 2)]
    textlist = ['学习', '检测', '错题', '词表', '设置', '帮助']
    imagelist = [learnpic, testpic, mistakepic,
                 wordlistpic, settingpic, helperpic]

    for i in range(6):
        createbutton(homeframe, 0, locationlist[i], text=textlist[i], image=imagelist[i], command=lambda j=i: homeclk(
            j), padx=rootheight // 8 + + (rootwidth - rootheight * 1.25) // 12, pady=rootheight // 20)


def units():
    '''enter units page'''

    global unitsframe

    unitsframe = tk.Frame(root)
    unitsframe.pack()
    createtitle(unitsframe, mode, 10)

    createlabel(unitsframe, (1, 0), 'A级词',
                columnspan=10, pady=rootheight // 400)
    for i in range(0, len(words['a']) // 250 + 1):
        for j in range(10 if (i + 1) * 250 < len(words['a']) else len(words['a']) % 250 // 25 + 1):
            createbutton(unitsframe, givestyle(10 * i + (j + 1), 'a'), (i + 2, j), 'Unit ' + '{:0>2d}'.format(10 * i + (
                j + 1)), command=lambda unit=10 * i + j + 1: unitclk(unit, 'a'), padx=rootheight // 300 + (rootwidth - rootheight * 1.25) // 40, pady=rootheight // 300)

    l = i + 2
    createlabel(unitsframe, (l + 1, 0), 'B级词',
                columnspan=10, pady=rootheight // 300)
    for i in range(l, l + len(words['b']) // 250 + 1):
        for j in range(10 if (i + 1 - l) * 250 < len(words['b']) else len(words['b']) % 250 // 25 + 1):
            createbutton(unitsframe, givestyle(10 * (i - l) + (j + 1), 'b'), (i + 2, j), 'Unit ' + '{:0>2d}'.format(10 * (i - l) + (j + 1)), command=lambda unit=10 * (
                i - l) + j + 1: unitclk(unit, 'b'), padx=rootheight // 300 + (rootwidth - rootheight * 1.25) // 40, pady=rootheight // 300)

    createbutton(unitsframe, 1, (i + 3, 4), text='返回', command=lambda: changeframe(
        unitsframe, home), columnspan=2, pady=rootheight // 300)


def learn():
    '''enter learn page'''

    global learnframe, soundpic, wordnumber

    learnframe = tk.Frame(root)
    learnframe.pack()
    createtitle(learnframe, 'Unit ' + '{:0>2d}'.format(unit), columnspan=4)

    soundpic = Image.open('image/sound.png')
    soundpic = soundpic.resize([rootheight // 25] * 2, Image.ANTIALIAS)
    soundpic = ImageTk.PhotoImage(soundpic)
    wordnumber = (unit - 1) * 25 + number - 1
    meaning = '  '.join(words[level][wordnumber][4: 0: -3])

    createlabel(learnframe, (1, 0), '{:0>2d}'.format(number) + '/' + '{:0>2d}'.format(
        min(unit * 25, len(words[level])) - (unit - 1) * 25) + '\n\n\n\n', columnspan=4)
    createlabel(learnframe, (2, 0),
                words[level][wordnumber][0], columnspan=4, size='big')
    createbutton(learnframe, 7, (3, 0), text=words[level][wordnumber][languagecode + 2] + '  ',
                 image=soundpic, command=lambda: soundclk(wordnumber), columnspan=4, compound='right')
    createlabel(learnframe, (4, 0), meaning + '\n\n\n\n\n', columnspan=4)
    createbutton(learnframe, 1, (5, 0), text='上个',
                 command=lambda: changeword('last'), padx=rootheight // 30)
    createbutton(learnframe, 1, (5, 1), text='下个',
                 command=lambda: changeword('next'), padx=rootheight // 30)
    createbutton(learnframe, 1 if givestyle(unit, level) != 2 else 6, (5, 2), text='检测',
                 command=lambda: changeframe(learnframe, CtoE, reset=True), padx=rootheight // 30)
    createbutton(learnframe, 1, (5, 3), text='返回', command=lambda: changeframe(
        learnframe, units), padx=rootheight // 30)


def CtoE():
    '''enter translate Chinese to English page'''

    global CtoEframe, wordnumber, questions

    if number == 1:
        global CtoEans
        random.shuffle(testlist)
        questions = 0
        CtoEans = [0] * len(testlist)

    CtoEframe = tk.Frame(root)
    CtoEframe.pack()
    createtitle(CtoEframe, '汉译英')

    wordnumber = testlist[number - 1]
    meaning = '  '.join(words[level][wordnumber][4: 0: -3])

    createlabel(CtoEframe, (1, 0), '{:0>2d}'.format(
        number) + '/' + '{:0>2d}'.format(len(testlist)) + '\n\n\n\n\n')
    createlabel(CtoEframe, (2, 0), meaning + '\n')
    createentry(CtoEframe, (3, 0))


def LandW():
    '''enter listen and write words page'''

    global LandWframe, wordnumber, questions, soundpic

    if number == 1:
        global LandWans
        random.shuffle(testlist)
        questions = 1
        LandWans = [0] * len(testlist)

    LandWframe = tk.Frame(root)
    LandWframe.pack()
    createtitle(LandWframe, '听音默写')

    wordnumber = testlist[number - 1]
    soundpic = Image.open('image/sound.png')
    soundpic = soundpic.resize([rootheight // 25] * 2, Image.ANTIALIAS)
    soundpic = ImageTk.PhotoImage(soundpic)

    createlabel(LandWframe, (1, 0), '{:0>2d}'.format(
        number) + '/' + '{:0>2d}'.format(len(testlist)) + '\n\n\n\n')
    createbutton(LandWframe, 0, (2, 0), text='\n', image=soundpic,
                 command=lambda: soundclk(wordnumber))
    createentry(LandWframe, (3, 0))
    soundclk(wordnumber)


def Fill():
    '''enter fill in blanks page'''

    global Fillframe, wordnumber, questions

    if number == 1:
        global EtoCans
        random.shuffle(testlist)
        questions = 2
        EtoCans = [0] * len(testlist)

    Fillframe = tk.Frame(root)
    Fillframe.pack()
    createtitle(Fillframe, '英译汉')

    wordnumber = testlist[number - 1]

    createlabel(Fillframe, (1, 0), '{:0>2d}'.format(
        number) + '/' + '{:0>2d}'.format(len(testlist)) + '\n\n\n\n\n')
    createlabel(Fillframe, (2, 0), words[level]
                [wordnumber][0] + '\n', size='big')
    createentry(Fillframe, (3, 0))


def Choose():
    '''enter choose write answer page'''

    global Chooseframe, wordnumber, questions, optionslist

    if number == 1:
        global EtoCans
        random.shuffle(testlist)
        questions = 3
        EtoCans = [0] * len(testlist)

    Chooseframe = tk.Frame(root)
    Chooseframe.pack()
    createtitle(Chooseframe, '英译汉')

    wordnumber = testlist[number - 1]
    removedlist = list(range((wordnumber // 25) * 25,
                       min((wordnumber // 25 + 1) * 25, len(words[level]))))
    removedlist.remove(wordnumber)
    others = random.sample(removedlist, 3)
    optionslist = others + [wordnumber]
    random.shuffle(optionslist)

    createlabel(Chooseframe, (1, 0), '{:0>2d}'.format(
        number) + '/' + '{:0>2d}'.format(len(testlist)) + '\n\n\n')
    createlabel(Chooseframe, (2, 0),
                words[level][wordnumber][0] + '\n', size='big')
    options = 'ABCD'
    for i in range(len(optionslist)):
        createbutton(Chooseframe, 5, (i + 3, 0), text=options[i] + ' ' + words[level][optionslist[i]]
                     [1], command=lambda j=i: meaningclk(j), pady=rootheight // 200, bd=1, width=30)


def marks():
    '''enter marks page'''

    givemarks()
    marksframe = tk.Frame(root)
    marksframe.pack()
    createtitle(marksframe, ' \n得分\n\n' + str(sum(CtoEans) + sum(LandWans) +
                sum(EtoCans)) + '/' + str(len(testlist) * 4) + '\n', columnspan=2, height=4)
    markssub = tk.Frame(marksframe)
    markssub.grid(row=1, column=0, columnspan=2)
    createtext(markssub, 100, 14, size='small')
    createscrollbar(markssub)

    marksson = tk.Frame(text)
    for a in range(5):
        createlabel(marksson, (0, a * 4), '        单词        ', size='small',
                    pady=rootheight // 55, padx=(rootwidth - rootheight * 1.25) // 80, style=1)
        createlabel(marksson, (0, a * 4 + 1), ' 得分 ', columnspan=3, pady=rootheight //
                    55, padx=(rootwidth - rootheight * 1.25) // 80, size='small', style=1)

    for b in range(len(testlist)):
        createlabel(marksson, (b // 5 + 1, (b % 5) * 4), words[level][questionlist[b]][0], size='small',
                    pady=rootheight // 55, style=1 if CtoEans[b] + LandWans[b] + EtoCans[b] == 4 else 2)
        createlabel(marksson, (b // 5 + 1, (b % 5) * 4 + 1),
                    CtoEans[b], size='small', pady=rootheight // 55)
        createlabel(marksson, (b // 5 + 1, (b % 5) * 4 + 2),
                    LandWans[b], size='small', pady=rootheight // 55)
        createlabel(marksson, (b // 5 + 1, (b % 5) * 4 + 3),
                    EtoCans[b], size='small', pady=rootheight // 55)
    text.window_create(tk.END, window=marksson)

    createbutton(marksframe, 1, (2, 0), text='返回', command=lambda: changeframe(
        marksframe, home), pady=rootheight // 22)
    createbutton(marksframe, 1, (2, 1), text='错题', command=lambda: changeframe(
        marksframe, mistake), pady=rootheight // 22)
    writerecord()


def mistake():
    '''enter mistake page'''

    global mistakeframe, soundpic, number, testlist, questionlist, mode
    number = 1
    mode = '检测'
    readrecord()

    soundpic = Image.open('image/sound.png')
    soundpic = soundpic.resize([rootheight // 25] * 2, Image.ANTIALIAS)
    soundpic = ImageTk.PhotoImage(soundpic)

    mistakeframe = tk.Frame(root)
    mistakeframe.pack()
    createtitle(mistakeframe, '\n错题\n', columnspan=2)
    createbutton(mistakeframe, level == 'a', (1, 0), text='A级词',
                 command=lambda: changelevel('a'), bd=1, width=30)
    createbutton(mistakeframe, level == 'b', (1, 1), text='B级词',
                 command=lambda: changelevel('b'), bd=1, width=30)
    mistakesub = tk.Frame(mistakeframe)
    mistakesub.grid(row=2, column=0, columnspan=2, pady=rootheight // 25)
    createtext(mistakesub, 60, 12, size='middle')
    createscrollbar(mistakesub)

    testlist = []
    for i in range(len(words[level])):
        if len(records[level][i]) != 0 and records[level][i][-1][-3:] != '112' and records[level][i][-1][-3:] != '211':
            testlist.append(i)

    for i in testlist:
        meaning = '  '.join(words[level][i][4: 0: -3])

        text.insert(tk.END, ' '.join(
            [words[level][i][0], words[level][i][languagecode + 2], meaning]) + '  ')
        soundbutton = tk.Button(
            text, image=soundpic, bd=0, command=lambda j=i: soundclk(j), cursor='hand2')
        text.window_create(tk.END, window=soundbutton)
        text.insert(tk.END, '\n')

    text['state'] = 'disable'
    questionlist = testlist.copy()

    createbutton(mistakeframe, 1 if testlist != [] else 2, (3, 0), text='检测',
                 command=lambda: changeframe(mistakeframe, CtoE), pady=rootheight // 50)
    createbutton(mistakeframe, 1, (3, 1), text='返回', command=lambda: changeframe(
        mistakeframe, home), pady=rootheight // 50)


def wordlist():
    '''enter wordlist page'''

    global wordlistframe, mode, soundpic
    mode = '学习'

    soundpic = Image.open('image/sound.png')
    soundpic = soundpic.resize([rootheight // 31] * 2, Image.ANTIALIAS)
    soundpic = ImageTk.PhotoImage(soundpic)

    wordlistframe = tk.Frame(root)
    wordlistframe.pack()
    createtitle(wordlistframe, '\n词表\n', columnspan=2)
    createbutton(wordlistframe, level == 'a', (1, 0), text='A级词',
                 command=lambda: changelevel('a'), bd=1, width=32)
    createbutton(wordlistframe, level == 'b', (1, 1), text='B级词',
                 command=lambda: changelevel('b'), bd=1, width=30)
    wordlistsub = tk.Frame(wordlistframe)
    wordlistsub.grid(row=2, column=0, columnspan=2, pady=rootheight // 25)

    createtext(wordlistsub, 80, 15)
    createscrollbar(wordlistsub)

    for i in range(len(words[level])):
        meaning = '  '.join(words[level][i][4: 0: -3])
        text.insert(tk.END, ' '.join(
            [words[level][i][0], words[level][i][languagecode + 2], meaning]) + '  ')
        soundbutton = tk.Button(
            text, image=soundpic, bd=0, command=lambda j=i: soundclk(j), cursor='hand2')
        text.window_create(tk.END, window=soundbutton)
        text.insert(tk.END, '\n')

    text['state'] = 'disable'
    createbutton(wordlistframe, 1, (3, 0), text='返回',
                 command=lambda: changeframe(wordlistframe, home), columnspan=2)


def setting():
    '''enter setting page'''

    global settingframe

    settingframe = tk.Frame(root)
    settingframe.pack()
    createtitle(settingframe, '\n设置\n', columnspan=4)

    createlabel(settingframe, (1, 0), '单词音标和音频所使用的语言', columnspan=4,
                style=1, width=60, pady=rootheight // 50)
    createbutton(settingframe, settings[0][1] == 'uk', (2, 0), text='英式英语',
                 command=lambda: settingsclk(0, 'uk'), bd=1, width=10, size='small')
    createbutton(settingframe, settings[0][1] == 'en', (2, 1), text='美式英语',
                 command=lambda: settingsclk(0, 'en'), bd=1, width=10, size='small')

    createlabel(settingframe, (3, 0), '英译汉的检测题型', columnspan=4,
                style=1, width=60, pady=rootheight // 50)
    createbutton(settingframe, settings[1][1] == 'Choose', (4, 0), text='选择题',
                 command=lambda: settingsclk(1, 'Choose'), bd=1, width=10, size='small')
    createbutton(settingframe, settings[1][1] == 'Fill', (4, 1), text='填空题',
                 command=lambda: settingsclk(1, 'Fill'), bd=1, width=10, size='small')

    createlabel(settingframe, (5, 0), '同一单词第一和第二次检测的最小时间间隔',
                columnspan=4, style=1, width=60, pady=rootheight // 50)
    createbutton(settingframe, settings[2][1] == '10800', (6, 0), text='3小时',
                 command=lambda: settingsclk(2, '10800'), bd=1, width=10, size='small')
    createbutton(settingframe, settings[2][1] == '21600', (6, 1), text='6小时',
                 command=lambda: settingsclk(2, '21600'), bd=1, width=10, size='small')
    createbutton(settingframe, settings[2][1] == '43200', (6, 2), text='12小时',
                 command=lambda: settingsclk(2, '43200'), bd=1, width=10, size='small')
    createbutton(settingframe, settings[2][1] == '86400', (6, 3), text='24小时',
                 command=lambda: settingsclk(2, '86400'), bd=1, width=10, size='small')

    createlabel(settingframe, (7, 0), '认定单词已掌握所需的最少正确回答次数',
                columnspan=4, style=1, width=60, pady=rootheight // 50)
    createbutton(settingframe, settings[3][1] == '4', (8, 0), text='4次',
                 command=lambda: settingsclk(3, '4'), bd=1, width=10, size='small')
    createbutton(settingframe, settings[3][1] == '5', (8, 1), text='5次',
                 command=lambda: settingsclk(3, '5'), bd=1, width=10, size='small')
    createbutton(settingframe, settings[3][1] == '6', (8, 2), text='6次',
                 command=lambda: settingsclk(3, '6'), bd=1, width=10, size='small')
    createbutton(settingframe, settings[3][1] == '7', (8, 3), text='7次',
                 command=lambda: settingsclk(3, '7'), bd=1, width=10, size='small')

    createbutton(settingframe, 1, (9, 0), text='返回', command=lambda: changeframe(
        settingframe, home), columnspan=4, pady=rootheight // 20)


def helper():
    '''enter helper page'''

    global helperframe

    helperframe = tk.Frame(root)
    helperframe.pack()
    createtitle(helperframe, '\n帮助\n', columnspan=2, height=2)

    for i in range(len(helpers)):
        createbutton(helperframe, helperitem == i, (i + 1, 0),
                     text=helpers[i][0], command=lambda j=i: changehelper(j), padx=rootheight // 25)

    helpersub = tk.Frame(helperframe)
    helpersub.grid(row=1, column=1, rowspan=len(
        helpers), padx=rootheight // 25)
    createtext(helpersub, 60, 15)
    text.insert(tk.END, helpers[helperitem][1])
    text['state'] = 'disable'

    createbutton(helperframe, 1, (i + 2, 0), text='返回', command=lambda: changeframe(
        helperframe, home), columnspan=2, pady=rootheight // 15)


# 组件外观


def givestyle(unit, level):
    '''give unit buttons styles they should have'''

    learned = True
    mastered = True
    testable = True

    for i in range((unit - 1) * 25, min(unit * 25, len(words[level]))):
        if len(records[level][i]) == 0:
            learned = False
            break
    if learned == True:
        for i in range((unit - 1) * 25, min(unit * 25, len(words[level]))):
            counter = 0
            for j in range(len(records[level][i])):
                if records[level][i][j][-3:] == '112' or records[level][i][j][-3:] == '211':
                    counter += 1
            if counter < int(settings[3][1]):
                mastered = False
                break
        if mastered == False:
            nowtime = int(time.time())
            for i in range((unit - 1) * 25, min(unit * 25, len(words[level]))):
                counter = 0
                for j in range(len(records[level][i])):
                    if records[level][i][j][-3:] == '112' or records[level][i][j][-3:] == '211':
                        counter += 1
                lastright = -1
                for k in range(len(records[level][i])):
                    if records[level][i][k][-3:] == '112' or records[level][i][k][-3:] == '211':
                        lastright = k
                if lastright != -1 and (nowtime - int(records[level][i][lastright][:-3])) < max(int(settings[2][1]) * 2 ** (counter - 2), int(settings[2][1])):
                    testable = False
                    break

    if learned == False:
        return 4
    else:
        if mastered == True:
            return 3
        else:
            if testable == True:
                return 1
            return 2


def givemarks():
    '''give marks according to user's answer'''

    for j in range(len(testlist)):

        if CtoEans[j] == words[level][questionlist[j]][0]:
            CtoEans[j] = 1
        else:
            CtoEans[j] = 0
            otherans = []
            for i in range(len(testlist)):
                if words[level][questionlist[j]][1] == words[level][questionlist[i]][1]:
                    otherans.append(i)
            for k in otherans:
                if CtoEans[j] == words[level][questionlist[k]][0]:
                    CtoEans[j] = 1
                    break
        if settings[1][1] == 'Choose' and CtoEans[j] == 1:
            CtoEans[j] = 2

        if LandWans[j] == words[level][questionlist[j]][0]:
            LandWans[j] = 1
        else:
            LandWans[j] = 0

        if settings[1][1] == 'Fill':
            allans = words[level][questionlist[j]][1].replace('；', ' ')
            allans = allans.split()
            TFlist = [0] * len(allans)
            for a in range(len(allans)):
                counter = 0
                for b in range(len(allans[a])):
                    if allans[a][b] in EtoCans[j]:
                        counter += 1
                if counter / len(allans[a]) >= 0.5:
                    TFlist[a] = 1
            if sum(TFlist) == len(TFlist):
                EtoCans[j] = 2
            elif sum(TFlist) / len(TFlist) >= 0.5:
                EtoCans[j] = 1
            else:
                EtoCans[j] = 0
        else:
            if EtoCans[j] == words[level][questionlist[j]][1]:
                EtoCans[j] = 1
            else:
                EtoCans[j] = 0


if __name__ == '__main__':

    root = tk.Tk()
    root.title('南哪词表助手')
    root.iconbitmap(default='image/icon.ico')
    root.state('zoomed')
    root.update()
    rootwidth = root.winfo_width()
    rootheight = root.winfo_height()

    # 以下为彩蛋相关请跳过，彩蛋结束处将有提示

    year = time.localtime(time.time())[0]
    month = time.localtime(time.time())[1]
    date = time.localtime(time.time())[2]
    if month == 5 and date == 20:
        day = 'anniversary'
    elif month == 12 and date == 13:
        day = 'memory'
    else:
        day = 'normal'

    bar = tk.Canvas(root, bd=0, bg='purple' if day == 'normal' else (
        '#C00000' if day == 'anniversary' else 'black'), width=rootwidth, height=rootheight // 11)
    bar.pack()

    nju() if year == 2022 and day == 'anniversary' else home()

    # 彩蛋部分到此结束

    root.mainloop()
