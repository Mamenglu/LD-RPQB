*******************************************************************
************ THE RPQBench BENCHMARK ***************
*******************************************************************


=================================
******* TABLE OF CONTENTS *******
=================================
=  1. RPQBench                  =
=  2. Dataset                   =
=================================


1. RPQBench 
---------------
RPQBench is a Performance Benchmark for the SPARQL query language, focusing on Recursive Path Queries (RPQs) which are crucial in many graph-based applications. The benchmark comprises both a data generator for generating arbitrarily large, synthetic graph datasets, and a set of SPARQL benchmark queries, which cover a variety of typical recursive query patterns and RDF access scenarios.

RPQBench is a research project from TianJin University and aims to provide a foundation for comparing RPQ optimization approaches in a standardized benchmark setting. Additionally, it serves to compare SPARQL engines, identify shortcomings in current implementations, and help optimize SPARQL engine performance.

2. Dataset
------------------
This dataset directory contains a variety of .n3 files generated for the purpose of benchmarking RPQ (Regular Path Queries) on different graph databases. These files simulate different sizes of datasets to provide a robust test environment for RPQ algorithms.

Each .n3 file represents a distinct dataset size, allowing for comprehensive performance testing across different database implementations. This enables users to evaluate the scalability and efficiency of RPQ engines under diverse conditions.
