FROM gcc:latest
RUN apt update -y && \
    apt install -y build-essential cppcheck clang-tidy python3-pip \
     libc6-dbg gdb libgtest-dev lcov clang-format \
    google-mock libgmock-dev libboost-dev libboost-program-options-dev \
    libboost-thread-dev libboost-system-dev libboost-filesystem-dev libboost-serialization-dev
RUN pip install cpplint
RUN pip install cmake --upgrade
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 && \
    tar xfv valgrind-3.18.1.tar.bz2 && \
    cd valgrind-3.18.1 && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make install

# In CLion, change File->Settings->Build, Execution, Deployment->Toolchains->Decker->Cmake to "\usr\local\bin\cmake"
