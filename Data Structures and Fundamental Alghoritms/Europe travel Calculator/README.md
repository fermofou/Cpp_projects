## Europe Travel Calculator
This program reads a csv file that contains many different travel possibilities, it includes travel origin, destiny, distance by train and car, and time for both. I use a HashTable to save my cities, and with them and the edges I created with the info, I made a graphos. 

I implemented Dijkstra's shortest path to find the best travel itinerary (least distance) in both car and train. BFS and DFS are also available. In my Hashtable, I start it with a size of 81 (# of cities in my csv), but I added a feature to increase size if needed. To use HashTable's table, I added it as a friend class to Graph class. Also added print feature to show all cities in the graphos.
