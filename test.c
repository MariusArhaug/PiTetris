#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <poll.h>
#include <inttypes.h>

#include <linux/input.h>
#include <linux/fb.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/types.h>

#define PATH "../../../dev/fb0"
#define FILESIZE 64 * sizeof(uint16_t)

// colors to be used in sensehat
#define RGB_565_RED 0xF800
void delay(int);

int main(int argc, char **argv) {
  int fbfd;
  uint16_t *map;
  uint16_t *p;
  struct fb_fix_screeninfo fix_info;

  
  /* open the led frame buffer device */
  fbfd = open(PATH, O_RDWR);
  printf("%d \n", fbfd);
  if (fbfd == -1) {
    perror("Error (call to 'open')");
    exit(EXIT_FAILURE);
  } 

  /* read fixed screen info for the open device */
  if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info) == -1) {
    perror("Error (call to 'ioctl')");
	  close(fbfd);
	  exit(EXIT_FAILURE);
  }

  /* now check the correct device has been found 
  if (strcmp(fix_info.id, "RPi-Sense FB") != 0) {
 	printf("%s\n", "Error: RPi-Sense FB not found");
	close(fbfd);
	exit(EXIT_FAILURE);
  } */

  /* map the led frame buffer device into memory */
  map = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
  if (map == MAP_FAILED) {
    close(fbfd);
    perror("Error mmapping the file");
    exit(EXIT_FAILURE);
  }

  /* set a pointer to the start of the memory area */
  p = map;

  /* clear the led matrix */
  memset(map, 0, FILESIZE);

  /* light it up! */
  printf("lighting up \n");
  for (int i = 0; i < 64; i++) {
     	*(p + i) = RGB_565_RED;
	 delay(25);
  }

  
  /* clear the led matrix */
  memset(map, 0, FILESIZE);

  /* un-map and close */
  if (munmap(map, FILESIZE) == -1) {
  	perror("Error un-mmapping the file");
  }
  close(fbfd);

  return 0;
}

void delay(int t) {
	usleep(t* 1000);
}
