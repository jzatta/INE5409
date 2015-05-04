
template<typename T>
class SortedList<T>: public List<T> {
private:
    Element<T> *head;
public:
    
    virtual ~SortedList() {
        while (!empty())
            delete remove();
    }
    
    void add() {
        
    }
    
    T *remove() {
        
    }
    
    bool empty() {
        return head == NULL;
    }
}