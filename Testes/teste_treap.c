#include "check.h"
#include "treap.h"
#include "alloc.h"


static int* v;
static int* unique_keys;
static const int N = 10000;

static void setup(void){
    v = callocx(N,sizeof(int));
    unique_keys = callocx(N,sizeof(int));
    int i;
    unique_keys[0] = 0;
    for(i=0;i<N;i++){
        v[i] = rand();
    }
    for(i=0;i<N;i++){
        int unique;
        do{
            unique_keys[i] = rand();
            int j;
            unique = 1;
            for(j=0;j<i;j++){
                if(unique_keys[j]==unique_keys[i]){
                    unique = 0;
                }
            }
        }while(!unique);
    }
}

static void teardown(void){
    free(v);
    free(unique_keys);
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



static int has_key_property(treap_t* t,treap_node_t* v){
    if(v==NULL){
        return 1;
    }
    if(!has_key_property(t,v->left) || !has_key_property(t,v->right)){
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


static int has_heap_property(treap_t* t,treap_node_t* v){
    if(v==NULL){
        return 1;
    }
    else if(v->left!=NULL && v->left->priority > v->priority){
        return 0;
    }
    else if(v->right!=NULL && v->right->priority > v->priority){
        return 0;
    }
    if(!has_heap_property(t,v->left) || !has_heap_property(t,v->right)){
        return 0;
    }
    return 1;
}


START_TEST(test_treap_find){
    treap_t* t;
    treap_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        treap_insert(t,&v[i]);
    }
    for(i=0;i<N;i++){
        ck_assert(treap_find(t,&v[i]));
    }
    treap_delete(&t);

}
END_TEST


START_TEST(test_treap_key_property){
    treap_t* t;
    treap_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        treap_insert(t,&v[i]);
    }
    ck_assert(has_key_property(t,t->root));
	treap_delete(&t);
}
END_TEST


START_TEST(test_treap_key_property_unique_keys){
    treap_t* t;
    treap_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        treap_insert(t,&unique_keys[i]);
    }
    ck_assert(has_key_property(t,t->root));
	treap_delete(&t);
}
END_TEST

START_TEST(test_treap_remove){
    treap_t *t;
    treap_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        treap_insert(t,&v[i]);
    }
    ck_assert(has_heap_property(t,t->root));
    ck_assert(has_key_property(t,t->root));
    for(i=0;i<N;i++){
        ck_assert(treap_find(t,&v[i]));
        treap_remove(t,&v[i]);
        ck_assert(has_heap_property(t,t->root));
        ck_assert(has_key_property(t,t->root));
    }
    ck_assert(t->root==NULL);
    treap_delete(&t);

}
END_TEST


START_TEST(test_treap_remove_unique_keys){
    treap_t *t;
    treap_initialize(&t,int_constructor,int_destructor,int_comparator);
    int i;
    for(i=0;i<N;i++){
        treap_insert(t,&unique_keys[i]);
    }
    ck_assert(has_heap_property(t,t->root));
    ck_assert(has_key_property(t,t->root));
    for(i=0;i<N;i++){
        ck_assert(treap_find(t,&unique_keys[i]));
        treap_remove(t,&unique_keys[i]);
        ck_assert(!treap_find(t,&unique_keys[i]));
        ck_assert(has_heap_property(t,t->root));
        ck_assert(has_key_property(t,t->root));
    }
    ck_assert(t->root==NULL);
    treap_delete(&t);

}
END_TEST


Suite* make_treap_suite(void){
    Suite *s;
    TCase *test_cases;
    s = suite_create("Treap");
    test_cases = tcase_create("Core");
    tcase_add_checked_fixture(test_cases, setup, teardown);
    tcase_add_test(test_cases, test_treap_find);
    tcase_add_test(test_cases,test_treap_key_property);
    tcase_add_test(test_cases,test_treap_key_property_unique_keys);
    tcase_add_test(test_cases,test_treap_remove);
    tcase_add_test(test_cases,test_treap_remove_unique_keys);
    suite_add_tcase(s, test_cases);
    return s;
}
