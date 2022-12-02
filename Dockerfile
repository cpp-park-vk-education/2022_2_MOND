FROM gcc:latest
RUN apt update -y && \
    apt install -y cppcheck clang-tidy python3-pip \
     libc6-dbg gdb cmake libgtest-dev lcov clang-format \
    google-mock libgmock-dev libboost-dev libboost-program-options-dev \
    libboost-thread-dev libboost-system-dev libboost-serialization-dev
RUN pip install cpplint
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 && \
    tar xfv valgrind-3.18.1.tar.bz2 && \
    cd valgrind-3.18.1 && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make install