#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#define ALPHABETS 26

struct Node
{
    struct Node *children[ALPHABETS];
    bool endOfWord;
};

struct Node *getNode(void)
{
    struct Node *pNode = new Node;

    pNode->endOfWord == false;
    for(int i = 0; i < ALPHABETS; i++)
    {
        pNode->children[i] = NULL;
    }

    return pNode;
}

void insert (struct Node *root, std::string word)
{
    struct Node *pCrawl = root;
 
    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
    pCrawl->endOfWord = true;
}

// For Searching if the word is in the tree

bool search(struct Node *root, std::string word)
{
    struct Node *pCrawl = root;
 
    for (int i = 0; i < word.length(); i++)
    {
        int index = word[i] - 'a';
        if (!pCrawl->children[index])
            return false;
 
        pCrawl = pCrawl->children[index];
    }
 
    return (pCrawl->endOfWord);
}

bool isWord(struct Node* root)
{
    return root->endOfWord != false;
}

void display(struct Node* root, char str[], int level)
{
    if (isWord(root)) 
    {
        str[level] = '\0';
        std::cout << str << "\t";
    }
  
    int i;
    for (i = 0; i < ALPHABETS; i++) 
    {
        if (root->children[i]) 
        {
            str[level] = i + 'a';
            display(root->children[i], str, level + 1);
        }
    }
}

void skip(struct Node* root,char str[],int level,std::string input)
{
    for(int i=0;i<input.length();i++)
    {
        if(input[i] == '\0')
            break;
        int index = input[i] - 'a';
        root = root->children[index];
        str[level] = index + 'a';
        level++;
        if(!root)
        {
            std::cout<<"No such word."<<std::endl;
            exit(0);
        }
    }
    display(root,str,level);
}



int main()
{
    std::string data;
    struct Node *root = getNode();

    std::fstream wordfile;
    wordfile.open("words/5000-words.txt", std::ios::in);
    while(!wordfile.eof())
    {
        wordfile >> data;
        insert(root, data);
    }
    wordfile.close();
    int level = 0;
    char str[100];
    std::string input;
    while(1)
    {
        std::cout<<"\nEnter letters(-1 to exit): "<<std::endl;
        std::cin>>input;
        if(input=="-1")
            break;
        skip(root,str,level,input);
    }
    
    return 0;
}