/** mqueue library **/
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
  const char* QUEUE_NAME = "/my_posix_queue";
  mqd_t mq;
  struct mq_attr attr;

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;      // Max messages in queue
  attr.mq_msgsize = 1024;   // Max size of each message
  attr.mq_curmsgs = 0;

  mq = mq_open(QUEUE_NAME, O_CREATE | O_RDWR, 0644, &attr);
  if (mq == (mqd_t)-1) {
     perror("Failed to open queue.");
     return 1;
  }

  const char* msg = "Hello IPC";
  if (mq_send(mq, msg, strlen(msg) + 1, 0) == -1) {
     perror("Failed to send");
     return 1;
  }
  cout << "Sent: " << msg << endl;

  char buffer[1024];
  unsigned int priority;
  if (mq_receive(mq. buffer, 1024, &priority) == -1) {
     perror("Failed to receive");
     return 1;
  }
  cout << "Recevied: " << buffer << endl;

  mq_close(mq);
  mq_unlink(QUEUE_NAME);

  return 0;
}

/** Shared memory libary **/
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
  const char* SHM_NAME = "/my_shared_memory";
  const size_t SHM_SIZE = 4096;

  int shm_fd = shm_open(SHM_NAME, O_CREATE | O_RDWR, 0666);
  if (shm_fd == -1) {
     perror("shm_open failed");
     return 1;
  }

  if (ftruncate(shm_fd, SHM_SIZE) == -1) {
     perror("ftruncate failed");
     return 1;
  }

  void* ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
     perror("mmap failed");
     return 1;
  }

  const char* message = "Hello Shared Memory";
  memcpy(ptr, message, strlen(message) + 1);
  cout << "Written: " << message << endl;

  cout << "Read: " << static_cast<char*>(ptr) << endl;

  munmap(ptr, SHM_SIZE);
  close(shm_fd);
  shm_unlink(SHM_NAME);

  return 0;
}
