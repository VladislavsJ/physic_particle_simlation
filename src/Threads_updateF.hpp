///////////////////////////
// MPI_PARTICLE_UPDATE //
///////////////////////////
// now the idea
// i have many threads,
// they can work in "pairs"
// they have different movement priorty, rigt-left right-left
// if one thread ended its job, it sends the sygnal to the master
// master checks if thread "pair" is still working, if yes
// it divides total cells to compute by two TODO(thread safe check)
//
// and gives this half to free thread
// it is not perfect, but it is a good start
// improves performance as not all cells have same amount of particles
// TODO0: Init thread pool before the loop and use them for each frame.

// TODO3: possible improvement,
// I can count particle amount for each thread, and amount of cells
//  and next frame "shift" the cells,
//  like first and second thead eneded much faster, so they can take 1.2 times
//  more cells and the last thread can take 0.8 times less cells as most of the
//  colissions, particles are on the bottom, gravity...

///////////////////////////
// possible races
///////////////////////////
// if one thread ended its job, it sends the sygnal to the master
// master checks if thread "pair" is still working, if yes
// it divides total cells to compute by two TODO(thread safe check)
//
// in the push_back to the vector, I am not sure if it is a
//
// problem since all threads are working on different cells. possible race to
// get data as near thread may ask for the same data,(should not be a problem)
//(if button for one and top for another is the same cell)
// if start is not from the top left/right corner, it may be a problem
