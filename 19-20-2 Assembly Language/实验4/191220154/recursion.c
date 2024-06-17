int recursion(int x) {
    if(x <= 2)
        return 1;
    else
        return recursion(x - 1) + recursion (x - 2);
}
