#include <string>
using namespace std;
class Goods{
private:
  string name;
  int nums;
public:
  Goods(string name,int nums);
  void show();
  ~Goods();
};


class GoodsList{
private:
  struct Node{
    Goods* goods;
    Node* next;
  } *list;
public:
  GoodsList();
  void insert(Goods* goods);
  void remove(string name, int nums);
  void show();
  void sort();
  int count();
  void clear();
  ~GoodsList();
};
