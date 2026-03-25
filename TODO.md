### TODO
---

todo
  >  get rid of todo lists in .cpp file
  >  break down .cpp into seperate .cpp files
  >  

chats
    [ebbi] Rename Src/ to src/ and update it in CMakeLists.txt, build.sh and build.bat
    [saad] dont 👆 
    [saad] kia zaroorat parhi thi aapko meray merge say pehlay merge karnay ki?!
           karna teh hi toh apni merge saad say banatay, main say nhi...
           ab meri puri commit history chali gayi: 21 in main vs 31ish in saad...
    [saad] btw, hamaray paas koi teesra banda nhi teh kia?
           dunno y kuch yaad arha hai
    [saad] cant we put .bat, .sh, and cmake.txt in a sep dir? main page mai ho kar 
           they cluttering it

[saad]
 #include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

int main() {
    try {
        // 1. Open/Create a database file
        SQLite::Database db("example.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

        // 2. Write (Execute a simple command)
        db.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)");
        db.exec("INSERT INTO users VALUES (NULL, 'Alice')");

        // 3. Read (Use a statement for queries)
        SQLite::Statement query(db, "SELECT * FROM users");
        while (query.executeStep()) {
            int id = query.getColumn(0);
            std::string name = query.getColumn(1);
            std::cout << "ID: " << id << ", Name: " << name << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}