# ======= STAGE 1: Install dependencies ======= #
FROM ubuntu:latest AS base
WORKDIR /app
RUN apt-get update && apt-get install -y \
      cmake \
      build-essential \
      && rm -rf /var/lib/apt/lists/*

COPY CMakeLists.txt .
COPY src/ ./src/

# ======= STAGE 2: Build the app ======= #
FROM base AS build
RUN mkdir build
WORKDIR /app/build
RUN cmake .. && make

# ======= STAGE 3: Run the app ======= #
FROM ubuntu:latest
COPY --from=build /app/build/app /app/app
WORKDIR /app
CMD ["./app"]
