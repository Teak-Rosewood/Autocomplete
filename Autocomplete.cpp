#include <iostream>
#include <fstream>

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
        std::cout << "Inserting " << data << std::endl;
    }
    wordfile.close();
    return 0;
}
