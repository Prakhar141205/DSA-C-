/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    void dfs(Node* node, Node* cloned_node, unordered_map<Node*, Node* >& mp)  {

        
        for(Node* ngbr : node->neighbors) {

            if(mp.find(ngbr) == mp.end()) {
                Node* clone = new Node(ngbr->val) ;

                cloned_node->neighbors.push_back(clone);

                mp[ngbr] = clone ;

                dfs(ngbr, clone, mp) ;

            }else {
                cloned_node->neighbors.push_back(mp[ngbr]) ;
            }
        }
    }
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr ;
        Node* temp = new Node(node->val)  ;

        unordered_map<Node*, Node* > mp;
        mp[node] = temp ;


        dfs(node, temp, mp) ;


        return temp ;        
    }
};