FROM ubuntu:20.04

WORKDIR /app

RUN apt-get update

# Set timezone:
RUN ln -snf /usr/share/zoneinfo/$CONTAINER_TIMEZONE /etc/localtime && echo $CONTAINER_TIMEZONE > /etc/timezone

RUN apt-get install -y gcc ruby gcovr make cppcheck python3 python3-pip clang-tidy
RUN pip install lizard
RUN gem install ceedling
