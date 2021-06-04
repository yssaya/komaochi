// 2019 Team AobaZero
// This source code is in the public domain.
#ifdef _MSC_VER
#  define _CRT_SECURE_NO_WARNINGS
#endif
#include <algorithm>
#include <exception>
#include <random>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
using uint = unsigned int;
using uchar = unsigned char;
using std::max;
using std::terminate;
using std::mt19937_64;

class PF {
  FILE *_pf;
public:
  explicit PF(const char *p);
  ~PF();
  operator FILE *() const { return _pf; }
};

class Data {
  uint _u0, _u1, _u2;
public:
  Data() : _u0(0), _u1(0), _u2(0) {}
  explicit Data(uint u) : Data() { set_bit(u); }
  void set_bit(uint u);
  void set_bit(int r, int f);
  void out(const char *head, FILE *pf, const char *tail);
};

static void out_zkey() noexcept;
static void out_sq() noexcept;
static void out_bmap() noexcept;
static void out_board() noexcept;

int main() {
  out_zkey();
  out_sq();
  out_bmap();
  out_board();
  return 0;
}

PF::PF(const char *p) {
  assert(p);
  _pf = fopen(p, "w");
  if (!_pf) { perror("fopen() failed"); terminate(); }
  fputs("// This is generated by src/gencode/gencode.cpp\n\n", _pf); }

PF::~PF() {
  if (ferror(_pf) || fclose(_pf)) { perror("write failed"); terminate(); } }

void Data::set_bit(uint u) {
  assert(u < 81U);
  if      (u < 27U) _u0 |= 1U << (26U - u);
  else if (u < 54U) _u1 |= 1U << (53U - u);
  else              _u2 |= 1U << (80U - u); }

void Data::set_bit(int r, int f) {
  if (r < 0 || 8 < r || f < 0 || 8 < f) return;
  set_bit(static_cast<uint>(r)*9U + static_cast<uint>(f)); }

void Data::out(const char *head, FILE *pf, const char *tail) {
  fprintf(pf, "%sBMap(0x%08xU, 0x%08xU, 0x%08xU)%s", head, _u0, _u1, _u2, tail);
  _u0 = _u1 = _u2 = 0; }

static void out_zkey() noexcept {
  mt19937_64 mt64;
  PF pf("src/common/tbl_zkey.inc");
  fputs("static constexpr uint64_t zkey_turn ", pf);
  fprintf(pf, "= UINT64_C(0x%016" PRIx64 ");\n\n", mt64());
  
  fputs("static constexpr uint64_t tbl_zkey_hand", pf);
  fputs("[Color::ok_size][Pc::hand_size][Pc::npawn] = {\n", pf);
  for (uint uc = 0; uc < 2U; ++uc)
    for (uint upc = 0; upc < 7U; ++upc)
      for (uint u = 0; u < 9U; ++u) {
	if (upc == 0 && u == 0) fputs(" { {", pf);
	else if (u == 0)        fputs("   {", pf);
	else                    fputs("    ", pf);
	fprintf(pf, " UINT64_C(0x%016" PRIx64 "),", mt64());
	fprintf(pf, " UINT64_C(0x%016" PRIx64 ")", mt64());
	if (uc == 1U && upc == 6U && u == 8U) fputs(" } } };\n\n", pf);
	else if (upc == 6U && u == 8U)        fputs(" } },\n", pf);
	else if (u == 8U)                     fputs(" },\n", pf);
	else                                  fputs(",\n", pf); }

  fputs("static constexpr uint64_t tbl_zkey_sq", pf);
  fputs("[Color::ok_size][Pc::ok_size][Sq::ok_size] = {\n", pf);
  for (uint uc = 0; uc < 2U; ++uc)
    for (uint upc = 0; upc < 14U; ++upc)
      for (uint usq = 0; usq < 81U; ++usq) {
	if (upc == 0 && usq == 0) fputs(" { {", pf);
	else if (usq == 0)        fputs("   {", pf);
	else if ((usq % 2) == 0)  fputs("    ", pf);
	fprintf(pf, " UINT64_C(0x%016" PRIx64 ")", mt64());
	if (uc == 1U && upc == 13U && usq == 80U) fputs(" } } };\n", pf);
	else if (upc == 13U && usq == 80U)        fputs(" } },\n", pf);
	else if (usq == 80U)                      fputs(" },\n", pf);
	else if ((usq % 2) == 0)                  fputs(",", pf);
	else                                      fputs(",\n", pf); }
}

enum { A9, B9, C9, D9, E9, F9, G9, H9, I9,
       A8, B8, C8, D8, E8, F8, G8, H8, I8,
       A7, B7, C7, D7, E7, F7, G7, H7, I7,
       A6, B6, C6, D6, E6, F6, G6, H6, I6,
       A5, B5, C5, D5, E5, F5, G5, H5, I5,
       A4, B4, C4, D4, E4, F4, G4, H4, I4,
       A3, B3, C3, D3, E3, F3, G3, H3, I3,
       A2, B2, C2, D2, E2, F2, G2, H2, I2,
       A1, B1, C1, D1, E1, F1, G1, H1, I1 };

constexpr uchar tbl_file[] = { A1, A2, A3, A4, A5, A6, A7, A8, A9,
			       B1, B2, B3, B4, B5, B6, B7, B8, B9,
			       C1, C2, C3, C4, C5, C6, C7, C8, C9,
			       D1, D2, D3, D4, D5, D6, D7, D8, D9,
			       E1, E2, E3, E4, E5, E6, E7, E8, E9,
			       F1, F2, F3, F4, F5, F6, F7, F8, F9,
			       G1, G2, G3, G4, G5, G6, G7, G8, G9,
			       H1, H2, H3, H4, H5, H6, H7, H8, H9,
			       I1, I2, I3, I4, I5, I6, I7, I8, I9 };

constexpr uchar tbl_diag1[] = { I8, I7, I6, I5, I4, I3, I2, I1, I9,
				H7, H6, H5, H4, H3, H2, H1, H9, H8,
				G6, G5, G4, G3, G2, G1, G9, G8, G7,
				F5, F4, F3, F2, F1, F9, F8, F7, F6,
				E4, E3, E2, E1, E9, E8, E7, E6, E5,
				D3, D2, D1, D9, D8, D7, D6, D5, D4,
				C2, C1, C9, C8, C7, C6, C5, C4, C3,
				B1, B9, B8, B7, B6, B5, B4, B3, B2,
				A9, A8, A7, A6, A5, A4, A3, A2, A1 };

constexpr uchar tbl_diag2[] = { A9, B1, C2, D3, E4, F5, G6, H7, I8,
				A8, B9, C1, D2, E3, F4, G5, H6, I7,
				A7, B8, C9, D1, E2, F3, G4, H5, I6,
				A6, B7, C8, D9, E1, F2, G3, H4, I5,
				A5, B6, C7, D8, E9, F1, G2, H3, I4,
				A4, B5, C6, D7, E8, F9, G1, H2, I3,
				A3, B4, C5, D6, E7, F8, G9, H1, I2,
				A2, B3, C4, D5, E6, F7, G8, H9, I1,
				A1, B2, C3, D4, E5, F6, G7, H8, I9 };

static void out_sq() noexcept {
  PF pf("src/common/tbl_sq.inc");
  uint u;
  fputs("static_assert(SAux::ray_size == 4U, ", pf);
  fputs("\"SAux::ray_size != 4U\");\n\n", pf);

  fputs("static constexpr BMap tbl_sq_u2bmap[81][4] = {\n", pf);
  for (uint usq = 0; usq < 81U; ++usq) {
    Data data(usq);
    data.out("  { ", pf, ",\n");

    data.set_bit(tbl_file[usq]);
    data.out("    ", pf, ",\n");
    
    data.set_bit(tbl_diag1[usq]);
    data.out("    ", pf, ",\n");

    data.set_bit(tbl_diag2[usq]);
    data.out("    ", pf, (usq < 80U) ? " },\n" : " } };\n\n"); }
    
  fputs("static constexpr BMap tbl_sq_obstacle[81][81] = {\n", pf);
  auto fsign = [](int i){
    if (i < 0) return -1; else if (0 < i) return 1; else return 0; };
  for (int i1 = 0; i1 < 81; ++i1) {
    int rank1 = i1 / 9;
    int file1 = i1 % 9;
    for (int i2 = 0; i2 < 81; ++i2) {
      Data data;
      int rank2 = i2 / 9;
      int file2 = i2 % 9;
      if (rank1 == rank2 && file1 == file2);
      else if (rank1 == rank2 || file1 == file2
	       || rank2 - rank1 == file1 - file2
	       || rank2 - rank1 == file2 - file1) {
	int dr = fsign(rank2 - rank1);
	int df = fsign(file2 - file1);
	for (int factor = 1;; ++factor) {
	  int rank = rank1 + factor * dr;
	  int file = file1 + factor * df;
	  if (rank == rank2 && file == file2) break;
	  data.set_bit(rank, file); } }
      data.out((i2 == 0) ? "  { " : "    ", pf,
	       (i1 == 80 && i2 == 80) ? " } };\n\n"
	       : ((i2 == 80) ? " },\n" : ",\n")); } }
  
  fputs("static constexpr Sq::Attacks tbl_sq_atk[Color::ok_size][81] = {\n",
	pf);
  for (u = 0; u < 81U; ++u) {
    int rank = static_cast<int>(u / 9U);
    int file = static_cast<int>(u % 9U);
    Data data;
    // Black Silver
    data.set_bit(rank + 1, file - 1);
    data.set_bit(rank + 1, file + 1);
    data.set_bit(rank - 1, file - 1);
    data.set_bit(rank - 1, file + 0);
    data.set_bit(rank - 1, file + 1);
    data.out((u == 0) ? "  { { " : "    { ", pf, ",\n");

    // Black Gold
    data.set_bit(rank + 1, file + 0);
    data.set_bit(rank + 0, file + 1);
    data.set_bit(rank + 0, file - 1);
    data.set_bit(rank - 1, file - 1);
    data.set_bit(rank - 1, file + 0);
    data.set_bit(rank - 1, file + 1);
    data.out("      ", pf, ",\n");
  
    // Black Knight
    data.set_bit(rank - 2, file - 1);
    data.set_bit(rank - 2, file + 1);
    data.out("      ", pf, ",\n");
  
    // Black Lance
    for (int i = 1; i < 9; ++i) data.set_bit(rank - i, file);
    data.out("      ", pf, ",\n");

    // Black Pawn
    data.set_bit(rank - 1, file);
    data.out("      ", pf, (u < 80U) ? " },\n" : " } },\n"); }

  for (u = 0; u < 81U; ++u) {
    int rank = static_cast<int>(u / 9U);
    int file = static_cast<int>(u % 9U);
    Data data;
    // White Silver
    data.set_bit(rank - 1, file + 1);
    data.set_bit(rank - 1, file - 1);
    data.set_bit(rank + 1, file + 1);
    data.set_bit(rank + 1, file + 0);
    data.set_bit(rank + 1, file - 1);
    data.out((u == 0) ? "  { { " : "    { ", pf, ",\n");
    
    // White Gold
    data.set_bit(rank - 1, file + 0);
    data.set_bit(rank + 0, file - 1);
    data.set_bit(rank + 0, file + 1);
    data.set_bit(rank + 1, file + 1);
    data.set_bit(rank + 1, file + 0);
    data.set_bit(rank + 1, file - 1);
    data.out("      ", pf, ",\n");

    // Whight Knight
    data.set_bit(rank + 2, file + 1);
    data.set_bit(rank + 2, file - 1);
    data.out("      ", pf, ",\n");

    // White Lance
    for (int i = 1; i < 9; ++i) data.set_bit(rank + i, file);
    data.out("      ", pf, ",\n");

    // White Pawn
    data.set_bit(rank + 1, file);
    data.out("      ", pf, (u < 80U) ? " },\n" : " } } };\n\n"); }

  fputs("static constexpr BMap tbl_sq_atk_king[81] = {\n", pf);
  for (u = 0; u < 81U; ++u) {
    int rank = static_cast<int>(u / 9U);
    int file = static_cast<int>(u % 9U);
    Data data;
    data.set_bit(rank - 1, file + 1);
    data.set_bit(rank - 1, file + 0);
    data.set_bit(rank - 1, file - 1);
    data.set_bit(rank - 0, file + 1);
    data.set_bit(rank - 0, file - 1);
    data.set_bit(rank + 1, file + 1);
    data.set_bit(rank + 1, file + 0);
    data.set_bit(rank + 1, file - 1);
    data.out("  ", pf, (u < 80U) ? ",\n" : " };\n\n"); }

  fputs("static constexpr uchar tbl_sq_rel[2][81] = {\n", pf);
  for (int rank = 0; rank < 9; ++rank) {
    fputs((rank == 0) ? "  { " : "    ", pf);
    fprintf(pf, "%2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU",
	    9*rank + 0, 9*rank + 1, 9*rank + 2, 9*rank + 3, 9*rank + 4,
	    9*rank + 5, 9*rank + 6, 9*rank + 7, 9*rank + 8);
    fputs((rank == 8) ? " },\n" : ",\n", pf); }
  for (int rank = 8; 0 <= rank; --rank) {
    fputs((rank == 8) ? "  { " : "    ", pf);
    fprintf(pf, "%2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU",
	    9*rank + 8, 9*rank + 7, 9*rank + 6, 9*rank + 5, 9*rank + 4,
	    9*rank + 3, 9*rank + 2, 9*rank + 1, 9*rank + 0);
    fputs((rank == 0) ? " } };\n\n" : ",\n", pf); }
  
  fputs("static constexpr uchar tbl_sq_adv[2][81] = {\n", pf);
  fputs("  { 81U, 81U, 81U, 81U, 81U, 81U, 81U, 81U, 81U,\n", pf);
  for (int rank = 1; rank < 9; ++rank) {
    fprintf(pf, "    %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU",
	    9*rank - 9, 9*rank - 8, 9*rank - 7, 9*rank - 6, 9*rank - 5,
	    9*rank - 4, 9*rank - 3, 9*rank - 2, 9*rank - 1);
    fputs((rank == 8) ? " },\n" : ",\n", pf); }
  for (int rank = 0; rank < 8; ++rank) {
    fputs((rank == 0) ? "  { " : "    ", pf);
    fprintf(pf, "%2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU, %2dU,\n",
	    9*rank + 9, 9*rank +10, 9*rank +11, 9*rank +12, 9*rank +13,
	    9*rank +14, 9*rank +15, 9*rank +16, 9*rank +17); }
  fputs("    81U, 81U, 81U, 81U, 81U, 81U, 81U, 81U, 81U } };\n\n", pf);
  
  fputs("static constexpr uchar tbl_sq_ray[81][81] = {\n", pf);
  for (int sq1 = 0; sq1 < 81; ++sq1) {
    int rank1 = sq1 / 9;
    int file1 = sq1 % 9;
    unsigned int tbl[81];
    for (int sq2 = 0; sq2 < 81; ++sq2) {
      int rank2 = sq2 / 9;
      int file2 = sq2 % 9;
      if (rank1 == rank2 && file1 == file2)    tbl[sq2] = 4U;
      else if (rank1 == rank2)                 tbl[sq2] = 0;
      else if (file1 == file2)                 tbl[sq2] = 1U;
      else if (rank2 - rank1 == file1 - file2) tbl[sq2] = 2U;
      else if (rank2 - rank1 == file2 - file1) tbl[sq2] = 3U;
      else                                     tbl[sq2] = 4U; }
    for (int rank = 0; rank < 9; ++rank) {
      int x = rank*9;
      if (rank == 0) fputs("  { ", pf);
      else           fputs("    ", pf);
      fprintf(pf, "%uU, %uU, %uU, %uU, %uU, %uU, %uU, %uU, %uU",
	      tbl[x + 0], tbl[x + 1], tbl[x + 2], tbl[x + 3], tbl[x + 4],
	      tbl[x + 5], tbl[x + 6], tbl[x + 7], tbl[x + 8]);
      if (sq1 == 80 && rank == 8) fputs(" } };\n\n", pf);
      else if (rank == 8)         fputs(" },\n", pf);
      else                        fputs(",\n", pf); } }

  fputs("static constexpr uchar tbl_sq_distance[81][81] = {\n", pf);
  for (int sq1 = 0; sq1 < 81; ++sq1) {
    int rank1 = sq1 / 9;
    int file1 = sq1 % 9;
    unsigned int tbl[81];
    for (int sq2 = 0; sq2 < 81; ++sq2) {
      int rank2 = sq2 / 9;
      int file2 = sq2 % 9;
      tbl[sq2] = max(abs(rank2 - rank1), abs(file2 - file1)); }
    for (int rank = 0; rank < 9; ++rank) {
      int x = rank*9;
      if (rank == 0) fputs("  { ", pf);
      else           fputs("    ", pf);
      fprintf(pf, "%uU, %uU, %uU, %uU, %uU, %uU, %uU, %uU, %uU",
	      tbl[x + 0], tbl[x + 1], tbl[x + 2], tbl[x + 3], tbl[x + 4],
	      tbl[x + 5], tbl[x + 6], tbl[x + 7], tbl[x + 8]);
      if (sq1 == 80 && rank == 8) fputs(" } };\n\n", pf);
      else if (rank == 8)         fputs(" },\n", pf);
      else                        fputs(",\n", pf); } }

  fputs("static constexpr uchar tbl_sq_dir[81][81] = {\n", pf);
  for (int sq1 = 0; sq1 < 81; ++sq1) {
    int rank1 = sq1 / 9;
    int file1 = sq1 % 9;
    unsigned int tbl[81];
    for (int sq2 = 0; sq2 < 81; ++sq2) {
      int rank2 = sq2 / 9;
      int file2 = sq2 % 9;
      int drank = rank2 - rank1;
      int dfile = file2 - file1;
      if      (dfile ==  0 && drank <   0)     tbl[sq2] =   0U;
      else if (dfile <   0 && drank ==  dfile) tbl[sq2] =   1U;
      else if (dfile <   0 && drank ==  0)     tbl[sq2] =   2U;
      else if (dfile <   0 && drank == -dfile) tbl[sq2] =   3U;
      else if (dfile ==  0 && drank >   0)     tbl[sq2] =   4U;
      else if (dfile >   0 && drank ==  dfile) tbl[sq2] =   5U;
      else if (dfile >   0 && drank ==  0)     tbl[sq2] =   6U;
      else if (dfile >   0 && drank == -dfile) tbl[sq2] =   7U;
      else if (dfile == -1 && drank == -2)     tbl[sq2] =   8U;
      else if (dfile == +1 && drank == -2)     tbl[sq2] =   9U;
      else if (dfile == -1 && drank ==  2)     tbl[sq2] =  10U;
      else if (dfile == +1 && drank ==  2)     tbl[sq2] =  11U;
      else                                     tbl[sq2] = 255U; }
    for (int rank = 0; rank < 9; ++rank) {
      int x = rank*9;
      if (rank == 0) fputs("  { ", pf);
      else           fputs("    ", pf);
      fprintf(pf, "%3uU, %3uU, %3uU, %3uU, %3uU, %3uU, %3uU, %3uU, %3uU",
	      tbl[x + 0], tbl[x + 1], tbl[x + 2], tbl[x + 3], tbl[x + 4],
	      tbl[x + 5], tbl[x + 6], tbl[x + 7], tbl[x + 8]);
      if (sq1 == 80 && rank == 8) fputs(" } };\n", pf);
      else if (rank == 8)         fputs(" },\n", pf);
      else                        fputs(",\n", pf); } } }

void out_bmap() noexcept {
  PF pf("src/common/tbl_bmap.inc");
  fputs("static_assert(SAux::ray_size == 4U, ", pf);
  fputs("\"SAux::ray_size != 4U\");\n\n", pf);
  
  fputs("static constexpr RBB tbl_bmap_rbb[81][4] = {\n", pf);
  for (uint u = 0; u < 81U; ++u) {
    uint r = u / 9U;
    uint f = u % 9U;
    uint off_l = (r < f) ? 9U : 0;
    uint off_r = (f + r < 8U) ? 0 : 9U;
    fprintf(pf, "  { {%2uU, %2uU}, {%2uU, %2uU}, {%2uU, %2uU}, {%2uU, %2uU} }",
	    u/27U, 9U*(2U - r%3U) + 1U,
	    2U - f/3U, 9U*(f%3U) + 1U,
	    (r + f + 1U - off_r)/3U, 9U*(2U - ((r + f + 1U - off_r)%3U)) + 1U,
	    (off_l + r - f)/3U, 9U*(2U-((off_l + r - f)%3U)) + 1U);
    if (u + 1U < 81U) fputs(",\n", pf);
    else              fputs(" };\n\n", pf); }
}

void out_board() noexcept {
  PF pf("src/common/tbl_board.inc");
  fputs("static const BMap tbl_board_atk_slide"
	"[Sq::ok_size][SAux::ray_size][128] = {\n", pf);
  for (uint usq = 0; usq < 81U; ++usq) {
    const int rank = static_cast<int>(usq / 9U);
    const int file = static_cast<int>(usq % 9U);
    Data data;
    for (uint bits = 0; bits < 256U; bits += 2U) {
      for (int i = -1; 0 <= file + i; --i) {
	data.set_bit(rank, file + i);
	if (bits & (1U << (8 - file - i))) break; }
      for (int i = 1; file + i <= 8; ++i) {
	data.set_bit(rank, file + i);
	if (bits & (1U << (8 - file - i))) break; }
      data.out( (bits == 0) ? "  { { " : "      ", pf,
		(bits < 254U) ? ",\n" : " },\n" ); }
      
    for (uint bits = 0; bits < 256U; bits += 2U) {
      for (int i = -1; 0 <= rank + i; --i) {
	data.set_bit(rank + i, file);
	if (bits & (1U << (8 - rank - i))) break; }
      for (int i = 1; rank + i <= 8; ++i) {
	data.set_bit(rank + i, file);
	if (bits & (1U << (8 - rank - i))) break; }
      data.out( (bits == 0) ? "    { " : "      ", pf,
		(bits < 254U) ? ",\n" : " },\n" ); }

    for (uint bits = 0; bits < 256U; bits += 2U) {
      if (8 <= file + rank) {
	for (int i = -1; rank - i <= 8; --i) {
	  data.set_bit(rank - i, file + i);
	  if (bits & (1U << (rank - i))) break;	}
	for (int i = 1; file + i <= 8; ++i) {
	  data.set_bit(rank - i, file + i);
	  if (bits & (1U << (rank - i))) break;	}
      } else {
	for (int i = -1; 0 <= file + i; --i) {
	  data.set_bit(rank - i, file + i);
	  if (bits & (1U << (rank - i))) break;	}
	for (int i = 1; 0 <= rank - i; ++i) {
	  data.set_bit(rank - i, file + i);
	  if (bits & (1U << (rank - i))) break; }
      }
      data.out( (bits == 0) ? "    { " : "      ", pf,
		(bits < 254U) ? ",\n" : " },\n" ); }

    for (uint bits = 0; bits < 256U; bits += 2U) {
      if (file <= rank) {
	for (int i = -1; 0 <= file + i; --i) {
	  data.set_bit(rank + i, file + i);
	  if (bits & (1U << (8 - file - i))) break; }
	for (int i = 1; rank + i <= 8; ++i) {
	  data.set_bit(rank + i, file + i);
	  if (bits & (1U << (8 - file - i))) break; }
      } else {
	for (int i = -1; 0 <= rank + i; --i) {
	  data.set_bit(rank + i, file + i);
	  if (bits & (1U << (8 - file - i))) break; }
	for (int i = 1; file + i <= 8; ++i) {
	  data.set_bit(rank + i, file + i);
	  if (bits & (1U << (8 - file - i))) break; }
      }
      data.out((bits == 0) ? "    { " : "      ", pf, "");
      if (bits < 254U)    fputs(",\n", pf);
      else if (usq < 80U) fputs(" } },\n", pf);
      else                fputs(" } } };\n", pf); }
  }
}
