## TODO
- separate object model from gui
- maybe allow storage of geometries for display-purposes?
- connect to server
    choice: sqlite (debugging), mysql
- selection: time-range to display
- periodically query for new data
- plot data
    - line graph, histogram, boxplot, ...
- list of sensors, and sensor-descriptions for every one of them
    - wait.. really? not intuitive!
    the sensor-description is the thing we are interested in: not the number of
    the sensor, but the variable it stands for. *furthermore*, every sensor node
    may have multiple sensors (temperature, humidity, fill-level, ...)
    how can we model that nicely?
