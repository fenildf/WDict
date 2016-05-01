#include "WordConsole.h"
#include <typeinfo>

WordConsole::WordConsole(Console &Root, const string &Word)
    : ConsoleComponent(Root), btnAddDesc(Root, '0', "�������"), btnAddSent(Root, '1', "�������"),
                              btnDelDesc(Root, '2', "ɾ������"), btnDelSent(Root, '3', "ɾ������"), btnBack(Root, 'b', "����"), Word(Word)
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
        cout << str + "����:" << endl;
        size_t i = 0;
        for (string desc : wi.Desc)
        {
            cout << "    " << i++ << ". " << desc << endl;
        }
    }
    else
    {
        cout << string("δ�ҵ�") + str + "���塣" << endl;
    }
    cout << endl;
    
    if (wi.Sentences.size() > 0)
    {
        cout << str + "����:" << endl;
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
        cout << string("δ�ҵ�") + str + "���䡣" << endl;
    }
    cout << endl;
}

bool WordConsole::Show()
{
    auto &evalPtr = Globals::CurrentUser->WordEvaluate;
    bool haveFlags = false;
    
    if (evalPtr->IsCommon(Word))
    {
        cout << "*������*    ";
        haveFlags = true;
    }
    else
    {
        cout << "*��Ƨ��*    ";
        haveFlags = true;
    }
    
    if (evalPtr->IsForgettable(Word))
    {
        cout << "*����������*    ";
        haveFlags = true;
    }
    
    if (evalPtr->IsKnown(Word))
    {
        cout << "*���*    ";
        haveFlags = true;
    }
    else
    {
        cout << "*����*    ";
        haveFlags = true;
    }
    
    if (haveFlags)
    {
        cout << endl;
    }
    
    cout << string(80, '-') << endl;
    
    PrintWord("ϵͳ", Globals::Dict->GetWord(Word));
    PrintWord("����ӵ�", Globals::CurrentUser->GetWord(Word));
    
    ShowSubComponents();
    DoButtons();

    return true;
}

void WordConsole::AddDesc()
{
    TextInputConsole txtDesc(Root, "����:", TEXTINPUT_LINE);
    txtDesc.Show();
    if (txtDesc.Value != "")
    {
        Globals::CurrentUser->AddDesc(Word, txtDesc.Value);
        Globals::UserDictDB->Sync();
    }
}

void WordConsole::AddSent()
{
    TextInputConsole txtSent(Root, "����:", TEXTINPUT_LINE);
    txtSent.Show();
    if (txtSent.Value != "")
    {
        TextInputConsole txtDesc(Root, "����:", TEXTINPUT_LINE);
        txtDesc.Show();
        Globals::CurrentUser->AddSentence(Word, txtSent.Value, txtDesc.Value);
        Globals::UserSentDB->Sync();
    }
}

void WordConsole::DelDesc()
{
    TextInputConsole txtId(Root, "��������:", TEXTINPUT_LINE);
    txtId.Show();
    if (txtId.Value != "")
    {
        size_t id = StringUtils::FromString<size_t>(txtId.Value);
        if (txtId.Value != StringUtils::ToString(id))
        {
            // is not number
            return;
        }
        
        ConfirmConsole cc(Root, "��ȷ��Ҫɾ����?", false);
        cc.Show();
        if (cc.Value)
        {
            Globals::CurrentUser->DelDesc(Word, id);
            Globals::UserDictDB->Sync();
        }
    }
}

void WordConsole::DelSent()
{
    TextInputConsole txtId(Root, "��������:", TEXTINPUT_LINE);
    txtId.Show();
    if (txtId.Value != "")
    {
        size_t id = StringUtils::FromString<size_t>(txtId.Value);
        if (txtId.Value != StringUtils::ToString(id))
        {
            // is not number
            return;
        }
        
        ConfirmConsole cc(Root, "��ȷ��Ҫɾ����?", false);
        cc.Show();
        if (cc.Value)
        {
            Globals::CurrentUser->DelSentence(Word, id);
            Globals::UserSentDB->Sync();
        }
    }
}

void WordConsole::Back()
{
    Root.Back();
}