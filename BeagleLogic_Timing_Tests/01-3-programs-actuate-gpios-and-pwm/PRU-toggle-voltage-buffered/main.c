#include "jpp-pru-lib.h"



// What voltage to apply, as a fn of sample number?
double f(unsigned int sn) {
  double voltage;
  voltage = (sn%2==0) ? 1 : -3 ;
  return voltage;
}

int main(int argc, char* argv[]) {

const int MAX_NUM_TIMESTEPS = 200;

  start_pru();

    printf("go!!!!!!!\n");

    for( int i=0; i<MAX_NUM_TIMESTEPS; i++ ) {

      DataBuffer db;    
      get_data_buf( &db );
      unsigned int sample_num = db[PKTS_PER_DATA_BUFFER-1].sample_num;

      double voltages[PKTS_PER_CMD_BUFFER];

      for( int j=0; j<PKTS_PER_CMD_BUFFER; j++) {
	voltages[j] = f(sample_num+j);
      }

      CommandBuffer cb;
      motor_voltage_schedule_to_cmd_buf( voltages,
					 PKTS_PER_CMD_BUFFER,
					 sample_num,
					 &cb );

      set_cmd_buf( cb ); // ship it off

      usleep(15000); // 32 cmd pkts * 1ms per cmd pkt = 32 ms. 

    }

    printf("done!!!!!!!\n");

    send_single_voltage(0);

}
