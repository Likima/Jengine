# JEngine

A modular C++ game engine currently in development (v0.0.0).

## Project Structure

```
JEngine/
├── Core/           # Core engine utilities
├── Engine/         # Main engine systems
├── UI/            # User interface components
├── Game/          # Game logic and examples
│   └── ColorWave/ # Example game implementation
├── App/           # Application launcher
└── Vendor/        # Third-party dependencies
```

## Features

- OpenGL rendering system
- GLFW window management
- Modular architecture
- Game state management
- Input handling system
- Example game implementation (ColorWave)

## Dependencies

- GLFW
- GLEW
- OpenGL 3.3+
- C++17 compiler

## Building

### Linux

1. Install dependencies:
```bash
sudo apt-get install libglfw3-dev libglew-dev
```

2. Run the setup script:
```bash
chmod +x Scripts/Setup-Linux.sh
cd Scripts && bash Setup-Linux.sh && cd ..
```

3. Build the project:
```bash
make
```

4. Run the application:
```bash
./Binaries/linux-x86_64/Debug/App/App
```

Alternatively, use the automated build script:
```bash
chmod +x linux_run.sh
./linux_run.sh
```

### Windows

1. Run the setup script:
```cmd
Scripts\Setup-Windows.bat
```

2. Open the generated solution file in Visual Studio

## Project Components

### Core
- Basic utilities and version management
- Engine initialization

### UI
- Window management via GLFW
- Basic UI components

### Engine
- OpenGL rendering system
- Input handling
- Game loop implementation
- State management

## License

This project is licensed under the Unlicense - see the [UNLICENSE.txt](UNLICENSE.txt) file for details.