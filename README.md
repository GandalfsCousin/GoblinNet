# GoblinNet

csmit863 cogitatio:
- colloquii secretae inter pares
- codex et disputatio de projecto solum Latine agendae, nisi aliter statutum erit.
- Codicem lingua C scribendum esse oportet. Hoc modo, binarium productum verificari potest.
- Propositum Latine scribendi est discere: linguam Latinam, codicis scribendi, architecturam programmatis, atque cogitationem criticam.
- pulchrum videtur
![goblin](resources/goblinnet.jpg)

## Program Commands

#### CLI:
`goblinnet [--name <name>]`

#### Top level commands 
| Command | Function |
|---------|----------|
| `help`  | Prints all commands. |
| `host <port> [--name <name>] [--password <password>]` | Creates a chatroom.|
| `join <ip> <port>` | Joins established chatroom.|
| `exit` | Closes the program. |

#### Chat level commands
| Command | Function |
|---------|----------|
| `-help`  | Prints all commands. |
| `-leave` | Leaves the current chat, if owner closes chatroom.|
| `-users` | Prints all users currently in the chat, along with their IPs.|