/**
 * @file
 * <pre> CPE 357 Spring 2011
 * -------------------
 *
 *  Program "describe the program here (without quotes)"
 *
 *  Last Modified: Wed Oct 29 13:39:06 PM PDT 2008</pre>
 *  @author Matthew Tondreau
 */

#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include "formation.h"
#include <iostream>
#include <ostream>
#include "genetic.h"
#include <ctime>
using namespace std; 

void mydisp( ostream &out, int time ); 
/** Main entry.
 * @param argc the number of tokens on the input line.
 * @param argv an array of tokens.
 * @return 0 on success, 1-255 on failure
 */
int
main(int argc, char *argv[])
{ 
  srand(time(0));
  int old[10];
  for( int i =0; i < 10; ++i) {
    cin >>old[i];
  }
  cout << "Init pool.." << endl;
  genetic g(old);
  cout << "Starting simulations " << endl; 
  formation f(old);
  g.simulate_formation(f);
  cerr << "Using Prev Max: ";
  int i = 0;
  f.print();
  while(true) {
    g.run();
    if( f < (g.best()) ) {
      f = g.best();
      cerr << "New Best Found: ";
      f.print();
    }
    cerr << '\r' << i << "Matings: " << g.num_mates 
      << " Mutations: " << g.num_mutations << " ";
    
    i++;
  }

  /*formation f;
  int myFormation [] = {0,0,0,0,16,16,17,17,17,17};
  int count [] = {0,0,0};
  int outcome;
  f.print(myFormation);
  for( int i = 0; i < SIMULATIONS; ++i ) {
    int * enemy = f.rand_formation();
    f.print(enemy);
    
    outcome = battle(myFormation,enemy);
    ++count[outcome];
  }

  cout << "Wins: \t" << count[WIN] << endl
       << "Ties: \t" << count[TIE] << endl
       << "Loses:\t" << count[LOSE] << endl;

    */
  return EXIT_SUCCESS;
}
void mydisp( ostream &out, int time ) {
  int secs = time %60;
  time /= 60;
  int mins = time % 60;
  time /=60;
  int hours = time;
  if( hours ) {
    out << hours << " hrs. ";
  }
  if ( mins || hours) {
    out << mins << " min. ";
  }
  out << secs << "sec. ";
}

