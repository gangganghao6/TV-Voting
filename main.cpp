#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include "classes.hpp"
#include "IO.cpp"
using namespace std;

void handleUser(user *current);
void handleRoot(root *current);
void handleOwner();

vector<competition *> allCompetitions;
vector<user *> allUsers;
vector<root *> allRoots;
vector<string> allSerialNumbers;

char initInterface() //身份选择
{
    system("cls");
    cout << "TV Voting System" << endl;
    cout << "1.我是观众" << endl;
    cout << "2.我是管理员" << endl;
    cout << "3.我是所有者" << endl;
    return getch();
};
char initInterface2() //登录与注册选择
{
    system("cls");
    cout << "TV Voting System" << endl;
    cout << "1.我要登录" << endl;
    cout << "2.我还没有账号" << endl;
    return getch();
}
void userLogin() //用户登录
{
    system("cls");
    cout << "观众登录" << endl;
    string account, password;
    cout << "账号：";
    cin >> account;
    cout << "密码：";
    cin >> password;
    for (auto user : allUsers)
    {
        if (user->getAccount() == account && user->getPassword() == password)
        {
            handleUser(user);
            return;
        }
    }
    cout << "登录失败！" << endl;
}
void rootLogin() //管理员登录
{
    system("cls");
    cout << "管理员登录" << endl;
    string account, password;
    cout << "账号：";
    cin >> account;
    cout << "密码：";
    cin >> password;
    for (auto root : allRoots)
    {
        if (root->getAccount() == account && root->getPassword() == password)
        {
            handleRoot(root);
            return;
        }
    }
    cout << "登录失败！" << endl;
}
string createSerialNumber() //随机创建序列号
{
    unsigned seed;
    seed = time(0);
    srand(seed);
    return to_string(rand());
}
void ownerLogin() //主账号登录
{
    system("cls");
    cout << "所有者登录" << endl;
    string account, password;
    cout << "账号：";
    cin >> account;
    cout << "密码：";
    cin >> password;
    if (account == "111" && password == "111")
    {
        handleOwner();
    }
    else
    {
        cout << "登录失败！" << endl;
        return;
    }
}

void userSignin() //用户注册
{
    system("cls");
    cout << "观众注册" << endl;
    string account, password, sex, name;
    char chSex;
    cout << "账号（推荐手机号）：";
    cin >> account;
    cout << "密码：";
    cin >> password;
    cout << "性别：1.男 2.女";
    chSex = getch();
    switch (chSex)
    {
    case '1':
        sex = "男";
        break;
    case '2':
        sex = "女";
        break;
    default:;
    }
    cout << "  " << sex << endl;
    cout << "姓名：";
    cin >> name;
    for (auto i : allUsers)
    {
        if (i->getAccount() == account)
        {
            cout << "账号重复！" << endl;
            return;
        }
    }
    allUsers.push_back(new user(account, password, sex, name));
    system("cls");
    cout << "注册成功！" << endl;
    cout << "账号：" << account << endl;
    cout << "密码：" << password << endl;
    cout << "性别：" << sex << endl;
    cout << "姓名：" << name << endl;
    return;
}
void rootSignin() //管理员注册
{
    system("cls");
    cout << "管理员注册" << endl;
    string account, password, serialNumber;
    cout << "账号（推荐手机号）：";
    cin >> account;
    cout << "密码：";
    cin >> password;
    cout << "序列号：";
    cin >> serialNumber;
    for (auto i = allSerialNumbers.begin(); i != allSerialNumbers.end(); i++)
    {
        if (*i == serialNumber)
        {
            allRoots.push_back(new root(account, password));
            allSerialNumbers.erase(i);
            system("cls");
            cout << "注册成功！" << endl;
            cout << "账号：" << account << endl;
            cout << "密码：" << password << endl;
            return;
        }
        else
        {
            continue;
        }
    }
    cout << "序列号无效！" << endl;
    return;
}
void createCompetition() //创建赛事
{
    system("cls");
    string name;
    int voteLimit;

    string contestantName;
    cout << "竞赛名称：";
    cin >> name;
    cout << "每人总投票数量限制：";
    cin >> voteLimit;
    competition *temp = new competition(name, voteLimit);
    cout << "添加选手信息（输入end结束）：" << endl;
    int count = 1;
    cout << count++ << ".";
    cin >> contestantName;
    while (contestantName != "end")
    {
        temp->getContestants()->insert(contestantName);
        cout << count++ << ".";
        cin >> contestantName;
    }
    allCompetitions.push_back(temp);
    cout << "已添加：" << endl;
    temp->getContestants()->printAll();
    return;
}
competition *selectCompetition() //选择赛事
{
    system("cls");
    int i = 1;
    for (auto it : allCompetitions)
    {
        cout << i++ << "." << it->getName() << " " << it->getVoteLimit() << " " << it->getIsDeadline() << endl;
    }
    cout << "选择比赛：";
    int index;
    cin >> index;
    if (index > (int)allCompetitions.size())
    {
        cout << "未找到比赛！" << endl;
        return nullptr;
    }
    return allCompetitions[index - 1];
}
void addCompetitor(root *currentRoot) //添加选手
{
    system("cls");
    cin.clear();
    string name;
    competition *current = selectCompetition();
    if (current == nullptr)
    {
        return;
    }
    system("cls");
    cout << "选手列表：" << endl;
    current->getContestants()->printAll();
    cout << "输入新增选手信息：" << endl;
    cout << "姓名：" << endl;
    cin >> name;
    current->addContestant(name);
    cout << "成功添加：" << name << endl;
}
void checkVotes() //查看赛事选手票数情况
{
    system("cls");
    cout << "赛事列表：" << endl;
    competition *current = selectCompetition();
    if (current == nullptr)
    {
        return;
    }
    system("cls");
    current->getContestants()->sortNode();
    cout << "投票情况：" << endl;
    current->getContestants()->printAll();
}
void changePassword(root *current) //修改管理员密码
{
    system("cls");
    string oldPassword, newPassword, confirmPassword;
    cout << "旧密码：";
    cin >> oldPassword;
    cout << "新密码：";
    cin >> newPassword;
    cout << "确认密码：";
    cin >> confirmPassword;
    bool result = current->changePassword(oldPassword, newPassword, confirmPassword);
    if (result)
    {
        cout << "修改成功！" << endl;
    }
    else
    {
        cout << "修改失败！" << endl;
    }
}
void changePassword(user *current) //修改用户密码
{
    system("cls");
    string oldPassword, newPassword, confirmPassword;
    cout << "旧密码：";
    cin >> oldPassword;
    cout << "新密码：";
    cin >> newPassword;
    cout << "确认密码：";
    cin >> confirmPassword;
    bool result = current->changePassword(oldPassword, newPassword, confirmPassword);
    if (result)
    {
        cout << "修改成功！" << endl;
    }
    else
    {
        cout << "修改失败！" << endl;
    }
}
void changeName(user *current) //修改用户姓名
{
    system("cls");
    string name;
    cout << "原姓名：" << current->getName() << endl;
    cout << "新姓名：";
    cin >> name;
    current->changeName(name);
    cout << "修改成功！" << endl;
}
void voting(user *current) //用户投票
{
    system("cls");
    competition *currentCompetition = selectCompetition();
    if (currentCompetition == nullptr)
    {
        return;
    }
    else if (currentCompetition->getIsDeadline() == true)
    {
        system("cls");
        cout << "赛事投票已截止！" << endl;
        return;
    }
    int voteLimit = currentCompetition->getVoteLimit();
    system("cls");
    cout << "你要为谁投票？" << endl;
    currentCompetition->getContestants()->printAll();
    int index;
    cin >> index;
    node *currentContestant = currentCompetition->getContestants()->get(index - 1);
    if (currentContestant == nullptr)
    {
        cout << "选手不存在" << endl;
        return;
    }
    cout << "选手信息：" << currentContestant->data << " " << currentContestant->num << "票" << endl;
    cout << "要为TA投的票数(单次投票数量限制：" << voteLimit << "票)：";
    int count;
    cin >> count;
    if (count > voteLimit)
    {
        cout << "超出投票限制！" << endl;
        return;
    }
    currentContestant->num += count;
    current->voting(currentCompetition->getName() + " " + currentContestant->data, count);
    currentCompetition->getContestants()->sortNode();
    cout << "成功为" << currentContestant->data << "投了" << count << "票！" << endl;
    return;
}
void checkMyVotes(user *current) //查看用户投票记录
{
    system("cls");
    cout << current->getName() << " 的投票记录：" << endl;
    current->getVotes()->printAll();
}
void changeMessage(user *current) //修改用户信息（菜单）
{
    system("cls");
    cout << "我的个人信息：" << endl;
    cout << "姓名：" << current->getName() << endl;
    cout << "账号：" << current->getAccount() << endl;
    cout << "性别：" << current->getSex() << endl;
    cout << "你要修改哪项信息？" << endl;
    cout << "1.密码" << endl;
    cout << "2.姓名" << endl;
    char choose = getch();
    switch (choose)
    {
    case '1':
        changePassword(current);
        break;
    case '2':
        changeName(current);
        break;
    default:;
    }
}
void handleUser(user *current) //用户逻辑处理
{
    system("cls");
    cout << "Hello," << current->getName() << endl;
    cout << "1.投票" << endl;
    cout << "2.查看我的投票记录" << endl;
    cout << "3.查看投票情况" << endl;
    cout << "4.修改个人信息" << endl;
    char choose = getch();
    switch (choose)
    {
    case '1':
        voting(current);
        writeAllCompetitions(allCompetitions);
        writeAllUsers(allUsers);
        break;
    case '2':
        checkMyVotes(current);
        break;
    case '3':
        checkVotes();
        break;
    case '4':
        changeMessage(current);
        writeAllUsers(allUsers);
        break;
    default:;
    }
    system("pause");
    system("cls");
    handleUser(current);
}
void setIsDeadline() //设置比赛投票截止
{
    competition *current = selectCompetition();
    system("cls");
    string state = (current->getIsDeadline() == true) ? "已截止" : "投票中";
    string untiState = (current->getIsDeadline() == true) ? "投票中" : "已截止";
    cout << current->getName() << " 目前的状态是：" << state << endl;
    cout << "是否要更改？"
         << " 1.是  2.否";
    char choose = getch();
    cout << "  " << (choose == '1' ? "是" : "否");
    if (choose == '1')
    {
        current->setIsDeadline(!current->getIsDeadline());
        cout << "\n已改为：" << untiState << endl;
    }
    else if (choose == '2')
    {
        cout << endl;
        return;
    }
    else
    {
        cout << "\n输入有误！" << endl;
    }
}
void handleRoot(root *current) //管理员逻辑处理
{
    system("cls");
    cout << "Hello," << current->getAccount() << endl;
    cout << "1.创建比赛" << endl;
    cout << "2.添加选手" << endl;
    cout << "3.查看投票情况" << endl;
    cout << "4.修改密码" << endl;
    cout << "5.设置比赛截止" << endl;
    char choose = getch();
    switch (choose)
    {
    case '1':
        createCompetition();
        writeAllCompetitions(allCompetitions);
        break;
    case '2':
        addCompetitor(current);
        writeAllCompetitions(allCompetitions);
        break;
    case '3':
        checkVotes();
        break;
    case '4':
        changePassword(current);
        writeAllRoots(allRoots);
        break;
    case '5':
        setIsDeadline();
        writeAllCompetitions(allCompetitions);
        break;
    default:;
    }
    system("pause");
    system("cls");
    handleRoot(current);
}
void handleOwner() //主账号逻辑处理
{
    system("cls");
    cout << "1.添加序列号" << endl;
    cout << "2.查看所有序列号" << endl;
    char choose = getch();
    system("cls");
    switch (choose)
    {
    case '1':
    {
        string serialNumber = createSerialNumber();
        allSerialNumbers.push_back(serialNumber);
        cout << serialNumber << " 已添加" << endl;
        break;
    }
    case '2':
    {
        int count = 1;
        for (auto i : allSerialNumbers)
        {
            cout << count++ << "." << i << endl;
        }
        break;
    }
    default:
    {
        break;
    }
    }
    writeAllSerialNumbers(allSerialNumbers);
    system("pause");
    system("cls");
    handleOwner();
}

void login(char choose, char choose2) //登录菜单
{
    switch (choose)
    {
    case '1':
        if (choose2 == '1')
            userLogin();
        else
        {
            userSignin();
            writeAllUsers(allUsers);
        }
        break;
    case '2':
        if (choose2 == '1')
            rootLogin();
        else
        {
            rootSignin();
            writeAllRoots(allRoots);
        }
        break;
    case '3':
        ownerLogin();
        break;
    default:
        cout << "输入有误！" << endl;
    }
    system("pause");
    system("cls");
    char newChoose = initInterface();
    char newChhose2 = initInterface2();
    login(newChoose, newChhose2);
    return;
}

int main()
{
    readAllCompetitions(allCompetitions);
    readAllUsers(allUsers);
    readAllRoots(allRoots);
    readAllSerialNumbers(allSerialNumbers);
    char choose = initInterface();
    char choose2 = initInterface2();
    login(choose, choose2);
    return 1;
}