// The typical paradigm for monotonous increase stack
for (int i = 0; i < A.size(); i++) {
   while (!in_stk.empty() && in_stk.top() > A[i]) {
     in_stk.pop();
   }
  in_stk.push(A[i]);
}

// Find the previous less element of each element in a vector with O(n) time:
vector<int> previous_less(A.size(), -1);
stack<int> in_stk;
for (int i = 0; i < A.size(); i++) {
   while (!in_stk.empty() && A[in_stk.top()] > Ap[i]) {
     in_stk.pop();
   }
   previous_less[i] = in_stk.empty() ? -1 : in_stk.top();
   in_stk.puhs(i);
}

// Find the next less element of each element in a vector with O(n) time:
vector<int> next_less(A.size(), -1);
stack<int> in_stk;
for (int i = 0;i < A.size(); i++) {
  while (!in_stk.empty() && A[in_stk.top()] > A[i]) {
    auto x = in_stk.top();
    in_stk.pop();
    next_less[x] = i;
  }
  in_stk.push(i);
}
