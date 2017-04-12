#include <iostream>
#include <string>

class Task
{
private:
    void operator=(const Task&);
    Task(const Task&);
    int _id;
public:
    Task() : _id(0) {
        std::cout << "task init" << std::endl;        
    };
    virtual void SetId(int id);
    virtual int Id() const;
};

class Meta
{
private:
    void operator=(const Meta&);
    Meta(const Meta&);
public:
    Meta(){
        std::cout << "meta init" << std::endl;
    };
    virtual std::string Name() const = 0;
    virtual void SetName(const std::string& name) = 0;
};

class EventMeta : public Meta
{
private:
    std::string _name;
public:
    EventMeta() : _name("") {
        std::cout << "event meta init" << std::endl;
    }

    std::string Name() const {
        return _name;
    }

    void SetName(const std::string& name){
        _name = name;
    }
};

void Task::SetId(int id){
    _id = id;
}

int Task::Id() const {
    return _id;
}

int main(int argc, char *argv[])
{
    //Meta m;
    Task t;
    t.SetId(12);
    std::cout << t.Id() << std::endl;

    EventMeta *em = new EventMeta();

    Meta *m = em;
    m->SetName("baorenyi");
    std::cout << m->Name() << std::endl;
    return 0;
}
