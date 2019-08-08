CXX = g++
CXXFLAGS = -std=c++17

SRCS =  main.cpp
OBJS = ${SRCS:.cpp=.o}
HEADERS = summation.h average.h

MAIN = rr_sched

all: ${MAIN}
		@echo   Compiled!!!

${MAIN}: ${OBJS}
		${CXX} ${CXXFLAGS} ${OBJS} -o ${MAIN}

.cpp.o:
		${CXX} ${CXXFLAGS} -c $< -o $@

clean:
		${RM} ${PROGS} ${OBJS} *.o *~. ${MAIN}
