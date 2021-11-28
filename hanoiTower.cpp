#include <iostream>
#include <stack>
#include <string>
#include <tuple>

using namespace std;

//Helper function: returns a stack of same elements, in reversed order
stack<int> reverse_stack(stack<int> *stk) {
    stack<int> r_stk, r_stk_temp;
    int temp;

    //Fill r_stk with elements of *stk, in reversed order
    while (!stk->empty()) {
        temp = stk->top();
        r_stk.push(temp);
        r_stk_temp.push(temp);
        stk->pop();
    }

    //Recover *stk
    while (!r_stk_temp.empty()) {
        temp = r_stk_temp.top();
        stk->push(temp);
        r_stk_temp.pop();
    }
    
    return r_stk;
}

//Print function
void print_rods(stack<int> *rods) {
    //Reversed stacks
    stack<int> r_rods[] = {reverse_stack(rods), reverse_stack(rods + 1), reverse_stack(rods + 2)};

    for (int i = 0; i < 3; i++) {
        switch(i) {
            case 0: cout << "1st: [ "; break;
            case 1: cout << "2nd: [ "; break;
            case 2: cout << "3rd: [ "; break;
        }

        while (!r_rods[i].empty()) {
            cout << r_rods[i].top() << " ";
            r_rods[i].pop();
        }

        switch(i) {
            case 0:
            case 1: cout << "], "; break;
            case 2: cout << "]" << endl; break;
        }
    }
}

//Move the Hanoi-tower from "from" to "to"
//  print every single state during move
void move_disks(stack<int> *rods, int n, int from, int to, int anchor) {
    int largest_disk;
    //Base case
    if (n == 1) {
        largest_disk = (rods + from)->top();
        (rods + to)->push(largest_disk);
        (rods + from)->pop();
        print_rods(rods);
        return;
    }
    //Recursively move:
    //  move n-1 disks from -> anchor
    move_disks(rods, n - 1, from, anchor, to);
    //  move the largest disk from -> to
    largest_disk = (rods + from)->top();
    (rods + from)->pop();
    (rods + to)->push(largest_disk);
    print_rods(rods);
    //  move n-1 disks anchor -> to
    move_disks(rods, n - 1, anchor, to, from);
}

//Driver code
int main() {
    //Stack initialization
    stack<int> rod1, rod2, rod3;
    stack<int> rods[] = {rod1, rod2, rod3};
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        rods[0].push(n - i);
    //Print initial state
    print_rods(rods);

    //Move disks
    move_disks(rods, n, 0, 1, 2);

    //Print final state (once again)
    print_rods(rods);

    return 0;
}