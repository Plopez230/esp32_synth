#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "seq_include.h"

BaseType_t seq_kb_command( char *pcWriteBuffer, size_t xWriteBufferLen, const char *command_string )
{
  int value;
  uint8_t option;
  char *parameter = strtok((char *)command_string, " ");
  snprintf(pcWriteBuffer, xWriteBufferLen, parameter);
  parameter = strtok(NULL," ");
  option = parameter[0];
  parameter = strtok(NULL," ");
  value = atoi(parameter);
  snprintf(pcWriteBuffer, xWriteBufferLen, "change %c to value %i", option, value);
  if (option == 'c')
  {
    seq_system.keyboard->midi_channel = value % 16;
    snprintf(pcWriteBuffer, xWriteBufferLen, "Updated keyboard channel to %i", value % 16);
  }
  else if (option == 't')
  {
    seq_system.keyboard->traspose = value % 128;
    snprintf(pcWriteBuffer, xWriteBufferLen, "Updated keyboard traspose to %i", value % 128);
  }
  else if (option == 'v')
  {
    seq_system.keyboard->velocity = value % 128;
    snprintf(pcWriteBuffer, xWriteBufferLen, "Updated keyboard velocity to %i", value % 128);
  }
  else
  {
    snprintf(pcWriteBuffer, xWriteBufferLen, "Option '%c' not recognized", option);
  }
  //snprintf( pcWriteBuffer, xWriteBufferLen, "keyboard configuration tool");
  return pdFALSE;
}

static const CLI_Command_Definition_t seq_kb_command_def =
{
    "kb",
    "kb <option> <value>",
    seq_kb_command,
    -1
};

BaseType_t seq_mem_command( char *pcWriteBuffer, size_t xWriteBufferLen, const char *command_string )
{
  snprintf(pcWriteBuffer, xWriteBufferLen, "Free heap: %d bytes", ESP.getFreeHeap());
  return pdFALSE;
}

static const CLI_Command_Definition_t seq_mem_command_def =
{
    "mem",
    "mem",
    seq_mem_command,
    0
};

void seq_register_commands()
{
  FreeRTOS_CLIRegisterCommand(&seq_kb_command_def);
  FreeRTOS_CLIRegisterCommand(&seq_mem_command_def);
}
