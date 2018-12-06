// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %cheri_cc1 -emit-llvm %s -o - -verify | FileCheck %s
// RUN: %cheri_purecap_cc1 -emit-llvm %s -o - -verify | FileCheck %s -check-prefix PURECAP
// expected-no-diagnostics

// CHECK-LABEL: @assume_aligned_ptr(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[PTR_ADDR:%.*]] = alloca i8*, align 8
// CHECK-NEXT:    store i8* [[PTR:%.*]], i8** [[PTR_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i8*, i8** [[PTR_ADDR]], align 8
// CHECK-NEXT:    [[PTRINT:%.*]] = ptrtoint i8* [[TMP0]] to i64
// CHECK-NEXT:    [[MASKEDPTR:%.*]] = and i64 [[PTRINT]], 3
// CHECK-NEXT:    [[MASKCOND:%.*]] = icmp eq i64 [[MASKEDPTR]], 0
// CHECK-NEXT:    call void @llvm.assume(i1 [[MASKCOND]])
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast i8* [[TMP0]] to i32*
// CHECK-NEXT:    ret i32* [[TMP1]]
//
// PURECAP-LABEL: @assume_aligned_ptr(
// PURECAP-NEXT:  entry:
// PURECAP-NEXT:    [[PTR_ADDR:%.*]] = alloca i8 addrspace(200)*, align {{16|32}}, addrspace(200)
// PURECAP-NEXT:    store i8 addrspace(200)* [[PTR:%.*]], i8 addrspace(200)* addrspace(200)* [[PTR_ADDR]], align {{16|32}}
// PURECAP-NEXT:    [[TMP0:%.*]] = load i8 addrspace(200)*, i8 addrspace(200)* addrspace(200)* [[PTR_ADDR]], align {{16|32}}
// PURECAP-NEXT:    [[PTRINT:%.*]] = ptrtoint i8 addrspace(200)* [[TMP0]] to i64
// PURECAP-NEXT:    [[MASKEDPTR:%.*]] = and i64 [[PTRINT]], 3
// PURECAP-NEXT:    [[MASKCOND:%.*]] = icmp eq i64 [[MASKEDPTR]], 0
// PURECAP-NEXT:    call void @llvm.assume(i1 [[MASKCOND]])
// PURECAP-NEXT:    [[TMP1:%.*]] = bitcast i8 addrspace(200)* [[TMP0]] to i32 addrspace(200)*
// PURECAP-NEXT:    ret i32 addrspace(200)* [[TMP1]]
//
int* assume_aligned_ptr(void* ptr) {
  return __builtin_assume_aligned(ptr, 4);
}

int* __capability assume_aligned_cap(void* __capability ptr) {
  return __builtin_assume_aligned_cap(ptr, 4);
}