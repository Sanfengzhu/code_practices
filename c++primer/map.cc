#include <iostream>
#include <stdint.h>
#include <map>
#include <memory>
#include <string>

struct TabletNode {
private:
    std::string addr_; 
    int64_t uuid_;
public:
    TabletNode():addr_(""), uuid_(0) {}
    TabletNode(const std::string& addr, const int64_t& uuid) : addr_(addr), uuid_(uuid){
    }
    ~TabletNode(){
        std::cout << "call ~TabletNode " << addr_ << " " << uuid_ << "\n";
    }

    std::string getAddr(){
        return addr_;
    }

    int64_t getUuid(){
        return uuid_;
    }
};

typedef std::shared_ptr<TabletNode> TabletNodePtr;

class TabletNodeManager {
public:
    TabletNodeManager(){}
    ~TabletNodeManager(){
        std::cout << "call ~TabletNodeManager" << "\n";
    }

    void AddTabletNode(const std::string& addr, const int64_t& uuid){
        TabletNodePtr null_ptr;
        std::pair<TabletNodeList::iterator, bool> ret
            = tabletnode_list_.insert(std::pair<std::string, TabletNodePtr>(addr, null_ptr));
        if (ret.second){
            TabletNodePtr& tnp = ret.first->second;
            tnp.reset(new TabletNode(addr,uuid));
        }
    }

    void DelTabletNode(const std::string& addr){
        TabletNodeList::iterator it = tabletnode_list_.begin();
        if ( it!= tabletnode_list_.end()) {
            std::cout << "DelTabletNode" << "\n";
            tabletnode_list_.erase(addr);
        }
    }

    int64_t TabletNodeCnt(){
        return tabletnode_list_.size();
    }

    void FindTabletNode(const std::string& addr, TabletNodePtr* node){
        TabletNodeList::iterator it = tabletnode_list_.find(addr);
        if ( it!= tabletnode_list_.end()) {
            *node = it->second;
        }
    }

private:
    typedef std::map<std::string, TabletNodePtr> TabletNodeList;
    TabletNodeList tabletnode_list_;
};

class Flags {
public:
    Flags(){
        std::cout << "into \{" << "\n";
    }

    ~Flags(){
        std::cout << "leave }" << "\n";
    }
};

int main(int argc, char *argv[])
{
    TabletNodePtr node;
    {
        Flags f;
        std::shared_ptr<TabletNodeManager> tnm = std::make_shared<TabletNodeManager>();
        tnm->AddTabletNode("127.0.0.1:1001", 1235);
        tnm->AddTabletNode("127.0.0.1:1000", 1234);
        tnm->AddTabletNode("127.0.0.1:1002", 1236);
        tnm->FindTabletNode("127.0.0.1:1002", &node);
        std::cout << tnm->TabletNodeCnt() << "\n";
        tnm->DelTabletNode("127.0.0.1:1002");
    }
    std::cout << node->getUuid() << "\n";
    return 0;
}
