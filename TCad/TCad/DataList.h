#ifndef DATA_LIST_H_
#define DATA_LIST_H_
#include "stdafx.h"

template<typename T>
class DataNote
{
public:
    DataNote() : next_(NULL), prev_(NULL) { ; }
    void         set_data(T val) { data_ = val; }
    T            get_data() const { return data_; }
    void         set_next(DataNote<T>* next) { next_ = next; }
    DataNote<T>* get_next() const { return next_; };
    void         set_prev(DataNote<T>* prev) { prev_ = prev; }
    DataNote<T>* get_prev() const { return prev_; }
private:
    T            data_;
    DataNote<T>* next_;
    DataNote<T>* prev_;
};

template<typename T>
class DataList
{
public:
    DataList() : p_head_(NULL) {};
    ~DataList()
    {
        DataNote<T>* temp = p_head_;
        while (temp != NULL)
        {
            p_head_ = p_head_->get_next();
            delete temp;
            temp = p_head_;
        }
    };

    void InsetFront(T val)
    {
        DataNote<T>* temp = new DataNote<T>();
        temp->set_data(val);
        temp->set_next(p_head_);
        temp->set_prev(NULL);
        if (p_head_ != NULL)
            p_head_->set_prev(temp);
        p_head_ = temp;
    }

    void InsertBack(T val) 
    {
        DataNote<T>* last = p_head_;
        if (last == NULL)
        {
            DataNote<T>* temp = new DataNote<T>();
                temp->set_data(val);
            p_head_ = temp;
            last = temp;
        }
        else
        {
            while (last->get_next() != NULL)
            {
                last = last->get_next();
            }

            DataNote<T>* temp = new DataNote<T>();
                temp->set_data(val);
            temp->set_next(NULL);
            temp->set_prev(last);
            last->set_next(temp);
        }
    }

    void InsertAfterNode(DataNote<T>* node, T val)
    {
        if (node != NULL)
        {
            DataNote<T>* temp = new DataNote<T>();
            temp->set_data(val);
            temp->set_next(node->get_next());
            temp->set_prev(node);
            node->set_next(temp);

            if (temp->get_next() != NULL)
            {
                temp->get_next()->set_prev(temp);
            }
        }
    }

    void InsertBeforeNode(DataNote<T>* node, T val)
    {
        if (node != NULL)
        {
            DataNote<T>* temp = new DataNote<T>();
            temp->set_data(val);
            temp->set_next(node);
            temp->set_prev(node->get_prev());
            node->set_prev(temp);

            if (temp->get_prev() != NULL)
            {
                temp->get_prev()->set_next(temp);
            }
        }
    }

    void RemoveFront()
    {
        if (p_head_ != NULL)
        {
            DataNote<T>* temp = p_head_;
            p_head_ = p_head_->get_next();
            if (p_head_ != NULL)
                p_head_->set_prev(NULL);
            delete temp;
        }
    }

    void RemoveEnd()
    {
        DataNote<T>* last = p_head_;
        while (last->get_next() != NULL)
        {
            last = last->get_next();
        }

        DataNote<T>* temp = last->get_prev();
        if (temp)
        {
            temp->set_next(NULL);
        }
        
        delete last;
        last = NULL;
    }

    void RemoveObject(DataNote<T>* object)
    {
        if (object != NULL)
        {
            DataNote<T>* prev = object->get_prev();
            DataNote<T>* next = object->get_next();

            if (prev == NULL)
            {
                RemoveFront();
            }
            else if (next == NULL)
            {
                RemoveEnd();
            }
            else if (prev && next)
            {
                prev->set_next(next);
                next->set_prev(prev);
                delete object;
                object = NULL;
            }
        }
        
    }

    DataNote<T>* head() { return p_head_; };

public:
    DataNote<T>* p_head_;
};

#endif

