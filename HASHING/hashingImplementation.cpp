#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;
class Node{
public:
    string key;
    int val;
    Node* next;

    Node(string key, int val){
        this->key = key;
        this->val = val;
        next = nullptr;
    }

    ~Node(){
        if(next != nullptr){
            delete next;
        }
    }
};


class HashTable{
    int totSize;
    int currSize;
    Node* *table;

    int hashFunction(string key){
        int idx=0;

        for(int i=0; i<key.size(); ++i){
            idx = idx + (key[i]*key[i])%totSize;
        }
        return idx % totSize;
    }

    void rehash(){
        Node** oldTable = table;

        int oldSize = totSize;
        totSize = 2 * totSize;
        currSize=0;

        table = new Node* [totSize];

        for(int i=0; i<totSize; ++i){
            table[i]=nullptr;
        }

        for(int i=0; i<oldSize; i++){
            Node* temp = oldTable[i];
            while(temp != nullptr){
                insert(temp->key, temp->val);
                temp = temp->next;
            }

            if(oldTable[i] != nullptr){
                delete oldTable[i];
            }
        }
        delete[] oldTable;
    }
public:
    HashTable(int size=5){
        totSize = size;
        currSize = 0;

        table = new Node*[totSize]; // currently table has null value in each index
        
        // Initialize the table with the NULL value
        for(int i=0; i<totSize; ++i){
            table[i]=nullptr;
        }
    }


    void insert(string key, int val){
        int idx = hashFunction(key);

        Node* newNode = new Node(key, val);
        Node* head = table[idx];

        newNode->next = head;
        head = newNode;

        currSize++;


        double lambda() = currSize/(double)totSize;

        if(lambda > 1){
            rehash();
        }
    }

    bool exists(string key){
        int idx = hashFunction(key);
        Node* temp = table[idx];

        while(temp != nullptr){
            if(temp->key == key){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    int search(string key){
        int idx = hashFunction(key);
        Node* temp = table[idx];

        while(temp != nullptr){
            if(temp->key == key){
                return temp->val;
            }
            temp = temp->next;
        }
        return -1;
    }
    void remove(){
        int idx = hashFunction(key);
        Node* temp = table[idx];

        Node prev = temp;

        while(temp != nullptr){
            if(temp->key == key){
                if(prev == temp){
                    table[idx] = temp->next;
                }else{
                    prev-next = temp->next;
                }
                break;
            }
            prev = temp;
            temp = temp->next;
        }
    }

    void print(){
        for(int i=0; i<totSize; i++){
            cout << "idx= "<<i << " -> ";

            Node* temp = table[i];

            while(temp != nullptr){
                cout << "(" << temp->key << " , "<< temp->val <<")->";
            }
            cout << endl;
        }
    }
};
int main(){
    HashTable ht;

    ht.insert("China", 120);
    ht.insert("India", 100);
    ht.insert("Nepal", 23);
    ht.insert("Pakistan", 20);

    ht.print();

    ht.remove("China");
    ht.print();
    return 0;
}