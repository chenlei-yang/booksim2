#ifndef HARA_HPP
#define HARA_HPP

#include <string>

extern int gK;

namespace HaraCh {
  const int L = 0;
  const int E = 1;
  const int W = 2;
  const int N1 = 3;
  const int S1 = 4;
  const int N2 = 5;
  const int S2 = 6;
  static std::string get_hara_ch(int x) {
    switch (x) {
      case(L): return std::string("L");
      case(E): return std::string("E");
      case(W): return std::string("W");
      case(N1): return std::string("N1");
      case(S1): return std::string("S1");
      case(N2): return std::string("N2");
      case(S2): return std::string("S2");
    }
    return std::string("");
  };
  static int ch2port();
};

namespace OutCh {
  const int L = 1 << HaraCh::L;
  const int E = 1 << HaraCh::E;
  const int W = 1 << HaraCh::W;
  const int N1 = 1 << HaraCh::N1;
  const int S1 = 1 << HaraCh::S1;
  const int N2 = 1 << HaraCh::N2;
  const int S2 = 1 << HaraCh::S2;
  static std::string get_out_ch(int x) {
    switch (x) {
      case(L): return std::string("L");
      case(E): return std::string("E");
      case(W): return std::string("W");
      case(N1): return std::string("N1");
      case(S1): return std::string("S1");
      case(N2): return std::string("N2");
      case(S2): return std::string("S2");
    }
    return std::string("");
  };
};

namespace HaraPos {
  const int L = 0;
  const int N = 1;
  const int S = 2;
  const int E = 3;
  const int W = 4;
  const int NE = 5;
  const int NW = 6;
  const int SE = 7;
  const int SW = 8;
  static std::string get_hara_pos(int x) {
    switch (x) {
      case(L): return std::string("L");
      case(N): return std::string("N");
      case(S): return std::string("S");
      case(E): return std::string("E");
      case(W): return std::string("W");
      case(NE): return std::string("NE");
      case(NW): return std::string("NW");
      case(SE): return std::string("SE");
      case(SW): return std::string("SW");
    }
    return std::string("");
  };

  static int id2pos(int cur, int dest) {
    int cx = cur / gK, cy = cur % gK;
    int dx = dest / gK, dy = dest % gK;
    if (cx == dx && cy == dy)
      return HaraPos::L;
    if (cx == dx && cy < dy)
      return HaraPos::N;
    if (cx == dx && cy > dy)
      return HaraPos::S;
    if (cx < dx && cy == dy)
      return HaraPos::E;
    if (cx > dx && cy == dy)
      return HaraPos::W;
    if (cx < dx && cy < dy)
      return HaraPos::NE;
    if (cx < dx && cy > dy)
      return HaraPos::SE;
    if (cx > dx && cy < dy)
      return HaraPos::NW;
    if (cx > dx && cy > dy)
      return HaraPos::SW;
  };
}

namespace Port {
  const int S = 1;
  const int N = 0;
  const int E = 2;
  const int W = 3;
  static std::string get_port(int x) {
    switch (x) {
      case(N): return std::string("N");
      case(S): return std::string("S");
      case(E): return std::string("E");
      case(W): return std::string("W");
    }
    return std::string("");
  };

  static int port2ch(int port ,int vc) {
    switch (port) {
      case(N): {
        if (vc == 0) return HaraCh::N1;
        return HaraCh::N2;
      }
      case(S): {
        if (vc == 0) return HaraCh::S1;
        return HaraCh::S2;
      }
      case(E): return HaraCh::E;
      case(W): return HaraCh::W;
    }
    return HaraCh::L;
  };

  static void ch2port(int hara_port, int &out_port, int &vc) {
    switch (hara_port) {
      case (HaraCh::L):
        return;
      case (HaraCh::W): {
        out_port = Port::W;
        vc = 0;
        return;
      }
      case (HaraCh::E): {
        out_port = Port::E;
        vc = 0;
        return;
      }
      case (HaraCh::N1): {
        out_port = Port::N;
        vc = 0;
        return;
      }
      case (HaraCh::N2): {
        out_port = Port::N;
        vc = 1;
        return;
      }
      case (HaraCh::S1): {
        out_port = Port::S;
        vc = 0;
        return;
      }
      case (HaraCh::S2): {
        out_port = Port::S;
        vc = 1;
        return;
      }
    }
    return;
  }

  static std::string get_hara_ch(int port, int vc){
    switch (port) {
      case(N): {
        if (vc == 0) return std::string("N1");
        return std::string("N2");
      }
      case(S): {
        if (vc == 0) return std::string("S1");
        return std::string("S2");
      }
      case(E): return std::string("E");
      case(W): return std::string("W");
    }
    return std::string("");
  };
};

#endif