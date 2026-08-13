# Candy Versus

**Candy Versus** is a multiplayer PvP mod for **Geometry Dash**, developed by **Homeless Team** and all **contributor**

The project adds a dedicated versus experience to Geometry Dash, allowing players to compete against each other through synchronized multiplayer matches.

> **Status:** v1.0.0 — Early Development

---

## Features

### Multiplayer Versus

* Real-time PvP matches.
* Opponent state synchronization.
* Dedicated versus interface.
* Opponent player icon display.
* Automatic reconnection support.
* Configurable network synchronization interval.

### Connection

Candy Versus connects to a dedicated server for multiplayer functionality.

The server address can be configured through the mod settings.

### Anti-Cheat

Candy Versus includes server-side validation and anti-cheat systems designed to detect invalid or suspicious gameplay states.

Anti-cheat logging can be enabled for development and debugging purposes.

> Anti-cheat implementation is continuously evolving and should not be considered perfect.

### Debugging

Optional debugging tools are available for development:

* Anti-cheat event logging.
* Network packet logging.
* Configurable synchronization interval.
* Connection diagnostics.

---

## Supported Versions

| Platform | Geometry Dash |
| -------- | ------------- |
| Windows  | 2.2081        |
| Android  | 2.2081        |
| macOS    | 2.2081        |
| iOS      | 2.2081        |

Candy Versus currently targets **Geode 5.9.0**.

---

## Requirements

You need:

* Geometry Dash 2.2081
* Geode 5.9.0 or compatible installation
* `geode.node-ids` v1.23.3
* An active Candy Versus server connection

---

## Installation

### From a Release

1. Install Geode for your supported Geometry Dash platform.
2. Download the Candy Versus `.geode` package from an official release.
3. Install the package through Geode.
4. Launch Geometry Dash.
5. Open the Candy Versus interface.
6. Configure the server address if required.
7. Join or create a versus match.

### Development Installation

For developers working directly with the source code:

1. Clone the Candy Versus repository.
2. Install the required Geode development environment.
3. Install the required dependencies.
4. Configure the project for your target platform.
5. Build the mod.
6. Install the generated `.geode` package into your Geode installation.

The production server and backend are maintained separately from the public-facing mod package.

---

## Configuration

Candy Versus provides several settings.

### Connection

| Setting                | Description                                                  |
| ---------------------- | ------------------------------------------------------------ |
| **Server Address**     | Address of the Candy Versus server.                          |
| **Auto Reconnect**     | Automatically attempts to reconnect after a lost connection. |
| **Sync Interval (ms)** | Controls how frequently synchronization packets are sent.    |

The synchronization interval can be configured from **20 ms to 200 ms**.

Lower values may provide more frequent synchronization but can increase bandwidth usage.

### Gameplay

| Setting                   | Description                                         |
| ------------------------- | --------------------------------------------------- |
| **Show Opponent Icon**    | Displays the opponent's player icon during matches. |
| **Opponent Icon Opacity** | Controls the opacity of the opponent icon.          |
| **Toggle Versus Menu**    | Keyboard shortcut for opening the versus interface. |

### Debug

| Setting                 | Description                                    |
| ----------------------- | ---------------------------------------------- |
| **Log Anti-Cheat**      | Logs anti-cheat rejections and flagged events. |
| **Log Network Packets** | Logs detailed network traffic for debugging.   |

Debug logging is disabled by default.

---

## Architecture

Candy Versus consists of multiple components:

```text
Candy Versus
├── Geometry Dash Client
│   ├── Versus UI
│   ├── Gameplay Integration
│   ├── Network Client
│   └── State Synchronization
│
└── Multiplayer Backend
    ├── Authentication
    ├── Matchmaking
    ├── Match Management
    ├── State Validation
    └── Anti-Cheat
```

The client communicates with the Candy Versus backend during multiplayer matches.

Server-side validation is used where possible so that important gameplay decisions are not trusted exclusively to the client.

Detailed backend architecture and internal network implementation are intentionally not documented here.

---

## Development

Candy Versus is developed primarily using C++ and the Geode SDK.

Development tools may include:

* Geode SDK
* CMake
* Visual Studio
* Git
* GitHub Actions

The project uses automated workflows for development builds and other repository tasks.

### Project Structure

```text
Candy-Versus/
├── .github/
│   └── workflows/
├── src/
├── resources/
├── docs/
├── mod.json
├── CMakeLists.txt
├── README.md
├── ABOUT.md
├── CHANGELOG.md
└── SUPPORT.md
```

The exact project structure may change as development progresses.

---

## Building

A development build requires the appropriate Geode development environment.

A typical workflow is:

```text
Source Code
    ↓
CMake Configuration
    ↓
Compilation
    ↓
Geode Package
    ↓
Testing
```

Build artifacts generated during CI are intended for development and testing unless explicitly marked as a release build.

---

## Networking

Candy Versus uses a client/server architecture for multiplayer functionality.

The client is responsible for:

* Sending relevant player state.
* Receiving opponent state.
* Rendering synchronized gameplay information.
* Handling connection state.
* Reconnecting when enabled.

The server is responsible for:

* Managing multiplayer sessions.
* Coordinating matches.
* Validating client state.
* Handling synchronization.
* Detecting suspicious or invalid behavior.

Network behavior may change between versions as the multiplayer protocol evolves.

---

## Anti-Cheat

Candy Versus is designed with server-side validation in mind.

The anti-cheat system may inspect gameplay and network data for inconsistencies or invalid states.

However:

> No client/server anti-cheat system is guaranteed to detect every possible exploit.

Players should report suspected cheating rather than attempting to exploit vulnerabilities.

Detailed detection methods are intentionally kept private.

---

## Security

Do **not** report security vulnerabilities through normal public issue reports.

If you discover a vulnerability involving:

* Server security
* Authentication
* Account access
* Sensitive data
* Backend infrastructure
* Network protocol abuse

please use the private security reporting method provided by the project maintainers.

Never include passwords, API keys, tokens, or other credentials in bug reports.

---

## Support

For installation problems, crashes, configuration issues, or general questions, see [`SUPPORT.md`](SUPPORT.md).

When reporting a problem, include:

* Candy Versus version
* Geometry Dash version
* Platform
* Geode version
* Relevant error messages
* Steps to reproduce the problem
* Relevant logs, if available

Please do not publicly post private server credentials or sensitive information.

---

## Versioning

Candy Versus follows semantic versioning where practical:

```text
MAJOR.MINOR.PATCH
```

For example:

```text
1.0.0
```

Version changes generally represent:

* **MAJOR** — breaking changes
* **MINOR** — new functionality
* **PATCH** — fixes and minor improvements

See [`CHANGELOG.md`](CHANGELOG.md) for release history.

---

## Roadmap

The roadmap is subject to change as development progresses.

Potential future work includes:

* Improved matchmaking
* More versus modes
* Better synchronization
* Improved reconnect handling
* Expanded anti-cheat validation
* Match statistics
* Player profiles
* Improved server infrastructure
* Additional debugging tools
* Performance improvements

Features listed here are not guaranteed to ship.

---

## Contributing

Candy Versus is currently developed as a controlled project.

The repository may remain private while the multiplayer backend and server infrastructure are under development.

Contributions, testing, and code review may be granted to selected collaborators at the discretion of the project maintainer.

---

## Credits

### Developer

**NeonGD1667**

Candy Versus is an independent Geometry Dash multiplayer project.

### Technologies

Candy Versus is built using technologies from the Geometry Dash modding ecosystem, including:

* Geode
* Geode SDK
* `geode.node-ids`

See the project files and dependency metadata for the exact versions used by each release.

---

## License

The licensing terms for Candy Versus are defined by the project's repository and release distribution.

Until an explicit license is published, the source code should not be assumed to be freely redistributable or reusable.

---

## Disclaimer

Candy Versus is a third-party modification for Geometry Dash.

It is not affiliated with, endorsed by, or developed by RobTop Games.

Geometry Dash is a trademark of its respective owner.

---

**Candy Versus v1.0.0**
Developed by :
**Homeless Team** , **NeonGD1667** and **all contributor**
