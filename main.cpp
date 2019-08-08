#include <iostream>
#include <thread>

#include <unistd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <sys/prctl.h>

int main() {
    std::thread rr_thread([](){
      struct sched_param params = {5};
      pthread_setschedparam(pthread_self(), SCHED_RR, &params);

      struct itimerspec ts;
      struct epoll_event ev;
      int tfd ,epfd;

      ts.it_interval.tv_sec = 0;
	    ts.it_interval.tv_nsec = 0;
	    ts.it_value.tv_sec = 0;
	    ts.it_value.tv_nsec = 20000; // 50 kHz timer

      tfd = timerfd_create(CLOCK_MONOTONIC, 0);
      prctl(PR_SET_NAME, "RR Thread", 0, 0, 0);
      timerfd_settime(tfd, 0, &ts, NULL);
      epfd = epoll_create(1);

      ev.events = EPOLLIN;
      epoll_ctl(epfd, EPOLL_CTL_ADD, tfd, &ev);

      while (true) {
	//epoll_wait(epfd, &ev, 1, -1); // wait forever for the timer
	int missed = 0;
        read(tfd, &missed, sizeof(missed));

        // Here i have a blocking function (dummy in this example) which
        // takes on average 15ns to execute
	auto i=0;
	i++;
      }

    });

    rr_thread.join();
}
