valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --show-reachable=yes \
    --track-origins=yes \
    --error-limit=no \
    --gen-suppressions=all \
    --log-file=mpi_sup_scal.log \
    tests/unit_test_MPI_mpi_sup

cat mpi_sup_scal.log | ../tools/parse_valgrind_suppressions.sh > mpi_sup.sup_scal