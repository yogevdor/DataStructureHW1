template<class T>
class AVLtree {
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
    AVLtree();

    ~AVLtree();

    //insert new key and value,if key exists does nothing, keeps balance
    void insert(int key, T value);

    //remove key and val, keeps balance
    void remove(int key, T value);

    //find key and return value
    T* find(int key);

    //search if key exists (will use find)
    bool contains(int key);

    //return pointer to the value with min key
    T* getMin();

    //make an empty tree
    void clearTree();

private:
};
