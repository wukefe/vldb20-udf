## Notes

Copy from

    vldb20-udf/bs/hir/gencode

Code versions

    opt-table/bs2-high.h   === opt-scalar/bs2-high.h
    opt-table/bs2-medium.h === opt-scalar/bs2-medium.h
    opt-table/bs2-low.h    === opt-scalar/bs2-low.h

## Commands

Run a base version `bs0`

    scale=1 thread=1 runs=1 ./run.sh opt-table 0

Run a derived version `bs1-low`

    ./run.sh opt-table 1-low

Available versions (scalar / table)

    0 : bs0

    1-high   : bs1-high
    1-medium : bs1-medium
    1-low    : bs1-low

    2-high   : bs2-high
    2-medium : bs2-medium
    2-low    : bs2-low

    3-high   : bs3-high
    3-medium : bs3-medium
    3-low    : bs3-low



## Benchmarks

bs1

    return all three fields from UDF

bs2

    ignore UDF, equivalent to "SELECT optiontype, sptprice FROM blackscholes WHERE ...;"

bs3

    optionprice used in the WHERE clause, but not the return field




