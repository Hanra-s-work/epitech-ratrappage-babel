# epitech-ratrappage-babel

This is the epitech r-type catch up project called babel responsible for allowing two clients to speak to one another.

## Setting up

### Prerequisites

- CMake (version 3.10 or higher)
- A C++ compiler (GCC for Linux, Clang for macOS, Visual Studio for Windows)

### Linux

1. Install the required dependencies.

   ```sh
   sudo apt-get update
   sudo apt-get install -y cmake g++ git
   ```

2. Clone the repository.

   ```sh
   git clone https://github.com/Hanra-s-work/epitech-ratrappage-babel.git
   cd epitech-ratrappage-babel
   ```

3. Run the `RUN_ME.sh` script to compile the program

   ```sh
   chmod +x ./RUN_ME.sh && ./RUN_ME.sh
   ```

4. The `babel_client` binary will be located in the `build` directory as well as in the same folder from which you ran the `RUN_ME.sh` script.

### macOS

1. Install the required dependencies using Homebrew.

   ```sh
   brew install cmake git
   ```

2. Clone the repository.

   ```sh
   git clone https://github.com/Hanra-s-work/epitech-ratrappage-babel.git
   cd epitech-ratrappage-babel
   ```

3. Run the `RUN_ME.sh` script to compile the program

   ```sh
   chmod +x ./RUN_ME.sh && ./RUN_ME.sh
   ```

4. The `babel_client` binary will be located in the `build` directory as well as in the same folder from which you ran the `RUN_ME.sh` script.

### Windows

1. Install Visual Studio with C++ development tools and CMake.
2. Install the required dependencies using vcpkg.

   ```sh
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg integrate install
   .\vcpkg install git
   ```

3. Clone the repository.

   ```sh
   git clone https://github.com/Hanra-s-work/epitech-ratrappage-babel.git
   cd epitech-ratrappage-babel
   ```

4. Create a build directory and navigate into it.

   ```sh
   mkdir build
   cd build
   ```

5. Run CMake to configure the project and generate the Visual Studio solution.

   ```sh
   cmake -S . -B . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
   ```

6. Open the generated solution file (`epitech-ratrappage-babel.sln`) in Visual Studio.
7. Build the project by selecting `Build > Build Solution` from the menu.

8. The `babel_client.exe` binary will be located in the `build` directory.

## Running the Program

### Linux

1. Open a terminal.
2. Navigate to the directory containing the `babel_client` binary.

   ```sh
   cd /path/to/babel_client
   ```

3. Run the program with the desired options.

   ```sh
   ./babel_client -p <port> -i <ip> [options]
   ```

### macOS

1. Open a terminal.
2. Navigate to the directory containing the `babel_client` binary.

   ```sh
   cd /path/to/babel_client
   ```

3. Run the program with the desired options.

   ```sh
   ./babel_client -p <port> -i <ip> [options]
   ```

### Windows

1. Open Command Prompt.
2. Navigate to the directory containing the `babel_client` binary.

   ```batch
   cd \path\to\babel_client
   ```

3. Run the program with the desired options.

   ```batch
   babel_client.exe -p <port> -i <ip> [options]
   ```

### Options

- `-p <port>`: Set the port to connect to (default: 9000).
- `-i <ip>`: Set the IP to connect to (default: 0.0.0.0).
- `-r`: Set the client to receiver mode.
- `-s`: Set the client to sender mode.
- `-d`: Enable debug mode.
- `-l`: Enable log mode.
- `-m <maxRounds>`: Set the maximum number of rounds, 0 = endless.
- `-e`: Enable echo mode for the user prompt.
- `-a`: Display all boot screens.
- `-h, --help`: Display the help message.
- `-mono`: Set the program to mono mode.
- `-so`: Set the program to sender only mode.
- `-ro`: Set the program to receiver only mode.
- `-v`: Display the program's version.
- `--packet-delay, -pd, -packet-delay, --pd, -packetdelay, --packetdelay`: Set the delay between packets in milliseconds.

### Example

To start the program as a sender on port 9000 with IP 127.0.0.1:

```sh
./babel_client -p 9000 -i 127.0.0.1 -s -mono
```

To start the program as a receiver on the same port and ip (in another terminal instance):

```sh
./babel_client -p 9000 -i 127.0.0.1 -s -mono -ro
```

Once both instances are running, you should be able to hear the audio being picked up by your computer's mic come out of your computers speakers with a slight delay (due to it being recorded, encoded, sent, received, decoded, played in real time).

If you wish to visualise the data being sent in between the programs, you can add the `-l -d` flags, you will not be able to obtain sound that will bedicernable (due to the lag induced by the logger), but you will be able to visualise the raw data being exchanged between both clients.
