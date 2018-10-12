// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %cheri_purecap_cc1 -o - -O0 -emit-llvm %s | %cheri_FileCheck %s
// RUN: %cheri_cc1 -o - -O0 -emit-llvm %s | %cheri_FileCheck %s -check-prefix=HYBRID
// https://github.com/CTSRD-CHERI/clang/issues/178
struct a {
  void *__capability ptr;
};
// CHECK-LABEL: define void @c(
// CHECK:       entry:
// CHECK-NEXT:    %first = alloca %struct.a, align [[$CAP_SIZE]], addrspace(200)
// CHECK-NEXT:    %second = alloca %struct.a, align [[$CAP_SIZE]], addrspace(200)
// CHECK-NEXT:    %0 = bitcast %struct.a addrspace(200)* %second to i8 addrspace(200)*
// CHECK-NEXT:    %ptr = getelementptr inbounds %struct.a, %struct.a addrspace(200)* %first, i32 0, i32 0
// CHECK-NEXT:    store i8 addrspace(200)* %0, i8 addrspace(200)* addrspace(200)* %ptr, align [[$CAP_SIZE]]
// CHECK-NEXT:    ret void
//
// HYBRID-LABEL: define void @c(
// HYBRID:       entry:
// HYBRID-NEXT:    %first = alloca %struct.a, align [[$CAP_SIZE]]
// HYBRID-NEXT:    %second = alloca %struct.a, align [[$CAP_SIZE]]
// HYBRID-NEXT:    %0 = bitcast %struct.a* %second to i8*
// HYBRID-NEXT:    %1 = addrspacecast i8* %0 to i8 addrspace(200)*
// HYBRID-NEXT:    %ptr = getelementptr inbounds %struct.a, %struct.a* %first, i32 0, i32 0
// HYBRID-NEXT:    store i8 addrspace(200)* %1, i8 addrspace(200)** %ptr, align [[$CAP_SIZE]]
// HYBRID-NEXT:    ret void
void c(void) {
  struct a first;
  struct a second;
  first.ptr = (__cheri_tocap void *__capability) & second;
}

struct foo;

// CHECK-LABEL: define signext i32 @test(
// CHECK:       entry:
// CHECK-NEXT:    %fooptr.addr = alloca %struct.foo addrspace(200)*, align [[$CAP_SIZE]], addrspace(200)
// CHECK-NEXT:    %foocap.addr = alloca %struct.foo addrspace(200)*, align [[$CAP_SIZE]], addrspace(200)
// CHECK-NEXT:    %ptr = alloca i32 addrspace(200)*, align [[$CAP_SIZE]], addrspace(200)
// CHECK-NEXT:    %cap = alloca i32 addrspace(200)*, align [[$CAP_SIZE]], addrspace(200)
// CHECK-NEXT:    store %struct.foo addrspace(200)* %fooptr, %struct.foo addrspace(200)* addrspace(200)* %fooptr.addr, align [[$CAP_SIZE]]
// CHECK-NEXT:    store %struct.foo addrspace(200)* %foocap, %struct.foo addrspace(200)* addrspace(200)* %foocap.addr, align [[$CAP_SIZE]]
// CHECK-NEXT:    %0 = load %struct.foo addrspace(200)*, %struct.foo addrspace(200)* addrspace(200)* %foocap.addr, align [[$CAP_SIZE]]
// CHECK-NEXT:    %1 = bitcast %struct.foo addrspace(200)* %0 to i8 addrspace(200)*
// CHECK-NEXT:    %2 = bitcast i8 addrspace(200)* %1 to i32 addrspace(200)*
// CHECK-NEXT:    store i32 addrspace(200)* %2, i32 addrspace(200)* addrspace(200)* %ptr, align [[$CAP_SIZE]]
// CHECK-NEXT:    %3 = load %struct.foo addrspace(200)*, %struct.foo addrspace(200)* addrspace(200)* %fooptr.addr, align [[$CAP_SIZE]]
// CHECK-NEXT:    %4 = bitcast %struct.foo addrspace(200)* %3 to i8 addrspace(200)*
// CHECK-NEXT:    %5 = bitcast i8 addrspace(200)* %4 to i32 addrspace(200)*
// CHECK-NEXT:    store i32 addrspace(200)* %5, i32 addrspace(200)* addrspace(200)* %cap, align [[$CAP_SIZE]]
// CHECK-NEXT:    %6 = load i32 addrspace(200)*, i32 addrspace(200)* addrspace(200)* %ptr, align [[$CAP_SIZE]]
// CHECK-NEXT:    %7 = load i32, i32 addrspace(200)* %6, align 4
// CHECK-NEXT:    %8 = load i32 addrspace(200)*, i32 addrspace(200)* addrspace(200)* %cap, align [[$CAP_SIZE]]
// CHECK-NEXT:    %9 = load i32, i32 addrspace(200)* %8, align 4
// CHECK-NEXT:    %add = add nsw i32 %7, %9
// CHECK-NEXT:    ret i32 %add
//
// HYBRID-LABEL: define signext i32 @test(
// HYBRID:       entry:
// HYBRID-NEXT:    %fooptr.addr = alloca %struct.foo*, align 8
// HYBRID-NEXT:    %foocap.addr = alloca %struct.foo addrspace(200)*, align [[$CAP_SIZE]]
// HYBRID-NEXT:    %ptr = alloca i32*, align 8
// HYBRID-NEXT:    %cap = alloca i32 addrspace(200)*, align [[$CAP_SIZE]]
// HYBRID-NEXT:    store %struct.foo* %fooptr, %struct.foo** %fooptr.addr, align 8
// HYBRID-NEXT:    store %struct.foo addrspace(200)* %foocap, %struct.foo addrspace(200)** %foocap.addr, align [[$CAP_SIZE]]
// HYBRID-NEXT:    %0 = load %struct.foo addrspace(200)*, %struct.foo addrspace(200)** %foocap.addr, align [[$CAP_SIZE]]
// HYBRID-NEXT:    %1 = bitcast %struct.foo addrspace(200)* %0 to i8 addrspace(200)*
// HYBRID-NEXT:    %2 = addrspacecast i8 addrspace(200)* %1 to i8*
// HYBRID-NEXT:    %3 = bitcast i8* %2 to i32*
// HYBRID-NEXT:    store i32* %3, i32** %ptr, align 8
// HYBRID-NEXT:    %4 = load %struct.foo*, %struct.foo** %fooptr.addr, align 8
// HYBRID-NEXT:    %5 = bitcast %struct.foo* %4 to i8*
// HYBRID-NEXT:    %6 = addrspacecast i8* %5 to i8 addrspace(200)*
// HYBRID-NEXT:    %7 = bitcast i8 addrspace(200)* %6 to i32 addrspace(200)*
// HYBRID-NEXT:    store i32 addrspace(200)* %7, i32 addrspace(200)** %cap, align [[$CAP_SIZE]]
// HYBRID-NEXT:    %8 = load i32*, i32** %ptr, align 8
// HYBRID-NEXT:    %9 = load i32, i32* %8, align 4
// HYBRID-NEXT:    %10 = load i32 addrspace(200)*, i32 addrspace(200)** %cap, align [[$CAP_SIZE]]
// HYBRID-NEXT:    %11 = load i32, i32 addrspace(200)* %10, align 4
// HYBRID-NEXT:    %add = add nsw i32 %9, %11
// HYBRID-NEXT:    ret i32 %add
int test(struct foo* fooptr, struct foo* __capability foocap) {
  int* ptr = (__cheri_fromcap void*)foocap;
  int* __capability cap = (__cheri_tocap void* __capability)fooptr;
  return *ptr + *cap;
}