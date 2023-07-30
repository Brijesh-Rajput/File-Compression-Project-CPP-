#include <bits/stdc++.h>
#include<fstream> // for file handling ( object will be used to take input and give ouput. )
#include <cstddef> //for NULL
#define endl "\n"
using namespace std;

// =========================================================== HuffmanTree class ==========================================================================================
class HuffmanTree
{
private:
    char character;
    HuffmanTree *left, *right; // Declaring multiple variable like this which takes & store address of an object.
    int frequency;

public:
    HuffmanTree(char character, int frequency)
    {
        this->character = character;
        this->frequency = frequency;
        this->left = NULL; // NOT null or NOT Null
        this->right = NULL;
    }
    HuffmanTree(char character, int frequency, HuffmanTree *left, HuffmanTree *right)
    {
        this->character = character;
        this->left = left;
        this->right = right;
        this->frequency = frequency;
    }
    int getFrequency()
    { // No need to pass an object b'coz:- Object will call this method
        // cout<<this->frequency<<" "<<frequency<<endl;
        return this->frequency;
    }
    char getCharacter()
    {
        return this->character;
    }
    HuffmanTree *getLeft()
    {
        return this->left;
    }
    HuffmanTree *getRight()
    {
        return this->right;
    }
    void setCharacter(char ch)
    {
        this->character = ch;
    }
    void setFrequency(int freq)
    {
        this->frequency = freq;
    }
    void setLeft(HuffmanTree *htLeft)
    {
        this->left = htLeft;
    }
    void setRight(HuffmanTree *htRight)
    {
        this->right = htRight;
    }
    friend ostream &operator<<(ostream &, HuffmanTree);
};
ostream &operator<<(ostream &dout, HuffmanTree ht)
{
    dout << "character = " << ht.character << endl
         << "frequency = " << ht.frequency << endl;
    dout << "left = " << ht.left << endl
         << "right = " << ht.right << endl;
    return dout;
}

//================================================ Comparator for Priority-Queue of HuffmanTree object ====================================================================
struct IncreasingOrderByFrequency
{
    // Priority Queue will fetch that object first whose frequency is smallest among all the objects.
    bool operator()(HuffmanTree &lhs, HuffmanTree &rhs)
    { // Q. Why we can't use const here to protect an object from manipulation. It gives an error.
        return lhs.getFrequency() < rhs.getFrequency();
    }
};
struct DecreasingOrderByFrequency
{
    // Priority Queue will fetch that object first whose frequency is smallest among all the objects.
    bool operator()(HuffmanTree *&lhs, HuffmanTree *&rhs)
    { // Q. Why we can't use const here to protect an object from manipulation. It gives an error.
        return lhs->getFrequency() > rhs->getFrequency();
    }
};
//===============================
void traverseHuffmanTree(HuffmanTree *ht, map<char, string> &mp, string str)
{
    // cout<<"Hello I'm working"<<endl;
    // cout<<ht->getCharacter()<<" "<<ht->getFrequency()<<endl;
    // cout<<ht->getLeft()<<" "<<ht->getRight()<<endl;

    if (ht->getCharacter() != '#')
    {
        // We reached to the leaf Node
        mp.insert(pair<char, string>(ht->getCharacter(), str));
        // cout<<ht->getCharacter()<<endl;
    }
    else
    {
        traverseHuffmanTree(ht->getLeft(), mp, str + "0");
        traverseHuffmanTree(ht->getRight(), mp, str + "1");
    }
}
// ========================= File reading and writing operation ================================
bool reading(string filePath, string &str1){

    // File handling to retrieve the content form the "text.txt" file:
    // Reading File :
    ifstream fin;
    fin.open(filePath, ios::in);

    if(!fin){
        cout << "File Not Found!"; // give me the correct location of the file.
        return false;
    }else{

        // storing file content into this "str" variable.
        while (!fin.eof()) str1.push_back(fin.get()); // instread of fin>>ch;

        fin.close();

        // Below steps is used, so that generated compressed file should decompressed only by my software from where this compressed file is generated. By using the concept of "Cryptography learnt in CNS(Cryptography and Network security)"
        // str1 = "This file is Compressed by Brijesh's software \n" + str1; // Learn "How to add \n in the string ?"

        return true;
    }
    // If file not read successfully or any error coes then return false
    // else return true.
}

bool writing(string filePath){

}

//==================================================================== Driver Code ==========================================================================================
int main()
{
    cout << "Welcome To Huffman Coding!!!" << endl;

    // Checking HuffmanTree Class & it's function working & it's object.
    // HuffmanTree ht0('a',6);
    // HuffmanTree ht1('A',9);
    // HuffmanTree ht2('c', 3, &ht0, &ht1);
    // cout<<ht0<<endl<<ht1<<endl<<ht2;

    // select any one choice from the given two options:
    // 1. Do you want to compress the file ?
    // 2. Do you want to decompress the file ?
    // after selecting any one option:- please, give me the path of the file. so, that i can retrieve it process the operation.

    // 1. compressing File:
    // file path ====> Taken from the cin
    string filePath = "text.txt";
    string str1;
    bool readSuccessfully = reading(filePath, str1);
    // Now, we get the all the content from the file which is stored inside the str1 string variable.
    if(!readSuccessfully) cout << "Unsuccessfully reading of file";
    else cout<<"This is the content which is read successfully:-" << endl << str1;
    // Now just call again for the loop so, it shows an options to select above two options again.

    // else  go for the compression code.












    // string str1 = "One day people will thankyou that you didnot give up Now";
    cout << "String Length: " << str1.length() << endl;
    map<char, int> charFrequencyMap;
    for (auto ch : str1)
        charFrequencyMap[ch]++;

    // Printing charcterFrequencyMap
    // for(auto [ch, freq]: charFrequencyMap) cout<<ch<<" 	"<<freq<<endl;

    vector<HuffmanTree> characterObject;
    for (auto [ch, freq] : charFrequencyMap)
    {
        HuffmanTree ht(ch, freq);
        characterObject.push_back(ht);
    }

    // Printing characterObject vector Element
    // cout<<"---------------- Vector Object list ------------------"<<endl;
    // for(auto obj: characterObject) cout<<obj<<endl;

    priority_queue<HuffmanTree *, vector<HuffmanTree *>, DecreasingOrderByFrequency> huffmanTreePq;
    for (auto obj : characterObject)
    {
        huffmanTreePq.push(new HuffmanTree(obj.getCharacter(), obj.getFrequency()));
    }

    /*
    //Printing Priority Queue Object in Increasing Order based on Frequency
    cout<<"--------------- Priority Queue Object list ------------------"<<endl;
    while(!huffmanTreePq.empty()){
        HuffmanTree htObject = huffmanTreePq.top();
        cout<<htObject<<endl;
        huffmanTreePq.pop();
    }
    */

    // Creating Huffman Tree For Compression:-
    while (!huffmanTreePq.empty())
    { // Minimum size of huffmanTree is 2 initially

        if (huffmanTreePq.size() == 1)
        {
            // That means, we got the Root Node.
            break;
        }

        HuffmanTree *ht1 = huffmanTreePq.top();
        huffmanTreePq.pop();
        HuffmanTree *ht2 = huffmanTreePq.top();
        huffmanTreePq.pop();

        char character = '#'; // If we add two huffmanTree Node with its frequency then there is no character.
        int frequency = ht1->getFrequency() + ht2->getFrequency();
        if (ht1->getFrequency() < ht2->getFrequency())
        {
            // Left will address only that node whose frequency is less than right.
            huffmanTreePq.push(new HuffmanTree(character, frequency, ht1, ht2));
        }
        else
        {
            huffmanTreePq.push(new HuffmanTree(character, frequency, ht2, ht1));
        }
    }
    HuffmanTree *huffmanTreeRootNode = huffmanTreePq.top(); // Copy constructor concept will use.
    huffmanTreePq.pop();                                    // Now, Priority Queue is empty.

    // cout<<"Hello"<<endl;
    // cout<<huffmanTreeRootNode->getCharacter()<<" "<<huffmanTreeRootNode->getFrequency(); // If string Length == huffmanTreeRootNode.getFrequency()  ===> Our huffmanTree is correct!!!

    // Traversing
    map<char, string> mp;
    string s = "";
    traverseHuffmanTree(huffmanTreeRootNode, mp, s);

    for (auto [character, str] : mp)
    {
        cout << "ASCII CODE : " << int(character) <<"  ---> " << character << ": " << str << endl;
        // cout<<"Hello"<<endl;
    }

    // Creating Compression code
    string compressionString = "";
    for (auto character : str1)
    {
        compressionString += mp[character];
    }
    cout << "Original String : " << str1 << endl;
    cout << "Compressed String : " << compressionString << endl;

    // Storing compression Detail in compression file to Decompress easily
    // Ascii code --> compression code {for privacy}

    // Decompression of file

    // Creating Tree using Huffman Tree compression code
    HuffmanTree *htForDecompression = new HuffmanTree('#', 0, NULL, NULL);

    map<char, string> mpForDecompression(mp);
    string strForDecompression = compressionString;

    for (auto [character, str] : mpForDecompression)
    {
        char ch = character;
        HuffmanTree *htForDecompressionTemp = htForDecompression;
        for (auto x : str)
        {
            if (x == '1')
            {
                if (htForDecompressionTemp->getRight() == NULL)
                {
                    htForDecompressionTemp->setRight(new HuffmanTree('#', 0, NULL, NULL));
                }
                htForDecompressionTemp = htForDecompressionTemp->getRight();
            }
            else
            {
                if (htForDecompressionTemp->getLeft() == NULL)
                {
                    htForDecompressionTemp->setLeft(new HuffmanTree('#', 0, NULL, NULL));
                }
                htForDecompressionTemp = htForDecompressionTemp->getLeft();
            }
        }
        htForDecompressionTemp->setCharacter(ch);
        htForDecompressionTemp->setFrequency(1); // 1 means we reach to the leaf node successfully.
        cout << "charcter successfully : " << ch << endl;
    }

    // finding huffman code for 'O' Letter to check the above Huffman Tree For Decompression
    // traverseHuffmanTreeForDecompression(htForDecompression);  ==> Don't use this, No need to rebuild it again
    map<char, string> mpForDecompressionCodeCheck;
    string strForDecompressionCheck = "";
    traverseHuffmanTree(htForDecompression, mpForDecompressionCodeCheck, strForDecompressionCheck);
    cout << "To check Decompression Code " << endl;
    for (auto [ch, str] : mpForDecompressionCodeCheck)
    {
        cout << "character: " << ch << "  String: " << str << endl;
    }

    // Traversing Compressed string Data for Decompressing it.
    // We have Root node for Traversing HuffmanTreeForDecompression
    // htForDecompression ==> Stores the address of Root node of Huffman Tree For Decompression.
    string decompressionString = "";
    HuffmanTree *htForDecompressionTemp = htForDecompression;

    // cout<<strForDecompression<<endl;
    for (auto x : strForDecompression)
    {
        // cout<<"Hii"<<endl;
        if (x == '1')
        {
            // cout<<"Hello"<<endl;
            htForDecompressionTemp = htForDecompressionTemp->getRight();
            // cout<<htForDecompressionTemp->getCharacter()<<endl;
            if (htForDecompressionTemp->getCharacter() != '#' && htForDecompressionTemp->getFrequency() == 1)
            { // To verify this, we can also use frequency ==> If it is 1 then it's confirm that it's a leaf node.
                // We got a character detail & decompressed successfully this character
                decompressionString += htForDecompressionTemp->getCharacter();
                htForDecompressionTemp = htForDecompression; // Initializing with root node again!!
            }
        }
        else
        {
            // cout<<"Hello"<<endl;
            htForDecompressionTemp = htForDecompressionTemp->getLeft();
            // cout<<htForDecompressionTemp->getCharacter()<<endl;
            if (htForDecompressionTemp->getCharacter() != '#' && htForDecompressionTemp->getFrequency() == 1)
            { // To verify this, we can also use frequency ==> If it is 1 then it's confirm that it's a leaf node.
                // We got a character detail & decompressed successfully this character
                decompressionString += htForDecompressionTemp->getCharacter();
                htForDecompressionTemp = htForDecompression; // Initialization with root node again!!
            }
        }
    }
    cout << "Decompression String is : " << decompressionString << endl;
}

//================================================================== END ===============================================================================================
/* TestCase:-
1.
    Address  -> Pointer type ===> use arrow
    Refernce -> use dot notation
    //for(auto obj: huffmanTreePq) cout<<obj<<endl; // NOTE:- We can't traverse Priority Queue Like this B'coz:- It's a Heap(Binary Tree)
*/

// https://cplusplus.com/reference/string/string/push_back/
// std::string str;
//   std::ifstream file ("test.txt",std::ios::in);
//   if (file) {
//     while (!file.eof()) str.push_back(file.get());
//   }
//   std::cout << str << '\n';


// 
//  // For writing into compressed file : 
//     ofstream fout;

//     // Bydefault opening mode of this 👇 is "ios::out" 
//     fout.open("CompressedFile.txt"); // File in which we will write compressed code.
//     // If file exist already then it will erase the content of this file and writing will perform. If file doesn't exist then It will create it with the provided name and start writing content in it.

//     fout << "Copressed string" ;
//     fout.close(); // Now, file is successfully stored in the hard-disk