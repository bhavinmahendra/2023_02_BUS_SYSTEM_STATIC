This project consists in creating a bus management system (static memory allocation - on purpose). It uses the following commands:
 - `q` to quit.
 - `c` lists all lines, with each line showing the first and last stops, the number of stops,  total cost and total duration.
 - `c <line>` adds a line if it does not exist, if it does, lists the stops associated to that line.
 - `c <line> <option>` where `option = {i, in, inv, inve}` and it lists the stops associated to a line, in reverse order.
 - `p` lists all lines, with each line showing the first and last stops, the number of stops,  total cost and total duration.
 - `p <stops>` lists all lines associated with the stop.
 - `p <stop> <latitude> <longitude>` adds a stop with a specific latitude and longitude.
 - `l <line> <stop1> <stop2> <cost> <duration>` creates a link between two stops (on a certain line).
 - `i` lists all the interceptions.

Note: This is an academic project. The idea of the project came from Vasco Manquinho (Instituto Superior Técnico, Lisbon, Portugal)