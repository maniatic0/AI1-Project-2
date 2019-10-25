// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 1/11/16
// Modified by:

#include "othello_cut.h" // won't work correctly until .h is fixed!
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <limits>

#include <unordered_map>

using namespace std;

unsigned expanded = 0;
unsigned generated = 0;
int tt_threshold = 32; // threshold to save entries in TT

// Transposition table (it is not necessary to implement TT)
struct stored_info_t {
  int value_;
  int type_;
  enum { EXACT, LOWER, UPPER };
  stored_info_t(int value = -100, int type = LOWER)
      : value_(value), type_(type) {}
};

struct hash_function_t {
  size_t operator()(const state_t &state) const { return state.hash(); }
};

class hash_table_t
    : public unordered_map<state_t, stored_info_t, hash_function_t> {};

hash_table_t TTable[2];

// int maxmin(state_t state, int depth, bool use_tt);
// int minmax(state_t state, int depth, bool use_tt = false);
// int maxmin(state_t state, int depth, bool use_tt = false);
int negamax(state_t state, int depth, int color, bool use_tt = false) {
  if (depth <= 0 || state.terminal()) {
    return color * state.value();
  }
  bool isBlack = color == 1;
  bool pass = true;
  int alpha = std::numeric_limits<int>::min();
  for (int pos = 4; pos < DIM; ++pos) {
    if ((isBlack && state.is_black_move(pos)) || (!isBlack && state.is_white_move(pos))) {
      pass = false;
      ++generated;
      ++expanded;
      alpha = std::max(alpha, -negamax(state.move(isBlack, pos), depth - 1, -color, use_tt));
    }
  }

  if (pass) {
    ++generated;
    ++expanded;
    alpha = std::max(alpha, -negamax(state.move(isBlack, DIM), depth - 1, -color, use_tt));
  }

  return alpha;
}
int negamax(state_t state, int depth, int alpha, int beta, int color, bool use_tt = false) {
  if (depth <= 0 || state.terminal()) {
    return color * state.value();
  }
  bool isBlack = color == 1;
  bool pass = true;
  int score = std::numeric_limits<int>::min();
  int val;
  for (int pos = 4; pos < DIM; ++pos) {
    if ((isBlack && state.is_black_move(pos)) || (!isBlack && state.is_white_move(pos))) {
      val = -negamax(state.move(isBlack, pos), depth - 1, -beta, -alpha, -color, use_tt);
      score = std::max(score, val);
      alpha = std::max(alpha, val);
      pass = false;
      ++generated;
      ++expanded;
      if (alpha >= beta) break;
    }
  }

  if (pass) {
    ++generated;
    ++expanded;
    score = std::max(score, -negamax(state.move(isBlack, DIM), depth - 1, -beta, -alpha, -color, use_tt));
  }

  return score;
}

bool test(state_t state, int depth, int score, bool condition, int color) {
  if (depth <= 0 || state.terminal()) {
    if (condition){
      return state.value() > score ? true : false;
    } else {
      return state.value() >= score ? true : false;
    }
  }
  
  bool isBlack = color == 1;
  bool pass = true;

  for (int pos = 4; pos < DIM; ++pos) {
    if ((isBlack && state.is_black_move(pos)) || (!isBlack && state.is_white_move(pos))) {
      pass = false;
      if (isBlack && test(state.move(isBlack, pos), depth - 1, score, condition, -color)) return true;
      if (!isBlack && !test(state.move(isBlack, pos), depth - 1, score, condition, -color)) return false;
    }
  }

  if (pass) {
    if (isBlack && test(state.move(isBlack, DIM), depth - 1, score, condition, -color)) return true;
    if (!isBlack && !test(state.move(isBlack, DIM), depth - 1, score, condition, -color)) return false;
  }

  return !isBlack;
}

int scout(state_t state, int depth, int color, bool use_tt = false) {
  if (depth <= 0 || state.terminal()) {
    return state.value();
  }
  bool isBlack = color == 1;
  bool pass = true;
  bool firstChild = true;
  int score = 0;
  for (int pos = 4; pos < DIM; ++pos) {
    if ((isBlack && state.is_black_move(pos)) || (!isBlack && state.is_white_move(pos))) {
      if (firstChild) {
        firstChild = false;
        ++expanded;
        score = scout(state.move(isBlack, pos), depth - 1, -color, use_tt);
      } else {
        if (isBlack && test(state.move(isBlack, pos), depth - 1, score, true, -color)) {
          ++expanded;
          score = scout(state.move(isBlack, pos), depth - 1, -color, use_tt);
        }
        if (!isBlack && !test(state.move(isBlack, pos), depth - 1, score, false, -color)) {
          ++expanded;
          score = scout(state.move(isBlack, pos), depth - 1, -color, use_tt);
        }
      }
      pass = false;
      ++generated;
    }
  }

  if (pass) {
    if (firstChild) {
      firstChild = false;
      ++expanded;
      score = scout(state.move(isBlack, DIM), depth - 1, -color, use_tt);
    } else {
      if (isBlack && test(state.move(isBlack, DIM), depth - 1, score, true, -color)) {
        ++expanded;
        score = scout(state.move(isBlack, DIM), depth - 1, -color, use_tt);
      }
      if (!isBlack && !test(state.move(isBlack, DIM), depth - 1, score, false, -color)) {
        ++expanded;
        score = scout(state.move(isBlack, DIM), depth - 1, -color, use_tt);
      }
    }
    ++generated;
    }
  return score;
}

int negascout(state_t state, int depth, int alpha, int beta, int color,
              bool use_tt = false);

int main(int argc, const char **argv) {
  state_t pv[128];
  int npv = 0;
  for (int i = 0; PV[i] != -1; ++i)
    ++npv;

  int algorithm = 0;
  if (argc > 1)
    algorithm = atoi(argv[1]);
  bool use_tt = argc > 2;

  // Extract principal variation of the game
  state_t state;
  cout << "Extracting principal variation (PV) with " << npv << " plays ... "
       << flush;
  for (int i = 0; PV[i] != -1; ++i) {
    bool player = i % 2 == 0; // black moves first!
    int pos = PV[i];
    pv[npv - i] = state;
    state = state.move(player, pos);
  }
  pv[0] = state;
  cout << "done!" << endl;

#if 0
    // print principal variation
    for( int i = 0; i <= npv; ++i )
        cout << pv[npv - i];
#endif

  // Print name of algorithm
  cout << "Algorithm: ";
  if (algorithm == 1)
    cout << "Negamax (minmax version)";
  else if (algorithm == 2)
    cout << "Negamax (alpha-beta version)";
  else if (algorithm == 3)
    cout << "Scout";
  else if (algorithm == 4)
    cout << "Negascout";
  cout << (use_tt ? " w/ transposition table" : "") << endl;

  // Run algorithm along PV (bacwards)
  cout << "Moving along PV:" << endl;
  for (int i = 0; i <= npv; ++i) {
    // cout << pv[i];
    int value = 0;
    TTable[0].clear();
    TTable[1].clear();
    float start_time = Utils::read_time_in_seconds();
    expanded = 0;
    generated = 0;
    int color = i % 2 == 1 ? 1 : -1;

    try {
      if (algorithm == 1) {
        value = negamax(pv[i], i + 1, color, use_tt);
      } else if (algorithm == 2) {
        value = negamax(pv[i], i + 1, -200, 200, color, use_tt);
      } else if (algorithm == 3) {
        value = scout(pv[i], i + 1, color, use_tt);
      } else if (algorithm == 4) {
        // value = negascout(pv[i], 0, -200, 200, color, use_tt);
      }
    } catch (const bad_alloc &e) {
      cout << "size TT[0]: size=" << TTable[0].size()
           << ", #buckets=" << TTable[0].bucket_count() << endl;
      cout << "size TT[1]: size=" << TTable[1].size()
           << ", #buckets=" << TTable[1].bucket_count() << endl;
      use_tt = false;
    }

    float elapsed_time = Utils::read_time_in_seconds() - start_time;

    cout << npv + 1 - i << ". " << (color == 1 ? "Black" : "White")
         << " moves: "
         << "value=" << color * value << ", #expanded=" << expanded
         << ", #generated=" << generated << ", seconds=" << elapsed_time
         << ", #generated/second=" << generated / elapsed_time << endl;
  }

  return 0;
}
