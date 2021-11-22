valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --show-reachable=yes \
    --track-origins=yes \
    --error-limit=no \
    --gen-suppressions=all \
    --log-file=mpi_supp_scal.log \
    tests/unit_test_MPI_mpi

cat mpi_supp_scal.log | ../tools/parse_valgrind_suppressions.sh > basec.sup

valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --show-reachable=yes \
    --track-origins=yes \
    --error-limit=no \
    --gen-suppressions=all \
    --log-file=global_supp_scal.log \
    tests/unit_test_Global_global

cat global_supp_scal.log | ../tools/parse_valgrind_suppressions.sh >> basec.sup