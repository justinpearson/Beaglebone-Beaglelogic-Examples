#include "jadcpwmeqep.h"


///////////////////////////////////////////////////////////////
// common.c

#include <stdio.h> // jpp added
#include <string.h> // jpp added
#include <errno.h> // jpp added


#include <dirent.h>
#include <time.h>
#include <unistd.h> // for usleep








///////////////////////////////////////////////////////////////
// eqep.h



///////////////////////////////////////////////////////////////
// eqep.cpp

// Language dependencies
// #include <cstdint>
// #include <cstdlib>
// #include <cstdio>

// POSIX dependencies
#include <unistd.h>
#include <fcntl.h>
#include <poll.h> 
#include <sys/types.h> 
#include <sys/stat.h> 


// Constructor for eQEP driver interface object
void eqep_init()
{
    // Set the mode of the hardware
  eqep_set_mode(0); // absolute
    
    // Reset the position
  eqep_set_position(0);
}

// Set the position of the eQEP hardware
void eqep_set_position(int32_t position)
{
    // Open the file representing the position
    FILE *fp = fopen((EQEP_SYSFS "/position"), "w");
    
    // Check that we opened the file correctly
    if(fp == NULL)
    {
        // Error, break out
        printf(  "[eQEP "  EQEP_SYSFS  "] Unable to open position for write"  );
        return;
    }

    // Write the desired value to the file
    fprintf(fp, "%d\n", position);
    
    // Commit changes
    fclose(fp);
}

// Set the period of the eQEP hardware
void eqep_set_period(uint64_t period)
{
    // Open the file representing the position
    FILE *fp = fopen((EQEP_SYSFS "/period"), "w");
    
    // Check that we opened the file correctly
    if(fp == NULL)
    {
        // Error, break out
        printf(  "[eQEP "  EQEP_SYSFS  "] Unable to open period for write"  );
        return;
    }

    // Write the desired value to the file
    fprintf(fp, "%llu\n", (long long) period);
    
    // Commit changes
    fclose(fp);
}

// Set the mode of the eQEP hardware
void eqep_set_mode(eQEP_Mode _mode)
{
    // Open the file representing the position
    FILE *fp = fopen((EQEP_SYSFS "/mode"), "w");
    
    // Check that we opened the file correctly
    if(fp == NULL)
    {
        // Error, break out
        printf(  "[eQEP "  EQEP_SYSFS  "] Unable to open mode for write"  );
        return;
    }

    // Write the desired value to the file
    fprintf(fp, "%u\n", _mode);
    
    // Commit changes
    fclose(fp);
}


// Get the position of the hardware
int32_t eqep_get_position()
{
 
  //  bool _poll = false; // jpp: dunno. was set to true by default in cpp code, but it says false reads the immediate value.
  
    // Position temporary variable
    int32_t       position;


    /* char          dummy; */
    /* struct pollfd ufd; */
    
    /* // Do we want to poll?  */
    /* if(_poll) */
    /* { */
    /*     // Open a connection to the attribute file. */
    /*     if ((ufd.fd = open((EQEP_SYSFS "/position"), O_RDWR)) < 0) */
    /*     { */
    /*         // Error, break out */
    /*         printf(  "[eQEP "  EQEP_SYSFS  "] Unabled to open position for polling"  ); */
    /*         return 0 ; */
    /*     } */

    /*     // Dummy read */
    /*     read(ufd.fd, &dummy, 1); */
        
    /*     // Poll the port */
    /*     ufd.events = POLLPRI; */
    /*     if (poll(&ufd, 1, -1) < 0) */
    /*     { */
    /*         // Error, break out */
    /*         printf(  "[eQEP "  EQEP_SYSFS  "] Error occured whilst polling"  ); */
    /*         close(ufd.fd); */
    /*         return 0 ; */
    /*     } */
    /* }  */
    
    // Read the position
    FILE *fp = fopen((EQEP_SYSFS "/position"), "r");
    
    // Check that we opened the file correctly
    if(fp == NULL)
    {
        // Error, break out
      printf( "[eQEP " EQEP_SYSFS "] Unable to open position for read");
      //        close(ufd.fd);
        return 0 ;
    }

    // Write the desired value to the file
    fscanf(fp, "%d", &position);
    
    // Commit changes
    fclose(fp);
    
    /* // If we were polling, close the polling file */
    /* if(_poll) */
    /* { */
    /*     close(ufd.fd); */
    /* } */
    
    // Return the position
    return position;
}

// Get the period of the eQEP hardware
uint64_t eqep_get_period()
{
    // Open the file representing the position
    FILE *fp = fopen((EQEP_SYSFS "/period"), "r");
    
    // Check that we opened the file correctly
    if(fp == NULL)
    {
        // Error, break out
      printf("[eQEP " EQEP_SYSFS "] Unable to open period for read");
        return 0 ;
    }

    // Write the desired value to the file
    uint64_t period = 0;
    fscanf(fp, "%llu", (long long unsigned int*) &period);
    
    // Commit changes
    fclose(fp);
    
    // Return the period
    return period;
}

// Get the mode of the eQEP hardware
eQEP_Mode eqep_get_mode()
{
    // Open the file representing the position
    FILE *fp = fopen((EQEP_SYSFS "/mode"), "r");
    
    // Check that we opened the file correctly
    if(fp == NULL)
    {
        // Error, break out
      printf("[eQEP " EQEP_SYSFS "] Unable to open mode for read");
        return eQEP_Mode_Error;
    }

    // Write the desired value to the file
    eQEP_Mode mode;
    fscanf(fp, "%u", (unsigned int*) &mode);
    
    // Commit changes
    fclose(fp);
    
    // Return the mode
    return mode;
}




///////////////////////////////////////////////////////////////
// common.h
#define MODE_UNKNOWN -1
#define BOARD        10
#define BCM          11

#define ARRAY_SIZE(a)  (sizeof(a) / sizeof(a[0]))

#define FILENAME_BUFFER_SIZE 128

int gpio_mode;
int gpio_direction[120];
char ctrl_dir[128];
char ocp_dir[128];



int get_uart_device_tree_name(const char *name, char *dt);
int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len);
int get_spi_bus_path_number(unsigned int spi);
int load_device_tree(const char *name);
int unload_device_tree(const char *name);
int setup_error;
int module_setup;


///////////////////////////////////////////////////////////////
// common.c
typedef struct pins_t { 
    const char *name; 
    const char *key; 
    int gpio;
    int pwm_mux_mode;
    int ain;
} pins_t;

//Table generated based on https://raw.github.com/jadonk/bonescript/master/node_modules/bonescript/bone.js
pins_t table[] = {
  { "USR0", "USR0", 53, -1, -1},
  { "USR1", "USR1", 54, -1, -1},
  { "USR2", "USR2", 55, -1, -1},
  { "USR3", "USR3", 56, -1, -1},
  { "DGND", "P8_1", 0, -1, -1},
  { "DGND", "P8_2", 0, -1, -1},
  { "GPIO1_6", "P8_3", 38, -1, -1},
  { "GPIO1_7", "P8_4", 39, -1, -1},
  { "GPIO1_2", "P8_5", 34, -1, -1},
  { "GPIO1_3", "P8_6", 35, -1, -1},
  { "TIMER4", "P8_7", 66, -1, -1},
  { "TIMER7", "P8_8", 67, -1, -1},
  { "TIMER5", "P8_9", 69, -1, -1},
  { "TIMER6", "P8_10", 68, -1, -1},
  { "GPIO1_13", "P8_11", 45, -1, -1},
  { "GPIO1_12", "P8_12", 44, -1, -1},
  { "EHRPWM2B", "P8_13", 23, 4, -1},
  { "GPIO0_26", "P8_14", 26, -1, -1},
  { "GPIO1_15", "P8_15", 47, -1, -1},
  { "GPIO1_14", "P8_16", 46, -1, -1},
  { "GPIO0_27", "P8_17", 27, -1, -1},
  { "GPIO2_1", "P8_18", 65, -1, -1},
  { "EHRPWM2A", "P8_19", 22, 4, -1},
  { "GPIO1_31", "P8_20", 63, -1, -1},
  { "GPIO1_30", "P8_21", 62, -1, -1},
  { "GPIO1_5", "P8_22", 37, -1, -1},
  { "GPIO1_4", "P8_23", 36, -1, -1},
  { "GPIO1_1", "P8_24", 33, -1, -1},
  { "GPIO1_0", "P8_25", 32, -1, -1},
  { "GPIO1_29", "P8_26", 61, -1, -1},
  { "GPIO2_22", "P8_27", 86, -1, -1},
  { "GPIO2_24", "P8_28", 88, -1, -1},
  { "GPIO2_23", "P8_29", 87, -1, -1},
  { "GPIO2_25", "P8_30", 89, -1, -1},
  { "UART5_CTSN", "P8_31", 10, -1, -1},
  { "UART5_RTSN", "P8_32", 11, -1, -1},
  { "UART4_RTSN", "P8_33", 9, -1, -1},
  { "UART3_RTSN", "P8_34", 81, 2, -1},
  { "UART4_CTSN", "P8_35", 8, -1, -1},
  { "UART3_CTSN", "P8_36", 80, 2, -1},
  { "UART5_TXD", "P8_37", 78, -1, -1},
  { "UART5_RXD", "P8_38", 79, -1, -1},
  { "GPIO2_12", "P8_39", 76, -1, -1},
  { "GPIO2_13", "P8_40", 77, -1, -1},
  { "GPIO2_10", "P8_41", 74, -1, -1},
  { "GPIO2_11", "P8_42", 75, -1, -1},
  { "GPIO2_8", "P8_43", 72, -1, -1},
  { "GPIO2_9", "P8_44", 73, -1, -1},
  { "GPIO2_6", "P8_45", 70, 3, -1},
  { "GPIO2_7", "P8_46", 71, 3, -1},
  { "DGND", "P9_1", 0, -1, -1},
  { "DGND", "P9_2", 0, -1, -1},
  { "VDD_3V3", "P9_3", 0, -1, -1},
  { "VDD_3V3", "P9_4", 0, -1, -1},
  { "VDD_5V", "P9_5", 0, -1, -1},
  { "VDD_5V", "P9_6", 0, -1, -1},
  { "SYS_5V", "P9_7", 0, -1, -1},
  { "SYS_5V", "P9_8", 0, -1, -1},
  { "PWR_BUT", "P9_9", 0, -1, -1},
  { "SYS_RESETn", "P9_10", 0, -1, -1},
  { "UART4_RXD", "P9_11", 30, -1, -1},
  { "GPIO1_28", "P9_12", 60, -1, -1},
  { "UART4_TXD", "P9_13", 31, -1, -1},
  { "EHRPWM1A", "P9_14", 50, 6, -1},
  { "GPIO1_16", "P9_15", 48, -1, -1},
  { "EHRPWM1B", "P9_16", 51, 6, -1},
  { "I2C1_SCL", "P9_17", 5, -1, -1},
  { "I2C1_SDA", "P9_18", 4, -1, -1},
  { "I2C2_SCL", "P9_19", 13, -1, -1},
  { "I2C2_SDA", "P9_20", 12, -1, -1},
  { "UART2_TXD", "P9_21", 3, 3, -1},
  { "UART2_RXD", "P9_22", 2, 3, -1},
  { "GPIO1_17", "P9_23", 49, -1, -1},
  { "UART1_TXD", "P9_24", 15, -1, -1},
  { "GPIO3_21", "P9_25", 117, -1, -1},
  { "UART1_RXD", "P9_26", 14, -1, -1},
  { "GPIO3_19", "P9_27", 115, -1, -1},
  { "SPI1_CS0", "P9_28", 113, 4, -1},
  { "SPI1_D0", "P9_29", 111, 1, -1},
  { "SPI1_D1", "P9_30", 112, -1, -1},
  { "SPI1_SCLK", "P9_31", 110, 1, -1},
  { "VDD_ADC", "P9_32", 0, -1, -1},
  { "AIN4", "P9_33", 0, -1, 4},
  { "GNDA_ADC", "P9_34", 0, -1, -1},
  { "AIN6", "P9_35", 0, -1, 6},
  { "AIN5", "P9_36", 0, -1, 5},
  { "AIN2", "P9_37", 0, -1, 2},
  { "AIN3", "P9_38", 0, -1, 3},
  { "AIN0", "P9_39", 0, -1, 0},
  { "AIN1", "P9_40", 0, -1, 1},
  { "CLKOUT2", "P9_41", 20, -1, -1},
  { "GPIO0_7", "P9_42", 7, 0, -1},
  { "DGND", "P9_43", 0, -1, -1},
  { "DGND", "P9_44", 0, -1, -1},
  { "DGND", "P9_45", 0, -1, -1},
  { "DGND", "P9_46", 0, -1, -1},
    { NULL, NULL, 0, -1, -1 }
};

typedef struct uart_t { 
    const char *name; 
    const char *path; 
    const char *dt; 
    const char *rx;
    const char *tx;
} uart_t;

uart_t uart_table[] = {
  { "UART1", "/dev/ttyO1", "ADAFRUIT-UART1", "P9_26", "P9_24"},
  { "UART2", "/dev/ttyO2", "ADAFRUIT-UART2", "P9_22", "P9_21"},
  { "UART3", "/dev/ttyO3", "ADAFRUIT-UART3", "P9_42", ""},
  { "UART4", "/dev/ttyO4", "ADAFRUIT-UART4", "P9_11", "P9_13"},
  { "UART5", "/dev/ttyO5", "ADAFRUIT-UART5", "P8_38", "P8_37"},
  { NULL, NULL, 0, NULL, NULL }
};

int lookup_gpio_by_key(const char *key)
{
  pins_t *p;
  for (p = table; p->key != NULL; ++p) {
      if (strcmp(p->key, key) == 0) {
          return p->gpio;
      }
  }
  return 0;
}

int lookup_gpio_by_name(const char *name)
{
  pins_t *p;
  for (p = table; p->name != NULL; ++p) {
      if (strcmp(p->name, name) == 0) {
          return p->gpio;
      }
  }
  return 0;
}

int lookup_ain_by_key(const char *key)
{
  pins_t *p;
  for (p = table; p->key != NULL; ++p) {
      if (strcmp(p->key, key) == 0) {
        if (p->ain == -1) {
          return -1;
        } else {
          return p->ain;
        }
      }
  }
  return -1;
}

int lookup_ain_by_name(const char *name)
{
  pins_t *p;
  for (p = table; p->name != NULL; ++p) {
      if (strcmp(p->name, name) == 0) {
        if (p->ain == -1) {
          return -1;
        } else {
          return p->ain;
        }
      }
  }
  return -1;
}

int lookup_uart_by_name(const char *input_name, char *dt)
{
    uart_t *p;
    for (p = uart_table; p->name != NULL; ++p) {
        if (strcmp(p->name, input_name) == 0) {
            strncpy(dt, p->dt, FILENAME_BUFFER_SIZE);
            dt[FILENAME_BUFFER_SIZE - 1] = '\0';
            return 1;                
        }
    }
    fprintf(stderr, "return 0 lookup_uart_by_name");
    return 0;
}

int copy_pwm_key_by_key(const char *input_key, char *key)
{
    pins_t *p;
    for (p = table; p->key != NULL; ++p) {
        if (strcmp(p->key, input_key) == 0) {
            //validate it's a valid pwm pin
            if (p->pwm_mux_mode == -1)
                return 0;

            strncpy(key, p->key, 7);
            key[7] = '\0';
            return 1;                
        }
    }
    return 0;
}

int get_pwm_key_by_name(const char *name, char *key)
{
    pins_t *p;
    for (p = table; p->name != NULL; ++p) {
        if (strcmp(p->name, name) == 0) {
            //validate it's a valid pwm pin
            if (p->pwm_mux_mode == -1)
                return 0;

            strncpy(key, p->key, 7);
            key[7] = '\0';
            return 1;
        }
    }
    return 0;
}

int get_gpio_number(const char *key, unsigned int *gpio)
{
    *gpio = lookup_gpio_by_key(key);
    
    if (!*gpio) {
        *gpio = lookup_gpio_by_name(key);
    }

    return 0;
}

int get_pwm_key(const char *input, char *key)
{
    if (!copy_pwm_key_by_key(input, key)) {
        return get_pwm_key_by_name(input, key);
    }

    return 1;
}

int get_adc_ain(const char *key, int *ain)
{
    *ain = lookup_ain_by_key(key);
    
    if (*ain == -1) {
        *ain = lookup_ain_by_name(key);

        if (*ain == -1) {
          return 0;
        }
    }

    return 1;
}

int get_uart_device_tree_name(const char *name, char *dt)
{
    if (!lookup_uart_by_name(name, dt)) {
      fprintf(stderr, "return 0 get_uart");
        return 0;
    }

    return 1;
}

int build_path(const char *partial_path, const char *prefix, char *full_path, size_t full_path_len)
{
    DIR *dp;
    struct dirent *ep;

    dp = opendir (partial_path);
    if (dp != NULL) {
        while ((ep = readdir (dp))) {
            // Enforce that the prefix must be the first part of the file
            char* found_string = strstr(ep->d_name, prefix);

            if (found_string != NULL && (ep->d_name - found_string) == 0) {
                snprintf(full_path, full_path_len, "%s/%s", partial_path, ep->d_name);
                (void) closedir (dp);
                return 1;
            }
        }
        (void) closedir (dp);
    } else {
        return 0;
    }

    return 0;
}

int get_spi_bus_path_number(unsigned int spi)
{
  char path[50];
  
  build_path("/sys/devices/platform", "ocp", ocp_dir, sizeof(ocp_dir));

  if (spi == 0) {
    snprintf(path, sizeof(path), "%s/48030000.spi/spi_master/spi1", ocp_dir);
  } else {
    snprintf(path, sizeof(path), "%s/481a0000.spi/spi_master/spi1", ocp_dir);
  }
  
  DIR* dir = opendir(path);
  if (dir) {
    closedir(dir);
    //device is using /dev/spidev1.x
    return 1;
  } else if (ENOENT == errno) {
    //device is using /dev/spidev2.x
    return 2;
  } else {
    return -1;
  }
}


int load_device_tree(const char *name)
{
    FILE *file = NULL;
    char slots[128];
    char line[256];

    build_path("/sys/devices/platform", "bone_capemgr", ctrl_dir, sizeof(ctrl_dir));
    snprintf(slots, sizeof(slots), "%s/slots", ctrl_dir);

    file = fopen(slots, "r+");
    if (!file) {
        // PyErr_SetFromErrnoWithFilename(PyExc_IOError, slots);
      printf("__FILE__, __func__ (__LINE__): Can't open the slots file: %s", slots);
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        //the device is already loaded, return 1
        if (strstr(line, name)) {
            fclose(file);
            return 1;
        }
    }

    //if the device isn't already loaded, load it, and return
    fprintf(file, "%s",name);
    fclose(file);

    //0.2 second delay
    // nanosleep((struct timespec[]){{0, 200000000L}}, NULL);
    usleep(200000L); // jpp

    return 1;
}

int unload_device_tree(const char *name)
{
    FILE *file = NULL;
    char slots[128];
    char line[256];
    char *slot_line;

    build_path("/sys/devices/platform", "bone_capemgr", ctrl_dir, sizeof(ctrl_dir));
    snprintf(slots, sizeof(slots), "%s/slots", ctrl_dir);

    file = fopen(slots, "r+");
    if (!file) {
        // PyErr_SetFromErrnoWithFilename(PyExc_IOError, slots);
      printf("__FILE__, __func__ (__LINE__): Can't open the slots file: %s", slots);
        return 0;
    }

    while (fgets(line, sizeof(line), file)) {
        //the device is loaded, let's unload it
        if (strstr(line, name)) {
            slot_line = strtok(line, ":");
            //remove leading spaces
            while(*slot_line == ' ')
                slot_line++;

            fprintf(file, "-%s", slot_line);
            fclose(file);
            return 1;
        }
    }

    //not loaded, close file
    fclose(file);

    return 1;
}


///////////////////////////////////////////////////////////////
// c_adc.h
//int adc_initialized;
// int adc_setup(void);
// int read_value(unsigned int ain, float *value);
// void adc_cleanup(void);





//////////////////////////////////////////////////////////////
// c_adc.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


const char *adc_prefix_dir = "/sys/bus/iio/devices/iio:device0/";

int adc_initialized = 0;

int initialize_adc(void)
{
    char test_path[60];
    FILE *fh;
    if (adc_initialized) {
        return 1;
    }

    snprintf(test_path, sizeof(test_path), "%s", adc_prefix_dir);
    fh = fopen(test_path, "r");

    if (!fh) {
        return 0;
    }
    fclose(fh);

    adc_initialized = 1;
    return 1;
}

int read_value(unsigned int ain, float *value)
{
    FILE * fh;
    char ain_path[60];
    int err, try_count=0;
    int read_successful;
    snprintf(ain_path, sizeof(ain_path), "%s/in_voltage%d_raw", adc_prefix_dir, ain);
    
    read_successful = 0;

    // Workaround to AIN bug where reading from more than one AIN would cause access failures
    while (!read_successful && try_count < 3)
    {
        fh = fopen(ain_path, "r");

        // Likely a bad path to the ocp device driver 
        if (!fh) {
            return -1;
        }

        fseek(fh, 0, SEEK_SET);
        err = fscanf(fh, "%f", value);

        if (err != EOF) read_successful = 1;
        fclose(fh);

        try_count++;
    }

    if (read_successful) return 1;

    // Fall through and fail
    return -1;
}

int adc_setup()
{
    return initialize_adc();
}

void adc_cleanup(void)
{
    unload_device_tree("cape-bone-iio");
}



//////////////////////////////////////////////////////////////
// c_pwm.h




//////////////////////////////////////////////////////////////
// c_pwm.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


#define KEYLEN 7

#define PERIOD 0
#define DUTY 1

int pwm_initialized = 0;

// pwm exports
struct pwm_exp
{
    char key[KEYLEN+1]; /* leave room for terminating NUL byte */
    int period_fd;
    int duty_fd;
    int polarity_fd;
    unsigned long duty;
    unsigned long period_ns;
    struct pwm_exp *next;
};
struct pwm_exp *exported_pwms = NULL;

struct pwm_exp *lookup_exported_pwm(const char *key) 
{
    struct pwm_exp *pwm = exported_pwms;
    //printf("SEARCH\n");
    while (pwm != NULL)
    {
	//printf("%s -> %s\n",pwm->key,key);
        if (strcmp(pwm->key, key) == 0) {
            return pwm;
        }
        pwm = pwm->next;
    }

    return NULL; /* standard for pointers */
}

int initialize_pwm(void)
{
    if  (!pwm_initialized && load_device_tree("am33xx_pwm")) {
        build_path("/sys/devices/platform", "ocp", ocp_dir, sizeof(ocp_dir));

	printf("(%s) (%s) (%d) ocp_dir: %s\n",__FILE__,__func__,__LINE__,ocp_dir);
        pwm_initialized = 1;
        return 1;
    }

    return 0;   
}

int pwm_set_frequency(const char *key, float freq) {
    int len;
    char buffer[20];
    unsigned long period_ns;
    struct pwm_exp *pwm;

    if (freq <= 0.0)
        return -1;

    pwm = lookup_exported_pwm(key);

    if (pwm == NULL) {
        return -1;
    }

    period_ns = (unsigned long)(1e9 / freq);

    if (period_ns != pwm->period_ns) {
        pwm->period_ns = period_ns;

        len = snprintf(buffer, sizeof(buffer), "%lu", period_ns);
        write(pwm->period_fd, buffer, len);
    }

    return 1;
}

int pwm_set_polarity(const char *key, int polarity) {
    int len;
    char buffer[7]; /* allow room for trailing NUL byte */
    struct pwm_exp *pwm;

    pwm = lookup_exported_pwm(key);

    if (pwm == NULL) {
        return -1;
    }

    len = snprintf(buffer, sizeof(buffer), "%d", polarity);
    write(pwm->polarity_fd, buffer, len);

    return 0;
}

int pwm_set_duty_cycle(const char *key, float duty) {
    int len;
    char buffer[20];
    struct pwm_exp *pwm;

    if (duty < 0.0 || duty > 100.0)
        return -1;

    pwm = lookup_exported_pwm(key);

    if (pwm == NULL) {
        return -1;
    }    

    pwm->duty = (unsigned long)(pwm->period_ns * (duty / 100.0));

    len = snprintf(buffer, sizeof(buffer), "%lu", pwm->duty);
    write(pwm->duty_fd, buffer, len);

    return 0;
}

int pwm_start(const char *key, float duty, float freq, int polarity)
{
    char fragment[32];
    char pwm_test_fragment[32];
    char pwm_test_path[128];
    char period_path[128];
    char duty_path[128];
    char polarity_path[128];
    int period_fd, duty_fd, polarity_fd;
    struct pwm_exp *new_pwm, *pwm;

    if(!pwm_initialized) {
        initialize_pwm();
    }

    snprintf(fragment, sizeof(fragment), "bone_pwm_%s", key);

	printf("preload\n");   

    if (!load_device_tree(fragment)) {
        printf("__FILE__, __func__, __LINE__: Shit, error enabling pin for pwm!");
        return -1;
    }

	printf("postload\n");   

    //creates the fragment in order to build the pwm_test_filename, such as "pwm_test_P9_13"
    snprintf(pwm_test_fragment, sizeof(pwm_test_fragment), "ocp:pwm_test_%s", key);

    //finds and builds the pwm_test_path, as it can be variable...
    build_path(ocp_dir, pwm_test_fragment, pwm_test_path, sizeof(pwm_test_path));

printf("ocp_dir: %s\n", ocp_dir);
printf("key: %s\n", key);
printf("test_frag: %s\n", pwm_test_fragment);
printf("test_path: %s\n", pwm_test_path);

    //create the path for the period and duty
    snprintf(period_path, sizeof(period_path), "%s/period", pwm_test_path);
    snprintf(duty_path, sizeof(duty_path), "%s/duty", pwm_test_path);
    snprintf(polarity_path, sizeof(polarity_path), "%s/polarity", pwm_test_path);

printf("peiod: %s\n", period_path);
printf("duty: %s\n", duty_path);
printf("polarity: %s\n", polarity_path);


    //add period and duty fd to pwm list    
    if ((period_fd = open(period_path, O_RDWR)) < 0)
        return -1;


    if ((duty_fd = open(duty_path, O_RDWR)) < 0) {
        //error, close already opened period_fd.
        close(period_fd);
        return -1;
    }

    if ((polarity_fd = open(polarity_path, O_RDWR)) < 0) {
        //error, close already opened period_fd and duty_fd.
        close(period_fd);
        close(duty_fd);
        return -1;
    }    

    // add to list
    new_pwm = (struct pwm_exp *)malloc(sizeof(struct pwm_exp));
    if (new_pwm == 0) {
        return -1; // out of memory
    }

    strncpy(new_pwm->key, key, KEYLEN);  /* can leave string unterminated */
    new_pwm->key[KEYLEN] = '\0'; /* terminate string */
    new_pwm->period_fd = period_fd;
    new_pwm->duty_fd = duty_fd;
    new_pwm->polarity_fd = polarity_fd;
    new_pwm->next = NULL;

    if (exported_pwms == NULL)
    {
        // create new list
        exported_pwms = new_pwm;
    } else {
        // add to end of existing list
        pwm = exported_pwms;
        while (pwm->next != NULL)
            pwm = pwm->next;
        pwm->next = new_pwm;
    }

    pwm_set_frequency(key, freq);
    pwm_set_polarity(key, polarity);
    pwm_set_duty_cycle(key, duty);

    return 1;
}

int pwm_disable(const char *key)
{
    struct pwm_exp *pwm, *temp, *prev_pwm = NULL;
    char fragment[18];

    snprintf(fragment, sizeof(fragment), "bone_pwm_%s", key);
    unload_device_tree(fragment);

    // remove from list
    pwm = exported_pwms;
    while (pwm != NULL)
    {
        if (strcmp(pwm->key, key) == 0)
        {
            //close the fd
            close(pwm->period_fd);
            close(pwm->duty_fd);
            close(pwm->polarity_fd);

            if (prev_pwm == NULL)
            {
                exported_pwms = pwm->next;
                prev_pwm = pwm;
            } else {
                prev_pwm->next = pwm->next;
            }

            temp = pwm;
            pwm = pwm->next;
            free(temp);
        } else {
            prev_pwm = pwm;
            pwm = pwm->next;
        }
    }
    return 0;    
}

void pwm_cleanup(void)
{
    while (exported_pwms != NULL) {
        pwm_disable(exported_pwms->key);
    }
}


///////////////////////////////////////////////////////
// event_gpio.h


/////////////////////////////////////////////////////
// event_gpio.c

#include <pthread.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

const char *stredge[4] = {"none", "rising", "falling", "both"};

// file descriptors
struct fdx
{
    int fd;
    unsigned int gpio;
    int initial;
    unsigned int is_evented;
    struct fdx *next;
};
struct fdx *fd_list = NULL;

// event callbacks
struct callback
{
    unsigned int gpio;
    void (*func)(unsigned int gpio);
    struct callback *next;
};
struct callback *callbacks = NULL;

// gpio exports
struct gpio_exp
{
    unsigned int gpio;
    struct gpio_exp *next;
};
struct gpio_exp *exported_gpios = NULL;

pthread_t threads;
int event_occurred[120] = { 0 };
int thread_running = 0;
int epfd = -1;

int gpio_export(unsigned int gpio)
{
    int fd, len;
    char str_gpio[10];
    struct gpio_exp *new_gpio, *g;

    if ((fd = open("/sys/class/gpio/export", O_WRONLY)) < 0)
    {
        return -1;
    }
    len = snprintf(str_gpio, sizeof(str_gpio), "%d", gpio);
    write(fd, str_gpio, len);
    close(fd);

    // add to list
    new_gpio = (struct gpio_exp *)malloc(sizeof(struct gpio_exp));
    if (new_gpio == 0)
        return -1; // out of memory

    new_gpio->gpio = gpio;
    new_gpio->next = NULL;

    if (exported_gpios == NULL)
    {
        // create new list
        exported_gpios = new_gpio;
    } else {
        // add to end of existing list
        g = exported_gpios;
        while (g->next != NULL)
            g = g->next;
        g->next = new_gpio;
    }
    return 0;
}

void close_value_fd(unsigned int gpio)
{
    struct fdx *f = fd_list;
    struct fdx *temp;
    struct fdx *prev = NULL;

    while (f != NULL)
    {
        if (f->gpio == gpio)
        {
            close(f->fd);
            if (prev == NULL)
                fd_list = f->next;
            else
                prev->next = f->next;
            temp = f;
            f = f->next;
            free(temp);
        } else {
            prev = f;
            f = f->next;
        }
    }
}

int fd_lookup(unsigned int gpio)
{
    struct fdx *f = fd_list;
    while (f != NULL)
    {
        if (f->gpio == gpio)
            return f->fd;
        f = f->next;
    }
    return 0;
}

int add_fd_list(unsigned int gpio, int fd)
{
    struct fdx *new_fd;

    new_fd = (struct fdx *)malloc(sizeof(struct fdx));
    if (new_fd == 0)
        return -1;  // out of memory

    new_fd->fd = fd;
    new_fd->gpio = gpio;
    new_fd->initial = 1;
    new_fd->is_evented = 0;
    if (fd_list == NULL) {
        new_fd->next = NULL;
    } else {
        new_fd->next = fd_list;
    }
    fd_list = new_fd;
    return 0;
}

int open_value_file(unsigned int gpio)
{
    int fd;
    char filename[40];

    // create file descriptor of value file
    snprintf(filename, sizeof(filename), "/sys/class/gpio/gpio%d/value", gpio);
    if ((fd = open(filename, O_RDONLY | O_NONBLOCK)) < 0)
        return -1;
    add_fd_list(gpio, fd);
    return fd;
}

int gpio_unexport(unsigned int gpio)
{
    int fd, len;
    char str_gpio[10];
    struct gpio_exp *g, *temp, *prev_g = NULL;

    close_value_fd(gpio);

    if ((fd = open("/sys/class/gpio/unexport", O_WRONLY)) < 0)
        return -1;

    len = snprintf(str_gpio, sizeof(str_gpio), "%d", gpio);
    write(fd, str_gpio, len);
    close(fd);

    // remove from list
    g = exported_gpios;
    while (g != NULL)
    {
        if (g->gpio == gpio)
        {
            if (prev_g == NULL)
                exported_gpios = g->next;
            else
                prev_g->next = g->next;
            temp = g;
            g = g->next;
            free(temp);
        } else {
            prev_g = g;
            g = g->next;
        }
    }
        return 0;
}

int gpio_set_direction(unsigned int gpio, unsigned int in_flag)
{
        int fd;
        char filename[40];
        char direction[10] = { 0 };

        snprintf(filename, sizeof(filename), "/sys/class/gpio/gpio%d/direction", gpio);
        if ((fd = open(filename, O_WRONLY)) < 0)
            return -1;

        if (in_flag) {
            strncpy(direction, "out", ARRAY_SIZE(direction) - 1);
        } else {
            strncpy(direction, "in", ARRAY_SIZE(direction) - 1);
        }

        write(fd, direction, strlen(direction));
        close(fd);
        return 0;
}

int gpio_get_direction(unsigned int gpio, unsigned int *value)
{
    int fd;
    char direction[4] = { 0 };
    char filename[40];

    snprintf(filename, sizeof(filename), "/sys/class/gpio/gpio%d/direction", gpio);
    if ((fd = open(filename, O_RDONLY | O_NONBLOCK)) < 0)
        return -1;

    lseek(fd, 0, SEEK_SET);
    read(fd, &direction, sizeof(direction) - 1);

    if (strcmp(direction, "out") == 0) {
        *value = OUTPUT;
    } else {
        *value = INPUT;
    }
 
    return 0;
}

int gpio_set_value(unsigned int gpio, unsigned int value)
{
    int fd;
    char filename[40];
    char vstr[10];

    snprintf(filename, sizeof(filename), "/sys/class/gpio/gpio%d/value", gpio);

    if ((fd = open(filename, O_WRONLY)) < 0)
        return -1;

    if (value) {
        strncpy(vstr, "1", ARRAY_SIZE(vstr) - 1);
    } else {
        strncpy(vstr, "0", ARRAY_SIZE(vstr) - 1);
    }

    write(fd, vstr, strlen(vstr));
    close(fd);
    return 0;
}

int gpio_get_value(unsigned int gpio, unsigned int *value)
{
    int fd = fd_lookup(gpio);
    char ch;

    if (!fd)
    {
        if ((fd = open_value_file(gpio)) == -1)
            return -1;
    }    

    lseek(fd, 0, SEEK_SET);
    read(fd, &ch, sizeof(ch));

    if (ch != '0') {
        *value = 1;
    } else {
        *value = 0;
    }

    return 0;
}

int gpio_set_edge(unsigned int gpio, unsigned int edge)
{
        int fd;
        char filename[40];

        snprintf(filename, sizeof(filename), "/sys/class/gpio/gpio%d/edge", gpio);

        if ((fd = open(filename, O_WRONLY)) < 0)
        return -1;

        write(fd, stredge[edge], strlen(stredge[edge]) + 1);
        close(fd);
        return 0;
}

unsigned int gpio_lookup(int fd)
{
    struct fdx *f = fd_list;
    while (f != NULL)
    {
        if (f->fd == fd)
            return f->gpio;
        f = f->next;
    }
    return 0;
}

void exports_cleanup(void)
{
    // unexport everything
    while (exported_gpios != NULL)
        gpio_unexport(exported_gpios->gpio);
}

int add_edge_callback(unsigned int gpio, void (*func)(unsigned int gpio))
{
    struct callback *cb = callbacks;
    struct callback *new_cb;

    new_cb = (struct callback *)malloc(sizeof(struct callback));
    if (new_cb == 0)
        return -1;  // out of memory

    new_cb->gpio = gpio;
    new_cb->func = func;
    new_cb->next = NULL;

    if (callbacks == NULL) {
        // start new list
        callbacks = new_cb;
    } else {
        // add to end of list
        while (cb->next != NULL)
            cb = cb->next;
        cb->next = new_cb;
    }
    return 0;
}

void run_callbacks(unsigned int gpio)
{
    struct callback *cb = callbacks;
    while (cb != NULL)
    {
        if (cb->gpio == gpio)
            cb->func(cb->gpio);
        cb = cb->next;
    }
}

void remove_callbacks(unsigned int gpio)
{
    struct callback *cb = callbacks;
    struct callback *temp;
    struct callback *prev = NULL;

    while (cb != NULL)
    {
        if (cb->gpio == gpio)
        {
            if (prev == NULL)
                callbacks = cb->next;
            else
                prev->next = cb->next;
            temp = cb;
            cb = cb->next;
            free(temp);
        } else {
            prev = cb;
            cb = cb->next;
        }
    }
}

void set_initial_false(unsigned int gpio)
{
    struct fdx *f = fd_list;

    while (f != NULL)
    {
        if (f->gpio == gpio)
            f->initial = 0;
        f = f->next;
    }
}

int gpio_initial(unsigned int gpio)
{
    struct fdx *f = fd_list;

    while (f != NULL)
    {
        if ((f->gpio == gpio) && f->initial)
            return 1;
        f = f->next;
    }
    return 0;
}

void *poll_thread(void *threadarg)
{
    struct epoll_event events;
    char buf;
    unsigned int gpio;
    int n;

    thread_running = 1;
    while (thread_running)
    {
        if ((n = epoll_wait(epfd, &events, 1, -1)) == -1)
        {
            thread_running = 0;
            pthread_exit(NULL);
        }
        if (n > 0) {
            lseek(events.data.fd, 0, SEEK_SET);
            if (read(events.data.fd, &buf, 1) != 1)
            {
                thread_running = 0;
                pthread_exit(NULL);
            }
            gpio = gpio_lookup(events.data.fd);
            if (gpio_initial(gpio)) {     // ignore first epoll trigger
                set_initial_false(gpio);
            } else {
                event_occurred[gpio] = 1;
                run_callbacks(gpio);
            }
        }
    }
    thread_running = 0;
    pthread_exit(NULL);
}

int gpio_is_evented(unsigned int gpio)
{
    struct fdx *f = fd_list;
    while (f != NULL)
    {
        if (f->gpio == gpio)
            return 1;
        f = f->next;
    }
    return 0;
}

int gpio_event_add(unsigned int gpio)
{
    struct fdx *f = fd_list;
    while (f != NULL)
    {
        if (f->gpio == gpio)
        {
            if (f->is_evented)
                return 1;

            f->is_evented = 1;
            return 0;
        }
        f = f->next;
    }
    return 0;
}

int gpio_event_remove(unsigned int gpio)
{
    struct fdx *f = fd_list;
    while (f != NULL)
    {
        if (f->gpio == gpio)
        {
            f->is_evented = 0;
            return 0;
        }
        f = f->next;
    }
    return 0;
}

int add_edge_detect(unsigned int gpio, unsigned int edge)
// return values:
// 0 - Success
// 1 - Edge detection already added
// 2 - Other error
{
    int fd = fd_lookup(gpio);
    pthread_t threads;
    struct epoll_event ev;
    long t = 0;

    // check to see if this gpio has been added already
    if (gpio_event_add(gpio) != 0)
        return 1;

    // export /sys/class/gpio interface
    gpio_export(gpio);
    gpio_set_direction(gpio, 0); // 0=input
    gpio_set_edge(gpio, edge);

    if (!fd)
    {
        if ((fd = open_value_file(gpio)) == -1)
            return 2;
    }

    // create epfd if not already open
    if ((epfd == -1) && ((epfd = epoll_create(1)) == -1))
        return 2;

    // add to epoll fd
    ev.events = EPOLLIN | EPOLLET | EPOLLPRI;
    ev.data.fd = fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
        return 2;

    // start poll thread if it is not already running
    if (!thread_running)
    {
        if (pthread_create(&threads, NULL, poll_thread, (void *)t) != 0)
            return 2;
    }

    return 0;
}

void remove_edge_detect(unsigned int gpio)
{
    struct epoll_event ev;
    int fd = fd_lookup(gpio);

    // delete callbacks for gpio
    remove_callbacks(gpio);

    // delete epoll of fd
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);

    // set edge to none
    gpio_set_edge(gpio, NO_EDGE);

    // unexport gpio
    gpio_event_remove(gpio);

    // clear detected flag
    event_occurred[gpio] = 0;
}

int event_detected(unsigned int gpio)
{
    if (event_occurred[gpio]) {
        event_occurred[gpio] = 0;
        return 1;
    } else {
        return 0;
    }
}

void event_cleanup(void)
{
    close(epfd);
    thread_running = 0;
    exports_cleanup();
}

int blocking_wait_for_edge(unsigned int gpio, unsigned int edge)
// standalone from all the event functions above
{
    int fd = fd_lookup(gpio);
    int epfd, n, i;
    struct epoll_event events, ev;
    char buf;

    if ((epfd = epoll_create(1)) == -1)
        return 1;

    // check to see if this gpio has been added already, if not, mark as added
    if (gpio_event_add(gpio) != 0)
        return 2;

    // export /sys/class/gpio interface
    gpio_export(gpio);
    gpio_set_direction(gpio, 0); // 0=input
    gpio_set_edge(gpio, edge);

    if (!fd)
    {
        if ((fd = open_value_file(gpio)) == -1)
            return 3;
    }

    // add to epoll fd
    ev.events = EPOLLIN | EPOLLET | EPOLLPRI;
    ev.data.fd = fd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
    {
        gpio_event_remove(gpio);
        return 4;
    }

    // epoll for event
    for (i = 0; i<2; i++) // first time triggers with current state, so ignore
       if ((n = epoll_wait(epfd, &events, 1, -1)) == -1)
       {
           gpio_event_remove(gpio);
           return 5;
       }

    if (n > 0)
    {
        lseek(events.data.fd, 0, SEEK_SET);
        if (read(events.data.fd, &buf, sizeof(buf)) != 1)
        {
            gpio_event_remove(gpio);
            return 6;
        }
        if (events.data.fd != fd)
        {
            gpio_event_remove(gpio);
            return 7;
        }
    }

    gpio_event_remove(gpio);
    close(epfd);
    return 0;
}
