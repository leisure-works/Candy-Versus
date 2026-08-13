# <c-11f917>C</c><c-12f534>a</c><c-13f348>n</c><c-14f155>d</c><c-14ef67>y</c> <c-15ed76>V</c><c-16eb6a>e</c><c-18e05b>r</c><c-1de57a>s</c><c-24d6c7>u</c><c-299cf2>s</c>

The multiplayer <cp>versus</c> mod for Geometry Dash. Candy Versus brings a dedicated <cj>real-time multiplayer experience</c> to Geometry Dash, allowing players to compete against each other through synchronized gameplay, dedicated matches, and server-side validation.

The project is developed and maintained by <cg>Homeless Team</c>, with <ca>NeonGD1667</c> serving as the team leader and lead developer.

## <cg>Features</c>

* Real-time multiplayer PvP matches
* Synchronized opponent gameplay
* Dedicated Versus interface
* Opponent player icon display
* Automatic reconnection support
* Configurable network synchronization interval
* Server-side gameplay validation
* Anti-cheat systems
* Match and connection management
* Network and anti-cheat debugging tools
* Cross-platform support
* And more!

## <ca>Multiplayer</c>

Candy Versus uses a <cp>client/server architecture</c> to provide its multiplayer functionality.

The Geometry Dash client communicates with the Candy Versus backend during matches. Player state and other relevant gameplay information can be synchronized with the server and other players.

The server is responsible for managing multiplayer sessions, handling connections, coordinating matches, validating gameplay state, and providing additional server-side protections.

Some internal networking and backend implementation details are intentionally kept private.

## <cb>Anti-Cheat</c>

Candy Versus is designed with <cg>server-side validation</c> in mind.

Important gameplay information should not be trusted exclusively to the client. The server can validate received state and detect potentially invalid or suspicious behavior.

The anti-cheat system is continuously being developed and improved. It is not intended to guarantee detection of every possible exploit.

Detailed anti-cheat and backend implementation is kept private to help protect the infrastructure.

## <cp>Development</c>

Candy Versus is primarily developed using <c-4ddbf2>C++</c> and the <c-7b61ff>Geode SDK</c>.

The project also uses technologies including:

* Geode
* Geode SDK
* CMake
* Git
* GitHub Actions
* `geode.node-ids`

Development builds and other automated tasks are handled through the project's CI workflows.

## <cy>Team</c>

### <ca>Homeless Team</c>

Candy Versus is a project developed and maintained by <cg>Homeless Team</c>.

The team works on software, tools, game modifications, and other development projects.

### <cj>Team Leader & Lead Developer</c>

**NeonGD1667**

NeonGD1667 leads the development of Candy Versus and is responsible for the project's overall direction, architecture, and technical development.

### <cp>Contributors</c>

Candy Versus is supported by contributors who help with:

* Programming
* UI and design
* Testing
* Debugging
* Documentation
* Feedback
* Development and project support

Every contribution helps the project move forward.

## <co>Project Status</c>

**Version:** `v1.0.0`

**Status:** Early Development

Candy Versus is actively being developed. Gameplay systems, networking, UI, backend infrastructure, and other components may change as development continues.

The `v1.0.0` version represents an early stage of the project and does not necessarily represent the final direction of Candy Versus.

## <cr>Security</c>

Candy Versus includes server-side systems designed to reduce the impact of client-side manipulation.

Because the project uses dedicated multiplayer infrastructure, certain backend details, credentials, protocols, and security-related implementation are intentionally not publicly documented.

If you discover a security vulnerability, please report it privately to the project maintainers rather than publicly exposing the issue.

## <cg>Project Vision</c>

Candy Versus aims to make Geometry Dash multiplayer feel <cp>responsive</c>, <cj>competitive</c>, and <ca>fun</c>.

The project is not only about placing two players in the same level. It is intended to explore what a proper multiplayer system for Geometry Dash can look like, including synchronization, matchmaking, validation, competitive gameplay, and dedicated multiplayer infrastructure.

Future development may introduce additional versus modes, improved matchmaking, better synchronization, statistics, player features, and other multiplayer systems.

## <cb>Disclaimer</c>

Candy Versus is an independent third-party modification for Geometry Dash.

It is not affiliated with, endorsed by, or developed by RobTop Games.

Geometry Dash is a trademark of its respective owner.

---

**Candy Versus v1.0.0**
Developed by <cg>Homeless Team</c>
Led by <ca>NeonGD1667</c>
With contributions from the <cp>Candy Versus community</c>
