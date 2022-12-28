#include <iostream>
#include <string>
#include <list>


class clientVM
{
  private:
    
    std::string _clientName;
    std::string _clientEmail;
    int _deviceCount{0};
    
  public:
    clientVM(std::string& Name, std::string& Email, int deviceCount=0) : _clientName{Name}, _clientEmail{Email}, _deviceCount{deviceCount}
    {
        
    }
    
    clientVM() : _clientName{"anon"}, _clientEmail{"anon"}
    {
        
    }
    constexpr int& getCount()
    {
        return _deviceCount;
    }
    
    void setCount(const int& count)
    {
        _deviceCount = count;
    }
    
    void resetCount()
    {
        _deviceCount = 0;
        _clientName = "anon";
        _clientEmail = "anon";
    }
    
    void display()
    {
        std::cout << "\n" << "Details :" << "\n";
        std::cout << "Name : " << _clientName << "\nEmail : " << _clientEmail << "\ndevice count :" << _deviceCount << "\n";
    }
    
    void setName(const std::string& Name)
    {
        _clientName = Name;
    }
    void setEmail(const std::string& Name)
    {
        _clientEmail = Name;
    }
};


class PoolManager
{
    
  private:
  const int MAX_SIZE{1};
    std::list<clientVM*> list;
    static PoolManager* _instance;
    static int Obj_counter;
    
    PoolManager() {}
    PoolManager(const PoolManager& _p) = delete;
    PoolManager* operator=(const PoolManager& _p) = delete;
    
    public:
    static PoolManager* getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new PoolManager;
        }
        return _instance;
    }
    
    clientVM* getResource()
    {
        if(list.size() >= MAX_SIZE)
            throw -1;
        clientVM* _resource;
        if(list.empty())
        {
             _resource = new clientVM;
        }
        else
        {
            _resource = list.front();
            list.pop_front();
        }
        Obj_counter++;
        return _resource;
    }
    
    void returnResource(clientVM* _resource)
    {
        _resource->resetCount();
        list.push_back(_resource);
        std::cout << "Resource Returned adding to pool\n"; 
    }
    
    void displayStats()
    {
        std::cout << "\nSTATS:\n";
        std::cout << "Objects Created Thus Far :" << Obj_counter;
        std::cout << "\nNumber of Objects that can be created Additionally : " << MAX_SIZE - Obj_counter ;
        std::cout <<"\nNumber of Objects currently in Pool : " << list.size() << "\n";
    }
    
};

PoolManager* PoolManager::_instance = nullptr;
int PoolManager::Obj_counter{0};
int main()
{
    PoolManager *_poolManager = PoolManager::getInstance();
    _poolManager -> displayStats();
    clientVM *vm1;
    
    
    vm1 = _poolManager -> getResource();
    vm1 -> display();
    vm1 -> setName("Resource 1");
    vm1 -> setEmail("Resource1@ObjectPool.in");
    vm1 -> display();
     _poolManager -> displayStats();
    clientVM *vm2;
    clientVM *vm3;
    
    vm2 = _poolManager -> getResource();
    vm2 -> display();
    _poolManager -> returnResource(vm1);
     _poolManager -> displayStats();
    _poolManager -> returnResource(vm2);
}
