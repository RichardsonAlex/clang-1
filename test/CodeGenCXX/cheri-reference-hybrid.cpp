// capability references in hybrid mode crash:
// https://github.com/CTSRD-CHERI/clang/issues/147
// RUN: %cheri_cc1 -std=c++11 -o - %s -emit-llvm
// just for comparison the purecap abi
// RUN: %cheri_cc1 -std=c++11 -o - -target-abi purecap %s -emit-llvm
// XFAIL: *


int global_int = 3;


void ref() {
  int i = 0;
  int& ptr_ref = i;
  int& __capability cap_ref = i;
  int& ptr_ref2 = global_int;
  int& __capability cap_ref2 = global_int;
}

int& global_ptr_ref = global_int;
int& __capability global_cap_ref = global_int;

void ptr() {
  int i = 0;
  int* ptr = &i;
  int* __capability cap_ptr = &i;
  int* ptr2 = &global_int;
  int* __capability cap_ptr2 = &global_int;
}

int* global_ptr = &global_int;
int* __capability global_cap = &global_int;
