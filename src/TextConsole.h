#ifndef _TEXTCONSOLE_H_
#define _TEXTCONSOLE_H_

#include <libdict.h>
#include <libui.h>
#include <libtextdb.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "WordConsole.h"
#include "EvaluateStrategy.h"

using namespace std;

class TextConsole
    : public ConsoleComponent
{
protected:
    TextInputConsole txtFilename, txtWord;
    string filename;
    vector<string> Words;
public:
    TextConsole(Console &Root)
        : ConsoleComponent(Root), txtFilename(Root, "请输入要分析的文本的路径(可将文件拖入控制台来获得文件路径，输入空行返回):", TEXTINPUT_LINE),
                                  txtWord(Root, "请输入要查询的单词(输入空行返回):", TEXTINPUT_LINE)
    {
        
    }
    
    bool Show() override;
};

#endif // _TEXTCONSOLE_H_
