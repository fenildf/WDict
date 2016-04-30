#include "WordConsole.h"
#include <typeinfo>

WordConsole::WordConsole(Console &Root, const string &Word)
    : ConsoleComponent(Root), btnAddDesc(Root, '0', "添加释义"), btnAddSent(Root, '1', "添加例句"),
                              btnDelDesc(Root, '2', "删除释义"), btnDelSent(Root, '3', "删除例句"), btnBack(Root, 'b', "返回"), Word(Word)
{
    btnAddDesc.OnClick = bind(&WordConsole::AddDesc, this);
    Add(btnAddDesc);
    
    btnAddSent.OnClick = bind(&WordConsole::AddSent, this);
    Add(btnAddSent);
    
    btnDelDesc.OnClick = bind(&WordConsole::DelDesc, this);
    Add(btnDelDesc);
    
    btnDelSent.OnClick = bind(&WordConsole::DelSent, this);
    Add(btnDelSent);
    
    btnBack.OnClick = bind(&WordConsole::Back, this);
    Add(btnBack);
}

void WordConsole::PrintWord(const string &str, WordInfo wi)
{
    if (wi.Desc.size() > 0)
    {
        cout << str + "释义:" << endl;
        size_t i = 0;
        for (string desc : wi.Desc)
        {
            cout << "    " << i++ << ". " << desc << endl;
        }
    }
    else
    {
        cout << string("未找到") + str + "释义。" << endl;
    }
    cout << endl;
    
    if (wi.Sentences.size() > 0)
    {
        cout << str + "例句:" << endl;
        size_t i = 0;
        for (auto p : wi.Sentences)
        {
            cout << "  " << i++ << ". " << p.first << endl
                 << "    " << p.second << endl
                 << endl;
        }
    }
    else
    {
        cout << string("未找到") + str + "例句。" << endl;
    }
    cout << endl;
}

bool WordConsole::Show()
{
    PrintWord("系统", Globals::Dict->GetWord(Word));
    PrintWord("您添加的", Globals::CurrentUser->GetWord(Word));
    
    for (auto ptr : Components)
    {
        ptr->Show();
    }
        
    DoButtons();

    return true;
}

void WordConsole::AddDesc()
{
    TextInputConsole txtDesc(Root, "释义:", TEXTINPUT_LINE);
    txtDesc.Show();
    if (txtDesc.Value != "")
    {
        Globals::CurrentUser->AddDesc(Word, txtDesc.Value);
    }
}

void WordConsole::AddSent()
{
    TextInputConsole txtSent(Root, "例句:", TEXTINPUT_LINE);
    txtSent.Show();
    if (txtSent.Value != "")
    {
        TextInputConsole txtDesc(Root, "释义:", TEXTINPUT_LINE);
        txtDesc.Show();
        Globals::CurrentUser->AddSentence(Word, txtSent.Value, txtDesc.Value);
    }
}

void WordConsole::DelDesc()
{
    TextInputConsole txtId(Root, "请输入编号:", TEXTINPUT_LINE);
    txtId.Show();
    if (txtId.Value != "")
    {
        size_t id = StringUtils::FromString<size_t>(txtId.Value);
        if (txtId.Value != StringUtils::ToString(id))
        {
            // is not number
            return;
        }
        Globals::CurrentUser->DelDesc(Word, id);
    }
}

void WordConsole::DelSent()
{
    TextInputConsole txtId(Root, "请输入编号:", TEXTINPUT_LINE);
    txtId.Show();
    if (txtId.Value != "")
    {
        size_t id = StringUtils::FromString<size_t>(txtId.Value);
        if (txtId.Value != StringUtils::ToString(id))
        {
            // is not number
            return;
        }
        Globals::CurrentUser->DelSentence(Word, id);
    }
}

void WordConsole::Back()
{
    Root.Back();
}