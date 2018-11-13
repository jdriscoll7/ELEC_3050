#include "pid_controller.h"

static uint16_t data_acquisition_buffer[DATA_ACQUISITION_BUFFER_SIZE];
static uint32_t data_acquisition_index = 0;
