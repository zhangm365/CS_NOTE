
#include <iostream>
#include <memory>

using namespace std;

class Child;
class Parent;

class Parent {
private:
    std::weak_ptr<Child> pChild;
    //std::shared_ptr<Child> pChild;
public:
    void setChild(std::shared_ptr<Child> myChild) {
        this->pChild = myChild;
    }

    void doSomething() {
        if (this->pChild.lock()) {

        }
    }

    ~Parent() {
        
    }
};

class Child {
private:
    std::shared_ptr<Parent> pParent;
public:
    void setPartent(std::shared_ptr<Parent> myParent) {
        this->pParent = myParent;
    }
    void doSomething() {
        if (this->pParent) {

        }
    }
    ~Child() {
        
    }
};

int main() {

    std::weak_ptr<Parent> wp;
    std::weak_ptr<Child> wc;
    
    {
    
        std::shared_ptr<Parent> pt(new Parent);
        std::shared_ptr<Child> pc(new Child);

        pt->setChild(pc);
        pc->setPartent(pt);

        wp = pt;
        wc = pc;

        cout << pt.use_count() << endl;
        cout << pc.use_count() << endl;

    }
    
    cout << wp.use_count() << endl;
    cout << wc.use_count() << endl;

    return 0;
}