#include <iostream>
#include <string>

#ifndef N
#define N 1
using namespace std;

class node//链表节点类
{
public:
    string data;
    int num;
    node *next;
    node(string myData, int myNum) : data(myData), num(myNum), next(nullptr) {}
};

class linkList//链表类
{
public:
    node *front;
    node *end;
    int size;
    linkList() : front(nullptr), end(nullptr), size(0) {}
    void insert(string data, int num = 0)//插入数据
    {
        if (front == nullptr)
        {
            front = end = new node(data, num);
        }
        else
        {
            end->next = new node(data, num);
            end = end->next;
        }
        ++size;
    }
    void sortNode()//用冒泡排序对数据降序排序
    {
        for (node *i = front; i != nullptr; i = i->next)
        {

            for (node *j = front; j->next != nullptr; j = j->next)
            {
                if (j->num < j->next->num)
                {
                    string tempStr = j->data;
                    int tempNum = j->num;
                    j->data = j->next->data;
                    j->num = j->next->num;
                    j->next->num = tempNum;
                    j->next->data = tempStr;
                }
            }
        }
    }
    int countAllVotes()//计算票数总和
    {
        int result = 0;
        node *temp = front;
        while (temp != nullptr)
        {
            result += temp->num;
            temp = temp->next;
        }
        return result;
    }
    bool deleteNode(string myData)//删除数据对应节点
    {
        node *temp = front;
        node *prev = nullptr;
        while (temp != nullptr)
        {
            if (temp->data == myData)
            {
                if (prev == nullptr)
                {
                    front = temp->next;
                    delete temp;
                }
                else
                {
                    prev->next = temp->next;
                    delete temp;
                }
                return true;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
        return false;
    }
    node *findNode(string myData)//查找数据
    {
        node *temp = front;
        while (temp != nullptr)
        {
            if (temp->data == myData)
            {
                return temp;
            }
            else
            {
                temp = temp->next;
            }
        }
        return nullptr;
    }
    void printAll()//打印所有数据
    {
        node *temp = front;
        for (int i = 1; temp != nullptr; i++)
        {
            cout << i << "." << temp->data << " " << temp->num << endl;
            temp = temp->next;
        }
    }
    node *get(int i)//得到对应下标的节点
    {
        if (i > size)
        {
            return nullptr;
        }
        node *temp = front;
        for (int j = 0; j < i; j++)
        {
            temp = temp->next;
        }
        return temp;
    }
};

class root
{
private:
    string account;
    string password;

public:
    root(string myAccount, string myPassword) : account(myAccount), password(myPassword) {}
    string getAccount() { return account; }//获得账号
    string getPassword() { return password; }//获得密码
    bool changePassword(string oldPassword, string newPassword, string confirmPassword)//修改管理员密码
    {
        if (oldPassword != password)
        {
            return false;
        }
        else if (newPassword != confirmPassword)
        {
            return false;
        }
        else
        {
            password = newPassword;
            return true;
        }
    }
};

class user
{
private:
    string account;
    string password;
    string sex;
    string name;
    linkList *votes;

public:
    user(string myAccount, string myPassword, string mySex,
         string myName) : account(myAccount), password(myPassword),
                          sex(mySex), name(myName) { votes = new linkList(); }
    linkList *getVotes() { return votes; }//获得投票记录
    bool voting(string myData, int count)//增加投票记录
    {
        linkList *userVotes = getVotes();
        userVotes->insert(myData, count);
        return true;
    }
    string getAccount() { return account; }//获得账号
    string getPassword() { return password; }//获得密码
    string getSex() { return sex; }//获得性别
    string getName() { return name; }//获得名称
    bool changePassword(string oldPassword, string newPassword, string confirmPassword)//修改用户密码
    {
        if (oldPassword != password)
        {
            return false;
        }
        else if (newPassword != confirmPassword)
        {
            return false;
        }
        else
        {
            password = newPassword;
            return true;
        }
    }
    bool changeName(string newName)//更改名称
    {
        name = newName;
        return true;
    }
};
class competition
{
private:
    string name;
    linkList *contestants;
    int voteLimit;
    bool isDeadline;

public:
    competition(string myName, int myVoteLimit) : name(myName), voteLimit(myVoteLimit),
                                                  isDeadline(false)
    {
        contestants = new linkList();
    }
    competition(string myName, int myVoteLimit, bool myIsDeadline) : name(myName), voteLimit(myVoteLimit),
                                                                     isDeadline(myIsDeadline)
    {
        contestants = new linkList();
    }
    string getName() { return name; }//获得赛事名称
    linkList *getContestants() { return contestants; }//获得成员信息
    int getVoteLimit() { return voteLimit; }//获得赛事投票限制
    bool getIsDeadline() { return isDeadline; }//获得是否截止
    bool addContestant(string contestantName, int votes = 0)//添加成员
    {
        contestants->insert(contestantName, votes);
        return true;
    }
    bool setIsDeadline(bool myIsDeadline)//设置是否截止
    {
        isDeadline = myIsDeadline;
        return true;
    }
};
#endif