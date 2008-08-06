/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2004
 *
 *  Last modified:
 *     $Date$ by $Author$
 *     $Revision$
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "examples/support.hh"

/**
 * \brief %Example: Stress test for the minimum constraint
 *
 * \ingroup ExStress
 *
 */
class StressMin : public Example {
protected:
  /// Size of problem
  const int n;
  /// Variables
  IntVarArray x;
public:
  /// The actual problem
  StressMin(const SizeOptions& opt)
    : n(opt.size()), x(*this,n,0,2*n-1) {
    for (int i=1; i<n; i++) {
      IntVarArgs y(i);
      for (int j=0; j<i; j++)
        y[j]=x[j];
      IntVar m(*this,0,2*n);
      min(*this, y, m);
      rel(*this, m, IRT_GR, x[i]);
    }
    branch(*this, x, INT_VAR_NONE, INT_VAL_SPLIT_MAX);
  }

  /// Constructor for cloning \a s
  StressMin(bool share, StressMin& s) : Example(share,s), n(s.n) {
    x.update(*this, share, s.x);
  }

  /// Perform copying during cloning
  virtual Space*
  copy(bool share) {
    return new StressMin(share,*this);
  }

  /// Print solution
  virtual void
  print(std::ostream& os) {
    os << "\tx[" << n << "] = " << x << std::endl;
  }
};


/** \brief Main-function
 *  \relates StressMin
 */
int
main(int argc, char* argv[]) {
  SizeOptions opt("StressMin");
  opt.parse(argc,argv);
  opt.size(200);
  Example::run<StressMin,DFS,SizeOptions>(opt);
  return 0;
}

// STATISTICS: example-any
