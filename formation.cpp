#include "formation.h"
#include <iostream>
#include <cstring>
#include "given.h"
using std::cout;

formation::formation()
:wins(0),loses(0)
{
  ties = 0;
  memset(form,0,BATTLEFIELDS);
}
bool formation::validate() const {
  int sum = 0;
  for( int i = 0; i < BATTLEFIELDS; ++i) {
    sum += form[i];
  }
  if( sum == 100 ) {
   return true;
  }
  return false;
}
int formation::simulate( int enemy[][10], unsigned size) const {
  int score = 0;
  for( unsigned i = 0; i < size; ++i) {
    switch( battle(*this, formation(enemy[i]))) {
      case WIN: score++;

        }
  }
  return score;
}
formation formation::randf()  {
  static int ret[BATTLEFIELDS];
  int dist[BATTLEFIELDS-1];
  for( int i = 0; i < BATTLEFIELDS-1; ++i ) {
    dist[i] = rand() % 100;
  }
  sort( dist, dist + BATTLEFIELDS-1);

  int prev = 0;
  for( int i = 0; i < BATTLEFIELDS-1; ++i ) {
    ret[i] = dist[i]-prev;
    prev = dist[i];
  }
  ret[BATTLEFIELDS-1] = 100 - prev;

  return formation(ret);
}
bool formation::lopsided() {
  int count = 0;
  for( int i = 0; i < BATTLEFIELDS; ++i) {
    if( form[i] < 7  ) {
      count++;
    }
    if ( form[i] > 35 ) {
      return true;
    }
  }
  if( count >4 ) {
    return true;
  }
  return false;
}
bool formation::poor() const {
  int score;
 if( ( score = this->simulate(given,GIVEN_SIZE)) < GIVEN_SIZE / 3  ) {
   return true;
 }
 return false;
}
formation formation::rand_formation() {
  formation f = formation::randf();
  bool  por;
  while(  (por = f.poor()) && f.lopsided()) {
    if( por ) {
    } 
    f = formation::randf();
  }
  return f;
}
int formation::battle( const formation &player_formation,
    const formation &enemy_formation) {
  int victories = 0;

  for (int i = 0; i < BATTLEFIELDS; ++i) {
    if( player_formation[i] > enemy_formation[i] ) {
      ++victories;
    }
  }
  if( victories == 5 ) {
    return TIE;
  } else if ( victories > 5 ) {
    return WIN;
  } else {
    return LOSE;
  }

}
formation::formation( int form[] )
:wins(0),loses(0)
{
  ties = 0;
  for( int i = 0; i < BATTLEFIELDS; ++i) {
    this->form[i] = form[i];
  }
}
void formation::print( const formation &form) {
  print(form.form);
  cout << "L" << form.loses << " W" 
    << form.wins<< " " << form.score() << endl;
}
int formation::operator<(const formation &r) const {
  return this->score() < r.score();
}
int& formation::operator[](int index) {
  return form[index];
}
int formation::operator[](int index) const {
  return form[index];
}
formation::formation( const formation &r){
  *this = r;
}
void formation::print() const {
  print(*this);
}
formation& formation::operator=(const formation &r) {
  for( int i = 0; i < BATTLEFIELDS; ++i) {
    this->form[i] = r[i];
  }
  this->wins = r.wins;
  this->loses = r.loses;
  return *this;
}
void formation::print( const int form [] ) {
  for( int i = 0; i < BATTLEFIELDS; ++i ) {
    cout << form[i] << " ";
  }
}
