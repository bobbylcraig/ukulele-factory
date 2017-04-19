#ifndef UKULELE_H
#define UKULELE_H

#include <stddef.h>
#include <string>
#include <list>

// PREPROCESSOR DIRECTIVE
#define DEBUG 0

class Subpart;
class Rectangle;
class Circle;
class String;
class Part;
class Ukulele;
class Production;
class Supplier;

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
    virtual int get_thickness() {
      return 0;
    }
    virtual int get_length() {
      return 0;
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
      return length > 0 && width > 0 && color != "";
    }
    int get_thickness() {
      return 0;
    }
    int get_length() {
      return length;
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
      return diameter > 0 && color != "";
    }
    int get_thickness() {
      return 0;
    }
    int get_length() {
      return 0;
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
      return length > 0 && thickness > 0 && metal_type != "";
    }
    int get_thickness() {
      return thickness;
    }
    int get_length() {
      return length;
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
    void change_supplier (std::string supp) {
      this->supplier = supp;
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
      subpart_count++;
      return;
    }
    void remove_subpart_front() {
      Subpart* temp = subpart_list.front();
      subpart_list.pop_front();
      delete temp;
      temp = NULL;
      subpart_count--;
      return;
    }
    void remove_subpart_back() {
      Subpart* temp = subpart_list.back();
      subpart_list.pop_back();
      delete temp;
      temp = NULL;
      subpart_count--;
      return;
    }
    // Only for use with strings
    bool check_strings () {
      if ( subpart_count != 4 ) { // assumming ukuleles can only have 4 strings
        return false;
      }
      for (std::list<Subpart*>::const_iterator iterator1 = subpart_list.begin(), end1 = subpart_list.end(); iterator1 != end1; ++iterator1) {
        for (std::list<Subpart*>::const_iterator iterator2 = subpart_list.begin(), end2 = subpart_list.end(); iterator2 != end2; ++iterator2) {
          if ( iterator1 == iterator2 ) {
            continue;
          }
          else if ( (*iterator1)->get_thickness() == (*iterator2)->get_thickness() ) {
            return false;
          }
        }
      }
      return true;
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
    int get_max_length () {
      int max_length = 0, curr_length = 0;
      for (std::list<Subpart*>::const_iterator iterator = subpart_list.begin(), end = subpart_list.end(); iterator != end; ++iterator) {
        curr_length = (*iterator)->get_length();
        if ( curr_length > max_length ) {
          max_length = curr_length;
        }
      }
      return max_length;
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
      headstock = NULL;
      strings = NULL;
      neck = NULL;
      body = NULL;
    }
    ~Ukulele() {
      delete headstock;
      delete strings;
      delete neck;
      delete body;
    }
    bool quality_check() {
      bool string_neck_comp = strings->get_max_length() > neck->get_max_length(); // strings longer than neck?
      bool string_check = strings->check_strings();
      bool basic_checks = headstock->quality_check() && strings->quality_check() && neck->quality_check() && body->quality_check();
      if ( DEBUG ) std::cout
          << "STR_NECK_COMP: " << string_neck_comp << std::endl
          << "STR_CHECK: " << string_check << std::endl
          << "BASIC_CHECKS: " << basic_checks << "\n\n";
      return string_check && basic_checks && string_neck_comp; // add quality checks to individual parts
    }
    float calc_cost() {
      return headstock->get_cost() + strings->get_cost() + neck->get_cost() + body->get_cost();
    }
};

class Supplier {
  public:
    Supplier( int inventory_size, std::string supplier_name ) {
      name = supplier_name;
      inventory = inventory_size;
    }
    std::string name;
    int inventory;
    Part* create_headstock(int length, int width, std::string color) {
      // create headstock
      Part * part = new Part();
      part->add_subpart('r', length, width, 0, 0, color);
      part->change_supplier(this->name);
      return part;
    }
    Part* create_neck(int length, int width, std::string color) {
      // create neck
      Part * part = new Part();
      part->add_subpart('r', length, width, 0, 0, color);
      part->change_supplier(this->name);
      return part;
    }
    Part* create_strings(int thickness, int length, int distance, std::string material) {
      // create strings
      Part * part = new Part();
      // need specifications on different thicknesses for different sounds
      part->add_subpart('s', length, thickness, 0, 0, material);
      part->add_subpart('s', length, thickness, 0, 0, material);
      part->add_subpart('s', length, thickness, 0, 0, material);
      part->add_subpart('s', length, thickness, 0, 0, material);
      part->update_dist_bet(distance);
      part->change_supplier(this->name);
      return part;
    }
    Part* create_body(int diameter, int distance, std::string color) {
      // create body
      Part * part = new Part();
      part->add_subpart('c', diameter, 0, 0, 0, color);
      part->add_subpart('c', diameter, 0, 0, 0, color);
      part->update_dist_bet(distance);
      part->change_supplier(this->name);
      return part;
    }
};

class Production {
  private:
    int ukulele_count;
    std::list<Ukulele*> ukulele_list;
  public:
    Production() {
      ukulele_count = 0;
    }
    void build_ukulele(Supplier * headstock_sup, Supplier * neck_sup, Supplier * strings_sup, Supplier * body_sup,
                       int headstock_len, int headstock_wid, std::string headstock_col,
                       int neck_len, int neck_wid, std::string neck_col,
                       int strings_thick, int strings_len, int distance, std::string strings_material,
                       int body_diam, int body_dist, std::string body_col) {
      Ukulele * new_uk = new Ukulele();
      // add headstock
      new_uk->headstock = headstock_sup->create_headstock(headstock_len, headstock_wid, headstock_col);
      // add neck
      new_uk->neck = neck_sup->create_neck(neck_len, neck_wid, neck_col);
      // add strings
      new_uk->strings = strings_sup->create_strings(strings_thick, strings_len, distance, strings_material);
      // add body
      new_uk->body = body_sup->create_body(body_diam, body_dist, body_col);
      ukulele_list.push_back(new_uk); // push new Ukulele onto list
    }
    void destroy_ukulele( Ukulele * destroy_this ) {
      ukulele_list.remove(destroy_this);  // remove Ukulele from list
      ukulele_count--;
    }
};

#endif // UKULELE_H
