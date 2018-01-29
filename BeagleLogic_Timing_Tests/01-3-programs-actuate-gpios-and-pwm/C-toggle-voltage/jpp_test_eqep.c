// EQEP

#include <stdio.h>
#include <unistd.h>  // for usleep

// #include "eqep.h"
#include "jadcpwmeqep.h"
 #define EQEP_SYSFS "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep"


int main() {

  // ///////////////////////////////
  // // EQEP setup


  printf("Note: I'm using the qQEP sysfs entry:");
  printf("%s",EQEP_SYSFS);
  printf(", so make sure that exists!!\n");

  printf("Calling constructor...\n");
  eqep_init();

  printf("Setting period...\n");
  // Set the unit time period to 100,000,000 ns, or 0.1 seconds
  eqep_set_period(100000000L);


  printf("Starting loop...\n");

  /* printf("test 1:\n"); */

  /* unsigned long micros = 200000L; */
  
  /*   // read eqep encoder of motor shaft */
  /* for( int i=0; i<2; i++ ) {     */
  /*    printf("Shaft: %d\n", eqep1.get_position() );  */
  /*    usleep(micros);     */
  /*    printf("Shaft: %d\n", eqep1.get_position() );  */
  /*    usleep(micros);     */
  /*    printf("Shaft: %d\n", eqep1.get_position() );  */
  /*    usleep(micros);     */
  /*    printf("Shaft: %d\n", eqep1.get_position() );  */
  /*    usleep(micros);     */
  /*    printf("Shaft: %d\n", eqep1.get_position() );  */
  /*    usleep(micros);     */
  /*  }  */

  /* printf("test 2:\n"); */
  /* for( int i=0; i<2; i++ ) {     */
  /*    printf("Shaft: %d\n", eqep1.get_position() );  */
  /*    usleep(micros);     */
  /*  }  */

  /* printf("test 3:\n"); */
  /* for( int i=0; i<20; i++ ) {     */
  /*    printf("Shaft: %d\n", eqep1.get_position() );  */
  /*    usleep(micros);     */
  /*  }  */


  printf("test 4:\n");
  for( int i=0; i<50; i++ ) {    
     printf("Shaft: %d\n", eqep_get_position() ); 
     usleep(100000LL);    
   } 

  
  return 0;



}
