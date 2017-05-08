#include <iostream>
#include "ukulele.hpp"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

bool check_good();
bool check_bad();
bool check_bad2();
bool check_bad3();
void create_ukulele_prompt();

Supplier * headstock_supplier = new Supplier(100, "Headstock Supplier");
Supplier * neck_supplier = new Supplier(100, "Neck Supplier");
Supplier * strings_supplier = new Supplier(100, "Strings Supplier");
Supplier * body_supplier = new Supplier(100, "Body Supplier");
Production factory;

int main( int argc, char *argv[] )
{
//  assert(check_good() == 1);
//  assert(check_bad() == 0);
//  assert(check_bad2() == 0);
//  assert(check_bad3() == 0);
//  std::cout << "All Automated Tests Passed\n" << std::endl;
  if ( argc < 1 )
    exit(0);
  else if ( argc == 2 ) {
    if ( strcmp(argv[1],"-h") == 0 ) {
      std::cout << "\nusage: ./ukulele-factory [-h] [-l path-to-log-file] \n" <<
                   "\th: this help message\n\tl: read from log file to recreate a previous factory\n" << std::endl;
      exit(0);
    }
  }
  else if ( argc == 3 ) {
    if ( strcmp(argv[1],"-l") == 0 ) {
      std::string line;
      int i = 0;
      std::string inputs[13];
      std::ifstream myfile ( argv[2] );
      if (myfile.is_open()) {
        while ( std::getline (myfile,line) ) {
          inputs[i++] = line;
          if ( i == 13 ) {
            factory.build_ukulele(headstock_supplier,neck_supplier,strings_supplier,body_supplier,
                                  atoi(inputs[0].c_str()), atoi(inputs[1].c_str()), inputs[2],
                                  atoi(inputs[3].c_str()), atoi(inputs[4].c_str()), inputs[5],
                                  atoi(inputs[6].c_str()), atoi(inputs[7].c_str()), atoi(inputs[8].c_str()), inputs[9],
                                  atoi(inputs[10].c_str()), atoi(inputs[11].c_str()), inputs[12]);
            i = 0;
          }
        }
        myfile.close();
      }
    }
    else {
      std::cout << "Unclear what directions are. Exiting." << std::endl;
      exit(0);
    }
  }
//  std::system("clear");
  int command;
  std::string save, save_name = "";
  bool end = false;
  std::cout << "\n=========================================\n" << std::endl;
  std::cout << "Welcome to your ukulele factory! Here are your options:" << std::endl <<
                 "\t1: Quality check of all ukuleles" << std::endl <<
                 "\t2: Individual quality check of all ukuleles" << std::endl <<
                 "\t3: Detailed printout report of ukuleles" << std::endl <<
                 "\t4: Create new ukulele" << std::endl <<
                 "\t9: Help (options)" << std::endl <<
                 "\t0: Exit factory" << std::endl;
  std::cout << "\n=========================================\n" << std::endl;
  while ( !end ) {
      std::cout << "Please enter a command: ";
      std::cin >> command;
      if ( std::cin.fail() ) {
        std::cout << "\nCommand not recognized. Exiting factory.\n" << std::endl;
        exit(0);
      }
      std::cout << "\n=========================================\n" << std::endl;
      switch ( command ) {
        case 1: // quality
          if ( factory.check_all_uk_valid() ) {
            std::cout << "All ukuleles are valid and of the best quality." << std::endl;
          }
          else {
            std::cout << "You have a faulty ukulele. Press 2 to figure out which ukulele it is." << std::endl;
          }
          break;
        case 2: // individual quality
          factory.check_indiv_uk_valid();
          break;
        case 3: // detailed printout report
          factory.uk_detail_report();
          break;
        case 4: // create new ukulele
          std::system("clear");
          create_ukulele_prompt();
          break;
        case 9:
          std::cout << "You pressed \"9\" to receive help! Here are your options:" << std::endl <<
                       "\t1: Quality check of all ukuleles" << std::endl <<
                       "\t2: Individual quality check of all ukuleles" << std::endl <<
                       "\t3: Detailed printout report of ukuleles" << std::endl <<
                       "\t4: Create new ukulele" << std::endl <<
                       "\t9: Help (you are here)" << std::endl <<
                       "\t0: Exit factory" << std::endl;
          break;
        case 0:
          end = true;
          std::cout << "Would you like to save your factory to a log to be reused? (y/n): ";
          std::cin >> save;
          if ( save == "y" ) {
            std::cout << "Ok, we'll save your factory. Please choose a file name: ";
            std::cin >> save_name;
            factory.write_to_log(save_name);
          }
          break;
        default:
          std::cout << "Command not recognized. Please type \"9\" to reprint the options." << std::endl;
        }
      std::cout << "\n=========================================\n" << std::endl;
  }
//  std::system("clear");
  return 0;
}

void create_ukulele_prompt() {
  std::string ok;
  int headstock_len, headstock_wid, neck_len, neck_wid, strings_thick, strings_len, strings_distance, body_diam, body_dist;
  std::string headstock_col, neck_col, body_col, strings_material;
  std::cout << "Let's create a ukulele!\n\nHow long should the headstock be? (cm): ";
  std::cin >> headstock_len;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nHow wide should the headstock be? (cm): ";
  std::cin >> headstock_wid;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nHow long should the neck be? (cm): ";
  std::cin >> neck_len;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nHow wide should the neck be? (cm): ";
  std::cin >> neck_wid;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nHow thick should the strings be? (μm): ";
  std::cin >> strings_thick;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nHow long should the strings be? (cm): ";
  std::cin >> strings_len;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nHow far apart should the strings be? (μm): ";
  std::cin >> strings_distance;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nWhat should the diameter of the body sections be? (cm): ";
  std::cin >> body_diam;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nWhat should the distance between the body sections be? (cm): ";
  std::cin >> body_dist;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nWhat color should the headstock be?: ";
  std::cin >> headstock_col;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nWhat color should the neck be?: ";
  std::cin >> neck_col;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nWhat color should the body be?: ";
  std::cin >> body_col;
  std::system("clear");
  std::cout << "Let's create a ukulele!\n\nWhat material should the strings be made of?: ";
  std::cin >> strings_material;
  std::system("clear");
  std::cout << "You want to create a ukulele with the following specs:" << std::endl <<
               "Headstock:" << std::endl <<
                  "\tLen (cm)      - " << headstock_len << std::endl <<
                  "\tWid (cm)      - " << headstock_wid << std::endl <<
                  "\tColor         - " << headstock_col << std::endl <<
               "Neck:" << std::endl <<
                  "\tLen (cm)      - " << neck_len << std::endl <<
                  "\tWid (cm)      - " << neck_wid << std::endl <<
                  "\tColor         - " << neck_col << std::endl <<
               "Strings:" << std::endl <<
                  "\tThick (μm)    - " << strings_thick << std::endl <<
                  "\tLen (cm)      - " << strings_len << std::endl <<
                  "\tMaterial      - " << strings_material << std::endl <<
                  "\tDist Bet (μm) - " << strings_distance << std::endl <<
               "Body:" << std::endl <<
                  "\tDiam (cm)     - " << body_diam << std::endl <<
                  "\tBody Col      - " << body_col << std::endl <<
                  "\tDist Bet (cm) - " << body_dist << std::endl <<
    "\n\nIs this okay? (y/n): ";
  std::cin >> ok;
  if ( ok == "y" ) {
    factory.build_ukulele(  headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                            headstock_len, headstock_wid, headstock_col,
                            neck_len, neck_wid, neck_col,
                            strings_thick, strings_len, strings_distance, strings_material,
                            body_diam, body_dist, body_col );
    std::system("clear");
    std::cout << "Ukulele Created!\n1" << std::endl;
  }
  else {
    std::system("clear");
    std::cout << "Ukulele Not Created.\n" << std::endl;
  }
}

// Good params
bool check_good() {
  factory.build_ukulele(headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                        13, 6, "brown",
                        20, 4, "brown",
                        650, 37, 660, "nylon",
                        15, 5, "brown");
  factory.build_ukulele(headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                        13, 6, "brown",
                        20, 4, "brown",
                        650, 37, 660, "nylon",
                        15, 5, "brown");
  return factory.check_all_uk_valid();
}

// Checking negative lengths
bool check_bad() {
  factory.build_ukulele(headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                        13, 6, "brown",
                        20, 4, "brown",
                        650, 37, 660, "nylon",
                        15, 5, "brown");
  factory.build_ukulele(headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                        13, 6, "brown",
                        -20, 4, "brown",  // invalid because of negative length
                        650, 37, 660, "nylon",
                        15, 5, "brown");
  return factory.check_all_uk_valid();
}

// Checking neck longer than strings
bool check_bad2() {
  factory.build_ukulele(headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                        13, 6, "brown",
                        20, 4, "brown",
                        650, 37, 660, "nylon",
                        15, 5, "brown");
  factory.build_ukulele(headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                        13, 6, "brown",
                        84, 4, "brown",
                        650, 37, 660, "nylon",
                        15, 5, "brown");
  return factory.check_all_uk_valid();
}

// Checking two strings being the same thickness
bool check_bad3() {
  factory.build_ukulele(headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                        13, 6, "brown",
                        20, 4, "brown",
                        650, 37, 660, "nylon",
                        15, 5, "brown");
  factory.build_ukulele(headstock_supplier, neck_supplier, strings_supplier, body_supplier,
                        13, 6, "brown",
                        20, 4, "brown",
                        650, 37, 0, "nylon", // strings are closer than their thickness
                        15, 5, "brown");
  return factory.check_all_uk_valid();
}
