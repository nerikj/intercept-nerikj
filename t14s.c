#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

int read_event(struct input_event *event) {
  return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}

void write_event(const struct input_event *event) {
  if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
    exit(EXIT_FAILURE);
}

int main(void) {
  struct input_event input;

  setbuf(stdin, NULL), setbuf(stdout, NULL);

  while (read_event(&input)) {
    if (input.type == EV_MSC && input.code == MSC_SCAN)
      continue;

    if (input.type != EV_KEY) {
      write_event(&input);
      continue;
    }

    if (input.code == KEY_LEFTALT)
      input.code = KEY_LEFTCTRL;
    else if (input.code == KEY_LEFTMETA)
      input.code = KEY_LEFTALT;
    else if (input.code == KEY_LEFTCTRL)
      input.code = KEY_RIGHTMETA;
    else if (input.code == KEY_RIGHTALT)
      input.code = KEY_RIGHTCTRL;
    else if (input.code == KEY_SYSRQ)
      input.code = KEY_RIGHTALT;
    else if (input.code == KEY_RIGHTCTRL)
      input.code = KEY_RIGHTMETA;

    write_event(&input);
  }
}
