// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %cheri_cc1 -target-cpu mips4 -target-abi n64 -o - -fsyntax-only -ast-dump -verify %s | FileCheck %s -check-prefix AST
// RUN: %cheri_cc1 -target-cpu mips4 -target-abi n64 -o - -emit-llvm -O0 -verify %s | FileCheck %s

// CHECK-LABEL: @a(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[PTR_TO_CAP_ADDR:%.*]] = alloca i32 addrspace(200)**, align 8
// CHECK-NEXT:    [[C:%.*]] = alloca i32**, align 8
// CHECK-NEXT:    store i32 addrspace(200)** [[PTR_TO_CAP:%.*]], i32 addrspace(200)*** [[PTR_TO_CAP_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i32 addrspace(200)**, i32 addrspace(200)*** [[PTR_TO_CAP_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast i32 addrspace(200)** [[TMP0]] to i32**
// CHECK-NEXT:    store i32** [[TMP1]], i32*** [[C]], align 8
// CHECK-NEXT:    [[TMP2:%.*]] = load i32**, i32*** [[C]], align 8
// CHECK-NEXT:    ret i32** [[TMP2]]
//

int **a(int *__attribute__((cheri_capability)) * ptr_to_cap) {
  // casting a capability pointer to a non-capability pointer used to crash
  int **c = ptr_to_cap; // expected-warning{{initializing 'int **' with an expression of type 'int * __capability *' discards qualifiers in nested pointer types}}
  return c;
}

// The AST for this was broken (there was suddenly a CK_NoOp instead of a capability cast):
//    |-DeclStmt 0x7fec38000650 <line:7:3, col:23>
//    | `-VarDecl 0x7fec38000100 <col:3, col:13> col:9 used c 'int **' cinit
//    |   `-ImplicitCastExpr 0x7fec380001a0 <col:13> 'int **' <NoOp>
//    |     `-ImplicitCastExpr 0x7fec38000188 <col:13> 'int * __capability *' <LValueToRValue>
//    |       `-DeclRefExpr 0x7fec38000160 <col:13> 'int * __capability *' lvalue ParmVar 0x7fec3501f6a0 'ptr_to_cap' 'int * __capability *'


// AST:       |-DeclStmt {{.+}} <line:19:3, col:23>
// AST-NEXT:  | `-VarDecl {{.+}} <col:3, col:13> col:9 used c 'int **' cinit
// AST-NEXT:  |   `-ImplicitCastExpr {{.+}} <col:13> 'int **' <BitCast>
// AST-NEXT:  |     `-ImplicitCastExpr {{.+}} <col:13> 'int * __capability *' <LValueToRValue>
// AST-NEXT:  |       `-DeclRefExpr {{.+}} <col:13> 'int * __capability *' lvalue ParmVar {{.+}} 'ptr_to_cap' 'int * __capability *'