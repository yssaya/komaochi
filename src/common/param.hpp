// 2019 Team AobaZero
// This source code is in the public domain.
#pragma once
namespace Ver {
  constexpr unsigned char major       = 2;	// komaochi >= 2.0
  constexpr unsigned char minor       = 4;	// 2...kldgain, 3...kld bufix, mtemp 1.3
  constexpr unsigned short usi_engine = 25;	// komaochi >= 16
}

#define AOBA_UNIQUE ".jBQoNA7kEd"

namespace Param {
  using uint = unsigned int;
  constexpr uint maxnum_child         = 1024U;
  constexpr uint maxlen_play_learn    = 513U;
  constexpr uint maxlen_play          = 4096U;
  // 81*81*2 + (81*7) = 13122 + 567 = 13689 * 512 = 7008768
  constexpr uint len_seq_prn          = 7008768U;
//constexpr char name_autousi[]       = "/tmp/autousi"   AOBA_UNIQUE;
  constexpr char name_server[]        = "/tmp/server"    AOBA_UNIQUE;
  constexpr char name_sem_nnet[]      = "/sem-nnet"      AOBA_UNIQUE;
  constexpr char name_sem_lock_nnet[] = "/sem-lock-nnet" AOBA_UNIQUE;
  constexpr char name_seq_prn[]       = "/mmap-seq-prn"  AOBA_UNIQUE;
  constexpr char name_mmap_nnet[]     = "/mmap-nnet"     AOBA_UNIQUE;
}

const int HEADER_SIZE = 64;	// version 2 byte(major,minor), resign_th(2 byte), handicap rate 14 byte (2*7)
const int HANDICAP_TYPE = 7;	// hirate(0),ky(1),ka(2),hi(3),2mai(4),4mai(5),6mai(6)

