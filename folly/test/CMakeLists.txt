#
# Copyright (C) 2015, Yeolar
#

set(FOLLY_BASE_TEST_LIB_SRCS
    DeterministicSchedule.cpp
)
add_library(folly_base_test STATIC ${FOLLY_BASE_TEST_LIB_SRCS})
target_link_libraries(folly_base_test folly_static)


set(FOLLY_BASE_TEST_SRCS
    ApplyTupleTest.cpp
    AsciiCaseInsensitiveTest.cpp
    AtomicStructTest.cpp
    BatonTest.cpp
    BenchmarkTest.cpp
    BitIteratorTest.cpp
    BitsTest.cpp
    CacheLocalityTest.cpp
    ConvTest.cpp
    CpuIdTest.cpp
    DemangleTest.cpp
    DeterministicScheduleTest.cpp
    DynamicConverterTest.cpp
    DynamicOtherTest.cpp
    DynamicTest.cpp
    EndianTest.cpp
    EvictingCacheMapTest.cpp
    ExceptionTest.cpp
    ExceptionWrapperTest.cpp
    FileTest.cpp
    FileTestLockHelper.cpp
    FileUtilTest.cpp
    ForeachTest.cpp
    FormatOtherTest.cpp
    FormatTest.cpp
    FutexTest.cpp
    GroupVarintTest.cpp
    HashTest.cpp
    HasMemberFnTraitsTest.cpp
    IndexedMemPoolTest.cpp
    IPAddressTest.cpp
    JsonOtherTest.cpp
    JsonTest.cpp
    LifoSemTests.cpp
    LoggingTest.cpp
    MacAddressTest.cpp
    MapUtilTest.cpp
    MemoryIdlerTest.cpp
    MemoryTest.cpp
    MergeTest.cpp
    MoveWrapperTest.cpp
    MPMCQueueTest.cpp
    OptionalTest.cpp
    PortabilityTest.cpp
    RandomTest.cpp
    RangeTest.cpp
    RWSpinLockTest.cpp
    ScopeGuardTest.cpp
    #    SingletonTest.cpp
    SmallLocksTest.cpp
    SocketAddressTest.cpp
    SpinLockTest.cpp
    SpookyHashV1Test.cpp
    SpookyHashV2Test.cpp
    StringTest.cpp
    SynchronizedTest.cpp
    TestUtilTest.cpp
    ThreadLocalTest.cpp
    TraitsTest.cpp
    UriTest.cpp
    VarintTest.cpp
)

foreach(test_src ${FOLLY_BASE_TEST_SRCS})
    get_filename_component(test_name ${test_src} NAME_WE)
    set(test folly_${test_name})
    add_executable(${test} ${test_src})
    target_link_libraries(${test}
        ${GTEST_BOTH_LIBRARIES} ${GMOCK_LIBRARIES}
        folly_static folly_base_test)
    if(NOT ${test_name} STREQUAL "FileTestLockHelper")
        add_test(${test} ${test} CONFIGURATIONS Debug)
    endif()
endforeach()

execute_process(
    COMMAND ln -fs "${PROJECT_SOURCE_DIR}/folly/test/json_test_data"
                   "${PROJECT_BINARY_DIR}/folly/test/json_test_data"
)


set(FOLLY_BASE_BENCHMARK_SRCS
    AsciiCaseInsensitiveBenchmark.cpp
    ExceptionWrapperBenchmark.cpp
    FormatBenchmark.cpp
    IPAddressBenchmark.cpp
    RangeFindBenchmark.cpp
    StringBenchmark.cpp
)

foreach(bench_src ${FOLLY_BASE_BENCHMARK_SRCS})
    get_filename_component(bench_name ${bench_src} NAME_WE)
    set(bench folly_${bench_name})
    add_executable(${bench} ${bench_src})
    target_link_libraries(${bench} ${GTEST_BOTH_LIBRARIES} folly_static)
endforeach()

