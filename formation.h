/**
 * @file
 * <pre> CPE 357 Spring 2011
 * -------------------
 *
 *  Header to "progrma header"
 *
 *  Last Modified: Mon Apr 08 11:48:36 PM PDT 2013</pre>
 *  @author Matthew Tondreau
 */

#ifndef _FORMATION_H_
#define _FORMATION_H_

#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>
#define BATTLEFIELDS 10
#define WIN 1
#define TIE 0
#define LOSE 2
using namespace std;

class formation {
  public:
  formation( const formation &form);
  formation& operator=(const formation &r);
  formation();
  formation( int form[] );
  static int battle( const formation &player_formation, 
      const formation &enemy_formation) ;
  static formation rand_formation() ;
  static formation randf() ;
  void print() const;
  static void print( const int form [] ) ;
  static void print( const formation & form) ;
  int score() const {return wins-loses;}
  int operator[](int index) const;
  int& operator[](int index);
  int operator<(const formation &r) const;
  int wins;
  int ties;
  int loses;
  bool lopsided();
  bool poor() const;
  const int* getFormation() const {return form;}
  bool validate() const;
  private:
  int form[BATTLEFIELDS];
  int simulate( int enemy[][10], unsigned size) const;
};

#endif
