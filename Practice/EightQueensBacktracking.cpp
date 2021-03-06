
/*
 
 There are two types of diagonals, A and B, each of them has (2 * N - 1) kinds.
 On every diagonal A, col + row = Constant, [0, 2 * N - 1]
 On every diagonal B, col - row + N - 1 = Constant [0, 2 * N - 1]
 
 nonRecursive() using iteration.
 nonRecursiveBacktracking() using iteration and backtracking.
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
using namespace std;

/// 8 Quene Puzzle
const int N = 8;
int columnUsed, diagonalUsed1, diagonalUsed2;
int columnPosiForRow[N];
int ans;

void clear()
{
  ans = 0;
  memset(columnPosiForRow, 0, sizeof(columnPosiForRow));
  columnUsed = diagonalUsed1 = diagonalUsed2 = 0;
}

void output()
{
  ans++;
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
      if (columnPosiForRow[i] == j)
        cout << "*";
      else
        cout << "-";
    cout << endl;
  }
  cout << endl;
}

void search(int curRow)
{
  if (curRow == N)
    return output();
  
  for (int c = 0; c < N; ++c)
  {
    if (!(columnUsed & (1 << c))
        && !(diagonalUsed1 & (1 << (c + curRow))) 
        && !(diagonalUsed2 & (1 << (c - curRow + N - 1))))
    {
      columnPosiForRow[curRow] = c;
      
      columnUsed ^= 1 << c;                       //columnUsed != 1 << c;
      diagonalUsed1 ^= 1 << (c + curRow);         //diagonalUsed1 |= 1 << (c + curRow);
      diagonalUsed2 ^= 1 << (c - curRow + N - 1); //diagonalUsed2 |= 1 << (c - curRow + N - 1);
      search(curRow + 1);
      columnUsed ^= 1 << c;                       //columnUsed &= (~(1 << c));
      diagonalUsed1 ^= 1 << (c + curRow);         //diagonalUsed1 &= ~(1 << (c + curRow));
      diagonalUsed2 ^= 1 << (c - curRow + N - 1); //diagonalUsed2 &= ~(1 << (c - curRow + N - 1));
    }
  }
}

struct Node {
  int row;
  int col;
  Node () {}
  Node (int r, int c) : row(r), col(c) {}
};


bool check(int row, int col)
{
  for (int r = 0; r < row; r ++) {
    int diff = columnPosiForRow[r] - columnPosiForRow[row];
    if (diff == 0 || abs(diff) == abs(row - r)) {
      return false;
    }
  }
  return true;
}

void nonRecursive()
{
  clear();
  
  list<Node *> s;
  s.push_back(new Node(0, 0));
  
  while (!s.empty()) {
    Node *node = s.back();
    
    if (node->row >= 8) {
      cout << ans + 1 << endl;
      output();
      s.pop_back();
      continue;
    }
    
    
    if (node->col >= 8) {
      s.pop_back();
      continue;
    }
    
    while (node->col < 8) {
      columnPosiForRow[node->row] = node->col;
      if (check(node->row, node->col)) {
        s.push_back(new Node(node->row + 1, 0));
        node->col ++;
        break;
      }
      
      node->col ++;
    }
  }
}


void nonRecursiveBacktracking()
{
  clear();
  int curRow = 0;
  
  memset(columnPosiForRow, -1, sizeof(columnPosiForRow));
  
  while (curRow >= 0) {
    //Output
    if (curRow >= 8) {
      output();
      curRow --;
      continue;
    }
    
    //Search for the next available position for curRow
    int c;
    for (c = columnPosiForRow[curRow] + 1; c < 8; c ++) {
      columnPosiForRow[curRow] = c;
      if (check(curRow, c)) {
        curRow ++;
        break;
      }
    }
    
    //No available position found
    if (c >= 8) {
      columnPosiForRow[curRow] = -1;
      curRow --;
    }
  }
}


int main()
{
  //  clear();
  //  search(0);
  
  clear();
  nonRecursive();
  nonRecursiveBacktracking();
  
  cout << "Total = " << ans << endl;
}