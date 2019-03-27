#include<string>
#include<list>
#include <variant>
#include <iostream>
#include <sstream>

struct Attribute{ std::string name; std::string value;};

struct Text{ std::string content; };

struct Element;

typedef std::variant<Element, Text> Node;

struct Element{ std::string name; std::list<Attribute> attributes; std::list<Node> children;};

auto text(std::string content){return Text{content};}

auto element(std::string name){
  return [=](std::list<Attribute> attrs, std::list<Node> children){ return Element{name, attrs, children};};
}

void render(std::ostream&, Node);

struct renderer
{
  std::ostream& os_;
  renderer(std::ostream &os): os_{os}{}
  void operator()(Element element){
    os_ << "<" << element.name << ">";
    for(std::list<Node>::const_iterator iterator = element.children.begin(), end=element.children.end();
        iterator != end; ++iterator){
        render(os_, *iterator);
    }
    os_ <<"</" << element.name << ">";
  }
  void operator()(Text text){ os_ << text.content; }
};

void render(std::ostream& os, Node const node){
  std::visit(renderer{os}, node);
}

std::string renderstring(Node const node){
  std::stringstream os;
  render(os, node);
  return os.str();
}

auto hr = element("hr");
auto div_ = element("div");
auto nav = element("nav");
auto p = element("p");
