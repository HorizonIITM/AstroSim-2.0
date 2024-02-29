Enter body information in infile.txt in the format

0 m r x y z vx vy vz

1 m r x y z vx vy vz

2 m r x y z vx vy vz

3 m r x y z vx vy vz

...


For initializers:
./init.exe <infile name> <Initializer type> <Number of bodies>
Where initializer type is 0 for asteroids, 1 for galaxies
Or just use make run

For main code:
./sim.exe <outfile name> <infile name> <Number of particles> <Time step> <Collisions flag>


