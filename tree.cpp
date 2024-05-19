#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
    int n;
    vector <int> key;
    vector <int> left;
    vector <int> right;

  public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    void inorder_traversal(vector<int> &result, int i) {
		std::cout << "i: " << i << std::endl;
        if (i == -1) return;
		std::cout << "left : " << left[i] << std::endl;
        inorder_traversal(result, left[i]);
		
        result.push_back(key[i]);
		std::cout << "right : " << right[i] << std::endl;
        inorder_traversal(result, right[i]);
    }

    vector <int> in_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        inorder_traversal(result, 0);

        return result;
    }

    void preorder_traversal(vector<int> &result, int i) {
        if (i == -1) return;
        result.push_back(key[i]);
        preorder_traversal(result, left[i]);
        preorder_traversal(result, right[i]);
    }

    vector <int> pre_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        preorder_traversal(result, 0);

        return result;
    }

    void postorder_traversal(vector<int> &result, int i) {
        if (i == -1) return;
        postorder_traversal(result, left[i]);
        postorder_traversal(result, right[i]);
        result.push_back(key[i]);
    }

    vector <int> post_order() {
        vector<int> result;
        // Finish the implementation
        // You may need to add a new recursive method to do that
        postorder_traversal(result, 0);

        return result;
    }
};

void print(const vector <int>& a) {
	std::cout << "empty? " << a.empty();
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
	std::cout << "read!\n";
	std::cout << t.in_order().empty();
    // vector<int> in = t.in_order();
	// for (const auto& ele : in) {
	// 	std::cout << ele << std::endl;
	// }
	// print(in);
	// std::cout << "in order!\n";
    // print(t.pre_order());
	// std::cout << "preorder!\n";
    // print(t.post_order());
	// std::cout << "postorder!\n";
    return 0;
}

int main (int argc, char **argv) 
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) {
                std::cerr << "setrlimit returned result = " << result << std::endl;
            }
        }
    }
#endif

    return main_with_large_stack_space();
}