#include <bits/extc++.h>
using namespace std;

template<typename T>
class List {
    template<typename U>
    struct Element {
        U val;
        Element* next;
    };
    static Element<T>* null, none;
    Element<T>* head;

public :

    class iterator {
    public :
        Element<T>* ptr;
        iterator() : ptr(null) {}
        iterator(Element<T>* p) : ptr(p) {}
        iterator & operator ++() {
            if (ptr != null) {
                ptr = ptr->next;
            }
            return *this;
        }
        iterator operator ++(int) {
            iterator t = *this;
            ++(*this);
            return t;
        }
        iterator & operator --() {
            if (ptr == head) {return null;}
            auto t = head;
            while (t != null && t->next != ptr) {
                t = t->next;
            }
            ptr = t;
            return *this;
        }
        iterator operator --(int) {
            iterator t = *this;
            --(*this);
            return t;
        }
        T & operator *() {
            if (ptr == null) {
                return none.val;
            }
            return ptr->val;
        }
        bool operator == (iterator y) {
            return ptr == y.ptr;
        }
        bool operator != (iterator y) {
            return ptr != y.ptr;
        }
    };


    List() : head(null) {}
    virtual ~List() {
        while (head != null) {
            auto t = head->next;
            delete head;
            head = t;
        }
    }
    
    void push_front(const T & val) {
        head = new Element<T>{val, head};
    }

    void push_back(const T & val) {
        if (head == null) {
            push_front(val);
            return;
        }
        auto x = head;
        while (x->next != null) {
            x = x->next;
        }
        insert(val, iterator(x));
    }

    void insert(const T & val, iterator it) {
        if (it.ptr == null) {return;}
        it.ptr->next = new Element<T>{val, it.ptr->next};
    }

    void print() {
        if (head == null) {return;}
        cout << head->val;
        auto x = head->next;
        while (x != null) {
            cout << " " << x->val;
            x = x->next;
        }
    }
    iterator indexof(const T & val) {
        return indexof(val, head);
    }
    iterator indexof(const T & val, iterator pos) {
        auto t = pos.ptr;
        while (t != null && t->val != val) {
            t = t->next;
        }
        return iterator(t);
    }
    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(null);
    }
    iterator erase(const T & val) {
        if (head == null) {return null;}
        if (head->val == val) {
            auto t = head;
            head = head->next;
            delete t;
            return head;
        }
        auto x = head;
        while (x->next != null && x->next->val != val) {
            x = x->next;
        }
        if (x->next->val == val) {
            auto t = x->next;
            x->next = t->next;
            delete t;
            return x->next;
        }
        return null;
    }
};

template<typename T>
List<T>::Element<T> List<T>::none = {T(), nullptr};

template<typename T>
List<T>::Element<T>* List<T>::null = &(List<T>::none);

signed main() {
    list<double> l;
    double t;
    while (cin >> t) {
        l.push_back(t);
    }
    for (auto x : l) {
        cout << x << " ";
    }
    return 0;
}