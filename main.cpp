#include <fcntl.h>
#include <ioctl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/uinput.h>


//static int fd_kbd_emulator = -1;
/* Set up a fake keyboard device */
static int fd_kbd_emulator = open("/dev/uinput", O_WRONLY | O_NONBLOCK); // or /dev/input/uinput
if (fd_kbd_emulator == NULL) {
	printf("unable to open fd\n");
	return -1;
}

ioctl(fd_kbd_emulator, UI_SET_EVBIT, EV_KEY);
struct uinput_user_dev uidev;
memset(&uidev, 0, size_of(uinput_ser_dev));


write(fd_kbd_emulator, &uidev, sizeof(uidev));
ioctl(fd_kbd_emulator, UI_DEV_CREATE);
/* Send an event */
struct input_event ev;
memset(&ev, 0, size_of(input_event));

ev.type = EV_KEY;
ev.code = KEY_A;
ev.value = 1;

write(fd_kbd_emulator, &ev, sizeof(ev));
/* Clean up */
ioctl(fd_kbd_emulator, UI_DEV_DESTROY);
close(fd_kbd_emulator);

