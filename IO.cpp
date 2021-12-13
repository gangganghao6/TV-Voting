#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "classes.hpp"

using namespace std;

void writeAllCompetitions(vector<competition *> &allCompetitions) //写入所有赛事信息
{
    ofstream outFile;
    outFile.open("D:\\test\\allCompetitions.csv");
    for (auto it : allCompetitions)
    {
        outFile << it->getName() << ",";
        outFile << it->getVoteLimit() << ",";
        outFile << (it->getIsDeadline() == true ? 1 : 0) << ",";
        linkList *contestants = it->getContestants();
        node *temp = contestants->front;
        while (temp != nullptr)
        {
            outFile << temp->data << " " << temp->num << ";";
            temp = temp->next;
        }
        outFile << "," << contestants->size << "\n";
    }
    outFile.close();
}
void writeAllUsers(vector<user *> &allUsers) //写入所有用户信息
{
    ofstream outFile;
    outFile.open("D:\\test\\allUsers.csv");
    for (auto it : allUsers)
    {
        outFile << it->getAccount() << ",";
        outFile << it->getPassword() << ",";
        outFile << (it->getSex() == "男" ? 1 : 0) << ",";
        outFile << it->getName() << ",";
        linkList *votes = it->getVotes();
        node *temp = votes->front;
        while (temp != nullptr)
        {
            outFile << temp->data << " " << temp->num << ";";
            temp = temp->next;
        }
        outFile << "," << votes->size << "\n";
    }
    outFile.close();
}
void writeAllRoots(vector<root *> &allRoots) //写入所有管理员信息
{
    ofstream outFile;
    outFile.open("D:\\test\\allRoots.csv");
    for (auto it : allRoots)
    {
        outFile << it->getAccount() << ",";
        outFile << it->getPassword() << "\n";
    }
    outFile.close();
}
void writeAllSerialNumbers(vector<string> &allSerialNumbers) //写入所有序列号
{
    ofstream outFile;
    outFile.open("D:\\test\\allSerialNumbers.csv");
    for (auto it : allSerialNumbers)
    {
        outFile << it << "\n";
    }
    outFile.close();
}
void writeFile(vector<competition *> &allCompetitions, vector<user *> &allUsers,
               vector<root *> &allRoots, vector<string> &allSerialNumbers)//统一写入所有所需信息
{
    writeAllCompetitions(allCompetitions);
    writeAllUsers(allUsers);
    writeAllRoots(allRoots);
    writeAllSerialNumbers(allSerialNumbers);
}
void readAllCompetitions(vector<competition *> &allCompetitions)//读取所有赛事信息
{
    ifstream inFile;
    inFile.open("D:\\test\\allCompetitions.csv");
    string fileStr;
    while (getline(inFile, fileStr))
    {
        istringstream stringStr(fileStr);
        string splitStr;
        vector<string> tempStr;
        while (getline(stringStr, splitStr, ','))
        {
            tempStr.push_back(splitStr);
        }
        vector<string> linkListStr;
        istringstream linkListStringStr(tempStr[3]);
        while (getline(linkListStringStr, splitStr, ';'))
        {
            linkListStr.push_back(splitStr);
        }
        competition *temp = new competition(tempStr[0], atoi(tempStr[1].c_str()), (tempStr[2] == "1" ? true : false));
        for (int i = 0; i < atoi(tempStr[4].c_str()); i++)
        {
            istringstream is(linkListStr[i]);
            string name;
            int votes;
            getline(is, name, ' ');
            is >> votes;
            temp->getContestants()->insert(name, votes);
        }
        allCompetitions.push_back(temp);
    }
    inFile.close();
}
void readAllUsers(vector<user *> &allUsers)//读取所有用户信息
{
    ifstream inFile;
    inFile.open("D:\\test\\allUsers.csv");
    string fileStr;
    while (getline(inFile, fileStr))
    {
        istringstream stringStr(fileStr);
        string splitStr;
        vector<string> tempStr;
        while (getline(stringStr, splitStr, ','))
        {
            tempStr.push_back(splitStr);
        }
        vector<string> linkListStr;
        istringstream linkListStringStr(tempStr[4]);
        while (getline(linkListStringStr, splitStr, ';'))
        {
            linkListStr.push_back(splitStr);
        }
        user *temp = new user(tempStr[0], tempStr[1], tempStr[2] == "1" ? "男" : "女", tempStr[3]);
        for (int i = 0; i < atoi(tempStr[5].c_str()); i++)
        {
            istringstream is(linkListStr[i]);
            string competitionName;
            string contestantName;
            int votes;
            getline(is, competitionName, ' ');
            getline(is, contestantName, ' ');
            is >> votes;
            temp->getVotes()->insert(competitionName + " " + contestantName, votes);
        }
        allUsers.push_back(temp);
    }
    inFile.close();
}
void readAllRoots(vector<root *> &allRoots)//读取所有管理员信息
{
    ifstream inFile;
    inFile.open("D:\\test\\allRoots.csv");
    string fileStr;
    while (getline(inFile, fileStr))
    {
        istringstream stringStr(fileStr);
        string splitStr;
        vector<string> tempStr;
        while (getline(stringStr, splitStr, ','))
        {
            tempStr.push_back(splitStr);
        }
        root *temp = new root(tempStr[0], tempStr[1]);
        allRoots.push_back(temp);
    }
    inFile.close();
}
void readAllSerialNumbers(vector<string> &allSerialNumbers)//读取所有序列号
{
    ifstream inFile;
    inFile.open("D:\\test\\allSerialNumbers.csv");
    string fileStr;
    while (getline(inFile, fileStr))
    {
        allSerialNumbers.push_back(fileStr);
    }
    inFile.close();
}
