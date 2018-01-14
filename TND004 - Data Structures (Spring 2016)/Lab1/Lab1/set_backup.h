
#include <memory>
#include <iostream>
#include <string>

using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;
using std::cout;
using std::ostream;
using std::string;


template <typename T>
class Set
{
private:
    struct Node
    {
        T value;

        shared_ptr<Node> next;
        weak_ptr<Node> prev;

        explicit Node(const T &value, shared_ptr<Node> prev, shared_ptr<Node> next)
            : value(value), prev(prev), next(next) {}
    };

public:
    //Default constructor
    Set();

    //Conversion constructor
    Set(T element);

    //Copy constructor
    Set(const Set &s);

    //Move constructor
    Set(Set && s);

    Set(const T a[], int n);

    //Destructor
    ~Set() = default;

    //Assignment operator
    Set &operator= (const Set & s);
    Set &operator= (Set && s);


    bool _empty() const;

    unsigned int cardinality() const;

    bool is_member(const T &value) const;

    void make_empty();

    Set &operator+= (const Set &s);

    Set &operator*= (const Set &s);

    Set &operator-= (const Set &s);

    template <typename U>
    friend ostream &operator<<(ostream &os, const Set<U> &s);

    bool operator<=(const Set &s) const;

    bool operator<(const Set &s) const;

    bool operator==(const Set &s) const;

    bool operator!=(const Set &s) const;



private:
    unsigned int counter;

    shared_ptr<Node> head, tail;

    void _insert(const shared_ptr<Node> before, const T &value);

    void _remove(const shared_ptr<Node> node);
};


//Constructors
template<typename T>
Set<T>::Set()
    : head(make_shared<Node>(T(), nullptr, nullptr)),
      tail(make_shared<Node>(T(), nullptr, nullptr)),
      counter(0)
{
    head->next = tail;
    tail->prev = head;
}

//Conversion constructor
template<typename T>
Set<T>::Set(T element)
    : Set<T>()
{
    _insert(head, element);
}

//Copy constructor
template<typename T>
Set<T>::Set(const Set &s)
    : Set<T>()
{
    shared_ptr<Node> before = head;

    for (auto src = s.head->next;
            src->next;
            src = src->next, before = before->next)
    {
        _insert(before, src->value);
    }
}

//Move constructor
template<typename T>
Set<T>::Set(Set && s)
    : head(s.head), tail(s.tail), counter(s.counter)
{
    s.head = s.tail = nullptr;
    s.counter = 0;
}

template<typename T>
Set<T>::Set(const T a[], int n)
    : Set<T>()
{
    shared_ptr<Node> before = head;

    for (int i = 0; i < n; ++i)
    {
        _insert(before, a[i]);
        before = before->next;
    }
}


template<typename T>
Set<T> &Set<T>::operator= (const Set & s)
{
    Set cpy(s);
    //*this = std::move(cpy);
    // swap works since Set is "MoveAssignable" and "MoveConstructible"
    std::swap(*this, cpy);
    return *this;
}

template<typename T>
Set<T> &Set<T>::operator= (Set && s)
{
    std::swap(counter, s.counter);
    std::swap(head, s.head);
    std::swap(tail, s.tail);
    return *this;
}

template<typename T>
bool Set<T>::_empty() const
{
    return counter == 0;
}

template<typename T>
unsigned int Set<T>::cardinality() const
{
    return counter;
}

template<typename T>
bool Set<T>::is_member(const T &value) const
{
    for (auto tmp = head->next;
            tmp->next;
            tmp = tmp->next)
    {
        if(tmp->value == value)
            return true;

        if(tmp->value > value)
            return false;
    }
    return false;
}

template<typename T>
void Set<T>::make_empty()
{
    auto node = head->next;

    while (node->next)
    {
        auto next = node->next;

        _remove(node);

        node = next;
    }
}

template<typename T>
Set<T> &Set<T>::operator+= (const Set &s)
{
    if(s.cardinality() == 0)
    {
        return *this;
    }
    auto s_node = s.head->next;
    auto this_node = head->next;
    while(s_node->next)
    {
        // check if we should insert s_node's value
        while (this_node->next && this_node->value < s_node->value)
        {
            this_node = this_node->next;
        }

        if(!this_node->next || this_node->value != s_node->value)
        {
            _insert(this_node->prev.lock(), s_node->value);
        }

        s_node = s_node->next;
    }

    return *this;
}

template<typename T>
Set<T> &Set<T>::operator*= (const Set &s)
{
    if(s._empty())
    {
        make_empty();
        return *this;
    }
    auto s_node = s.head->next;
    auto this_node = head->next;
    while(this_node->next)
    {
        while (s_node->next && s_node->value < this_node->value)
        {
            s_node = s_node->next;
        }

        if (!s_node->next || this_node->value != s_node->value)
        {
            this_node = this_node->next;
            _remove(this_node->prev.lock());
        }

        else
        {
            this_node = this_node->next;
        }
    }

    return *this;
}

template<typename T>
Set<T> &Set<T>::operator-= (const Set &s)
{
    if(s._empty())
    {
        return *this;
    }
    auto s_node = s.head->next;
    auto this_node = head->next;
    while(s_node->next)
    {

        while (this_node->next && this_node->value < s_node->value)
        {
            this_node = this_node->next;
        }

        if(this_node->next && this_node->value == s_node->value)
        {
            this_node = this_node->next;
            _remove(this_node->prev.lock());
        }
        s_node = s_node->next;
    }

    return *this;
}

template<typename T>
bool Set<T>::operator<=(const Set &s) const
{
    if (cardinality() > s.cardinality())
    {
        return false;
    }

    auto this_node = head->next;
    auto s_node = s.head->next;
    while (this_node->next)
    {
        while (s_node->next && this_node->value > s_node->value)
        {
            s_node = s_node->next;
        }

        if (!s_node->next || this_node->value < s_node->value)
        {
            return false;
        }

        this_node = this_node->next;
    }

    return true;
}

template<typename T>
bool Set<T>::operator<(const Set &s) const
{
    return *this <= s && cardinality() < s.cardinality();
}

template<typename T>
bool Set<T>::operator==(const Set &s) const
{
    return *this <= s && cardinality() == s.cardinality();
}

template<typename T>
bool Set<T>::operator!=(const Set &s) const
{
    return !(*this == s);
}

template<typename T>
void Set<T>::_insert(const shared_ptr<Node> before, const T &value)
{
    // Create new node that points to correct nodes
    auto new_node = make_shared<Node>(value, before, before->next);

    // Re-point the surrounding nodes to the new node
    before->next->prev = new_node;
    before->next = new_node;

    ++counter;
}

template<typename T>
void Set<T>::_remove(const shared_ptr<Node> node)
{
    node->next->prev = node->prev;

    auto prev = node->prev.lock();
    if (prev)
    {
        prev->next = node->next;
    }

    node->next = nullptr;

    --counter;
}

/**
 * Friend stuff
 */
template<typename T>
ostream &operator<<(ostream &os, const Set<T> &s)
{
    if (s._empty())
    {
        cout << "Set is empty...";
        return os;
    }

    auto tmp = s.head->next;

    os << "{";
    while (tmp->next)
    {
        os << tmp->value;

        tmp = tmp->next;
        if (tmp->next)
        {
            os << ", ";
        }
    }
    os << "}";

    return os;
}

/**
 *  Template specialization for int
 */

const Set<int> operator* (const Set<int> &s1, const Set<int> &s2)
{
    Set<int> s(s1);

    return s *= s2;
}

const Set<int> operator- (const Set<int> &s1, const Set<int> &s2)
{
    Set<int> s(s1);

    return s -= s2;
}

Set<int> operator+ (Set<int> s1, const Set<int> &s2)
{
    Set<int> s(s1);

    return s += s2;
}

/**
 *  Template specialization for string
 */

const Set<string> operator* (const Set<string> &s1, const Set<string> &s2)
{
    Set<string> s(s1);

    return s *= s2;
}

const Set<string> operator- (const Set<string> &s1, const Set<string> &s2)
{
    Set<string> s(s1);

    return s -= s2;
}

Set<string> operator+ (Set<string> s1, const Set<string> &s2)
{
    Set<string> s(s1);

    return s += s2;
}
