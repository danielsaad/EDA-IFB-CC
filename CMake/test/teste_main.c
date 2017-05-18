#include <stdlib.h>
#include "check.h"
int main(void){
    int number_failed;
    SRunner *sr;
    sr = srunner_create(make_triangulo_suite());
    srunner_add_suite(sr,make_quadrado_suite());
    /* Importante para debug */
    srunner_set_fork_status(sr, CK_NOFORK);
    /* Importante para mostrar informações na tela */
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
