add_test([=[HelloTest.BasicAssertions]=]  /home/runner/work/physics-1/physics-1/_codeql_build_dir/hello_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/runner/work/physics-1/physics-1/_codeql_build_dir SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  hello_test_TESTS HelloTest.BasicAssertions)
