int roll_dice(int d) { return (d == 6 || d == 10 || d == 20) ? (rand() % d) + 1 : 0; }
