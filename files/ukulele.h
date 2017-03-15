#ifndef UKULELE_H
#define UKULELE_H

#include <stddef.h>
#include <string>
#include <list>

class Subpart;
class Rectangle;
class Circle;
class String;
class Part;
class Ukulele;

/*
 * Subpart Class
 */
class Subpart {
  protected:
    Part * parent;
    float cost_from_supply;
    int weight;
  public:
    virtual bool quality_check() {
      return weight > 0;
    }
};

/*
 * Rectangle Class from Subpart Class
 */
class Rectangle : public Subpart {
  private:
    int length;
    int width;
    std::string color;
  public:
    Rectangle (int lengthPass, int widthPass, std::string colorPass) {
      length = lengthPass;
      width = widthPass;
      color = colorPass;
    }
    ~Rectangle() {
      length = 0;
      width = 0;
      color = "";
    }
    bool quality_check() {
      std::cout << "RECT QUAL: " << (length > 0 && width > 0 && color != "") << std::endl;
      return length > 0 && width > 0 && color != "";
    }
};

/*
 * Circle Class from Subpart Class
 */
class Circle : public Subpart {
  private:
    int diameter;
    std::string color;
  public:
    Circle (int diameterPass, std::string colorPass) {
      diameter = diameterPass;
      color = colorPass;
    }
    ~Circle() {
      diameter = 0;
      color = "";
    }
    bool quality_check() {
      std::cout << "CIRC QUAL: " << (diameter > 0 && color != "") << std::endl;
      return diameter > 0 && color != "";
    }
};

/*
 * String Class from Subpart Class
 */
class String : public Subpart {
  private:
    int length;
    int thickness;
    std::string metal_type;
  public:
    String(int lengthPass, int thicknessPass, std::string metalPass) {
      length = lengthPass;
      thickness = thicknessPass;
      metal_type = metalPass;
    }
    ~String() {
      length = 0;
      thickness = 0;
      metal_type = "";
    }
    bool quality_check() {
      std::cout << "STR QUAL: " << (length > 0 && thickness > 0 && metal_type != "") << std::endl;
      return length > 0 && thickness > 0 && metal_type != "";
    }
};

/*
 * Part Class
 */
class Part {
  private:
    std::list<Subpart*> subpart_list;
    int subpart_count;
    std::string supplier;
    int dist_bet_subpart;
    float cost;
  public:
    Part () {
      subpart_count = 0;
      supplier = "";
      cost = 0.00;
      dist_bet_subpart = 0;
    }
    ~Part () {
      subpart_count = 0;
      subpart_list.clear();
      supplier = "";
      cost = 0.00;
      dist_bet_subpart = 0;
    }
    int subpart_count_print() {
      return subpart_count;
    }
    float get_cost() {
      return cost;
    }
    void update_dist_bet( int newDist ) {
      dist_bet_subpart = newDist;
      return;
    }
    void add_subpart(char type, int var1, int var2, int var3, float var4, std::string var5) {
      subpart_count++;
      Subpart * new_subpart;
      switch(type) {
        case 'r':
          // Uses var1 (length), var2 (width), and var5 (color)
          new_subpart = new Rectangle(var1, var2, var5);
          break;
        case 'c':
          // Uses var1 (diameter) and var5 (color)
          new_subpart = new Circle(var1, var5);
          break;
        case 's':
          // Uses var1 (length), var2 (thickness), and var5 (metal type)
          new_subpart = new String(var1, var2, var5);
          break;
        default:
          new_subpart = NULL;
          break;
      }
      if ( new_subpart != NULL ) {
        subpart_list.push_back(new_subpart);
      }
    }
    void remove_subpart_front() {
      Subpart* temp = subpart_list.front();
      subpart_list.pop_front();
      delete temp;
      temp = NULL;
    }
    void remove_subpart_back() {
      Subpart* temp = subpart_list.back();
      subpart_list.pop_back();
      delete temp;
      temp = NULL;
    }
    bool quality_check () {
      if ( subpart_count <= 0 ) {
        return false;
      }
      for (std::list<Subpart*>::const_iterator iterator = subpart_list.begin(), end = subpart_list.end(); iterator != end; ++iterator) {
        if ( !(*iterator)->quality_check() ) {
          return false;
        }
      }
      return true;
    }
};

/*
 * Ukulele Class
 */
class Ukulele {
  public:
    Part * headstock;
    Part * strings;
    Part * neck;
    Part * body;
    Ukulele() {   // Constructor
      headstock = new Part();
      strings = new Part();
      neck = new Part();
      body = new Part();
    }
    ~Ukulele() {
      delete headstock;
      delete strings;
      delete neck;
      delete body;
    }
    bool quality_check() {
      // strings longer than neck?
      // strings all different sizes?
      return ( headstock->quality_check() && strings->quality_check() && neck->quality_check() && body->quality_check() ); // add quality checks to individual parts
    }
    float calc_cost() {
      return headstock->get_cost() + strings->get_cost() + neck->get_cost() + body->get_cost();
    }
};

#endif // UKULELE_H
