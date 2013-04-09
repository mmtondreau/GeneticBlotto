/**
 * @file
 * <pre> CPE 357 Spring 2011
 * -------------------
 *
 *  Header to "progrma header"
 *
 *  Last Modified: Tue Apr 09 12:02:50 AM PDT 2013</pre>
 *  @author Matthew Tondreau
 */

#ifndef _GENETIC_H_
#define _GENETIC_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "formation.h"

#define POOL_SIZE 4096
#define SIMULATIONS 512

class genetic {
  public:
    genetic(int old[]);
    bool validate_formation( int form[] );
    formation mate( const formation &a,const formation &b) ;
    void init();
    void print() const;
    void run();
    void mutate(formation &form);
    formation select_mate();
  unsigned num_mutations;
  unsigned num_mates;
  const formation & best() const;
    static void simulate_formation(formation &myForm);
  private:
    formation pool[POOL_SIZE];
    static void simulate_formation(formation &myForm,
        const formation &enemy);
};

#endif
