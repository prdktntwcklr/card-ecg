FROM ubuntu:22.04

WORKDIR /app

COPY packages.txt requirements.txt .

# set timezone
RUN ln -snf /usr/share/zoneinfo/$CONTAINER_TIMEZONE /etc/localtime && \
    echo $CONTAINER_TIMEZONE > /etc/timezone

# update package information and install required packages
RUN apt-get update && \
    xargs -a packages.txt apt-get install --no-install-recommends -y

COPY requirements.txt .
RUN pip install --no-cache-dir --no-deps -r requirements.txt

RUN gem install ceedling

# clean up stale packages
RUN apt-get clean -y && \
    apt-get autoremove --purge -y && \
    rm -rf /var/lib/apt/lists/*
