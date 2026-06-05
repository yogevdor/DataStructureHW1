
class Rooms_Tree;

template<class T>
class AVLtree {

    friend class ::Rooms_Tree;
protected:
    struct node {
        int key;
        int height;
        T value;
        node* leftSon;
        node* rightSon;
        node* parent;
    };

    node* root;

public:
    AVLtree(); //DOR

    ~AVLtree(); //DOR

    //insert new key and value,if key exists does nothing, keeps balance
    void insert(int key, T value); //DOR

    //remove key and val, keeps balance
    void remove(int key, T value); //DOR

    //find key and return value
    T* find(int key); //DOR

    //search if key exists (will use find)
    bool contains(int key); //DOOR

    //return pointer to the value with min key
    T* getMin(); //DOR

    //make an empty tree
    void clearTree(); //DOR

private:
    node* rotateRL(node* v); //DOR
    node* rotateRR(node* v); //DOR
    node* rotateLR(node* v); //YAARA
    node* rotateLL(node* v); //YAARA


};
