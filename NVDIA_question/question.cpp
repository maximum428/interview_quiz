#include <string>
#include <iostream>
#include <vector>
using namespace std;

constexpr unsigned int PERM_READ = 1;
constexpr unsigned int PERM_WRITE = 2;
constexpr unsigned int PERM_EXEC = 4;

class Entity {
public:
    virtual bool is_directory() = 0;
    std::string get_name() const { return entity_name; }
    unsigned int get_permissions() const { return entity_permissions; }
protected:
    Entity(std::string name, int permissions) : entity_name(name), entity_permissions(permissions) {}
private:
    std::string entity_name;
    unsigned int entity_permissions;
};

class File : public Entity {
public:
    File(std::string name, int permissions) : Entity(name, permissions) {}
    bool is_directory() override { return false; }
    unsigned int get_size() { return file_size; }
private:
    unsigned int file_size;
};

class Directory : public Entity {
public:
    Directory(std::string name, int permissions) : Entity(name, permissions) {}
    const std::vector<Entity*>& get_children() const {
        return children;
    }
    void add_child(Entity* entity) {
        children.push_back(entity);
    }
    bool is_directory() override { return true; }
private:
    std::vector<Entity*> children;
};


void printFile(Entity* entity, string& name) {
    if (!entity) return;
    
    if (!entity->is_directory() && entity->get_name() == name) {
        cout << entity->get_name() << endl;
        return;
    }
    
    Directory *directory = dynamic_cast<Directory*>(entity);
    if (!directory) return;

    for (Entity* e : directory->get_children()) {
      printFile(e, name);
    }
}

void find_all_files(Directory* dir, std::string name) {
    if (!dir || dir->get_children().empty()) {
        cout << "No file found - empty!!\n";
        return;
    }
    
    // use recusive call
    printFile(dir, name);
}


int main() {
    Directory dir("root", PERM_READ);
    Directory dirA("dirA", PERM_READ);
    File fileA("fileA", PERM_READ | PERM_WRITE);
    File fileB("fileB", PERM_READ);
    File fileC("fileC", PERM_READ);

    // Root
    dir.add_child(&fileA);
    dir.add_child(&fileB);
    dir.add_child(&fileC);
    dir.add_child(&dirA);

    // dirA
    File fileX("fileX", PERM_READ);
    File fileY("fileY", PERM_READ);
    Directory dirB("dirB", PERM_READ);
    File fileA2("fileA", PERM_READ | PERM_WRITE);
    dirB.add_child(&fileA2);

    dirA.add_child(&fileX);
    dirA.add_child(&fileY);
    dirA.add_child(&dirB);
    
    find_all_files(&dir, "fileA");
    
    return 0;
}
