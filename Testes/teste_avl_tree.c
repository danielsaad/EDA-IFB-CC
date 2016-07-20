#include "check.h"
#include "avl_tree.h"
#include "alloc.h"


static int* v;
static const int N = 10000;

static void setup(void){
    v = callocx(N,sizeof(int));
    int i;
    for(i=0;i<N;i++){
        v[i] = rand();
    }
}

static void teardown(void){
    free(v);
}


static void* int_constructor(void* data){
    void* ptr = mallocx(sizeof(int));
    memcpy(ptr,data,sizeof(int));
    return ptr;
}

static void int_destructor(void* data){
    free(data);
}

static int int_comparator(const void* a,const void* b){
    if(*(int*)a < *(int*) b){
        return -1;
    }
    else if(*(int*)a == *(int*) b){
        return 0;
    }
    return 1;
}

static int get_height(avl_node_t* v){
    if(v==NULL){
        return 0;
    }
    size_t hl,hr;
    hl = get_height(v->left);
    hr = get_height(v->right);
    return hl>hr?hl+1:hr+1;
}

static int is_balanced(avl_node_t* v){
    if(v!=NULL){
        size_t hl,hr;
        if(!is_balanced(v->left) || !is_balanced(v->right)){
            return 0;
        }
        hl = get_height(v->left);
        hr = get_height(v->right);
        if(abs(hl-hr)>1){
            return 0;
        }
    }
    return 1;
}


static int has_key_propertie(avl_tree_t* t,avl_node_t* v){
    if(v==NULL){
        return 1;
    }
    if(!has_key_propertie(t,v->left) || !has_key_propertie(t,v->right)){
        return 0;
    }
    if(v->left!=NULL && t->comparator(v->left->data,v->data)>0){
        return 0;
    }
    if(v->right!=NULL && t->comparator(v->right->data,v->data)<0){
        return 0;
    }
    return 1;
}




START_TEST(test_avl_tree_find){
    avl_tree_t* t;
    avl_tree_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        avl_tree_insert(t,&v[i]);
    }
    for(i=0;i<N;i++){
        ck_assert(avl_tree_find(t,&v[i]));
    }
    avl_tree_delete(&t);

}
END_TEST

START_TEST(test_avl_balance){
    avl_tree_t* t;
    avl_tree_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        avl_tree_insert(t,&v[i]);
    }
    ck_assert(is_balanced(t->root));
    avl_tree_delete(&t);
}
END_TEST

START_TEST(test_avl_key_propertie){
    avl_tree_t* t;
    avl_tree_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        avl_tree_insert(t,&v[i]);
    }
    ck_assert(has_key_propertie(t,t->root));
}
END_TEST
/*
START_TEST(test_bst_remove){
    bst_t *t;
    bst_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        bst_insert(t,&v[i]);
    }
    for(i=0;i<N;i++){
        ck_assert(bst_find(t,&v[i]));
        bst_remove(t,&v[i]);
    }
    bst_delete(&t);

}
END_TEST
*/


Suite* make_avl_tree_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("AVL Tree");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases, test_avl_tree_find);
    tcase_add_test(test_cases, test_avl_balance);
    tcase_add_test(test_cases,test_avl_key_propertie);
    suite_add_tcase(s, test_cases);
    return s;
}
