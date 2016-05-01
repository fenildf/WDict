#include "TestConsole.h"

TestConsole::TestConsole(Console &Root)
    : ConsoleComponent(Root), btnBack(Root, 'b', "����"), selAnswer(Root, "������:")
{
    btnBack.OnClick = bind(&TestConsole::Back, this);
    Add(btnBack);
}

bool TestConsole::Show()
{
    selAnswer.Choices.clear();
    selAnswer.Choices.push_back(make_pair('A', "hello"));
    selAnswer.Choices.push_back(make_pair('B', "world"));
    selAnswer.Choices.push_back(make_pair('C', "int.���"));
    selAnswer.Choices.push_back(make_pair('D', "n.����"));
    selAnswer.Show();
    
    ShowSubComponents();
    DoButtons();
    
    return true;
}

void TestConsole::Back()
{
    Root.Back();
}