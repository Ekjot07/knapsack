//Ekjot Singh Panesar, 20BCE0787

#include <iostream>
#include <vector>

//function to return maximum of 2 numbers:
int max(int a, int b) { return (a > b) ? a : b;} //ternary operator

int bruteforceKnapsack(int W, int wt[], int profits[], int n){
    //base condition
    if (W == 0 || n == 0) {
        return 0; //return 0 if no more items or no more capacity
    }

    if (wt[n - 1] > W)  //if the last item is more than the capacity
        return bruteforceKnapsack(W, wt, profits, n - 1); //recursive call for the last item
    else
        return max(profits[n - 1] + bruteforceKnapsack(W - wt[n - 1], wt, profits, n - 1),
                   bruteforceKnapsack(W, wt, profits, n - 1)); //recursive call for the last item 
}


int knapsack2(int W, int wt[], int profits[], int n){ 
    std::vector<std::vector<int>> K(n + 1, std::vector<int>(W + 1)); //2d vector

    // Build table K[][] in bottom up manner
    for(int i = 0; i <= n; i++){ 
        for(int w = 0; w <= W; w++){ 
            if (i == 0 ||  w == 0){
                K[i][w] = 0; //if no more items or no more capacity 
            }
            else if (wt[i - 1] <= w) //if the last item is less than the capacity
                K[i][w] = max(profits[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]); //recursive call for the last item 
            else
                K[i][w] = K[i - 1][w]; //recursive call for the last item
        }
    }
    return K[n][W]; //return the last item
}

int main(int argc, const char * argv[]) {
    clock_t t1, t2; //clock_t is a data type for storing time
    int val[] = { 60, 100, 120 }; //profit of the objects
    int wt[] = { 10, 20, 30 }; //weight of the objects
    int W = 50; //capacity of the knapsack
    int n = sizeof(val) / sizeof(val[0]); //number of objects

    t1 = clock(); //start time
    std::cout << "Total weight(bruteforce): " << bruteforceKnapsack(W, wt, val, n) << std::endl; //bruteforce
    t1 = clock() - t1; //end time
    double time_taken1 = ((double)t1)/CLOCKS_PER_SEC; //converting to seconds
    std::cout << "time taken using bruteforce: " << time_taken1 << std::endl; //printing time taken
 
    t2 = clock(); //start time
    std::cout << "Total weight(dp): " << knapsack2(W, wt, val, n) << std::endl; //dynamic programming function
    t2 = clock() - t2; //end time
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC; //converting to seconds
    std::cout << "time taken using dp: " << time_taken2 << std::endl; //printing time taken
    return 0;
}