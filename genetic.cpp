#include "genetic.h"
#include "formation.h"
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "given.h"
using std::cerr;
using std::endl;
using std::logic_error;
genetic::genetic( int old[] ) {
  pool[POOL_SIZE-1] = formation(old);
  genetic::simulate_formation(pool[POOL_SIZE-1]);
  init();
}
void genetic::print() const {

  for( int i = 0; i < POOL_SIZE; ++i) {
    formation::print( pool[i]);
  }
}

bool genetic::validate_formation( int form[] ) {
  int sum = 0;
  for( int i = 0; i < BATTLEFIELDS; ++i) {
    sum += form[i];
  }
  if( sum == 100 ) {
    return true;
  }
  return false;
}
formation genetic::select_mate() {
  int sel = rand() % 6;
  switch( sel ){
    case 0: 
    case 1:
    case 2: return pool[rand()%10];  break;
    case 3:
    case 4: return pool[ rand() %30 + 10]; break;
    default: return pool[ rand() % 50 + 50]; break;
  }
}
formation genetic::mate( const formation &a, const formation &b) {
  static formation f;
  int val;
  bool off = false;
  for( int i = 0; i < BATTLEFIELDS; ++i ) {
    val = a[i] + b[i];
    if( val % 2 == 1 ) {
      if( off ) {
        //we took an extra pt earlier
        val = (val-1) / 2;
        off = false;
      } else {
        //we're odd and havent taken a pt earlier
        val = (val+1) / 2;
        off = true;
      }
    } else {
      val /= 2;
    }
    f[i] = val;
  }
  if( !f.validate() ) {
    throw logic_error("Invalid mating");
  }
  return f;
}

void genetic::init() {
  for( int i = 0; i < POOL_SIZE-1; ++i) {
    pool[i] = formation::rand_formation();
    genetic::simulate_formation(pool[i]);
    cerr << '\r' << double(i) / POOL_SIZE << "%";
  }
  std::stable_sort( pool, pool+ POOL_SIZE);
}
void genetic::simulate_formation(formation &myForm, 
        const formation &enemy) {
  int outcome;

  outcome = formation::battle(myForm,enemy);
  switch( outcome ) {
  case WIN: myForm.wins++; break;
  case LOSE: myForm.loses++; break;
  case TIE: myForm.ties++; break;
  }

}

void genetic::simulate_formation(formation &myForm) {
  myForm.wins =0;
  myForm.loses =0;
  for( int i = 0; i < GIVEN_SIZE; ++i) {
    formation enemy(given[i]);

    genetic::simulate_formation(myForm,enemy);
  }
}
const formation & genetic::best() const {
  return pool[POOL_SIZE-1];
}
void genetic::run() {
  //Zero out all previous scores
  for( int i = 0; i < POOL_SIZE; ++i) {
    pool[i].wins = pool[i].loses = 0;
  }
  num_mutations = num_mates = 0;
  static int rnd;
  for( int i = 0; i < POOL_SIZE / 8; ++i) {
    pool[i] = formation::rand_formation();
  }
  for( int i = POOL_SIZE /8; i < ((POOL_SIZE *7) / 8); ++i) {
     rnd = rand() %100;
    if( rnd < 10) { 
      num_mates++; 
      pool[i] = mate( pool[i], select_mate()); 
    }
    else if( rnd < 100 ) { 
     num_mutations++; 
     mutate(pool[i]); 
    }
  }
  for( int i = 0; i < POOL_SIZE; ++i) {
    genetic::simulate_formation(pool[i]);
  }

  std::stable_sort( pool, pool + POOL_SIZE);
}
void genetic::mutate(formation &form) {
  int mutations = rand() % 25;
  int pos, neg;
  for( int i = 0; i < mutations; ++i) {
    pos = rand() % 10;
    neg = rand() % 10;
    while( neg == pos || form[neg] == 0 ) { 
      neg = rand() % 10;
    }
    form[pos]++;
    form[neg]--;
  }

}
