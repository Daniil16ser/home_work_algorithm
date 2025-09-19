#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct Node
{
    Node* left;
    Node* right;
    bool isLeaf;
    char letter;
    int val;

    Node(char sim, int val): left(nullptr), right(nullptr), letter(sim), val(val), isLeaf(true){}

    Node(Node* left, Node* right): left(left), right(right), letter('\0'), val(left->val + right->val)
    ,isLeaf(false){}
};

void create_hafmen(Node* node, std::map<char,std::string>&  dict_hafmen, const std::string& cur = "")
{
    if (node== nullptr)
    {
        return;
    }
    if (node->isLeaf)
    {
        dict_hafmen[node->letter] = cur; 
    }
    create_hafmen(node->left, dict_hafmen, cur + "0");
    create_hafmen(node->right, dict_hafmen, cur + "1");
}
void heapup(std::vector<Node*>& vec, int index)
{
    int parent = (index-1)/2;
    if (vec[index]->val > vec[parent]->val)
    {
        std::swap(vec[index], vec[parent]);
        heapup(vec, parent);
    }
}

std::string build_hafman_tree(const std::string& str)
{

    if(str.empty())
    {
        return nullptr;
    }

    std::map<char, int> dict_num;
    for (char letter: str)
    {
        dict_num[letter]++;
    }

    
    std::vector<Node*> vec;

    for (auto & [key, value]: dict_num)
    {
        vec.push_back(new Node(key, value));
    }
    std::sort(vec.begin(), vec.end(), [](Node* a, Node* b) {
            return a->val > b->val;
        });


    int cur_index = vec.size()-1;
    while (cur_index != 0)
    {
        Node* node = new Node(vec[cur_index-1], vec[cur_index]);
        vec.pop_back();
        vec[cur_index-1] = node;
        cur_index--;
        heapup(vec, cur_index);
    }

    std::map<char, std::string> dict_hafmen;

    create_hafmen(vec[0], dict_hafmen);
    std::string res;
    for (char letter: str)
    {
        res += dict_hafmen[letter];
    }

    return res;
}


// Example
// int main()
// {
//     std::string a = "aaabc";
//     std::string res = build_hafman_tree(a);
//     std::cout << res << std::endl;

//     return 0;
// }