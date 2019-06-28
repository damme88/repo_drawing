
#ifndef DATA_STACK_H_
#define DATA_STACK_H_

template <typename T>
class NodeData
{
public:
    NodeData() : next_(NULL) { ; }
    void         set_data(T val) { data_ = val; }
    T            get_data() const { return data_; }
    void         set_next(NodeData<T>* next) { next_ = next; }
    NodeData<T>* get_next() const { return next_; };
private:
    T            data_;
    NodeData<T>* next_;
};

template<typename T>
class Stack
{
public:
    Stack() : p_head_(NULL) {};
    ~Stack() { ; };

    NodeData<T>* GetLast()
    {

        NodeData<T>* last = p_head_;
        if (last != NULL)
        {
            while (last->get_next() != NULL)
            {
                last = last->get_next();
            }
        }

        return last;
    }

    void push(T val)
    {
        NodeData<T>* last = p_head_; // Tim ra node cuoi cung.
        if (last == NULL)            // neu chua co node nao
        {
            NodeData<T>* temp = new NodeData<T>(); \
            temp->set_data(val);
            p_head_ = temp;
        }
        else
        {
            while (last->get_next() != NULL)
            {
                last = last->get_next();
            }

            NodeData<T>* temp = new NodeData<T>(); \
            temp->set_data(val);
            temp->set_next(NULL); // next temp = NULL
            last->set_next(temp); // next cua last la temp
        }
    }

    void pop() // remove last element
    {
        if (p_head_ != NULL)
        {
            NodeData<T>* temp = p_head_;
            NodeData<T>* prev = NULL;
            while (temp->get_next() != NULL)
            {
                prev = temp;
                temp = temp->get_next();

            }

            delete temp;
            temp = NULL;

            if (prev != NULL)
            {
                prev->set_next(NULL);
            }
            else
            {
                p_head_ = NULL;
            }
        }
    }

    NodeData<T>* head() { return p_head_; };

private:
    NodeData<T>* p_head_;
};


#endif
