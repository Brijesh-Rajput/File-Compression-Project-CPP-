#include <bits/stdc++.h>
#include<cstddef> //for NULL
#define endl "\n"
using namespace std;

// =========================================================== HuffmanTree class ==========================================================================================
class HuffmanTree
{
	private:
		char character;
		HuffmanTree *left, *right; //Declaring multiple variable like this which takes & store address of an object.
		int frequency;
	public:
		HuffmanTree(char character, int frequency){
			this->character = character;
			this->frequency = frequency;
			this->left = NULL; //NOT null or NOT Null
			this->right = NULL;
		}
		HuffmanTree(char character, int frequency, HuffmanTree* left, HuffmanTree* right){
			this->character = character;
			this->left = left;
			this->right = right;
			this->frequency = frequency;
		}
		int getFrequency(){ //No need to pass an object b'coz:- Object will call this method
            //cout<<this->frequency<<" "<<frequency<<endl;
            return this->frequency;
		}
		char getCharacter(){
            return this->character;
		}
		HuffmanTree* getLeft(){
            return this->left;
		}
		HuffmanTree* getRight(){
            return this->right;
		}
		friend ostream& operator << (ostream&, HuffmanTree);

};
ostream& operator<<(ostream& dout, HuffmanTree ht){
	dout<<"character = "<<ht.character<<endl<<"frequency = "<<ht.frequency<<endl;
	dout<<"left = "<<ht.left<<endl<<"right = "<<ht.right<<endl;
	return dout;
}


//================================================ Comparator for Priority-Queue of HuffmanTree object ====================================================================
struct IncreasingOrderByFrequency
{
    //Priority Queue will fetch that object first whose frequency is smallest among all the objects.
	bool operator()(HuffmanTree &lhs, HuffmanTree &rhs){ // Q. Why we can't use const here to protect an object from manipulation. It gives an error.
		return lhs.getFrequency() < rhs.getFrequency();
	}
};
struct DecreasingOrderByFrequency
{
    //Priority Queue will fetch that object first whose frequency is smallest among all the objects.
	bool operator()(HuffmanTree* &lhs, HuffmanTree* &rhs){ // Q. Why we can't use const here to protect an object from manipulation. It gives an error.
		return lhs->getFrequency() > rhs->getFrequency();
	}
};
//===============================
void traverseHuffmanTree(HuffmanTree *ht, map<char,string> &mp, string str){
    //cout<<"Hello I'm working"<<endl;
    //cout<<ht->getCharacter()<<" "<<ht->getFrequency()<<endl;
    //cout<<ht->getLeft()<<" "<<ht->getRight()<<endl;

    if(ht->getCharacter() != '#'){
        // We reached to the leaf Node
        mp.insert(pair<char,string>(ht->getCharacter(), str));
        //cout<<ht->getCharacter()<<endl;
    }else{
        traverseHuffmanTree(ht->getLeft(), mp, str+"0");
        traverseHuffmanTree(ht->getRight(), mp, str+"1");
    }

}






//==================================================================== Driver Code ==========================================================================================
int main() {
	cout<<"Welcome To Huffman Coding!!!"<<endl;

	//Checking HuffmanTree Class & it's function working & it's object.
	//HuffmanTree ht0('a',6);
	//HuffmanTree ht1('A',9);
	//HuffmanTree ht2('c', 3, &ht0, &ht1);
    //cout<<ht0<<endl<<ht1<<endl<<ht2;

	string str = "One day people will thankyou that you didnot give up Now";
	cout<<"String Length: "<<str.length()<<endl;
	map<char,int> charFrequencyMap;
	for(auto ch: str) charFrequencyMap[ch]++;

    //Printing charcterFrequencyMap
	//for(auto [ch, freq]: charFrequencyMap) cout<<ch<<" 	"<<freq<<endl;

    vector<HuffmanTree> characterObject;
    for(auto [ch, freq]: charFrequencyMap){
        HuffmanTree ht(ch, freq);
        characterObject.push_back(ht);
    }



    //Printing characterObject vector Element
    //cout<<"---------------- Vector Object list ------------------"<<endl;
    //for(auto obj: characterObject) cout<<obj<<endl;



    priority_queue<HuffmanTree*, vector<HuffmanTree*>, DecreasingOrderByFrequency> huffmanTreePq;
    for(auto obj: characterObject){
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


    //Creating Huffman Tree For Compression:-
    while(!huffmanTreePq.empty()){ // Minimum size of huffmanTree is 2 initially

        if(huffmanTreePq.size() == 1){
            // That means, we got the Root Node.
            break;
        }

        HuffmanTree *ht1 = huffmanTreePq.top();
        huffmanTreePq.pop();
        HuffmanTree *ht2 = huffmanTreePq.top();
        huffmanTreePq.pop();

        char character = '#'; // If we add two huffmanTree Node with its frequency then there is no character.
        int frequency = ht1->getFrequency() + ht2->getFrequency();
        if(ht1->getFrequency() < ht2->getFrequency()){
            // Left will address only that node whose frequency is less than right.
            huffmanTreePq.push(new HuffmanTree(character, frequency, ht1, ht2));
        }else{
             huffmanTreePq.push(new HuffmanTree(character, frequency, ht2, ht1));
        }

    }
    HuffmanTree *huffmanTreeRootNode = huffmanTreePq.top(); //Copy constructor concept will use.
    huffmanTreePq.pop(); //Now, Priority Queue is empty.

    //cout<<"Hello"<<endl;
    //cout<<huffmanTreeRootNode->getCharacter()<<" "<<huffmanTreeRootNode->getFrequency(); // If string Length == huffmanTreeRootNode.getFrequency()  ===> Our huffmanTree is correct!!!

    // Traversing
    map<char, string> mp;
    string s = "";
    traverseHuffmanTree(huffmanTreeRootNode, mp, s);

    for(auto [character, str]: mp){
        cout<<character<<": "<<str<<endl;
        //cout<<"Hello"<<endl;
    }

    //Creating Compression code
    string compressionString = "";
    for(auto character: str){
        compressionString += mp[character];
    }
    cout<<"Original String : "<<str<<endl;
    cout<<"Compression String : "<<compressionString<<endl;



}

//================================================================== END ===============================================================================================
/* TestCase:-
1.
    Address  -> Pointer type ===> use arrow
    Refernce -> use dot notation
    //for(auto obj: huffmanTreePq) cout<<obj<<endl; // NOTE:- We can't traverse Priority Queue Like this B'coz:- It's a Heap(Binary Tree)
*/


