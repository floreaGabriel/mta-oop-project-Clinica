# ServerPOO Project

## Overview
ServerPOO is a C++ server application designed using object-oriented programming principles. It implements a TCP socket server that handles client connections and processes incoming data.

## Project Structure
The project is organized as follows:

- **Application**: Singleton class that manages the core application logic
- **ServerConnection**: Handles network connections, client requests, and communication
- **DataBase**: (Currently commented out) Interface for database operations

## Setup & Requirements
- Microsoft Visual Studio (Project built with VS 2022)
- Windows platform
- C++ development environment
- Networking libraries (Winsock2)

## Features
- TCP socket server running on port 12345
- Multi-threaded client handling with detached threads
- Singleton application design pattern
- Data processing with routing based on metadata

## Database Schema
The project includes an SQL file to create the `Conturi` table with the following structure:
```sql
create table Conturi(
    ID int not null,
    Nume varchar(40) not null,
    Prenume varchar(40) not null,
    Job varchar(40) not null
);
```

## Building the Project
1. Open the solution file `ServerPOO.sln` in Visual Studio
2. Select the desired build configuration (Debug/Release)
3. Build the solution (F7 or Build > Build Solution)

## Running the Server
Execute the compiled application. The server will start and listen on port 12345.

## Data Processing
The server processes incoming data based on a protocol where:
- First byte is a metadata tag indicating the type of request
- The rest of the data is the actual content

Current implementation route:
- '1': Login window data processing

## Code Structure
- **Application.h/cpp**: Implements the Singleton pattern for the main application
- **ServerConnection.h/cpp**: Manages socket connections and client communication
- **DataBase.h**: Interface for database operations (currently commented out)
- **main.cpp**: Application entry point

## Network Communication
The server:
1. Creates a socket
2. Binds to port 12345
3. Listens for incoming connections
4. Accepts connections and processes data in separate threads

## Future Development
- Complete the database integration
- Implement more data processing routes
- Add robust error handling and logging
- Enhance security features

## Notes
- The database functionality is currently commented out and would need implementation
- Additional client handling logic can be added to the `manageData` function
